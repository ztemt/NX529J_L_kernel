/*
 * Simple synchronous userspace interface to platform devices
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
#include "et310_platform.h"

/*------------------------------- variables ---------------------------------*/
// platform minor related
static DECLARE_BITMAP(minors, N_PLATFORM_MINORS);

// irq related
static unsigned char irq_is_disable = 0;
static unsigned char irq_is_wake = 0;

// class that platform device belong to
static struct class *fp_class;

// global variables
struct fp_data *fp_global = NULL;

#ifdef CONFIG_ZTEMT_N940_FP_COMPATIBLE
extern void ztemt_get_hw_pcb_version(char* result);

static char ztemt_config_version[10] = "*,*";
static char ztemt_config_version_A[10] = "0,0";//config version A

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
static void fp_setup_fb_notifier(struct fp_data *fp);
static void fp_reset(struct fp_data *fp);

/*------------------------ function implementation --------------------------*/
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

	fp_irq_op(fp->int_desc.irq, FP_INT_DISABLE);

	if (bdata->int_count >= bdata->detect_threshold) {
		bdata->finger_on = true;
		FP_LOG_DEBUG("triggered\n");

		if (bdata->interrupt_state & INTERRUPT_STATE_SEND_KEY) {
			input_report_key(fp->key_input_dev, fp->int_desc.interrupt_key_code, 1);
			input_sync(fp->key_input_dev);
			input_report_key(fp->key_input_dev, fp->int_desc.interrupt_key_code, 0);
			input_sync(fp->key_input_dev);
			wake_lock_timeout(&fp->fp_wakelock_timeout.lock, msecs_to_jiffies(2000));
		}
	} else {
		FP_LOG_DEBUG("not triggered\n");
	}

	bdata->int_count = 0;
	wake_up_interruptible(&interrupt_waitq);
	fp_irq_op(fp->int_desc.irq, FP_INT_ENABLE);
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
	ret = request_threaded_irq(data->irq, NULL, fp_interrupt,
		IRQ_TYPE_EDGE_RISING | IRQF_ONESHOT, "et310", (void *)data);
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
	fp_irq_op(fp->int_desc.irq, FP_INT_DISABLE);
}

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

static long fp_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int err = 0;
	int retval = 0;
	struct fp_data *fp = NULL;
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
		}
		break;

		/*
		 * Disable tz spi
		 */
		case FP_DISABLE_TZ_SPI:
		{
			FP_LOG_INFO("disable tz spi\n");
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
		fp->users++;
		filp->private_data = fp;
		nonseekable_open(inode, filp);
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

		/* ... after we unbound from the underlying device? */
		spin_lock_irq(&fp->platform_lock);
		dofree = (fp->pdev == NULL);
		spin_unlock_irq(&fp->platform_lock);

		if (dofree)
			kfree(fp);
	}
	mutex_unlock(&device_list_lock);

	return 0;
}

static const struct file_operations fp_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = fp_ioctl,
	.compat_ioctl = fp_compat_ioctl,
	.open = fp_open,
	.release = fp_release,
	.poll = fps_interrupt_poll
};

