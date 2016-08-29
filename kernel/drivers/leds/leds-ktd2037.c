/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <asm/errno.h> 
#include <linux/leds.h>
#include <linux/ctype.h>
#define KTD_I2C_NAME			"ktd2037"


#ifdef CONFIG_ZTEMT_PRINTK_LED
#define  printk_led(fmt, args...) printk(KERN_ERR"ZTEMT:"fmt,##args)
#else
#define  printk_led(fmt, args...) do{}while(0)
#endif

struct ktd2037_led {
	struct i2c_client *client;
	struct led_classdev cdev;
	struct mutex mutex;
	int num_leds;
	int id;    
    int fadein_time;
    int hold_on_time;
    int hold_off_time;
    int min_grade;
    int max_grade;
    int ztemt_channel;
    int ztemt_effect;
    int main_channel;
    int second_channel;
    int third_channel;
    int controled_chip_channel; /* 0: d1; 1:d2;2:d3*/
	u8  reg4_backup;
};

enum led_control_effect {	
    LED_MODE_CLOSED = 0,
    LED_MODE_CONSTANT_ON,
    LED_MODE_OFF,
    LED_MODE_AUTO_BLINK,
    LED_MODE_FADE_ON,
    LED_MODE_FADE_OFF,
    LED_MODE_ONCE_BLINK,	
};

#define GRADE_PARAM_LEN  20
#define CONST_MIN_GRADE  10
#define CONST_MAX_GRADE  200
#define FADE_PARAM_LEN   20
#define MAX_SCALE_FOR_CURRENT 70

/*registor name define  */
#define RESET_CONTROL  0x00
#define FLASH_PERIOD   0x01
#define FLASH_ON_TIME1 0x02
#define FLASH_ON_TIME2 0x03
#define CHANNEL_CONTROL 0x04
#define RAMP_RATE  0x05
#define LED1_Iout  0x06
#define LED2_Iout  0X07
#define LED3_Iout  0x08
#define AUTO_BLINKQ 0x09
#define BREATH_ONCE_TIME 0x44
#define CHANNEL_BIT_CONTROL 2
#define CONSTANT_FLASH_PERIOD 3
#define DUAL_FADE_IN_TIME   2
#define PWM_ON_TIME_RATE    0x32


enum ztemt_led_channel{
 ZTEMT_MIAN_LED_CHANNEL = 16,
 ZTEMT_SECOND_LED_CHANNEL = 8,
 ZTEMT_THIRD_LED_CHANNEL = 32,
};

static int ktd2037_write(struct ktd2037_led *led, u8 reg, u8 val)
{
    int ret = 0;
    
	ret = i2c_smbus_write_byte_data(led->client, reg, val);
   
    printk_led("ktd2037_write reg = %x,val = %x\n",reg,val);

    if (ret < 0) {
        dev_err(&led->client->dev,
               "ktd2037_write reg fail, ret = %d\n",
               ret);
    } 
    return ret;
}
static void ktd20xx_chip_channel_map(struct ktd2037_led *led)
{
    if(led->ztemt_channel == ZTEMT_MIAN_LED_CHANNEL)
        led->controled_chip_channel = led->main_channel;
    if(led->ztemt_channel == ZTEMT_SECOND_LED_CHANNEL)
        led->controled_chip_channel = led->second_channel;
    if(led->ztemt_channel == ZTEMT_THIRD_LED_CHANNEL)
        led->controled_chip_channel = led->third_channel;
}

static ssize_t fade_parameter_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	char *after, *parm2,*parm3;
    
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ktd2037_led *led =
			container_of(led_cdev, struct ktd2037_led, cdev);
	
	led->fadein_time = (int) simple_strtoul(buf, &after, 10);

	mutex_lock(&led->mutex);

	while(isspace(*after))
		after++;
	parm2 = after;
	led->hold_on_time = (int) simple_strtoul(parm2, &after, 10);

	while(isspace(*after))
		after++;
	parm3 = after;
    
	led->hold_off_time = (int) simple_strtoul(parm3, &after, 10);	

    printk_led("%s : %d : fade_time=%d ,on_time=%d , off_time=%d\n",
		__func__,__LINE__,led->fadein_time,led->hold_on_time,led->hold_off_time);

    mutex_unlock(&led->mutex);
    
	return count;
}

static ssize_t fade_parameter_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ktd2037_led *led =
			container_of(led_cdev, struct ktd2037_led, cdev);

	return snprintf(buf, FADE_PARAM_LEN, "%4d %4d %4d\n",
			led->fadein_time, led->hold_on_time, led->hold_off_time);
}

