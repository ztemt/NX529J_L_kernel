/*
 * Simple synchronous userspace interface to SPI devices
 *
 * Copyright (C) 2006 SWAPP
 *	Andrea Paterniani <a.paterniani@swapp-eng.it>
 * Copyright (C) 2007 David Brownell (simplification, cleanup)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*------------------------------ header file --------------------------------*/
#include "et310-spi.h"

/*------------------------------- variables ---------------------------------*/
// spi minor related
static DECLARE_BITMAP(minors, N_SPI_MINORS);

// irq related
static unsigned char irq_is_disable = 0;
static unsigned char irq_is_wake = 0;

// class that spi device belong to
static struct class *fp_class;

// global variables
struct fp_data *fp_global = NULL;
u8 fp_bkg_intensity[FPS_IMG_WIDTH * FPS_IMG_HEIGHT];

#ifdef CONFIG_ZTEMT_N940_FP_COMPATIBLE
extern void ztemt_get_hw_pcb_version(char* result);

static char ztemt_config_version[10]="*,*";
static char ztemt_config_version_A[10]="0,0";//config version A

static int  ztemt_hw_version_get(char *param)
{
    memcpy(ztemt_config_version, param, strlen(param));
    return 0;
}
early_param("config_setup", ztemt_hw_version_get);
#endif

/*------------------------- function declaration ----------------------------*/
void fp_interrupt_enable(struct fp_data *fp);
void fp_interrupt_disable(struct fp_data *fp);
void fp_irq_op(int irq, int enable);
void fp_irq_wake_op(int irq, int enable);
static void fp_setup_fb_notifier(struct fp_data *fp);
static void fp_reset(struct fp_data *fp);

/*------------------------ function implementation --------------------------*/
// used for tz spi  added by nubia
static int spi_set_pinctrl(struct fp_data *fp, bool active)
{
    int ret = 0;

    FP_LOG_INFO("start\n");

    if (active) { // Change to active settings
        ret = pinctrl_select_state(fp->fp_pctrl.pinctrl, fp->fp_pctrl.spi_default);
    } else {
        ret = pinctrl_select_state(fp->fp_pctrl.pinctrl, fp->fp_pctrl.spi_sleep);
    }
    FP_LOG_INFO("setting(%d) = %d\n", active, ret);

    return ret;
}

static int spi_set_clks(struct fp_data *fp, bool enable)
{
    int ret = 0;

    FP_LOG_INFO("start\n");

    if (enable) {
		// Enable the spi clocks
        ret = clk_set_rate(fp->core_clk, fp->spi->max_speed_hz);
        if (ret)
            FP_LOG_ERROR("failed to spi_set_clks(%d) = %d\n",
				fp->spi->max_speed_hz, ret);

        ret = clk_prepare_enable(fp->core_clk);
        if (ret)
            FP_LOG_ERROR("failed to enable core clk = %d\n", ret);

        ret = clk_prepare_enable(fp->iface_clk);
        if (ret)
            FP_LOG_ERROR("failed to enable iface clk = %d\n", ret);
    } else {
        // Disable the clocks
        clk_disable_unprepare(fp->iface_clk);
        clk_disable_unprepare(fp->core_clk);
    }

    FP_LOG_INFO("end\n");
    return ret;
}

static int spi_change_pipe_owner(struct fp_data *fp, bool to_tz)
{
    // CMD ID collected from tzbsp_blsp.c to change Ownership
    const u32 TZ_BLSP_MODIFY_OWNERSHIP_ID = 3;
    const u32 TZBSP_APSS_ID = 1;
    const u32 TZBSP_TZ_ID = 3 ;
    struct scm_desc desc; //scm call descriptor
    int ret = 0;

    FP_LOG_INFO("start\n");

    // CMD ID to change BAM PIPE Owner
    desc.arginfo = SCM_ARGS(2); //# of arguments
    desc.args[0] = fp->qup_id; //BLSPID (1-12)
    desc.args[1] = (to_tz) ? TZBSP_TZ_ID : TZBSP_APSS_ID; //Owner if TZ or Apps
    ret = scm_call2(SCM_SIP_FNID(SCM_SVC_TZ, TZ_BLSP_MODIFY_OWNERSHIP_ID), &desc);

    FP_LOG_INFO("%s\n", (ret || desc.ret[0]) ? "failed" : "success");
    return (ret || desc.ret[0]) ? -1 : 0;
}

static int spi_set_fabric(struct fp_data *fp, bool active)
{
    int ret = 0;
    struct spi_master *master = fp->spi->master;

    FP_LOG_INFO("start\n");

    if (active)
        ret = master->prepare_transfer_hardware(master);
    else
        ret = master->unprepare_transfer_hardware(master);

    if (ret)
        FP_LOG_ERROR("failed ret = %d\n", ret);
    else
        FP_LOG_INFO("success\n");

    return ret;
}

static int spi_pinctrl_init(struct fp_data *fp, struct device *dev)
{
    FP_LOG_INFO("start\n");

    fp->fp_pctrl.pinctrl= devm_pinctrl_get(dev);
	if (IS_ERR_OR_NULL(fp->fp_pctrl.pinctrl)) {
        FP_LOG_ERROR("failed to get pinctrl handle\n");
        return -EINVAL;
    }

    fp->fp_pctrl.spi_default = pinctrl_lookup_state(fp->fp_pctrl.pinctrl, "default");
    if (IS_ERR_OR_NULL(fp->fp_pctrl.spi_default)) {
        FP_LOG_ERROR("failed to get spi_default pinctrl handle\n");
        return -EINVAL;
    }

    // Get sleep settings
    fp->fp_pctrl.spi_sleep = pinctrl_lookup_state(fp->fp_pctrl.pinctrl, "sleep");
    if (IS_ERR_OR_NULL(fp->fp_pctrl.spi_sleep)) {
        FP_LOG_ERROR("failed to get spi_sleep pinctrl handle\n");
        return -EINVAL;
    }

    FP_LOG_INFO("success\n");

	return 0;
}

static int spi_clock_init(struct fp_data *fp)
{
    int rc = 0;
	struct device_node *np = fp->spi->dev.of_node;

    FP_LOG_INFO("start\n");

    fp->iface_clk = clk_get(&(fp->spi->dev), "iface_clk");
    if (IS_ERR(fp->iface_clk)) {
        FP_LOG_ERROR("failed to get iface_clk %ld\n", PTR_ERR(fp->iface_clk));
        return PTR_ERR(fp->iface_clk);
    }

    // Get core_clk info
    fp->core_clk = clk_get(&(fp->spi->dev), "core_clk");
    if (IS_ERR(fp->core_clk)) {
        FP_LOG_ERROR("failed to get core_clk %p\n", fp->core_clk);
        return PTR_ERR(fp->core_clk);
    }

    // Get the QUP ID (#1-12)
    rc = of_property_read_u32(np, "qcom,qup-id", &fp->qup_id);
    if (rc) {
        FP_LOG_ERROR("failed to get qup_id\n");
        return rc;
    }

    FP_LOG_INFO("end\n");

	return 0;
}

static void spi_enable(struct fp_data *fp, bool enable)
{
    FP_LOG_INFO("tz spi %s\n", enable? "enable" : "disable");

#ifdef  CONFIG_ZTEMT_SENSORS_FP_ET310_CONTROL_BY_AP
    if (true == enable) {
        spi_set_pinctrl(fp, true);
        spi_set_fabric(fp, true);
        spi_set_clks(fp, true);
        //spi_change_pipe_owner(fp, true);
    } else {
        //spi_change_pipe_owner(fp, false);
        spi_set_clks(fp, false);
        spi_set_fabric(fp, false);
        spi_set_pinctrl(fp, false);
    }
#endif
    FP_LOG_INFO("end\n");
}

static void spi_init(struct fp_data *fp)
{
    spi_pinctrl_init(fp, &(fp->spi->dev));
    spi_clock_init(fp);
    spi_bus_lock(fp->spi->master);
}
// nubia add End

// read
int fp_read_register(struct fp_data *fp, u8 addr, u8 *buf)
{	
	struct spi_device *spi;
	struct spi_message m;

	int status = 0;

	// set address
	u8 write_addr[] = { FP_WRITE_ADDRESS, addr };
	u8 read_value[] = { FP_READ_DATA, 0x00 };
	u8 result[] = { 0xFF, 0xFF };

	struct spi_transfer t1 = {
		.speed_hz = FPC_BTP_SPI_CLOCK_SPEED,
		.tx_buf = write_addr,
		.len = 2,
	};
	struct spi_transfer t2 = {
		.speed_hz = FPC_BTP_SPI_CLOCK_SPEED,
		.tx_buf = read_value,
		.rx_buf = result,
		.len = 2,
	};

	spi = fp->spi;
	spi_message_init(&m);
	spi_message_add_tail(&t1, &m);
	status = spi_sync(spi, &m);
	if (status < 0) {
		FP_LOG_ERROR("failed to read data = %d\n", status);
		goto exit;
	}

	spi_message_init(&m);
	spi_message_add_tail(&t2, &m);
	status = spi_sync(spi, &m);
	if (status == 0) {
		*buf = result[1];
		FP_LOG_DEBUG("addr = 0x%x, result = 0x%x, 0x%x\n", addr, result[0], result[1]);
	} else {
		FP_LOG_ERROR("failed to read data = %d\n", status);
	}

exit:
	return status;
}

int fp_read_register_external(u8 addr, u8 *buf)
{
    return fp_read_register(fp_global, addr, buf);
}

