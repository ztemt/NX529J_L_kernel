#ifndef _FP_LINUX_DIRVER_H_
#define _FP_LINUX_DIRVER_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/spi/spi.h>
#include <linux/regulator/consumer.h>
#include <linux/of_gpio.h>
#include <linux/input.h>
#include <linux/wakelock.h>
#include <linux/pinctrl/consumer.h>
#include <linux/clk.h>
#include <soc/qcom/scm.h>
#ifdef CONFIG_FB
#include <linux/notifier.h>
#include <linux/fb.h>
#endif

#include "et310_log.h"

/* ------------------------- General Macro Definition ------------------------*/
#define FP_PLATFORM_MAJOR           154
#define N_PLATFORM_MINORS			32

//Interrupt description
#define FP_INT_DETECTION_PERIOD     10
#define FP_DETECTION_THRESHOLD	    10

#define FP_INT_ENABLE               1
#define FP_INT_DISABLE              0

/* ------------------------- Opcode ---------------------------------*/
#define FP_REGISTER_READ			0x01
#define FP_REGISTER_WRITE			0x02
#define FP_GET_ONE_IMG				0x03
#define FP_SENSOR_RESET				0x04
#define FP_POWER_ONOFF				0x05
#define FP_SET_SPI_CLOCK			0x06
#define FP_RESET_SET				0x07

/* trigger signal initial routine*/
#define INT_TRIGGER_INIT			0xA4
/* trigger signal close routine*/
#define INT_TRIGGER_CLOSE			0xA5
/* read trigger status*/
#define INT_TRIGGER_READ			0xA6
/* polling trigger status*/
#define INT_TRIGGER_POLLING			0xA7
/* polling abort*/
#define INT_TRIGGER_ABORT			0xA8

#define FP_SET_SCROLL_CALI_DATA		0xC0
#define FP_ENABLE_SCROLL            0xC1
#define FP_DISABLE_SCROLL           0xC2
#define FP_INT_DETECT_STATE         0xC3
#define FP_INT_SCROLL_STATE         0xC4
#define FP_INT_SEND_KEY_STATE       0xC5

#define FP_ENABLE_TZ_SPI            0xD0
#define FP_DISABLE_TZ_SPI           0xD1

#define INTERRUPT_STATE_DETECT      0
#define INTERRUPT_STATE_SCROLL      1
#define INTERRUPT_STATE_SEND_KEY    2 //(1<<1)
#define INTERRUPT_STATE_GETKEY      4 //(1<<2)

/* ------------------------- Structure ------------------------------*/
struct interrupt_desc {
	int reset_gpio;
	int irq_gpio;
	int irq;

	struct timer_list timer;

	int interrupt_state;
	int interrupt_key_code;

	int detect_period;
	int detect_threshold;
	int int_count;
	bool finger_on;			
};

struct egis_ioc_transfer {
	u8 *tx_buf;
	u8 *rx_buf;

	__u32 len;
	__u32 speed_hz;

	__u16 delay_usecs;
	__u8 bits_per_word;
	__u8 cs_change;
	__u8 opcode;
	__u8 pad[3];
};

#define EGIS_IOC_MAGIC			'k'
#define EGIS_MSGSIZE(N) \
	((((N)*(sizeof(struct egis_ioc_transfer))) < (1 << _IOC_SIZEBITS)) \
		? ((N)*(sizeof(struct egis_ioc_transfer))) : 0)
#define EGIS_IOC_MESSAGE(N) _IOW(EGIS_IOC_MAGIC, 0, char[EGIS_MSGSIZE(N)])

struct fp_pinctrl_info {
	struct pinctrl *pinctrl; 
	struct pinctrl_state *gpio_state_active;
	struct pinctrl_state *gpio_state_suspend;
};

struct fp_wake_lock{
    struct wake_lock lock;
    bool   locked;
    char   *name;
};

struct fp_data {
	struct platform_device *pdev;

	dev_t devt;
	spinlock_t platform_lock;
	struct list_head device_entry;

	struct fp_pinctrl_info fp_pctrl;

	struct input_dev *key_input_dev;

#ifdef CONFIG_FB
	struct notifier_block fb_notifier;
#endif

	/* buffer is NULL unless this device is open (users > 0) */
	struct mutex scroll_lock;
	unsigned users;

	struct fp_wake_lock fp_wakelock_timeout;

	bool wake_up;

	struct interrupt_desc int_desc;
};

static LIST_HEAD(device_list);
static DEFINE_MUTEX(device_list_lock);

static DECLARE_WAIT_QUEUE_HEAD(interrupt_waitq);

/* ------------------------- Interrupt ------------------------------*/
void fp_irq_op(int irq, int enable);
void fp_irq_wake_op(int irq, int enable);
void fp_wakelock_ops(struct fp_wake_lock *wakelock, bool enable);

#endif
