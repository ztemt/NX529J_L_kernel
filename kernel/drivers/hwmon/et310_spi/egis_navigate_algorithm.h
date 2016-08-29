#ifndef _NAVIGATION_AGRITHM_H_
#define _NAVIGATION_AGRITHM_H_

#include "scroll.h"

unsigned int EuclideanDistance(unsigned char *raw_data_1,
        int raw_data_1_width,
        unsigned char *raw_data_2,
        int width,
        int height,
        int test_width);

bool CalcNavOffset(unsigned char *ref,
	unsigned char* test,
	int w,
	int h,
	int *dx,
	int *dy,
	int max_diff);
unsigned int cal_diff(unsigned char *array1,
	unsigned char *array2,
	int start_index,
	int len);

#endif