int fp_mass_read(struct fp_data *fp, u8 addr, u8 *buf, int read_len)
{
	struct spi_transfer msg_xfer[EGIS_MASS_READ_SEGMENT_COUNT];	
	struct spi_device *spi;
	struct spi_message m;

	int status = 0;
	u8 write_addr[] = { FP_WRITE_ADDRESS, addr };
	u8 read_data[] = {FP_READ_DATA, 0x0, 0x0};

	int const msg_count = read_len / EGIS_MASS_READ_TRANSMITION_SIZE;
	int const msg_remainder = read_len % EGIS_MASS_READ_TRANSMITION_SIZE;
	int msg_index = 0;

	struct spi_transfer t1 = {
		.tx_buf = write_addr,
		.len = 2,
	};	
	struct spi_transfer t2 = {
		.tx_buf = read_data,
		.len = 3,
	};

	spi = fp->spi;
	spi_message_init(&m);
	spi_message_add_tail(&t1, &m);
	status = spi_sync(spi, &m);
	if (status < 0) {
		FP_LOG_ERROR("failed to read data = %d\n", status);
		goto out;
	}

	spi_message_init(&m);
	spi_message_add_tail(&t2, &m);

	// seperate msgs into transmition size
	memset(msg_xfer, 0x00, sizeof(struct spi_transfer) * EGIS_MASS_READ_SEGMENT_COUNT);
	for (msg_index = 0; msg_index < msg_count; msg_index++) {
		msg_xfer[msg_index].tx_buf = buf + msg_index * EGIS_MASS_READ_TRANSMITION_SIZE;
		msg_xfer[msg_index].rx_buf = buf + msg_index * EGIS_MASS_READ_TRANSMITION_SIZE;
		msg_xfer[msg_index].len = EGIS_MASS_READ_TRANSMITION_SIZE;
		spi_message_add_tail(&msg_xfer[msg_index], &m);
	}
	if (msg_remainder) {
		msg_xfer[msg_index].tx_buf = buf + msg_index * EGIS_MASS_READ_TRANSMITION_SIZE;
		msg_xfer[msg_index].rx_buf = buf + msg_index * EGIS_MASS_READ_TRANSMITION_SIZE;
		msg_xfer[msg_index].len = msg_remainder;
		spi_message_add_tail(&msg_xfer[msg_index], &m);
	}

	status = spi_sync(spi, &m);
	if (status < 0)
		FP_LOG_ERROR("failed to read data = %d\n", status);

out:
	return status;
}

int fp_mass_read_external(u8 addr, u8 *buf, int read_len)
{
	return fp_mass_read(fp_global, addr, buf, read_len);
}

int fp_write_register(struct fp_data *fp, u8 addr, u8 data)
{	
	struct spi_device *spi;
	struct spi_message m;

	int status = 0;

	// set address
	u8 write_addr[] = { FP_WRITE_ADDRESS, addr };
	u8 write_value[] = { FP_WRITE_DATA, data };

	struct spi_transfer t1 = {
		.speed_hz = FPC_BTP_SPI_CLOCK_SPEED,
		.tx_buf = write_addr,
		.len = 2,
	};
	struct spi_transfer t2 = {
		.speed_hz = FPC_BTP_SPI_CLOCK_SPEED,
		.tx_buf = write_value,
		.len = 2,
	};

	spi = fp->spi;
	spi_message_init(&m);
	spi_message_add_tail(&t1, &m);
	status = spi_sync(spi, &m);
	if (status < 0) {
		FP_LOG_ERROR("failed to write data = %d\n", status);
		goto out;
	}

	spi_message_init(&m);
	spi_message_add_tail(&t2, &m);
	status = spi_sync(spi, &m);
	if (status < 0)
		FP_LOG_ERROR("failed to write data = %d\n", status);

out:
	return status;
}

int fp_write_register_external(u8 addr, u8 data)
{
    return fp_write_register(fp_global, addr, data);
}

int fp_get_one_image(struct fp_data *fp, u8 *buf, u8 *image_buf)
{
	u8 read_val = 0;	
	u32 frame_not_ready_count = 0, read_count = 0;
	int status = 0;

	// total pixel , width * hight
	read_count = buf[0] * buf[1];

	while (1) {
		status = fp_read_register(fp, FSTATUS_FP_ADDR, &read_val);
		if (status < 0)
			goto end;

		if (read_val & FRAME_READY_MASK)
			break;

		if (frame_not_ready_count >= 250) {
			FP_LOG_ERROR("frame_not_ready_count = %d\n", frame_not_ready_count);
			break;
		}
		frame_not_ready_count++;
	}

	status = fp_mass_read(fp, FDATA_FP_ADDR, image_buf, read_count);
	if (status < 0)
		FP_LOG_ERROR("failed to mass read = %d\n", status);

end:
	return status;
}

// EEPROM
int fp_eeprom_wren(struct fp_data *fp)
{	
	struct spi_device *spi;
	struct spi_message m;

	int status = 0;
	u8 write_data[] = { FP_EEPROM_WREN_OP };

	struct spi_transfer t = {
		.speed_hz = FPC_BTP_SPI_CLOCK_SPEED,
		.tx_buf = write_data,
		.len = 1,
	};

	spi = fp->spi;
	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	status = spi_sync(spi, &m);
	if (status < 0)
		FP_LOG_INFO("failed to fp_eeprom_wren = %d\n", status);

	return status;
}

int fp_eeprom_wrdi(struct fp_data *fp)
{	
	struct spi_device *spi;
	struct spi_message m;

	int status = 0;
	u8 write_data[] = { FP_EEPROM_WRDI_OP };

	struct spi_transfer t = {
		.speed_hz = FPC_BTP_SPI_CLOCK_SPEED,
		.tx_buf = write_data,
		.len = 1,
	};

	spi = fp->spi;
	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	status = spi_sync(spi, &m);
	if (status < 0)
		FP_LOG_ERROR("failed to fp_eeprom_wrdi = %d\n", status);

	return status;
}

int fp_eeprom_rdsr(struct fp_data *fp, u8 *buf)
{	
	struct spi_device *spi;
	struct spi_message m;

	int status = 0;
	u8 read_value[] = { FP_EEPROM_RDSR_OP, 0x00 };
	u8 result[] = { 0xFF, 0xFF };

	struct spi_transfer t = {
		.speed_hz = FPC_BTP_SPI_CLOCK_SPEED,
		.tx_buf = read_value,
		.rx_buf = result,
		.len = 2,
	};

	spi = fp->spi;
	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	status = spi_sync(spi, &m);
	if (status < 0) {
		FP_LOG_ERROR("failed to fp_eeprom_rdsr = %d\n", status);
		goto out;
	}

	*buf = result[1];
	FP_LOG_DEBUG("op = 0x%x, buf = 0x%x\n", FP_EEPROM_RDSR_OP, *buf);

out:
	return status;
}

int fp_eeprom_wrsr(struct fp_data *fp, u8 *buf)
{	
	struct spi_device *spi;
	struct spi_message m;

	int status = 0;
	u8 write_data[] = { FP_EEPROM_WRSR_OP, buf[0] };

	struct spi_transfer t = {
		.speed_hz = FPC_BTP_SPI_CLOCK_SPEED,
		.tx_buf = write_data,
		.len = 2,
	};

	spi = fp->spi;
	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	status = spi_sync(spi, &m);
	if (status < 0)
		FP_LOG_ERROR("failed to fp_eeprom_wrsr = %d\n", status);

	return status;
}

int fp_eeprom_read(struct fp_data *fp, u8 *addr, u8 *buf, int read_len)
{
	int status = 0;
	u8 write_data[] = { FP_EEPROM_READ_OP, addr[0] };

	struct spi_device *spi;
	struct spi_message m;

	struct spi_transfer t = {
		.speed_hz = FPC_BTP_SPI_CLOCK_SPEED,
		.tx_buf = write_data,
		.rx_buf = buf,
		.len = read_len + 2,
	};

	if (read_len < 0) {
		FP_LOG_ERROR("invalid read_len(%d)\n", read_len);
		goto out;
	}

	spi = fp->spi;
	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	status = spi_sync(spi, &m);
	if (status < 0)
		FP_LOG_ERROR("failed to fp_eeprom_read = %d\n", status);

out:
	return status;
}

int fp_eeprom_write(struct fp_data *fp, u8 *buf, int write_len)
{
	int status = 0;
	u8 *write_value = NULL;

	struct spi_device *spi;
	struct spi_message m;

	struct spi_transfer t = {
		.speed_hz = FPC_BTP_SPI_CLOCK_SPEED,
		.tx_buf = NULL,
		.len = write_len + 2,
	};

	if (write_len < 0) {
		FP_LOG_ERROR("invalid write_len = %d\n", write_len);
		goto out;
	}

	write_value = kzalloc(write_len + 2, GFP_KERNEL);
	if (write_value == NULL) {
		FP_LOG_ERROR("failed to kzalloc\n");
		goto out;
	}

	write_value[0] = FP_EEPROM_WRITE_OP;
	memcpy(write_value + 1, buf, write_len + 1);
	t.tx_buf = write_value;

	spi = fp->spi;
	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	status = spi_sync(spi, &m);
	if (status < 0)
		FP_LOG_ERROR("failed to fp_eeprom_write = %d\n", status);

out:
	if (write_value)
		kfree(write_value);
	return status;
}

