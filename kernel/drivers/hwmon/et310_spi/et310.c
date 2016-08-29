/*
 * et310 register configuration
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
#include "et310.h"

/*------------------------------- variables ---------------------------------*/
extern struct fp_data *fp_global;

/*------------------------ function implementation --------------------------*/
int fp_set_scroll_detect_region(void)
{
	#define FPS_INTERRUPT_DETECT_BLOCK 16

	//16*1
	if((fp_write_register_external(SRBA_ET310_ADDR, FPS_IMG_HEIGHT >> 1) != 0) ||
		(fp_write_register_external(SREA_ET310_ADDR, (FPS_IMG_HEIGHT >> 1)) != 0) ||
		(fp_write_register_external(SCBA_ET310_ADDR,
			(FPS_IMG_WIDTH - FPS_INTERRUPT_DETECT_BLOCK) >> 1) != 0) ||
		(fp_write_register_external(SCEA_ET310_ADDR,
			((FPS_IMG_WIDTH - FPS_INTERRUPT_DETECT_BLOCK) >> 1)
			+ FPS_INTERRUPT_DETECT_BLOCK - 1) != 0)) {
		return -1;//·¶Î§??lcx
	}

	return 0;
}

int fp_set_getkey_detect_region(void)
{
	#define FPS_INTERRUPT_DETECT_GETKEY_BLOCK 108

	//16*1
	if((fp_write_register_external(SRBA_ET310_ADDR, FPS_IMG_HEIGHT >> 1) != 0) ||
		(fp_write_register_external(SREA_ET310_ADDR, (FPS_IMG_HEIGHT >> 1)) != 0) ||
		(fp_write_register_external(SCBA_ET310_ADDR,
			(FPS_IMG_WIDTH - FPS_INTERRUPT_DETECT_GETKEY_BLOCK) >> 1) != 0) ||
		(fp_write_register_external(SCEA_ET310_ADDR,
			((FPS_IMG_WIDTH - FPS_INTERRUPT_DETECT_GETKEY_BLOCK) >> 1)
			+ FPS_INTERRUPT_DETECT_GETKEY_BLOCK - 1) != 0)) {
		return -1;
	}

	return 0;
}

int fp_set_normal_detect_region(void)
{
	if ((fp_write_register_external(SRBA_ET310_ADDR, 0) != 0) ||
		(fp_write_register_external(SREA_ET310_ADDR, FPS_IMG_HEIGHT - 1) != 0) ||
		(fp_write_register_external(SCBA_ET310_ADDR, 0)) ||
		(fp_write_register_external(SCEA_ET310_ADDR, FPS_IMG_WIDTH-1) != 0)) {
			return -1;
	}

	return 0;
}

int fp_fetch_image(unsigned char *pData, int width, int height)
{
	int error = 0, clean_up_error = 0;

	error = fp_write_register_external(TGENC_ET310_ADDR, TGEN_GEN_ET310_ON);
	if (error != 0) {
		FP_LOG_INFO("failed to write TGENC_ET310_ADDR\n");
		goto CleanUp;
	}

	error = fp_mass_read_external(FDATA_FP_ADDR, pData, width * height);
	if (error < 0) {
		FP_LOG_ERROR("failed to mass_read = %d\n", error);
		goto CleanUp;
	}

CleanUp:
	clean_up_error = fp_write_register_external(TGENC_ET310_ADDR, TGEN_GEN_ET310_OFF);
	if ((error == 0) && (clean_up_error != 0)) {
		return clean_up_error;
	} else {
		return error;
	}
}

void fp_set_detect_mode_register(void)
{
	//FP_LOG_INFO("dc = 0x%x, gain = 0x%x, threshold = %d\n", fp_global->cali_info.dc_detect,
	//		fp_global->cali_info.gain_detect, fp_global->cali_info.interruptThrehold);

	fp_write_register_external(POWER_CONTL_ET310_ADDR, ET310_DETECT_DOWN);

	// dc
	fp_write_register_external(FPS_CTL_ET310_ADDR, fp_global->cali_info.dc_detect);

	// gain
	fp_write_register_external(PGA_CONTL_ET310_ADDR, fp_global->cali_info.gain_detect);

	// 0x0B set 0xFF
	fp_write_register_external(SUSC_ET310_ADDR, ET310_SUSPEND_CYCLE);

	// 0x05 set 0x08
	fp_write_register_external(OT_CTL_ET310_ADDR, ET310_300KHZ_ENABLE);

	// 0x02 set 0x08
	fp_write_register_external(INT_EN_ET310_ADDR, 0x08);

	// interrupt threshold
	fp_write_register_external(DETC_ET310_ADDR, fp_global->cali_info.interruptThrehold);
	fp_write_register_external(DETC_ET310_ADDR, fp_global->cali_info.interruptThrehold);
}

int fp_set_detect_mode(void)
{
	int ret = 0;

	FP_LOG_INFO("start\n");

	ret = fp_set_scroll_detect_region();
	if (ret) {
		FP_LOG_INFO("failed to fp_set_scroll_detect_region\n");
		return ret;
	}

	fp_set_detect_mode_register();

	FP_LOG_INFO("end\n");
	return ret;
}

void fp_set_sensor_mode(void)
{
	u8 status = 0;
	FP_LOG_INFO("start\n");

	fp_read_register_external(INT_EN_ET310_ADDR, &status);
	fp_write_register_external(INT_EN_ET310_ADDR, status & 0xF7);// bit 3 to 0
	fp_write_register_external(POWER_CONTL_ET310_ADDR, ET310_DETECT_DOWN);

	//FP_LOG_INFO("dc = %x gain = %x\n", fp_global->cali_info.dc, fp_global->cali_info.gain);
	// dc
	fp_write_register_external(FPS_CTL_ET310_ADDR, fp_global->cali_info.dc);

	// gain
    fp_write_register_external(PGA_CONTL_ET310_ADDR, fp_global->cali_info.gain);

	FP_LOG_INFO("end\n");
	return;
}

int fp_set_poweroff_mode_register(void)
{
	unsigned char status = 0;

	fp_read_register_external(INT_EN_ET310_ADDR, &status);
	fp_write_register_external(INT_EN_ET310_ADDR, status & 0xE7); //bit 4 and 3 to 0
	fp_write_register_external(POWER_CONTL_ET310_ADDR, ET310_POWER_DOWN);
	fp_write_register_external(OT_CTL_ET310_ADDR, ET310_300KHZ_DISABLE);

	return 0;
}

int fp_set_poweroff_mode(void)
{
	int ret = 0;

	FP_LOG_INFO("start\n");

	ret = fp_set_normal_detect_region();
	if (ret) {
		FP_LOG_ERROR("failed to set_normal_detect_region\n");
		return ret;
	}

	fp_set_poweroff_mode_register();

	FP_LOG_INFO("end\n");

	return ret;
}