static ssize_t grade_parameter_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	char *after, *parm2;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ktd2037_led *led =
			container_of(led_cdev, struct ktd2037_led, cdev);

    led->min_grade=(int) simple_strtoul(buf, &after, 10);

    led->min_grade = (led->min_grade*MAX_SCALE_FOR_CURRENT)/led->cdev.max_brightness;

	mutex_lock(&led->mutex);

	while(isspace(*after))
		after++;
	parm2 = after;
    
    led->max_grade=(int) simple_strtoul(parm2, &after, 10);

    led->max_grade = (led->max_grade*MAX_SCALE_FOR_CURRENT)/led->cdev.max_brightness;
	
	printk_led("%s : %d : min_grade=%d , max_grade=%d\n",
		__func__,__LINE__,led->min_grade,led->max_grade);
	
	mutex_unlock(&led->mutex);
	return count;
}

static ssize_t grade_parameter_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{

	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ktd2037_led *led =
			container_of(led_cdev, struct ktd2037_led, cdev);
		
	return snprintf(buf, GRADE_PARAM_LEN, "%4d %4d\n",led->min_grade,led->max_grade);
}

static ssize_t outn_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	char *after;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ktd2037_led *led =
			container_of(led_cdev, struct ktd2037_led, cdev);

	mutex_lock(&led->mutex);
	led->ztemt_channel = (int) simple_strtoul(buf, &after, 10);
	printk_led("%s : %d : ztemt_channel=%d \n",__func__,__LINE__,led->ztemt_channel);
	mutex_unlock(&led->mutex);
	return count;
}

static ssize_t outn_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ktd2037_led *led =
			container_of(led_cdev, struct ktd2037_led, cdev);

	return sprintf(buf, "%d\n",led->ztemt_channel);	
}
static int ktd20xx_led_powerdown(struct ktd2037_led *led)
{
    int ret = 0;
	
	ret = ktd2037_write(led,RESET_CONTROL,0x07); // reset chip complete
   	
	ret = ktd2037_write(led,AUTO_BLINKQ,0x06); //disable auto blink.
    if (ret < 0){
        return ret;
	}
    
    /*
       *   disable all channel, disable hole chip
       */
    led->reg4_backup = 0x00;
    
	ret = ktd2037_write(led,CHANNEL_CONTROL,0x00); 

    return ret;
}

static int ktd20xx_led_mode_off(struct ktd2037_led *led)
{
    int ret = 0;

    led->reg4_backup &= ~(0x03 << (led->controled_chip_channel * 2)) ;  // D1 OFF      

    /*
         *  enable or disable channel and device 
        */
    ret = ktd2037_write(led,CHANNEL_CONTROL,led->reg4_backup);
    
    return ret;
}

static int  ktd20xx_mode_constant_on(struct ktd2037_led *led)
{
    int ret = 0;

    led->reg4_backup &= ~(0x03 << (led->controled_chip_channel * 2));  // Dn clear bit
    led->reg4_backup |= (0x01 << (led->controled_chip_channel * 2));  // Dn pwm1  blink  
    led->reg4_backup |= 0x40;  // device enable 

    /* change Dn brightness */
    ret = ktd2037_write(led,(LED1_Iout+led->controled_chip_channel),led->min_grade);
    if (ret < 0){
        return ret;
    }
    
    /*
         * enable selected channel, hole chip
        */
    ret = ktd2037_write(led,CHANNEL_CONTROL,led->reg4_backup);
    
    return ret;
}

static int ktd20xx_led_breath_once_pre_set(struct ktd2037_led *led)

{
   int ret = 0; 
    /*
        *  change pwm scale  1x and set togging mode reg0 [4,3] = 01 
        */
    ret = ktd2037_write(led,RESET_CONTROL,0x08);
    if (ret < 0){
        return ret;
    }
    
    /*
       *  change rise and down time
       */
    ret = ktd2037_write(led,RAMP_RATE,BREATH_ONCE_TIME);
    if (ret < 0){
        return ret;
    }
    
    /*
         * set pwm1/pwm2  period,  when set 0x7f, just one shot. 
        */
    ret = ktd2037_write(led,FLASH_PERIOD,0x7f);
    
    return ret;
}


static int ktd20xx_led_breath_once_trigger(struct ktd2037_led *led)