int fp_set_cali_data(struct fp_data *fp, u8 *buf, uint32_t size)
{
	int status = 0;
	uint32_t bkg_size = 0;

	FP_LOG_INFO("size = %d\n", size);

	if (size < 10) {
		status = -EFAULT;
		FP_LOG_ERROR("invalid size = %d\n", size);
		goto out;
	}

	fp->cali_info.dc = buf[0];
	fp->cali_info.gain = buf[1];
	fp->cali_info.bkg_width = buf[2];
	fp->cali_info.bkg_height = buf[3];
	fp->cali_info.min_bkg_intensity = buf[4];
	fp->cali_info.fingerOnThreshold = buf[5];
	fp->cali_info.fingerOnThresholdLoose = buf[6];
	fp->cali_info.fingerOnStableThreshold = buf[7];
	fp->cali_info.interruptThrehold = buf[8];
	fp->cali_info.dc_detect = buf[9];
	fp->cali_info.gain_detect = buf[10];

	FP_LOG_INFO("cal width = 0x%x\n", fp->cali_info.bkg_width);
	FP_LOG_INFO("cal height = 0x%x\n", fp->cali_info.bkg_height);
	FP_LOG_INFO("cal dc = 0x%x\n", fp->cali_info.dc);
	FP_LOG_INFO("cal gain = 0x%x\n", fp->cali_info.gain);
	FP_LOG_INFO("cal min_bkg_intensity = 0x%x\n", fp->cali_info.min_bkg_intensity);
	FP_LOG_INFO("cal fingerOnThreshold = 0x%x\n", fp->cali_info.fingerOnThreshold);
	FP_LOG_INFO("cal fingerOnThresholdLoose = 0x%x\n", fp->cali_info.fingerOnThresholdLoose);
	FP_LOG_INFO("cal fingerOnStableThreshold = 0x%x\n", fp->cali_info.fingerOnStableThreshold);
	FP_LOG_INFO("cal interruptThrehold = 0x%x\n", fp->cali_info.interruptThrehold);
	FP_LOG_INFO("cal dc_detect = 0x%x\n", fp->cali_info.dc_detect);
	FP_LOG_INFO("cal gain_detect = 0x%x\n", fp->cali_info.gain_detect);

	bkg_size = buf[2] * buf[3];
	if (bkg_size > FPS_IMG_WIDTH * FPS_IMG_HEIGHT) {
		FP_LOG_ERROR("bkg_size(%d) is too big\n", bkg_size);
		status = -EFAULT;
		goto out;
	}

	memcpy(fp_bkg_intensity, buf + CALIBRATION_INFO_NUM, bkg_size);

out:
	return status;
}


// interrupt
void fp_start_scrolling(struct fp_data *fp)
{
	queue_work(fp->scroll_wq, &fp->scroll_work);
}

void fp_enable_scrolling(struct fp_data *fp, unsigned char enable)
{
	if (enable) {
		if ((fp->scroll_enable == true) || (fp->getkey_enable == true)) {
			FP_LOG_INFO("scroll already enabled\n");
			return;
		}

		mutex_lock(&fp_global->scroll_lock);
		fp_set_detect_mode();
		fp_interrupt_enable(fp);
		mutex_unlock(&fp_global->scroll_lock);
	} else {
		if (fp->scroll_enable == false) {
			FP_LOG_INFO("scroll already disabled\n");
			return;
		}
		mutex_lock(&fp_global->scroll_lock);
		fp_reset(fp);
		fp_interrupt_disable(fp);
		mutex_unlock(&fp_global->scroll_lock);
	}

	fp->scroll_enable = enable;
	fp->getkey_enable = enable;
}

void fp_start_getkey(struct fp_data *fp)
{
	FP_LOG_INFO("start\n");

	queue_work(fp->getkey_wq, &fp->getkey_work);
}

void fp_enable_getkey(struct fp_data *fp, int enable)
{
	if (enable) {
		if (fp->getkey_enable == true) {
			FP_LOG_ERROR("getkey already enabled\n");
			return;
		}

		fp_set_detect_mode();
		fp_set_getkey_detect_region();
		fp_interrupt_enable(fp);
		fp_start_getkey(fp);
	} else {
		if (fp->getkey_enable == false) {
			FP_LOG_INFO("getkey already disabled\n");
			return;
		}

		fp_interrupt_disable(fp);
	}
	fp->getkey_enable = enable;
}

/*
 *	FUNCTION NAME.
 *		interrupt_timer_routine
 *
 *	FUNCTIONAL DESCRIPTION.
 *		basic interrupt timer inital routine
 *
 *	ENTRY PARAMETERS.
 *		gpio - gpio address
 *
 *	EXIT PARAMETERS.
 *		Function Return
 */
void fp_interrupt_timer_routine(unsigned long _data)
{
	struct interrupt_desc *bdata = (struct interrupt_desc *)_data;
	struct fp_data *fp = container_of(bdata, struct fp_data, int_desc);

//	FP_LOG_DEBUG("interrupt count = %d\n", bdata->int_count);
//	FP_LOG_DEBUG("interrupt_state = %d\n", bdata->interrupt_state);
//      printk(KERN_ERR "ztemt 111 fp_interrupt_timer_routine\n");
	//disable_irq(fp_global->irq);
	fp_irq_op(fp->int_desc.irq, FP_INT_DISABLE);

	if (bdata->int_count >= bdata->detect_threshold) {
			bdata->finger_on = true;
			FP_LOG_DEBUG("triggered\n");

		if (fp->tz_enable == true) {
			if (bdata->interrupt_state & INTERRUPT_STATE_SEND_KEY) {
				input_report_key(fp->key_input_dev, fp->int_desc.interrupt_key_code, 1);
				input_sync(fp->key_input_dev);
                                input_report_key(fp->key_input_dev, fp->int_desc.interrupt_key_code, 0);
				input_sync(fp->key_input_dev);
				wake_lock_timeout(&fp->fp_wakelock_timeout.lock, msecs_to_jiffies(2000));
			}
			bdata->int_count = 0;
			wake_up_interruptible(&interrupt_waitq);
            fp_irq_op(fp->int_desc.irq, FP_INT_ENABLE);
		} else {
			if ((bdata->interrupt_state & INTERRUPT_STATE_SCROLL) ||
				(bdata->interrupt_state & INTERRUPT_STATE_SEND_KEY)) {
				FP_LOG_INFO("triggered start scroll\n");
				fp_start_scrolling(fp);
				bdata->int_count = 0;
				wake_up_interruptible(&interrupt_waitq);
			} else if (bdata->interrupt_state & INTERRUPT_STATE_GETKEY) {
				FP_LOG_INFO("triggered start getkey\n");
				fp_start_getkey(fp);
				bdata->int_count = 0;
				wake_up_interruptible(&interrupt_waitq);
			} else {
				bdata->int_count = 0;
				wake_up_interruptible(&interrupt_waitq);
				fp_irq_op(fp->int_desc.irq, FP_INT_ENABLE);
			}
		}
	} else {
		FP_LOG_DEBUG("not triggered\n");

		bdata->int_count = 0;
		wake_up_interruptible(&interrupt_waitq);
		fp_irq_op(fp->int_desc.irq, FP_INT_ENABLE);
	}
}

/*
 *	FUNCTION NAME.
 *		fp_interrupt
 *
 *	FUNCTIONAL DESCRIPTION.
 *		finger print interrupt callback routine
 *
 *	ENTRY PARAMETERS.
 *		irq
 *		dev_id
 *
 *	EXIT PARAMETERS.
 *		Function Return
 */
static irqreturn_t fp_interrupt(int irq, void *dev_id)
{
	struct interrupt_desc *bdata = (struct interrupt_desc *)dev_id;
	if (!bdata->int_count)
		mod_timer(&bdata->timer,
			jiffies + msecs_to_jiffies(bdata->detect_period));

	bdata->int_count++;
	return IRQ_HANDLED;
}

static void fp_scroll_work_func(struct work_struct *work)
{
	fp_scrolling();
}

static void fp_getkey_work_func(struct work_struct *work)
{
	fp_getkey();
}

unsigned int fps_interrupt_poll(struct file *file, struct poll_table_struct *wait)
{
	unsigned int mask = 0;

	FP_LOG_DEBUG("start\n");

	fp_global->int_desc.int_count = 0;

	poll_wait(file, &interrupt_waitq, wait);

	if (fp_global->int_desc.finger_on) {
		mask |= POLLIN | POLLRDNORM;
		fp_global->int_desc.finger_on = 0;
	}

	return mask;
}

void fps_interrupt_abort(void)
{
	fp_global->int_desc.finger_on = 0;
	wake_up_interruptible(&interrupt_waitq);
}

// irq related operation
void fp_irq_op(int irq, int enable)
{
	if (enable && irq_is_disable) {
		irq_is_disable = 0;
		enable_irq(irq);
	} else if (!enable && !irq_is_disable) {
		irq_is_disable = 1;
		disable_irq_nosync(irq);
	}
}

void fp_irq_wake_op(int irq, int enable)
{
	if (enable && !irq_is_wake) {
		irq_is_wake = 1;
		enable_irq_wake(irq);
	} else if (!enable && irq_is_wake) {
		irq_is_wake = 0;
		disable_irq_wake(irq);
	}
}

#if 0
void fp_irq_enable(int irq)
{
	if (irq_is_disable) {
		irq_is_disable = 0;
		enable_irq(irq);
	}
}

void fp_irq_disable(int irq)
{
	if (!irq_is_disable) {
		irq_is_disable = 1;
		disable_irq_nosync(irq);
	}
}

void fp_irq_wake_enable(int irq)
{
	if (!irq_is_wake) {
		enable_irq_wake(irq);
		irq_is_wake = 1;
	}
}

void fp_irq_wake_disable(int irq)
{
	if (irq_is_wake) {
		irq_is_wake = 0;
		disable_irq_wake(irq);
	}
}
#endif

int fp_interrupt_init(struct interrupt_desc *data)
{
	int ret = 0;

	data->irq = gpio_to_irq(data->irq_gpio);
	data->interrupt_state = INTERRUPT_STATE_DETECT;
	data->interrupt_key_code = KEY_F11;
	data->int_count = 0;
	data->finger_on = 0;
	data->detect_period = FP_INT_DETECTION_PERIOD;
	data->detect_threshold = FP_DETECTION_THRESHOLD;
	//ret = request_irq(data->irq, fp_interrupt, IRQ_TYPE_EDGE_RISING,
	//		"et310", (void *)data);
	ret = request_threaded_irq(data->irq, NULL, fp_interrupt, IRQ_TYPE_EDGE_RISING | IRQF_ONESHOT, "et310", (void *)data);
	if (ret)
		FP_LOG_ERROR("failed to request irq\n");

	fp_irq_op(data->irq, FP_INT_DISABLE);

	return ret;
}

