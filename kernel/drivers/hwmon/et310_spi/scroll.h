#ifndef __SCROLLING_PARAM_H_
#define __SCROLLING_PARAM_H_

#include "et310.h"
#include "et310Def.h"
#include "et310-log.h"
#include "et310-spi.h"
#include "egis_navigate_algorithm.h"

#define INTERRUPT_STATE_DETECT      0
#define INTERRUPT_STATE_SCROLL      1
#define INTERRUPT_STATE_SEND_KEY    2 //(1<<1)
#define INTERRUPT_STATE_GETKEY      4 //(1<<2)

#define NAV_WIDTH                   90
#define NAV_HEIGHT                  5

#define SCROLLING_WIDTH	            144
#define SCROLLING_HEIGHT            64

#define MAX_NAV_Y                   1
#define MAX_NAV_X                   25

#define FPS_IMG_WIDTH	            144
#define FPS_IMG_HEIGHT	            64

#define OFFX ((FPS_IMG_WIDTH - NAV_WIDTH) / 2)
#define OFFY ((FPS_IMG_HEIGHT - NAV_HEIGHT) / 2)

#define CHECK_BLOCK_SIZE            16

#ifdef ET300_EV_TOOL 
	#define BLOCK_OFFSET            16
#else
	#define BLOCK_OFFSET            0
#endif

void fp_scrolling(void);
int fp_getkey(void);

#endif