{
   int ret = 0; 

   /*
         * 2.5% of  one period,  fallin+hold_on
       */
   ret = ktd2037_write(led,FLASH_ON_TIME1,0x08);
   if (ret < 0){
      return ret;
   } 
   
   /*send command "reset digital only", reg0[2-0] = 110*/
   ret = ktd2037_write(led,RESET_CONTROL,0x06|0x08);
   if (ret < 0){
      return ret;
   } 
   
   //  enable d1 channel, enable  chip
   ret = ktd2037_write(led,CHANNEL_CONTROL,led->reg4_backup); 
   if (ret < 0){
       return ret;
   }
   
   /*trigger one shot reg0[4,3] = 00*/
   ret = ktd2037_write(led,RESET_CONTROL,0x00);
  
   return ret;
}


static int ktd20xx_led_breath_once(struct ktd2037_led *led)
{
    int ret = 0;

    ret = ktd20xx_led_breath_once_pre_set(led);
    if (ret < 0)
        return ret;

    if(led->controled_chip_channel != led->main_channel){
        led->reg4_backup &= ~(0x03 << (led->controled_chip_channel * CHANNEL_BIT_CONTROL));  // Dn clear bit
        led->reg4_backup &= ~(0x03 << (led->main_channel * CHANNEL_BIT_CONTROL));  // Dn clear bit
        led->reg4_backup |= (0x02 << (led->controled_chip_channel * CHANNEL_BIT_CONTROL));  // Dn pwm1  blink
    }else {
        led->reg4_backup &= ~(0x03 << (led->controled_chip_channel * CHANNEL_BIT_CONTROL));  // Dn clear bit
        led->reg4_backup |= (0x02 << (led->controled_chip_channel * CHANNEL_BIT_CONTROL));  // Dn pwm1  blink
    }
    led->reg4_backup |= 0x40;  // device enable 

    /* change Dn brightness */
    ret = ktd2037_write(led,(LED1_Iout+led->controled_chip_channel),led->max_grade);
    if (ret < 0)
        return ret;
    
    ret = ktd20xx_led_breath_once_trigger(led);

    return ret;
}

static int ktd20xx_led_auto_blink_pre_set(struct ktd2037_led *led)
{
    int ret = 0;

     /*
         *  change pwm scale for 2x
        */
    ret = ktd2037_write(led,RESET_CONTROL,0x20);   
    if (ret < 0)
        return ret;

    /*
         * set pwm1/pwm2  period,  when set 0xff, just one shot. 
        */
    ret = ktd2037_write(led,FLASH_PERIOD,0x7f&((led->fadein_time*DUAL_FADE_IN_TIME+led->hold_on_time+led->hold_off_time)*CONSTANT_FLASH_PERIOD));
    if (ret < 0)
        return ret;

    /*
         * set rise and fall time for all channel.
        */
    ret = ktd2037_write(led,RAMP_RATE,led->fadein_time << 4 |led->fadein_time); //change pwm scale  2x

    return ret;
}

static int  ktd20xx_led_auto_blink(struct ktd2037_led *led)
{
    int ret = 0;
    
    ret = ktd20xx_led_auto_blink_pre_set(led);
    if(ret < 0)
        return ret;

    led->reg4_backup &= ~(0x03 << (led->controled_chip_channel * 2));  // Dn clear bit
    led->reg4_backup |= (0x02 << (led->controled_chip_channel * 2));  // Dn pwm1  blink  
    led->reg4_backup |= 0x40;  // device enable 

    ret = ktd2037_write(led,(LED1_Iout+led->controled_chip_channel),led->max_grade); 
    if (ret < 0)
       return ret;
     
    /*    set pwm1 percentage of period ,fallin +hold_on time   */        
    ret = ktd2037_write(led,FLASH_ON_TIME1,PWM_ON_TIME_RATE);
    if (ret < 0)
       return ret;
     
     /*  enable select channel, and  enable chip,trigger effect  */
    ret = ktd2037_write(led,CHANNEL_CONTROL,led->reg4_backup); 

    return ret;
}