void fp_interrupt_enable(struct fp_data *fp)
{
	FP_LOG_INFO("start\n");
	fp_irq_op(fp->int_desc.irq, FP_INT_ENABLE);
}

void fp_interrupt_disable(struct fp_data *fp)
{
	FP_LOG_INFO("start\n");
	//del_timer_sync(&fp->int_desc.timer);
	fp_irq_op(fp->int_desc.irq, FP_INT_DISABLE);
}

void fp_wakelock_ops(struct fp_wake_lock *wakelock, bool enable)
{
    if (enable == wakelock->locked) {
        FP_LOG_INFO("doubule %s %s, retern here\n", enable? "lock" : "unlock",
			wakelock->name);
        return;
    }

    if (enable) {
        wake_lock(&wakelock->lock);
    } else {
        wake_unlock(&wakelock->lock);
    }

    wakelock->locked = enable;
    FP_LOG_INFO("%s %s \n", enable? "lock" : "unlock", wakelock->name);
}

/*-------------------------------------------------------------------------*/
static void fp_reset(struct fp_data *fp)
{
    FP_LOG_INFO("start\n");
	gpio_set_value(fp->int_desc.reset_gpio, 0);
	msleep(30);
	gpio_set_value(fp->int_desc.reset_gpio, 1);
	msleep(20);
    FP_LOG_INFO("end\n");
}

static void fp_reset_set(int enable, struct fp_data *fp)
{
	FP_LOG_DEBUG("enable = %d\n", enable);
	if (enable == 0) {
		gpio_set_value(fp->int_desc.reset_gpio, 0);
		msleep(30);
	} else {
		gpio_set_value(fp->int_desc.reset_gpio, 1);
		msleep(20);
	}
}

static ssize_t fp_read(struct file *filp, char __user *buf, size_t count,
	loff_t *f_pos)
{
	/*Implement by vendor if needed*/
	return 0;
}

static ssize_t fp_write(struct file *filp,	const char __user *buf,	size_t count,
	loff_t *f_pos)
{
	/*Implement by vendor if needed*/
	return 0;
}

static long fp_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int err = 0;
	int retval = 0;
	struct fp_data *fp = NULL;
	struct spi_device *spi;
	u32 tmp = 0;
	struct egis_ioc_transfer *ioc = NULL;

	/* Check type and command number */
	if (_IOC_TYPE(cmd) != EGIS_IOC_MAGIC) {
		FP_LOG_ERROR("failed to check magic\n");
		return -ENOTTY;
	}

	/*
	 * Check access direction once here; don't repeat below.
	 * IOC_DIR is from the user perspective, while access_ok is
	 * from the kernel perspective; so they look reversed.
	 */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE,
						(void __user *)arg,
						_IOC_SIZE(cmd));
	if (err == 0 && _IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ,
						(void __user *)arg,
						_IOC_SIZE(cmd));
	if (err) {
		FP_LOG_ERROR("failed to check access dirction\n");
		return -EFAULT;
	}

	/*
	 * guard against device removal before, or while,
	 * we issue this ioctl.
	 */
	fp = filp->private_data;
	spin_lock_irq(&fp->spi_lock);
	spi = spi_dev_get(fp->spi);
	spin_unlock_irq(&fp->spi_lock);

	if (spi == NULL) {
		FP_LOG_ERROR("failed to get spi\n");
		return -ESHUTDOWN;
	}

	//mutex_lock(&fp->buf_lock);

	/* segmented and/or full-duplex I/O request */
	if (_IOC_NR(cmd) != _IOC_NR(EGIS_IOC_MESSAGE(0))
					|| _IOC_DIR(cmd) != _IOC_WRITE) {
		retval = -ENOTTY;
		FP_LOG_ERROR("failed to check message\n");
		goto out;
	}

	tmp = _IOC_SIZE(cmd);
	if ((tmp == 0) || (tmp % sizeof(struct egis_ioc_transfer)) != 0) {
		retval = -EINVAL;
		FP_LOG_ERROR("failed to get size\n");
		goto out;
	}

	/* copy into scratch area */
	ioc = kmalloc(tmp, GFP_KERNEL);
	if (ioc == NULL) {
		retval = -ENOMEM;
		FP_LOG_ERROR("failed to kmalloc for ioc\n");
		goto out;
	}

	if (__copy_from_user(ioc, (void __user *)arg, tmp)) {
		retval = -EFAULT;
		FP_LOG_ERROR("failed to copy from user\n");
		goto out;
	}

	FP_LOG_DEBUG("opcode = 0x%x\n", ioc->opcode);

	switch(ioc->opcode) {
		/*
		 * Read register
		 * tx_buf include register address will be read
		 */
		case FP_REGISTER_READ:
		{
			u8 *address = ioc->tx_buf;
			u8 *result = ioc->rx_buf;
			u8 data = 0;

			FP_LOG_DEBUG("address = 0x%x(%d)\n", address[0], address[0]);
			
			retval = fp_read_register(fp, address[0], &data);
			if (retval < 0)	{
				FP_LOG_ERROR("failed to read register = %d\n", retval);
				goto out;
			}

			FP_LOG_DEBUG("result = 0x%x(%d)\n", data, data);

			if (copy_to_user((u8 __user *) (uintptr_t) result, &data, 1)) {
				FP_LOG_ERROR("failed to copy_to_user\n");
				goto out;
			}
		}
		break;

		/*
		 * Write data to register
		 * tx_buf includes address and value will be wrote
		 */
		case FP_REGISTER_WRITE:
		{
			u8 *buf = ioc->tx_buf;
			FP_LOG_DEBUG("address = 0x%x(%d), data = 0x%x(%d)\n", buf[0], buf[0], buf[1], buf[1]);

			retval = fp_write_register(fp, buf[0], buf[1]);
			if (retval < 0) {
				FP_LOG_ERROR("failed to write register = %d\n", retval);
				goto out;
			}
		}
		break;

		/*
		 * Get one frame data from sensor
		 */
		case FP_GET_ONE_IMG:
		{
			u8 *buf = ioc->tx_buf;
			u8 *image_buf = ioc->rx_buf;

			//u8 val[6] = { 0 };
			uint32_t read_count = 0;
			u8 *work_buf = NULL;

			read_count = buf[0] * buf[1];
			if(read_count <= 0) {
				FP_LOG_ERROR("invalid width and height\n");
				goto out;
			}

			work_buf = kzalloc(read_count, GFP_KERNEL);
			if (work_buf == NULL) {
				retval = -ENOMEM;
				goto out;
			}

			retval = fp_get_one_image(fp, buf, work_buf);
			if (retval < 0) {				
				FP_LOG_ERROR("failed to get one image = %d\n", retval);
				goto exit_get_one_img;
			}

			if (copy_to_user((u8 __user *) (uintptr_t) image_buf, work_buf, read_count)) {
				FP_LOG_ERROR("failed to copy_to_user\n");
				goto exit_get_one_img;
			}

exit_get_one_img:
			if (work_buf)
				kfree(work_buf);
		}
		break;

		/*
		 * Reset sensor
		 */
		case FP_SENSOR_RESET:
		{
			FP_LOG_INFO("reset sensor\n");
			mutex_lock(&fp_global->scroll_lock);
			fp_reset(fp);
			mutex_unlock(&fp_global->scroll_lock);
		}
		break;

		/*
		 * Reset set
		 */
		case FP_RESET_SET:
		{
			FP_LOG_INFO("reset set status = %d\n", ioc->len);
			fp_reset_set(ioc->len, fp);
		}
		break;

		/*
		 * Set spi clock
		 */
		case FP_SET_SPI_CLOCK:
		{
			__u32 current_speed = spi->max_speed_hz;

			FP_LOG_INFO("current_speed = %d, speed_hz = %d\n", current_speed,
				ioc->speed_hz);

			spi->max_speed_hz = ioc->speed_hz;
			retval = spi_setup(spi);
			if (retval < 0) {
				FP_LOG_ERROR("failed to spi_setup = %d\n", retval);
				spi->max_speed_hz = current_speed;
			}
		}
		break;

		/*
		 * Set scroll cali data
		 */
		case FP_SET_SCROLL_CALI_DATA:
		{
			u8 *buf = ioc->tx_buf;

			FP_LOG_INFO("set scroll cali data, len = %d\n", ioc->len);
			retval = fp_set_cali_data(fp, buf, ioc->len);
		}
		break;

		/*
		 * Enable scroll
		 */
		case FP_ENABLE_SCROLL:
		{
			FP_LOG_INFO("enable scroll\n");
			fp_enable_scrolling(fp, true);
		}
		break;

		/*
		 * Disable scroll
		 */
		case FP_DISABLE_SCROLL:
		{
			FP_LOG_INFO("disable scroll\n");
			fp_enable_scrolling(fp, false);
		}
		break;

		/*
		 * Int detect state
		 */
		case FP_INT_DETECT_STATE:
		{
			FP_LOG_INFO("work in detect mode\n");
			fp->int_desc.interrupt_state = INTERRUPT_STATE_DETECT;
		}
		break;

		/*
		 * Int scroll state
		 */
		case FP_INT_SCROLL_STATE:
		{
			FP_LOG_INFO("work in scroll mode\n");
			fp->int_desc.interrupt_state |= INTERRUPT_STATE_SCROLL;
		}
		break;

		/*
		 * Int send key state
		 */
		case FP_INT_SEND_KEY_STATE:
		{
			FP_LOG_INFO("work in send key mode\n");
			fp->int_desc.interrupt_state |= INTERRUPT_STATE_SEND_KEY;
		}
		break;

		/*
		 * Enable tz spi
		 */
		case FP_ENABLE_TZ_SPI:
		{
			FP_LOG_INFO("enable tz spi\n");
			spi_enable(fp, true);
		}
		break;

		/*
		 * Disable tz spi
		 */
		case FP_DISABLE_TZ_SPI:
		{
			FP_LOG_INFO("disable tz spi\n");
			spi_enable(fp, false);
		}
		break;

		/*
		 * Eeprom wren
		 */
		case FP_EEPROM_WREN:
		{
			FP_LOG_INFO("eeprom wren\n");
			fp_reset_set(0, fp);
			fp_eeprom_wren(fp);
			fp_reset_set(1, fp);
		}
		break;

		/*
		 * Eeprom wrdi
		 */
		case FP_EEPROM_WRDI:
		{
			FP_LOG_INFO("eeprom wrdi\n");
			fp_reset_set(0, fp);
			fp_eeprom_wrdi(fp);
			fp_reset_set(1, fp);
		}
		break;

		/*
		 * Eeprom rdsr
		 */
		case FP_EEPROM_RDSR:
		{
			u8 *result = ioc->rx_buf;
			u8 buf[1] = { 0 };

			FP_LOG_INFO("eeprom rdsr\n");
			fp_reset_set(0, fp);
			fp_eeprom_rdsr(fp, buf);

			if (copy_to_user((u8 __user *) (uintptr_t) result, buf, 1)) {
				FP_LOG_ERROR("failed to copy_to_user\n");
			}
	
			fp_reset_set(1, fp);
		}
		break;

		/*
		 * Eeprom wrsr
		 */
		case FP_EEPROM_WRSR:
		{
			u8 *buf = ioc->tx_buf;

			FP_LOG_INFO("eeprom wrsr\n");
			fp_reset_set(0, fp);
			fp_eeprom_wrsr(fp, buf);
			fp_reset_set(1, fp);
		}
		break;

		/*
		 * Eeprom read
		 */
		case FP_EEPROM_READ:
		{
			u8 *buf = ioc->tx_buf;
			u8 *result = ioc->rx_buf;
			u8 *read_value = NULL;

			read_value = kzalloc(ioc->len + 2, GFP_KERNEL);
			if (read_value == NULL) {
				FP_LOG_ERROR("failed to kzalloc\n");
				goto out;
			}

			FP_LOG_INFO("eeprom read\n");
			fp_reset_set(0, fp);
			fp_eeprom_read(fp, buf, read_value, ioc->len);

			if (copy_to_user((u8 __user *) (uintptr_t) result,	read_value + 2, ioc->len)) {
				FP_LOG_ERROR("failed to copy_to_user\n");
			}
			fp_reset_set(1, fp);

			if (read_value)
				kfree(read_value);
		}
		break;

		/*
		 * Eeprom write
		 */
		case FP_EEPROM_WRITE:
		{
			u8 *buf = ioc->tx_buf;
			u8 *write_value = kzalloc(ioc->len + 2, GFP_KERNEL);

			if (write_value == NULL) {
				FP_LOG_ERROR("failed to kzalloc\n");
				goto out;
			}

			memcpy(write_value + 1, buf, (ioc->len) + 1);

			write_value[0] = FP_EEPROM_WRITE_OP;

			FP_LOG_INFO("eeprom write\n");
			fp_reset_set(0, fp);
			fp_eeprom_write(fp, write_value, ioc->len);
			fp_reset_set(1, fp);

			if (write_value)
				kfree(write_value);
		}
		break;

		/*
		 * Power onoff
		 */
		case FP_POWER_ONOFF:
		{
			FP_LOG_INFO("power control status = %d\n", ioc->len);
		}
		break;

		/*
		 * Trigger inital routine
		 */
		case INT_TRIGGER_INIT:
		{
			FP_LOG_INFO("trigger function init\n");

			fp->int_desc.detect_period = (int)ioc->pad[1];
			fp->int_desc.detect_threshold = (int)ioc->pad[2];
			fp_interrupt_enable(fp);
		}
		break;

		/*
		 * Trigger close
		 */
		case INT_TRIGGER_CLOSE:
		{
			FP_LOG_INFO("trigger function close\n");
			fp_interrupt_disable(fp);
			FP_LOG_INFO("trigger close = %d\n", retval);
		}
		break;

		/*
		 * Trigger abort
		 */
		case INT_TRIGGER_ABORT:
		{
			FP_LOG_INFO("trigger abort\n");
			fps_interrupt_abort();
		}
		break;
	}	

