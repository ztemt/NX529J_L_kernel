/*
 * egis navigate algorithm
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
#include "egis_navigate_algorithm.h"

/*------------------------ function implementation --------------------------*/
unsigned int EuclideanDistance(unsigned char *raw_data_1,
        int raw_data_1_width,
        unsigned char *raw_data_2,
        int raw_data_2_width,
        int test_height,
        int test_width)
{
    int x = 0, i = 0;
    unsigned int diff = 0;
    int d = 0;
    for (i = 0; i < test_height; i++, raw_data_2 += raw_data_2_width, \
		raw_data_1 += raw_data_1_width) {
        x = 0;
        for (x = 0; x < test_width; x++) {
            d = raw_data_2[x] - raw_data_1[x];
			diff += d * d;
        }
    }
    return diff;
}

bool CalcNavOffset(unsigned char *ref, unsigned char* test, int w, int h,
	int *dx, int *dy, int max_diff)
{
	int x = 0, y = 0;
	bool ret = false;

	ref += OFFY*FPS_IMG_WIDTH + OFFX;
	test += (OFFY - MAX_NAV_Y) * FPS_IMG_WIDTH + OFFX - MAX_NAV_X;

	for (y = -MAX_NAV_Y; y <= MAX_NAV_Y; y++, test += w) {
		for (x = -MAX_NAV_X; x <= MAX_NAV_X; x++, test++) {
			int diff = EuclideanDistance(ref, w, test, w, NAV_HEIGHT, NAV_WIDTH);

			if (diff < max_diff) {
				max_diff = diff;
				*dx = x;
				*dy = y;
				ret = true;
			}
		}
		test -= (MAX_NAV_X * 2 + 1); //carriage return
	}

	return ret;
}

unsigned int cal_diff(unsigned char *array1, unsigned char *array2,
	int start_index, int len)
{
	unsigned int diff = 0;
	int i = 0, tmp = 0;

	for (i = 0; i < len; i++) {
		tmp = array1[start_index + i] - array2[start_index + i];
		diff += (tmp * tmp);
	}

	return diff;
}