static int  breath_led_effect_set(struct ktd2037_led *led)
{    
    int ret = 0;

    if(led == NULL)
        return -EINVAL;

    
    ktd20xx_chip_channel_map(led);
    
    switch (led->ztemt_effect){
    case LED_MODE_CLOSED:
	    ret = ktd20xx_led_powerdown(led);
        if (ret < 0){
          dev_err(&led->client->dev,
                "led powerdown fail!,ret = %d\n", ret);  
	    }
	    break;
    case LED_MODE_OFF:
        ret = ktd20xx_led_mode_off(led);
        if (ret < 0){
          dev_err(&led->client->dev,
                "led mode off fail,ret = %d\n", ret);    
	    }
        break;
    case LED_MODE_CONSTANT_ON:
        
		 /*
		    *  when led constant on, keep five multiple of min grade
		   */
        ret = ktd20xx_mode_constant_on(led);
        if (ret < 0){
            dev_err(&led->client->dev,
                "led mode constant on fail,ret = %d\n", ret);
	      }  
        break;
    case LED_MODE_ONCE_BLINK:
        ret = ktd20xx_led_breath_once(led);
        if (ret < 0){
            dev_err(&led->client->dev,
                "led mode blink once fail,ret = %d\n", ret);
	    }  
        break;
    case LED_MODE_AUTO_BLINK:  
       ret = ktd20xx_led_auto_blink(led);
       if (ret < 0){
           dev_err(&led->client->dev,
               "led mode auto blink fail,ret = %d\n", ret);
       }
       break;
    default:
        return -EINVAL;     
    }
   
    return ret;
}


static ssize_t qpnp_led_effect_store(struct device *dev,
	                     struct device_attribute *attr,
	                      const char *buf, size_t count)	
	
{
    unsigned long value = 0;
    int ret = 0;

	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ktd2037_led *ktd_led =
			container_of(led_cdev, struct ktd2037_led, cdev);

    if (NULL == buf) 
        return -EINVAL;
    
	ret = strict_strtoul(buf, 0, &value);
	if(ret < 0){
        dev_err(&ktd_led->client->dev,
                "strict_strtoul fail,ret = %d\n", ret);
        return ret; 
     }

	ktd_led->ztemt_effect = value;
	mutex_lock(&ktd_led->mutex);
		
	if(ktd_led->min_grade < 0){
       ktd_led->min_grade = 0;
    }else if(ktd_led->min_grade > 255){
	   ktd_led->min_grade = 255;
    }	
    if(ktd_led->max_grade < 0){
       ktd_led->max_grade = 0;
    }else if(ktd_led->max_grade > 255){
	   ktd_led->max_grade = 255;
    }	

    
    breath_led_effect_set(ktd_led);

	mutex_unlock(&ktd_led->mutex);
	return count;
}



static ssize_t qpnp_led_effect_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ktd2037_led *ktd_led =
			container_of(led_cdev, struct ktd2037_led, cdev);

	return sprintf(buf, "%d\n",ktd_led->ztemt_effect);	
}


static DEVICE_ATTR(blink_mode, 0664, qpnp_led_effect_show, qpnp_led_effect_store);
static DEVICE_ATTR(fade_parameter, 0664, fade_parameter_show, fade_parameter_store);
static DEVICE_ATTR(grade_parameter, 0664, grade_parameter_show, grade_parameter_store);
static DEVICE_ATTR(outn, 0664, outn_show, outn_store);


static struct attribute *led_func_attrs[] = {
    &dev_attr_blink_mode.attr,
	&dev_attr_fade_parameter.attr,
	&dev_attr_grade_parameter.attr,
	&dev_attr_outn.attr,
	NULL
};

static const struct attribute_group led_func_attr_group = {
	.attrs = led_func_attrs,
};

static int ktd20xx_led_parse_dt(struct ktd2037_led *led,
				struct device_node *node)
{
	int ret = 0;
    ret = of_property_read_string(node, "ktd2037,name",
        &led->cdev.name);
    if (ret < 0) {
       dev_err(&led->client->dev,
        "Failure reading led name, rc = %d\n", ret);
    }

    ret = of_property_read_u32(node, "ktd2037,max-brightness",
			&led->cdev.max_brightness);
    if (ret < 0) {
	    dev_err(&led->client->dev,
				"Failure reading max-brightness, rc = %d\n",
				ret);
	}
    
    ret = of_property_read_u32(node, "ktd2037,main_channel",
            &led->main_channel);
    
    if (ret < 0) {
        dev_err(&led->client->dev,
                    "Failure reading main_channel, rc = %d\n",
                    ret);
    }
    ret = of_property_read_u32(node, "ktd2037,second_channel",
            &led->second_channel);
    
    if (ret < 0) {
        dev_err(&led->client->dev,
                    "Failure reading sencond_channel, rc = %d\n",
                    ret);
    } 
    ret = of_property_read_u32(node, "ktd2037,third_channel",
            &led->third_channel);
    
    if (ret < 0) {
        dev_err(&led->client->dev,
                    "Failure reading sencond_channel, rc = %d\n",
                    ret);
    }
    return ret;
}