out:
	if (ioc != NULL)
		kfree(ioc);

	spi_dev_put(spi);
	if (retval < 0)
		FP_LOG_ERROR("retval = %d", retval);
		
	return retval;
} 
   
#ifdef CONFIG_COMPAT
static long fp_compat_ioctl(struct file *filp, unsigned int cmd,
	unsigned long arg)
{
    FP_LOG_INFO("start\n");

	return fp_ioctl(filp, cmd, (unsigned long)compat_ptr(arg));
}
#else
#define fp_compat_ioctl NULL
#endif /* CONFIG_COMPAT */

static int fp_open(struct inode *inode, struct file *filp)
{
	struct fp_data *fp = NULL;
	int	status = -ENXIO;

    FP_LOG_DEBUG("start\n");

	mutex_lock(&device_list_lock);

	list_for_each_entry(fp, &device_list, device_entry)
	{
		if (fp->devt == inode->i_rdev) {
			status = 0;
			break;
		}
	}

	if (status == 0) {
		/*if (fp->buffer == NULL) {
			fp->buffer = kmalloc(bufsiz, GFP_KERNEL);
			if (fp->buffer == NULL) {
				FP_LOG_ERROR("failed to open = -ENOMEM\n");
				status = -ENOMEM;
			}
		}*///lcx
		//if (status == 0) {
		fp->users++;
		filp->private_data = fp;
		nonseekable_open(inode, filp);
		//}
	} else {
		FP_LOG_ERROR("failed to fp_open: nothing for minor %d\n", iminor(inode));
	}

	mutex_unlock(&device_list_lock);

    FP_LOG_DEBUG("fp_open status = %d\n", status);
	return status;
}

static int fp_release(struct inode *inode, struct file *filp)
{
	struct fp_data *fp = NULL;

	FP_LOG_DEBUG("start\n");

	mutex_lock(&device_list_lock);
	fp = filp->private_data;
	filp->private_data = NULL;

	/* last close? */
	fp->users--;
	if (fp->users == 0) {
		int	dofree = 0;

		//kfree(fp->buffer);
		//fp->buffer = NULL;//lcx

		/* ... after we unbound from the underlying device? */
		spin_lock_irq(&fp->spi_lock);
		dofree = (fp->spi == NULL);
		spin_unlock_irq(&fp->spi_lock);

		if (dofree)
			kfree(fp);
	}
	mutex_unlock(&device_list_lock);

	return 0;
}

static const struct file_operations fp_fops = {
	.owner = THIS_MODULE,
	.write = fp_write,
	.read = fp_read,
	.unlocked_ioctl = fp_ioctl,
	.compat_ioctl = fp_compat_ioctl,
	.open = fp_open,
	.release = fp_release,
	.llseek = no_llseek,
	.poll = fps_interrupt_poll
};

static int fp_parse_dts(struct fp_data *fp)
{
	u32 temp_val = 0;
 	struct device_node *np = fp->spi->dev.of_node;

    FP_LOG_INFO("start\n");

    fp->int_desc.reset_gpio = of_get_named_gpio_flags(np, "fp-gpio-rst", 0, &temp_val);
    if(fp->int_desc.reset_gpio == 0) {
        FP_LOG_ERROR("failed to get reset gpio\n");
        return -1;
    }

    fp->int_desc.irq_gpio = of_get_named_gpio_flags(np, "fp-gpio-drdy", 0, &temp_val);
    if(fp->int_desc.irq_gpio == 0) {
        FP_LOG_ERROR("failed to get irq gpio\n");
        return -1;
    }

    FP_LOG_INFO("rst = %d, int = %d\n", (int)fp->int_desc.reset_gpio,
		(int)fp->int_desc.irq_gpio);

	fp->tz_enable = of_property_read_bool(np, "fp,tz-enable");
	FP_LOG_INFO("tz_enable = %s\n", fp->tz_enable ? "true" : "false");

    return 0;
}

static int fp_init_gpio(struct fp_data *fp)
{
    int ret = 0;

    FP_LOG_INFO("start\n");

    ret = gpio_request(fp->int_desc.reset_gpio, "fp_rst");
    if (ret) {
        FP_LOG_ERROR("failed to request fp_rst gpio %d\n", fp->int_desc.reset_gpio);
        goto err_request_rst;
    }
    gpio_direction_output(fp->int_desc.reset_gpio, 1);
	gpio_set_value(fp->int_desc.reset_gpio, 1);
 
    ret = gpio_request(fp->int_desc.irq_gpio, "fp_irq");
    if (ret) {
        FP_LOG_ERROR("failed to request fp_irq gpio %d\n", fp->int_desc.irq_gpio);
        goto err_requeset_irq;
    }

    gpio_direction_output(fp->int_desc.irq_gpio, 1);
    gpio_direction_input(fp->int_desc.irq_gpio);

	FP_LOG_INFO("success\n");
	return 0;

err_requeset_irq:
    gpio_free(fp->int_desc.reset_gpio);
err_request_rst:
    return ret;
}

