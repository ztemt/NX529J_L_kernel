#ifndef __ET310__
#define __ET310__

#include "et310Def.h"
#include "et310-log.h"
#include "et310-spi.h"

#define CALIBRATION_INFO_NUM 11

// et310 Sensor Width/Height
#define FPS_IMG_WIDTH			144
#define FPS_IMG_HEIGHT			64

int fp_set_scroll_detect_region(void);
int fp_set_getkey_detect_region(void);
int fp_fetch_image(unsigned char *pData, int width, int height);
int fp_set_detect_mode(void);
void fp_set_sensor_mode(void);
int fp_set_poweroff_mode(void);
#endif