static int ktd20xx_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    struct ktd2037_led *ktd2037_led;
	struct device_node *node;
	int ret = 0;

	node = client->dev.of_node;
	if (node == NULL)
		return -EINVAL;

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev,
				"%s: check_functionality failed.", __func__);
		return -ENODEV;
	}

	ktd2037_led = devm_kzalloc(&client->dev,
			sizeof(struct ktd2037_led), GFP_KERNEL);
	if (!ktd2037_led) {
		dev_err(&client->dev, "Unable to allocate memory\n");
		return -ENOMEM;
	}
    
	ktd2037_led->client = client;


    ret = ktd20xx_led_parse_dt(ktd2037_led,node);
    if(ret < 0){
	    dev_err(&client->dev, "Unable to parse device tree\n");
        goto parse_dt_fail;
     }
    
	mutex_init(&ktd2037_led->mutex);

    /* turn off led when first start ktd
        set reg9[0]=0 to disable autoBQ,reg9[2:1] should always written 11
    */
    ret = ktd2037_write(ktd2037_led,AUTO_BLINKQ,0x06);
	/*
          set reg4 = 0 disable all channel (bit 0-5), and shut down i2c (bit 6)
	*/
    ret = ktd2037_write(ktd2037_led,CHANNEL_CONTROL,0x00);
    if(ret < 0){
         dev_err(&client->dev, "can't write i2c data \n");
         goto write_data_fail;
    }
	
	ktd2037_led->reg4_backup = 0; 

	i2c_set_clientdata(client, ktd2037_led);


    ktd2037_led->cdev.brightness_set = NULL;
    
    ret = led_classdev_register(&ktd2037_led->client->dev, &ktd2037_led->cdev);
    if (ret) {
        dev_err(&ktd2037_led->client->dev,
            "unable to register led !!!\n");
        goto registor_fail;
    }
    
    ret= sysfs_create_group(&ktd2037_led->cdev.dev->kobj,
                &led_func_attr_group);
    if (ret) {
            dev_err(&client->dev, "led sysfs rc: %d\n", ret);
            goto free_class;
    }

    printk(KERN_ERR"ktd20xx probe sucess!!!");
    
   return ret;
   
free_class:
    led_classdev_unregister(&ktd2037_led->cdev);
registor_fail:
write_data_fail:    
parse_dt_fail:
    devm_kfree(&client->dev, ktd2037_led);
    ktd2037_led = NULL;
    printk(KERN_ERR"ktd20xx probe fail !!!");
	return ret;
}

static int ktd20xx_remove(struct i2c_client *client)
{
    int ret = 0;
    struct ktd2037_led *led = i2c_get_clientdata(client);

	ret = ktd2037_write(led,RESET_CONTROL,0x07); // reset chip complete

	if(ret < 0){
        dev_err(&client->dev,"write registor fail\n");
	}
    
	i2c_set_clientdata(client, NULL);
	sysfs_remove_group(&led->cdev.dev->kobj, &led_func_attr_group);
    led_classdev_unregister(&led->cdev);
    devm_kfree(&client->dev, led);
    led = NULL;
	return 0;
}

static void ktd20xx_shutdown(struct i2c_client *client)
{
    int ret = 0;
    struct ktd2037_led *led = i2c_get_clientdata(client);
	ret = ktd2037_write(led,RESET_CONTROL,0x07); // reset chip complete
 
}

static int ktd20xx_suspend(struct device *dev)
{
	printk_led("suspended\n");
	return 0;
}

static int ktd20xx_resume(struct device *dev)
{
	printk_led("resumed\n");
	return 0;
}


static const struct dev_pm_ops ktd20xx_pm_ops = {
	.suspend	= ktd20xx_suspend,
	.resume		= ktd20xx_resume,
};


static const struct i2c_device_id ktd20xx_id[] = {
	{KTD_I2C_NAME, 0},
	{ }
};

static struct of_device_id ktd20xx_match_table[] = {
        { .compatible = "ktd,ktd2037",},
        { },
};

static struct i2c_driver ktd20xx_driver = {
	.probe = ktd20xx_probe,
	.remove = ktd20xx_remove,
	.shutdown   = ktd20xx_shutdown,
	.id_table = ktd20xx_id,
	.driver = {
		.name	= KTD_I2C_NAME,
		.owner = THIS_MODULE,
		.of_match_table = ktd20xx_match_table,	
		.pm		= &ktd20xx_pm_ops,
	},
};

module_i2c_driver(ktd20xx_driver);

MODULE_DESCRIPTION("ktd2037 LED driver");
MODULE_LICENSE("GPL V2");
MODULE_AUTHOR("xiaojun xue <xue.xiaojun@zte.com.cn>");