static int fp_init_pinctrl(struct fp_data *fp, struct device *dev)
{
    FP_LOG_INFO("start\n");

	fp->fp_pctrl.pinctrl= devm_pinctrl_get(dev);
	if (IS_ERR_OR_NULL(fp->fp_pctrl.pinctrl)) {
        FP_LOG_ERROR("failed to get pinctrl handle\n");
        return -EINVAL;
    }

	fp->fp_pctrl.gpio_state_active = pinctrl_lookup_state(fp->fp_pctrl.pinctrl,
		"fp_active");
	if (IS_ERR_OR_NULL(fp->fp_pctrl.gpio_state_active)) {
		FP_LOG_ERROR("failed to get active state pinctrl handle\n");
		return -EINVAL;
	}

	fp->fp_pctrl.gpio_state_suspend = pinctrl_lookup_state(fp->fp_pctrl.pinctrl,
		"fp_suspend");
	if (IS_ERR_OR_NULL(fp->fp_pctrl.gpio_state_suspend)) {
		FP_LOG_ERROR("failed to get suspend state pinctrl handle\n");
		return -EINVAL;
	}

    FP_LOG_INFO("success\n");

	return 0;
}

static int fp_pinctrl_set(struct fp_data *fp, bool active)
{
    int ret = 0;

    FP_LOG_INFO("start\n");

    if (active) {
        ret = pinctrl_select_state(fp->fp_pctrl.pinctrl, fp->fp_pctrl.gpio_state_active);
    } else {
        ret = pinctrl_select_state(fp->fp_pctrl.pinctrl, fp->fp_pctrl.gpio_state_suspend);
    }

    FP_LOG_INFO("set %s = %d\n", active? "avtive" : "suspend", ret);

    return ret;
}

static int fp_enable_power(struct fp_data *fp, bool enable)
{
#if 0

    int rc = 0;

    FP_LOG_INFO("start, enable = %s\n", enable == true ? "enable" : "disable");

    if (enable) {
        fp->fp_power_vdd = regulator_get(&((fp->spi)->dev), "vdd");
        if (IS_ERR(fp->fp_power_vdd)) {
            rc = PTR_ERR(fp->fp_power_vdd);
            FP_LOG_ERROR("failed to get vdd rc = %d\n", rc);
            return rc;
        }

        if (regulator_count_voltages(fp->fp_power_vdd) > 0) {
            rc = regulator_set_voltage(fp->fp_power_vdd, 2850000, 3300000);
            if (rc) {
                FP_LOG_ERROR("failed to set vdd rc = %d\n", rc);
				goto err_set_vol;
            }
        }

        rc = regulator_set_optimum_mode(fp->fp_power_vdd, 60000);
        if (rc < 0) {
            FP_LOG_ERROR("failed to set_optimum_mode rc = %d\n", rc);
            goto err_set_opti;
        }

        rc = regulator_enable(fp->fp_power_vdd);
        if (rc) {
            FP_LOG_ERROR("failed to enable vdd rc = %d\n", rc);
			goto err_enable;
        }
    } else {
		if (regulator_count_voltages(fp->fp_power_vdd) > 0) {
			regulator_set_voltage(fp->fp_power_vdd, 0, 3300000);
		    regulator_put(fp->fp_power_vdd);
        }
    }

    FP_LOG_INFO("success\n");
	return 0;

err_enable:
err_set_opti:
	if (regulator_count_voltages(fp->fp_power_vdd) > 0)
		regulator_set_voltage(fp->fp_power_vdd, 0, 3300000);
err_set_vol:
	regulator_put(fp->fp_power_vdd);

    return rc;
#endif
    return 0;
}

static int fp_chip_detect(struct fp_data *fp)
{
    unsigned char read_buf[1] = { 0 };
    unsigned char check_reg   = 0x04;
    unsigned char check_data  = 0x1e;

    fp_write_register(fp, check_reg, check_data);

    fp_read_register(fp, check_reg, read_buf);

    if (check_data == read_buf[0]) {
        FP_LOG_INFO("success to detect chip\n");
        return true;
    } else {
        FP_LOG_ERROR("failed to detect chip, read_buf is %d\n", read_buf[0]);
        return false;
    }
}

static ssize_t fp_scroll_show(struct kobject *kobj, struct kobj_attribute *attr,
	char *buf)
{
	return snprintf(buf, PAGE_SIZE, "scroll enable = %d\n", fp_global->scroll_enable);
}

static ssize_t fp_scroll_store(struct kobject *kobj,	struct kobj_attribute *attr,
	const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

	if ((val != 0) && (val != 1)) {
		FP_LOG_ERROR("invalid value\n");
		goto exit;
	}

	fp_enable_scrolling(fp_global, val);

	FP_LOG_INFO("scroll enable = %d\n", val);

exit:
	return size;
}

static ssize_t fp_getkey_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "getkey enable = %d\n", fp_global->getkey_enable);
}

static ssize_t fp_getkey_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

	if ((val != 0) && (val != 1)) {
		FP_LOG_ERROR("invalid value\n");
		goto exit;
	}

	fp_enable_getkey(fp_global, val);

	FP_LOG_INFO("getkey enable = %d", val);

exit:
	return size;
}

static ssize_t fp_scroll_jitter_limit_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "scroll jitter limit = %d\n",
		fp_global->scroll_param.jitter_limit);
}

static ssize_t fp_scroll_jitter_limit_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

   	if (val <= 0) {
		FP_LOG_ERROR("invalid value\n");
		goto exit;
	}

	fp_global->scroll_param.jitter_limit = val;

	FP_LOG_INFO("scroll jitter limit = %d\n", val);

exit:
	return size;
}

static ssize_t fp_scroll_jitter_threshold_show
	(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "scroll jitter threshold = %d\n",
		fp_global->scroll_param.jitter_threshold);
}

static ssize_t fp_scroll_jitter_threshold_store
	(struct kobject *kobj, struct kobj_attribute *attr,
	const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

   	if (val <= 0) {
		FP_LOG_ERROR("invalid value\n");
		goto exit;
	}

	fp_global->scroll_param.jitter_threshold = val;

	FP_LOG_INFO("scroll jitter threshold val = %d", val);

exit:
	return size;
}

static ssize_t fp_interrupt_state_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "interrupt state = %d\n",
		fp_global->int_desc.interrupt_state);
}

static ssize_t fp_interrupt_state_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

   	if (val <= 0) {
		FP_LOG_ERROR("invalid value\n");
		goto exit;
	}

	fp_global->int_desc.interrupt_state = val;

	FP_LOG_INFO("interrupt state = %d", val);

exit:
	return size;
}

static ssize_t fp_interrupt_key_code_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "interrupt_key_code = %d\n",
		fp_global->int_desc.interrupt_key_code);
}

static ssize_t fp_interrupt_key_code_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

	FP_LOG_INFO("interrupt key code val = %d", val);

	fp_global->int_desc.interrupt_key_code = val;
	if (fp_global->int_desc.interrupt_key_code != KEY_F11)
		input_set_capability(fp_global->key_input_dev, EV_KEY,
		fp_global->int_desc.interrupt_key_code);

	return size;
}

static ssize_t fp_detect_period_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "detect_period = %d\n",
		fp_global->int_desc.detect_period);
}

static ssize_t fp_detect_period_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

	fp_global->int_desc.detect_period = val;

	FP_LOG_INFO("detect period val = %d",val);

	return size;
}

static ssize_t fp_detect_count_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "detect_count = %d\n",
		fp_global->int_desc.detect_threshold);
}

static ssize_t fp_detect_count_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

	fp_global->int_desc.detect_threshold = val;

	FP_LOG_INFO("detect count = %d", val);

	return size;
}

static ssize_t fp_finger_on_threshold_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "finger_on_threshold = %d\n",
		fp_global->cali_info.fingerOnThreshold);
}

static ssize_t fp_finger_on_threshold_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);  

    if (val > 0)
        fp_global->cali_info.fingerOnThreshold= val;
 	else
        fp_global->cali_info.fingerOnThreshold = 1;

	FP_LOG_INFO("finger_on_threshold = %d\n", fp_global->cali_info.fingerOnThreshold);

	return size;
}

static ssize_t fp_finger_on_threshold_loose_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "finger_on_threshold_loose = %d\n",
		fp_global->cali_info.fingerOnThresholdLoose);
}

static ssize_t fp_finger_on_threshold_loose_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

    if (val > 0)
        fp_global->cali_info.fingerOnThresholdLoose = val;
	else
        fp_global->cali_info.fingerOnThresholdLoose = 1;

	FP_LOG_INFO("fingerOnThresholdLoose = %d\n",
		fp_global->cali_info.fingerOnThresholdLoose);

	return size;
}

static ssize_t fp_wake_up_nomove_th_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "wake_up_nomove_th = %d\n",
		fp_global->scroll_param.no_move_th);
}

static ssize_t fp_wake_up_nomove_th_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

    if (val > 10)
        fp_global->scroll_param.no_move_th = val;
	else
        fp_global->scroll_param.no_move_th = 10;

	FP_LOG_INFO("wake_up_nomove_th = %d\n", fp_global->scroll_param.no_move_th);

	return size;
}

static ssize_t fp_wake_up_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "wake up = %d\n", fp_global->wake_up);
}

static ssize_t fp_wake_up_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

	if ((val != 0) && (val != 1)) {
		FP_LOG_ERROR("invalid value\n");
		goto exit;
	}

    fp_global->wake_up = val;

	FP_LOG_INFO("wake up as = %d\n", fp_global->wake_up);

exit:
	return size;
}

// used for tz spi added by nubia
static ssize_t finger_bam_owner_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;
	sscanf(buf, "%d", &val);

    FP_LOG_INFO("start\n");

    if (val) {
        spi_change_pipe_owner(fp_global, true);
    } else {
        spi_change_pipe_owner(fp_global, false);
    }

    FP_LOG_INFO("%s bam to tz\n", val? "enable" : "disable");

	return size;
}