static int fp_parse_dts(struct fp_data *fp)
{
	u32 temp_val = 0;
 	struct device_node *np = fp->pdev->dev.of_node;

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
	return 0;
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

static ssize_t finger_reset_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{	
    fp_reset(fp_global);
	return size;
}

static struct kobj_attribute interrupt_state_attribute =
	__ATTR(interrupt_state, 0664,
	fp_interrupt_state_show,
	fp_interrupt_state_store);
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
static struct kobj_attribute wake_up_control_attribute =
	__ATTR(wake_up, 0664,
	fp_wake_up_show,
	fp_wake_up_store);

static struct kobj_attribute finger_reset_attribute =
	__ATTR(finger_reset, 0220, NULL, finger_reset_store);

static struct attribute *attrs[] = {
	&interrupt_state_attribute.attr,
	&interrupt_key_code_attribute.attr,
	&detect_period_attribute.attr,
	&detect_count_attribute.attr,
	&wake_up_control_attribute.attr,
	&finger_reset_attribute.attr,
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
	key_input_dev->dev.parent = &fp->pdev->dev;

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
	fp->wake_up = false;
	fp->fp_wakelock_timeout.name = "fp_wakelock_timeout";
	fp->fp_wakelock_timeout.locked = false;
}

static int fp_probe(struct platform_device *pdev)		
{
	struct fp_data *fp = NULL;
	unsigned long minor = 0;
	int rc = 0;

    FP_LOG_INFO("start\n");

	/* Allocate driver data */
	fp = kzalloc(sizeof(struct fp_data), GFP_KERNEL);
	if (fp == NULL) {
		FP_LOG_ERROR("failed to kzalloc\n");
		return -ENOMEM;
	}

    fp_global = fp;

	platform_set_drvdata(pdev, fp);

	/* Initialize the driver data */
	fp->pdev = pdev;
	spin_lock_init(&fp->platform_lock);

	mutex_init(&fp->scroll_lock);

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

    rc = fp_init_pinctrl(fp, &pdev->dev);
	if (rc) {
		FP_LOG_ERROR("failed to fp_init_pinctrl\n");
		goto err_pinctrl_init;
	}

	rc = fp_pinctrl_set(fp, true);
    if (rc) {
        FP_LOG_ERROR("failed to fp_pinctrl_set\n");
        goto err_pinctrl_set;
    }

    rc = fp_enable_power(fp, true);
	if (rc) {
		FP_LOG_ERROR("failed to fp_enable_power\n");
		goto err_power_enable;
	}

	fp_reset(fp);

	setup_timer(&(fp->int_desc.timer), fp_interrupt_timer_routine,
		(unsigned long)&(fp->int_desc));

	/*
	 * If we can allocate a minor number, hook up this device.
	 * Reusing minors is fine so long as udev or mdev is working.
	 */
	mutex_lock(&device_list_lock);
	minor = find_first_zero_bit(minors, N_PLATFORM_MINORS);
	if (minor < N_PLATFORM_MINORS) {
		struct device *dev = NULL;
		fp->devt = MKDEV(FP_PLATFORM_MAJOR, minor);
		dev = device_create(fp_class, &pdev->dev, fp->devt,
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

	rc = fp_init_input(fp);
	if (rc) {
		FP_LOG_ERROR("failed to fp_init_input\n");
		goto err_input_init;
	}

	rc = fp_interrupt_init(&(fp->int_desc));

	wake_lock_init(&fp->fp_wakelock_timeout.lock, WAKE_LOCK_SUSPEND, "fp_wakelock_timeout");

	fp_param_init(fp);

#ifdef CONFIG_FB
	fp_setup_fb_notifier(fp);
#endif

    FP_LOG_INFO("success\n");
	return 0;

err_input_init:
err_sys_init:
err_alloc_minor:
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

static int fp_remove(struct platform_device *pdev)	
{
	struct fp_data *fp = platform_get_drvdata(pdev);

	FP_LOG_DEBUG("start\n");

	/* make sure ops on existing fds can abort cleanly */
	spin_lock_irq(&fp->platform_lock);
	fp->pdev = NULL;
	platform_set_drvdata(pdev, NULL);
	spin_unlock_irq(&fp->platform_lock);

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

#ifdef CONFIG_FB
static int fp_fb_notifier_callback(struct notifier_block *self,
	unsigned long event, void *data)
{
	struct fp_data *fp = container_of(self, struct fp_data, fb_notifier);
	struct fb_event *evdata = data;
	int *blank = NULL;

	FP_LOG_DEBUG("event = %lu\n", event);

	if (evdata && evdata->data && event == FB_EVENT_BLANK) {
		blank = evdata->data;
		if (*blank == FB_BLANK_UNBLANK) {
			FP_LOG_INFO("FB_BLANK_UNBLANK\n");
			if (fp->wake_up == true) {
				fp->int_desc.interrupt_state &= ~INTERRUPT_STATE_SEND_KEY;
			}
		} else if (*blank == FB_BLANK_POWERDOWN) {
		    FP_LOG_INFO("FB_BLANK_POWERDOWN\n");
			if (fp->wake_up == true) {
				fp->int_desc.interrupt_state |= INTERRUPT_STATE_SEND_KEY;
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

static int fp_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct fp_data *fp = platform_get_drvdata(pdev);

    FP_LOG_INFO("start\n");

	if (fp->wake_up == true) {
		fp_irq_wake_op(fp->int_desc.irq, FP_INT_ENABLE);
	} else {
		fp_irq_op(fp->int_desc.irq, FP_INT_DISABLE);
	}

    FP_LOG_INFO("end\n");

    return 0 ;
}

static int fp_resume(struct platform_device *pdev) 	
 {
	struct fp_data *fp = platform_get_drvdata(pdev);
 
	FP_LOG_INFO("start\n");

	if (fp->wake_up == true) {
		fp_irq_wake_op(fp->int_desc.irq, FP_INT_DISABLE);
	} else {
		fp_irq_op(fp->int_desc.irq, FP_INT_ENABLE);
	}

	FP_LOG_INFO("end\n");

     return 0;
 }

static struct of_device_id of_fp_device_idtable[] = {
	{.compatible = "egis,et310",},
	{}
};

static struct platform_driver fp_platform_driver = {
	.driver = {
		.name  = "et310",
		.owner = THIS_MODULE,
		.of_match_table = of_fp_device_idtable,
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
	char pcb_version[12] = { 0 };
	ztemt_get_hw_pcb_version(pcb_version);
	if (strcmp(pcb_version,"MB_E") >= 0)
		if (strcmp(ztemt_config_version, ztemt_config_version_A))
			return -1;
#endif

	FP_LOG_DEBUG("start\n");

	/*
	 * Claim our 256 reserved device numbers. Then register a class
	 * that will key udev/mdev to add/remove /dev nodes.  Last, register
	 * the driver which manages those device numbers.
	 */
	BUILD_BUG_ON(N_PLATFORM_MINORS > 256);

	status = register_chrdev(FP_PLATFORM_MAJOR, "spi", &fp_fops);
	if (status < 0) {
		FP_LOG_ERROR("failed to register chrdev = %d\n", status);
		return status;
	}

	fp_class = class_create(THIS_MODULE, "fp");
	if (IS_ERR(fp_class)) {
		FP_LOG_ERROR("failed to create class\n");
		unregister_chrdev(FP_PLATFORM_MAJOR, "fp");
		return PTR_ERR(fp_class);
	}

	status = platform_driver_register(&fp_platform_driver);
	if (status < 0) {
		FP_LOG_ERROR("failed to register platform driver = %d\n", status);
		class_destroy(fp_class);
		unregister_chrdev(FP_PLATFORM_MAJOR, "fp");
	}

	return status;
}
module_init(fp_init);

static void __exit fp_exit(void)
{
	FP_LOG_INFO("%s\n", __func__);

	gpio_free(fp_global->int_desc.irq_gpio);
	platform_driver_unregister(&fp_platform_driver);
	class_destroy(fp_class);
	unregister_chrdev(FP_PLATFORM_MAJOR, "fp");
}
module_exit(fp_exit);

MODULE_AUTHOR("nubia@zte.com.cn");
MODULE_DESCRIPTION("et310 platform driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:et310");
