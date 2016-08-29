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

#include "et310-log.h"
#include "et310.h"
#include "scroll.h"

/* ------------------------- General Macro Definition ------------------------*/
#define FPC_BTP_SPI_CLOCK_SPEED		 9600000
//#define FPC_BTP_SPI_CLOCK_SPEED		6000000

#define EGIS_MASS_READ_TRANSMITION_SIZE   2304
#define EGIS_MASS_READ_SEGMENT_COUNT 10

#define FP_MAJOR					154
#define N_SPI_MINORS				32

//Interrupt description
#define FP_INT_DETECTION_PERIOD     10
#define FP_DETECTION_THRESHOLD	    10

#define FP_INT_ENABLE               1
#define FP_INT_DISABLE              0

#define FP_ADDRESS_0				0x00
#define FP_WRITE_ADDRESS			0xAC
#define FP_READ_DATA				0xAF
#define FP_WRITE_DATA				0xAE

#define FP_EEPROM_WREN_OP			0x06
#define FP_EEPROM_WRDI_OP			0x04
#define FP_EEPROM_RDSR_OP			0x05
#define FP_EEPROM_WRSR_OP			0x01
#define FP_EEPROM_READ_OP			0x03
#define FP_EEPROM_WRITE_OP			0x02

/* ------------------------- Register Definition ------------------------*/
/*
 * Sensor Registers
 */
#define FDATA_FP_ADDR				0x00
#define FSTATUS_FP_ADDR				0x01

/*
 * Detect Define
 */
#define FRAME_READY_MASK			0x01

/* ------------------------- Opcode ---------------------------------*/
#define FP_REGISTER_READ			0x01
#define FP_REGISTER_WRITE			0x02
#define FP_GET_ONE_IMG				0x03
#define FP_SENSOR_RESET				0x04
#define FP_POWER_ONOFF				0x05
#define FP_SET_SPI_CLOCK			0x06
#define FP_RESET_SET				0x07

#define FP_EEPROM_WREN				0x90
#define FP_EEPROM_WRDI				0x91
#define FP_EEPROM_RDSR				0x92
#define FP_EEPROM_WRSR				0x93
#define FP_EEPROM_READ				0x94
#define FP_EEPROM_WRITE				0x95

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

/* interrupt polling */
/*unsigned int fps_interrupt_poll(
	struct file *file,
	struct poll_table_struct *wait
);*/

/* ------------------------- Structure ------------------------------*/
struct interrupt_desc {
	//int gpio;
	//int number;
	//char *name;
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

struct scroll_desc {
	int jitter_limit;
	int jitter_threshold;
	//int FingerOnThreshold;
	//int FingerOnThresholdLoose;
	int no_move_th;
	unsigned char FingerOnPartial;
};

struct calibration_info
{
	unsigned char dc;
	unsigned char gain;
	unsigned int min_bkg_intensity;
	unsigned int bkg_width;
	unsigned int bkg_height;
	unsigned int fingerOnThreshold;
	unsigned int fingerOnThresholdLoose;
	unsigned int fingerOnStableThreshold;
	unsigned char interruptThrehold;
	unsigned char dc_detect;
	unsigned char gain_detect;
	unsigned char* bkg_intensity;
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
	// used for tz spi  added by nubia
	struct pinctrl_state *spi_default;
	struct pinctrl_state *spi_sleep;
    // nubia add end
};

struct fp_wake_lock{
    struct wake_lock lock;
    bool   locked;
    char   *name;
};

struct fp_data {
	dev_t devt;
	spinlock_t spi_lock;
	struct spi_device *spi;
	struct list_head device_entry;

	struct regulator *fp_power_vdd;
	struct fp_pinctrl_info fp_pctrl;

	struct input_dev *key_input_dev;

#ifdef CONFIG_FB
	struct notifier_block fb_notifier;
#endif

	struct workqueue_struct *scroll_wq;
	struct work_struct scroll_work;

	struct workqueue_struct *getkey_wq;
	struct work_struct getkey_work;

	/* buffer is NULL unless this device is open (users > 0) */
	//struct mutex buf_lock;
	struct mutex scroll_lock;
	struct mutex getkey_lock;
	unsigned users;
	//u8 *buffer;

	//int reset_gpio;
	//int irq_gpio;
	//int	irq;

	struct fp_wake_lock fp_wakelock;
	struct fp_wake_lock fp_wakelock_timeout;

	bool scroll_enable;
	bool getkey_enable;
	bool tz_enable;
	bool wake_up;

    // add for TZ spi
    u32 qup_id;
    struct clk *core_clk;
    struct clk *iface_clk;
    // nubia add end

	struct interrupt_desc int_desc;
	struct scroll_desc scroll_param;
	struct calibration_info cali_info;
};

static LIST_HEAD(device_list);
static DEFINE_MUTEX(device_list_lock);

static DECLARE_WAIT_QUEUE_HEAD(interrupt_waitq);

/* ------------------------- Interrupt ------------------------------*/
void fp_irq_op(int irq, int enable);
void fp_irq_wake_op(int irq, int enable);
void fp_wakelock_ops(struct fp_wake_lock *wakelock, bool enable);

/* ------------------------- Data Transfer --------------------------*/
int fp_io_read_register(struct fp_data *fp, u8 *addr, u8 *buf);
int fp_io_write_register(struct fp_data *fp, u8 *buf);
int fp_io_get_one_image(struct fp_data *fp, u8 *buf, u8 *image_buf);
int fp_read_register(struct fp_data *fp, u8 addr, u8 *buf);
int fp_mass_read(struct fp_data *fp, u8 addr, u8 *buf, int read_len);

int fp_write_register_external(u8 addr, u8 data);
int fp_read_register_external(u8 addr, u8 *buf);
int fp_get_one_image_external(u8 *image_buf, int width, int height);
int fp_mass_read_external(u8 addr, u8 *buf, int read_len);
#endif