static ssize_t finger_spi_pinctrl_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;
	sscanf(buf, "%d", &val);

    FP_LOG_INFO("start\n");

    if (val) {
        spi_set_pinctrl(fp_global, true);
    } else {
        spi_set_pinctrl(fp_global, false);
    }

    FP_LOG_INFO("%s pinctrl to tz\n", val? "enable" : "disable");

	return size;
}

static ssize_t finger_spi_clock_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;
	sscanf(buf, "%d", &val);

    FP_LOG_INFO("start\n");

    if (val) {
        spi_set_clks(fp_global, true);
    } else {
        spi_set_clks(fp_global, false);
    }

    FP_LOG_INFO("%s clk to tz\n", val? "enable" : "disable");

	return size;
}

static ssize_t finger_spi_fabric_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;
	sscanf(buf, "%d", &val);

    FP_LOG_INFO("start\n");

    if (val) {
        spi_set_fabric(fp_global, true);
    } else {
        spi_set_fabric(fp_global, false);
    }

    FP_LOG_INFO("%s fabric to tz\n", val? "enable" : "disable");

	return size;
}

static ssize_t finger_reset_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{	
    fp_reset(fp_global);
	return size;
}
// nubia add end

static struct kobj_attribute scroll_attribute =
	__ATTR(scroll, 0664,
	fp_scroll_show,
	fp_scroll_store);
static struct kobj_attribute getkey_attribute =
	__ATTR(getkey, 0664,
	fp_getkey_show,
	fp_getkey_store);
static struct kobj_attribute scroll_jitter_limit_attribute =
	__ATTR(scroll_jitter_limit, 0664,
	fp_scroll_jitter_limit_show,
	fp_scroll_jitter_limit_store);
static struct kobj_attribute scroll_jitter_threshold_attribute =
	__ATTR(scroll_jitter_threshold, 0664,
	fp_scroll_jitter_threshold_show,
	fp_scroll_jitter_threshold_store);
static struct kobj_attribute interrupt_state_attribute =
	__ATTR(interrupt_state, 0664,
	fp_interrupt_state_show,
	fp_interrupt_state_store);//recovery??!!
static struct kobj_attribute interrupt_key_code_attribute =
	__ATTR(interrupt_key_code, 0664,
	fp_interrupt_key_code_show,
	fp_interrupt_key_code_store);
static struct kobj_attribute detect_period_attribute =
	__ATTR(detect_period, 0664,
	fp_detect_period_show,
	fp_detect_period_store);
static struct kobj_attribute detect_count_attribute =
	__ATTR(detect_count, 0664,
	fp_detect_count_show,
	fp_detect_count_store);
static struct kobj_attribute finger_on_threshold_attribute =
	__ATTR(finger_on_threshold, 0664,
	fp_finger_on_threshold_show,
	fp_finger_on_threshold_store);
static struct kobj_attribute finger_on_threshold_loose_attribute =
	__ATTR(finger_on_threshold_loose, 0664,
	fp_finger_on_threshold_loose_show,
	fp_finger_on_threshold_loose_store);
static struct kobj_attribute wake_up_nomove_th_attribute =
	__ATTR(wake_up_nomove_th, 0664,
	fp_wake_up_nomove_th_show,
	fp_wake_up_nomove_th_store);
static struct kobj_attribute wake_up_control_attribute =
	__ATTR(wake_up, 0664,
	fp_wake_up_show,
	fp_wake_up_store);

// used for tz spi added by nubia
static struct kobj_attribute finger_bam_owner_attribute =
	__ATTR(finger_bam_owner, 0220, NULL, finger_bam_owner_store);
static struct kobj_attribute finger_spi_pinctrl_attribute =
	__ATTR(finger_spi_pinctrl, 0220, NULL, finger_spi_pinctrl_store);
static struct kobj_attribute finger_spi_clock_attribute =
	__ATTR(finger_spi_clock, 0220, NULL, finger_spi_clock_store);
static struct kobj_attribute finger_spi_fabric_attribute =
	__ATTR(finger_spi_fabric, 0220, NULL, finger_spi_fabric_store);
static struct kobj_attribute finger_reset_attribute =
	__ATTR(finger_reset, 0220, NULL, finger_reset_store);
// nubia add end

static struct attribute *attrs[] = {
	&scroll_attribute.attr,
	&getkey_attribute.attr,
	&scroll_jitter_limit_attribute.attr,
	&scroll_jitter_threshold_attribute.attr,
	&interrupt_state_attribute.attr,
	&interrupt_key_code_attribute.attr,
	&detect_period_attribute.attr,
	&detect_count_attribute.attr,
	&finger_on_threshold_attribute.attr,
	&finger_on_threshold_loose_attribute.attr,
	&wake_up_nomove_th_attribute.attr,
	&wake_up_control_attribute.attr,

	// used for tz spi added by nubia
	&finger_bam_owner_attribute.attr,
	&finger_spi_pinctrl_attribute.attr,
	&finger_spi_clock_attribute.attr,
	&finger_spi_fabric_attribute.attr,
	&finger_reset_attribute.attr,
	// nubia add end
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};

int fingerprint_sys_init(void) {
	int retval = 0;
	static struct kobject *id_kobj;

    FP_LOG_INFO("start\n");

	id_kobj = kobject_create_and_add("fingerprint", kernel_kobj);
	if (!id_kobj)
		return -ENOMEM;

	/* Create the files associated with this kobject */
	retval = sysfs_create_group(id_kobj, &attr_group);
	if (retval)
		kobject_put(id_kobj);

    FP_LOG_INFO("end\n");

	return retval;
}

static int fp_init_input(struct fp_data *fp)
{
	struct input_dev *key_input_dev = NULL;
	int rc = 0;

	FP_LOG_INFO("start\n");

	key_input_dev = input_allocate_device();
	if (!key_input_dev) {
		rc = -1;
		FP_LOG_ERROR("failed to input_allocate_device\n");
		goto err_input_alloc;
	}

	key_input_dev->name = "et310";
	key_input_dev->id.bustype = BUS_SPI;
	key_input_dev->dev.parent = &fp->spi->dev;

	set_bit(EV_KEY, key_input_dev->evbit);
	set_bit(EV_SYN, key_input_dev->evbit);
	set_bit(INPUT_PROP_DIRECT, key_input_dev->propbit);

	input_set_capability(key_input_dev, EV_KEY, KEY_VOLUMEDOWN);
	input_set_capability(key_input_dev, EV_KEY, KEY_VOLUMEUP);
	input_set_capability(key_input_dev, EV_KEY, KEY_POWER);
	input_set_capability(key_input_dev, EV_KEY, KEY_F11);

	rc = input_register_device(key_input_dev);
	if (rc) {
		FP_LOG_ERROR("failed to input_register_device\n");
		goto err_input_register;
	}

	fp->key_input_dev = key_input_dev;

	FP_LOG_INFO("success\n");
	return 0;

err_input_register:
	input_free_device(key_input_dev);
err_input_alloc:
	return rc;
}

void fp_param_init(struct fp_data *fp)
{
	fp->users = 0;
	fp->scroll_enable = false;
	fp->scroll_param.jitter_limit = 10;
	fp->scroll_param.jitter_threshold = 30;
	fp->scroll_param.no_move_th = 15;
	fp->scroll_param.FingerOnPartial = 0;
	fp->cali_info.dc_detect = 0x7F;
	fp->cali_info.gain_detect = 0;
	fp->cali_info.interruptThrehold = 0x3F;
	fp->cali_info.fingerOnThreshold = 15;
	fp->cali_info.fingerOnThresholdLoose = 2;
	fp->wake_up = false;
	fp->fp_wakelock.name = "fp_wakelock";
	fp->fp_wakelock.locked = false;
	fp->fp_wakelock_timeout.name = "fp_wakelock_timeout";
	fp->fp_wakelock_timeout.locked = false;
}

