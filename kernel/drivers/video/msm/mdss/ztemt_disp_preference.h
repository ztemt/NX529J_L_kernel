#ifndef _ZTEMT_DISP_PREFERENCE_
#define _ZTEMT_DISP_PREFERENCE_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/device.h>
#include <linux/timer.h>
#include <linux/err.h>
#include <linux/ctype.h>
#include "mdss_mdp.h"
#include "mdss_dsi.h"
#include "mdss_mdp_pp.h"

#include <linux/hrtimer.h>

/* ------------------------- General Macro Definition ------------------------*/
#define ZTEMT_DISP_SATURATION_CMD_COUNT  1
#define ZTEMT_DISP_COLORTMP_DEBUG        1

enum {
	SATURATION_OFF = 23,
	SATURATION_SOFT,
	SATURATION_STD,
	SATURATION_GLOW
};

enum {
	COLORTMP_WARM = 24,
	COLORTMP_NORMAL,
	COLORTMP_COOL
};
enum {
	CABC_OFF = 23,
	CABC_LEVER1 ,
	CABC_LEVER2 ,
	CABC_LEVER3
};


#define ZTEMT_DISP_LOG_TAG "ZtemtDisp"
#define ZTEMT_DISP_LOG_ON
//#define ZTEMT_DISP_DEBUG_ON

#ifdef  ZTEMT_DISP_LOG_ON
#define ZTEMT_DISP_ERROR(fmt, args...) printk(KERN_ERR "[%s] [%s: %d] "  fmt, \
	ZTEMT_DISP_LOG_TAG, __FUNCTION__, __LINE__, ##args)
#define ZTEMT_DISP_INFO(fmt, args...) printk(KERN_ERR "[%s] [%s: %d] "  fmt, \
	ZTEMT_DISP_LOG_TAG, __FUNCTION__, __LINE__, ##args)

    #ifdef  ZTEMT_DISP_DEBUG_ON
#define  ZTEMT_DISP_DEBUG(fmt, args...) printk(KERN_DEBUG "[%s] [%s: %d] "  fmt, \
	ZTEMT_DISP_LOG_TAG, __FUNCTION__, __LINE__, ##args)
    #else
#define ZTEMT_DISP_DEBUG(fmt, args...)
    #endif
#else
#define ZTEMT_DISP_ERROR(fmt, args...)
#define ZTEMT_DISP_INFO(fmt, args...)
#define ZTEMT_DISP_DEBUG(fmt, args...)
#endif

/* ----------------------------- Structure ----------------------------------*/
struct ztemt_disp_type{
  int en_cabc;
  int en_saturation;
  int en_colortmp;
  unsigned int cabc;
  unsigned int saturation;
  unsigned int colortmp;
  int shield;
};

/* ------------------------- Function Declaration ---------------------------*/
void ztemt_set_dsi_ctrl(struct mdss_dsi_ctrl_pdata * ctrl);
void ztemt_disp_preference(void);

int ztemt_get_shield(void);
#endif