static int fp_probe(struct spi_device *spi)
{
	struct fp_data *fp = NULL;
	unsigned long minor = 0;
	int rc = 0;
	struct spi_device *spi_initialize;

    FP_LOG_INFO("start\n");

	/* Allocate driver data */
	fp = kzalloc(sizeof(struct fp_data), GFP_KERNEL);
	if (fp == NULL) {
		FP_LOG_ERROR("failed to kzalloc\n");
		return -ENOMEM;
	}

    fp_global = fp;

	spi_set_drvdata(spi, fp);

	/* Initialize the driver data */
	fp->spi = spi;
	spin_lock_init(&fp->spi_lock);
	//mutex_init(&fp->buf_lock);
	mutex_init(&fp->scroll_lock);
	mutex_init(&fp->getkey_lock);

	INIT_LIST_HEAD(&fp->device_entry);

    rc = fp_parse_dts(fp);
	if (rc) {
		FP_LOG_ERROR("failed to fp_parse_dts\n");
		goto err_dts_parse;
	}

	rc = fp_init_gpio(fp);
    if (rc) {
		FP_LOG_ERROR("failed to fp_init_gpio\n");
        goto err_gpio_init;
    }

    rc = fp_init_pinctrl(fp, &spi->dev);
	if (rc) {
		FP_LOG_ERROR("failed to fp_init_pinctrl\n");
		goto err_pinctrl_init;
	}

	rc = fp_pinctrl_set(fp, true);
    if (rc) {
        FP_LOG_ERROR("failed to fp_pinctrl_set\n");
        goto err_pinctrl_set;
    }
	// used for tz spi added by nubia
	if (fp->tz_enable == true)
		spi_init(fp);

    rc = fp_enable_power(fp, true);
	if(rc) {
		FP_LOG_ERROR("failed to fp_enable_power\n");
		goto err_power_enable;
	}

	spin_lock_irq(&fp->spi_lock);
	spi_initialize= spi_dev_get(fp->spi);
	spin_unlock_irq(&fp->spi_lock);

	spi_initialize->mode = SPI_MODE_3;
	spi_initialize->bits_per_word = 8;
	spi_initialize->irq = gpio_to_irq(fp->int_desc.irq_gpio);
	spi_initialize->max_speed_hz = FPC_BTP_SPI_CLOCK_SPEED;

	FP_LOG_INFO("spi port using : %s\n", spi_initialize->modalias);

	rc = spi_setup(spi_initialize);

    FP_LOG_INFO("spi set result is %d\n",rc);

	fp_reset(fp);

	if (fp->tz_enable == false) {
	    if (false == fp_chip_detect(fp)) {
			rc = -1;
	        goto err_chip_detect;
	    }
    fp_set_poweroff_mode();

	}

	setup_timer(&(fp->int_desc.timer), fp_interrupt_timer_routine,
		(unsigned long)&(fp->int_desc));

	/*
	 * If we can allocate a minor number, hook up this device.
	 * Reusing minors is fine so long as udev or mdev is working.
	 */
	mutex_lock(&device_list_lock);
	minor = find_first_zero_bit(minors, N_SPI_MINORS);
	if (minor < N_SPI_MINORS) {
		struct device *dev;
		fp->devt = MKDEV(FP_MAJOR, minor);
		dev = device_create(fp_class, &spi->dev, fp->devt,
					fp, "esfp0");
		rc = IS_ERR(dev) ? PTR_ERR(dev) : 0;
	} else {
		FP_LOG_ERROR("failed to get minor number\n");
		rc = -ENODEV;
	}

	if (rc == 0) {
		set_bit(minor, minors);
		list_add(&fp->device_entry, &device_list);
		mutex_unlock(&device_list_lock);
	} else {
		mutex_unlock(&device_list_lock);
		FP_LOG_ERROR("failed to device_create\n");
		goto err_alloc_minor;
	}

	rc = fingerprint_sys_init();
	if (rc) {
		FP_LOG_ERROR("failed to fingerprint_sys_init\n");
		goto err_sys_init;
	}

	fp->scroll_wq = create_singlethread_workqueue("scroll_wq");
	if (!fp->scroll_wq) {
		rc = -1;
		FP_LOG_ERROR("failed to creat workqueue\n");
		goto err_create_wq;
	}
	INIT_WORK(&fp->scroll_work, fp_scroll_work_func);

	fp->getkey_wq = create_singlethread_workqueue("getkey_wq");
	if (!fp->getkey_wq) {
		rc = -1;
		FP_LOG_ERROR("failed to creat workqueue\n");
		goto err_create_wq;
	}
	INIT_WORK(&fp->getkey_work, fp_getkey_work_func);

	rc = fp_init_input(fp);
	if (rc) {
		FP_LOG_ERROR("failed to fp_init_input\n");
		goto err_input_init;
	}

	rc = fp_interrupt_init(&(fp->int_desc));

	wake_lock_init(&fp->fp_wakelock.lock, WAKE_LOCK_SUSPEND, "fp_wakelock");
	wake_lock_init(&fp->fp_wakelock_timeout.lock, WAKE_LOCK_SUSPEND, "fp_wakelock_timeout");

	fp_param_init(fp);

#ifdef CONFIG_FB
	fp_setup_fb_notifier(fp);
#endif

    FP_LOG_INFO("success\n");
	return 0;

err_input_init:
err_create_wq:
err_sys_init:
err_alloc_minor:	
err_chip_detect:
	fp_enable_power(fp, false);
err_power_enable:
err_pinctrl_set:
	devm_pinctrl_put(fp->fp_pctrl.pinctrl);
err_pinctrl_init:
	gpio_free(fp->int_desc.reset_gpio);
	gpio_free(fp->int_desc.irq_gpio);
err_gpio_init:
err_dts_parse:
	kfree(fp);
	FP_LOG_INFO("failed\n");
	return rc;
}

static int fp_remove(struct spi_device *spi)
{
	struct fp_data *fp = spi_get_drvdata(spi);

	FP_LOG_DEBUG("start\n");

	/* make sure ops on existing fds can abort cleanly */
	spin_lock_irq(&fp->spi_lock);
	fp->spi = NULL;
	spi_set_drvdata(spi, NULL);
	spin_unlock_irq(&fp->spi_lock);

	/* prevent new opens */
	mutex_lock(&device_list_lock);
	list_del(&fp->device_entry);
	device_destroy(fp_class, fp->devt);
	clear_bit(MINOR(fp->devt), minors);
	if (fp->users == 0)
		kfree(fp);
	mutex_unlock(&device_list_lock);

    FP_LOG_INFO("end\n");

	return 0;
}

/*-------------------------------------------------------------------------*/
#ifdef CONFIG_FB
static int fp_fb_notifier_callback(struct notifier_block *self,
	unsigned long event, void *data)
{
	struct fp_data *fp = container_of(self, struct fp_data, fb_notifier);
	struct fb_event *evdata = data;
	int *blank;
	int rc = 0;

	FP_LOG_DEBUG("event = %lu\n", event);

	if (evdata && evdata->data && event == FB_EVENT_BLANK) {
		blank = evdata->data;
		if (*blank == FB_BLANK_UNBLANK) {

			FP_LOG_INFO("FB_BLANK_UNBLANK\n");
			if (fp->wake_up == true) {
				fp->int_desc.interrupt_state &= ~INTERRUPT_STATE_SEND_KEY;
			} else {
				if (fp->tz_enable == false) {
					//if (fp->int_desc.interrupt_state & INTERRUPT_STATE_SCROLL)
						rc = fp_set_detect_mode();
				}
			}
		} else if (*blank == FB_BLANK_POWERDOWN) {

		    FP_LOG_INFO("FB_BLANK_POWERDOWN\n");
			if (fp->wake_up == true) {
				fp->int_desc.interrupt_state |= INTERRUPT_STATE_SEND_KEY;
			} else {
				if (fp->tz_enable == false) {
					fp_set_poweroff_mode();
				}
			}
		}
	}

	return 0;
}

static void fp_setup_fb_notifier(struct fp_data *fp)
{
	int rc = 0;

	fp->fb_notifier.notifier_call = fp_fb_notifier_callback;

	rc = fb_register_client(&fp->fb_notifier);
	if (rc)
		FP_LOG_ERROR("failed to register fb_notifier: %d\n", rc);
}
#endif

static int fp_suspend(struct spi_device *spi_dev, pm_message_t mesg)
{
	struct fp_data *fp = spi_get_drvdata(spi_dev);

    FP_LOG_INFO("start\n");

	if (fp->wake_up == true) {
		fp_irq_wake_op(fp->int_desc.irq, FP_INT_ENABLE);
	} else {
		fp_irq_op(fp->int_desc.irq, FP_INT_DISABLE);
	}

    FP_LOG_INFO("end\n");

    return 0 ;
}

 static int fp_resume(struct spi_device *spi_dev)
 {
	struct fp_data *fp = spi_get_drvdata(spi_dev);
 
	FP_LOG_INFO("start\n");

	if (fp->wake_up == true) {
		fp_irq_wake_op(fp->int_desc.irq, FP_INT_DISABLE);
	} else {
		fp_irq_op(fp->int_desc.irq, FP_INT_ENABLE);
	}

	FP_LOG_INFO("end\n");

     return 0;
 }

static struct spi_driver fp_spi_driver = {
	.driver = {
		.name  = "et310",
		.bus   = &spi_bus_type,
		.owner = THIS_MODULE,
	},
	.probe = fp_probe,
	.remove = fp_remove,
	.suspend = fp_suspend,
	.resume = fp_resume,
};

static int __init fp_init(void)
{
	int status = 0;


#ifdef CONFIG_ZTEMT_N940_FP_COMPATIBLE
    char pcb_version[12];
    ztemt_get_hw_pcb_version(pcb_version);
    if(strcmp(pcb_version,"MB_E")>=0)
	    if(strcmp(ztemt_config_version,ztemt_config_version_A)) return -1;
#endif
	FP_LOG_DEBUG("start\n");


	/*
	 * Claim our 256 reserved device numbers.  Then register a class
	 * that will key udev/mdev to add/remove /dev nodes.  Last, register
	 * the driver which manages those device numbers.
	 */
	BUILD_BUG_ON(N_SPI_MINORS > 256);

	status = register_chrdev(FP_MAJOR, "spi", &fp_fops);
	if (status < 0) {
		FP_LOG_ERROR("failed to register chrdev = %d\n", status);
		return status;
	}

	fp_class = class_create(THIS_MODULE, "fp");
	if (IS_ERR(fp_class)) {
		FP_LOG_ERROR("failed to create class\n");
		unregister_chrdev(FP_MAJOR, "fp");
		return PTR_ERR(fp_class);
	}

	status = spi_register_driver(&fp_spi_driver);
	if (status < 0) {
		FP_LOG_ERROR("failed to register spi = %d\n", status);
		class_destroy(fp_class);
		unregister_chrdev(FP_MAJOR, "fp");
	}

	return status;
}
module_init(fp_init);

static void __exit fp_exit(void)
{
	FP_LOG_INFO("%s\n", __func__);

	gpio_free(fp_global->int_desc.irq_gpio);
	spi_unregister_driver(&fp_spi_driver);
	class_destroy(fp_class);
	unregister_chrdev(FP_MAJOR, "fp");
}
module_exit(fp_exit);

MODULE_AUTHOR("Wang YuWei, <robert.wang@egistec.com>");
MODULE_DESCRIPTION("SPI Interface for ET310");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:spidev");
