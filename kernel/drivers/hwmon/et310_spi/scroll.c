/*
 * scroll algorithm
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
#include "scroll.h"

/*------------------------------- variables ---------------------------------*/
int g_has_finger[6] = { 0 };

extern struct fp_data *fp_global;
extern u8 fp_bkg_intensity[FPS_IMG_WIDTH * FPS_IMG_HEIGHT];

/*------------------------ function implementation --------------------------*/
u8 fp_finger_on(u8 *intensity, int width, int height, u8 loose_check)
{
	int score = 0;
	unsigned int diff[6] = { 0 };
	int has_finger[6] = { 0 };
	unsigned int threshold = (loose_check ?
			fp_global->cali_info.fingerOnThresholdLoose :
			fp_global->cali_info.fingerOnThresholdLoose);

	threshold = (CHECK_BLOCK_SIZE * CHECK_BLOCK_SIZE * threshold * threshold);

	//
	//	Check 4 corners, CHECK_BLOCK_SIZE * CHECK_BLOCK_SIZE
	//	-----------
	//	|1   5   2|
	//	|		|	<== FingerprINT
	//	|3   6   4|
	//	-----------
	//

	//
	//	Block 1
	//
	if ((diff[0] = EuclideanDistance(
		fp_bkg_intensity + (width * BLOCK_OFFSET) + BLOCK_OFFSET,
		width,
		intensity + (width * BLOCK_OFFSET) + BLOCK_OFFSET,
		width,
		CHECK_BLOCK_SIZE,
		CHECK_BLOCK_SIZE)) >= threshold) {
		score++;
		has_finger[0] = 1;
	}

	//
	//	Block 2
	//
	if ((diff[1] = EuclideanDistance(
		fp_bkg_intensity + (width * BLOCK_OFFSET) + (width - CHECK_BLOCK_SIZE - BLOCK_OFFSET),
		width,
		intensity + (width * BLOCK_OFFSET) + (width - CHECK_BLOCK_SIZE - BLOCK_OFFSET),
		width,
		CHECK_BLOCK_SIZE,
		CHECK_BLOCK_SIZE)) >= threshold) {
		score++;
		has_finger[1] = 1;
	}

	//
	//	Block 3
	//
	if ((diff[2] = EuclideanDistance(
		fp_bkg_intensity + width * (height - CHECK_BLOCK_SIZE - BLOCK_OFFSET) + BLOCK_OFFSET,
		width,
		intensity + width*(height - CHECK_BLOCK_SIZE - BLOCK_OFFSET) + BLOCK_OFFSET,
		width,
		CHECK_BLOCK_SIZE,
		CHECK_BLOCK_SIZE)) >= threshold) {
		score++;
		has_finger[2] = 1;
	}

	//
	//	Block 4
	//
	if ((diff[3] = EuclideanDistance(
		fp_bkg_intensity + width * (height - CHECK_BLOCK_SIZE - BLOCK_OFFSET) + (width - CHECK_BLOCK_SIZE - BLOCK_OFFSET),
		width,
		intensity + width * (height - CHECK_BLOCK_SIZE - BLOCK_OFFSET) + (width - CHECK_BLOCK_SIZE - BLOCK_OFFSET),
		width,
		CHECK_BLOCK_SIZE,
		CHECK_BLOCK_SIZE)) >= threshold) {
		score++;
		has_finger[3] = 1;
	}

	//
	//	Block 5
	//
	if ((diff[4] = EuclideanDistance(
		fp_bkg_intensity + (width * BLOCK_OFFSET) + ((width - CHECK_BLOCK_SIZE) / 2),
		width,
		intensity + (width * BLOCK_OFFSET) + ((width - CHECK_BLOCK_SIZE / 2)),
		width,
		CHECK_BLOCK_SIZE,
		CHECK_BLOCK_SIZE)) >= threshold) {
		score++;
		has_finger[4] = 1;
	}

	//
	//	Block 6
	//
	if ((diff[5] = EuclideanDistance(
		fp_bkg_intensity + width * (height - CHECK_BLOCK_SIZE - BLOCK_OFFSET) + ((width - CHECK_BLOCK_SIZE)/2),
		width,
		intensity + width*(height - CHECK_BLOCK_SIZE - BLOCK_OFFSET) + ((width - CHECK_BLOCK_SIZE)/2),
		width,
		CHECK_BLOCK_SIZE,
		CHECK_BLOCK_SIZE)) >= threshold) {
		score++;
		has_finger[5] = 1;
	}

	if (fp_global->scroll_param.FingerOnPartial) {
		//
		//	If partial fingerprint is enable, use HasFinger of loose threshold.
		//
		return (score >= 2);
	} else {
		if (loose_check)
			return (score >= 3);
		else
			return (score >= 6);
	}
}

unsigned char fp_getkey_finger_on(unsigned char *intensity, int width, int len, int *result) //one line
{
	int score = 0;
	unsigned int diff[3] = { 0 };
	unsigned int threshold = fp_global->cali_info.fingerOnThresholdLoose;
	threshold = (len * threshold * threshold);

	//
	//	Check 4 corners, CHECK_BLOCK_SIZE * CHECK_BLOCK_SIZE
	//	-----------
	//	|1   3   2|		<== FingerprINT
	//	-----------
	//
	//
	//
	//	Block 1
	//
	if ((diff[0] = cal_diff(
		fp_bkg_intensity,
		intensity,
		0 + (SCROLLING_WIDTH - width) / 2,
		len)) >= threshold) {
		score++;
		result[0] = 1;
	} else {
		result[0] = 0;
	}

	//
	//	Block 2
	//
	if ((diff[1] = cal_diff(
		fp_bkg_intensity,
		intensity,
		SCROLLING_WIDTH - ((SCROLLING_WIDTH - width) / 2) - len,
		len)) >= threshold) {
		score++;
		result[1] = 1;
	} else {
		result[1] = 0;
	}

	FP_LOG_INFO("diff %d %d %d threshold = %d score = %d\n",
		diff[0], diff[1], diff[2], threshold, score);

	return (score >= 1);
}

void fp_scrolling()
{
#define SCROLL_FILTER
	int tot_dx = 0;
	int no_move_cnt = 0;
	int dx = 0, dy = 0;
	unsigned int max_diff = 0;

#ifdef SCROLL_FILTER
	int jitter_cnt = 0, jitter_flag = 0;
#endif

	//unsigned char register_buf[5] = { 0 };
	int i = 0;
	int image_temp = 0;
	unsigned char rec = 0;
	int dir = 0;
	unsigned char invalid_count = 0;
	int pre_state = -1;
	unsigned char *buf = NULL, *last_frame= NULL;

	mutex_lock(&fp_global->scroll_lock);
	fp_wakelock_ops(&fp_global->fp_wakelock, true);
	wake_lock_timeout(&fp_global->fp_wakelock_timeout.lock, msecs_to_jiffies(2000));

	mdelay(10);

	if (!fp_global->scroll_enable) {
		FP_LOG_INFO("scroll enable = %d, goto end\n", fp_global->scroll_enable);
		goto exit_enable;
	}

	buf = kzalloc(SCROLLING_WIDTH * SCROLLING_HEIGHT, GFP_KERNEL);
	if (buf == NULL) {
		FP_LOG_ERROR("failed to kzalloc\n");
		goto end;
	}

   	last_frame = kzalloc(SCROLLING_WIDTH * SCROLLING_HEIGHT, GFP_KERNEL);
	if(last_frame == NULL) {
		FP_LOG_ERROR("failed to kzalloc\n");
		goto end;
	}

	//FP_LOG_INFO("FingerOnThreshold = %d, FingerOnThresholdLoose = %d\n",
	//	fp_global->cali_info.fingerOnThreshold, fp_global->cali_info.fingerOnThresholdLoose);

	max_diff = NAV_WIDTH * NAV_HEIGHT * fp_global->cali_info.fingerOnThreshold * fp_global->cali_info.fingerOnThreshold * 4;

	//fp_read_register_external(ADC_CTL_ET310_ADDR, register_buf);
	//FP_LOG_INFO("buf[0x04] = 0x%x(%d)\n", register_buf[0], register_buf[0]);

	//fp_read_register_external(PGA_CONTL_ET310_ADDR, register_buf);
	//FP_LOG_INFO("buf[0x09] = 0x%x(%d)\n", register_buf[0], register_buf[0]);

	fp_set_sensor_mode();

	fp_write_register_external(SRBA_ET310_ADDR,
		(FPS_IMG_HEIGHT - SCROLLING_HEIGHT) / 2);
	fp_write_register_external(SREA_ET310_ADDR,
		(FPS_IMG_HEIGHT - SCROLLING_HEIGHT) / 2 + SCROLLING_HEIGHT - 1);
	fp_write_register_external(SCBA_ET310_ADDR,
		(FPS_IMG_WIDTH - SCROLLING_WIDTH) / 2);
	fp_write_register_external(SCEA_ET310_ADDR,
		(FPS_IMG_WIDTH - SCROLLING_WIDTH) / 2 + SCROLLING_WIDTH - 1);

	//for(i = 0; i < 32; i++)
	//	FP_LOG_INFO("fingerprint [%x],", fp_bkg_intensity[SCROLLING_WIDTH*(SCROLLING_HEIGHT/2 - 1)+i]);

	FP_LOG_INFO("start FingerDetect\n");

FingerDetect:
	tot_dx = 0;
	dir = 0;
	rec = 0;
	invalid_count = 0;

	while (fp_global->scroll_enable) {
		if (fp_fetch_image(buf, SCROLLING_WIDTH, SCROLLING_HEIGHT) != 0) {
			FP_LOG_ERROR("failed to fetch image, goto end\n");
           	goto end;
		}

		if (fp_finger_on(buf, SCROLLING_WIDTH, SCROLLING_HEIGHT, true)) {
			break;
		} else {
			FP_LOG_INFO("failed to judge finger, goto end\n");
			goto end;
		}
	}

	FP_LOG_INFO("Finger Detectd\n");

#ifdef SCROLL_FILTER
	jitter_cnt = 0;
	jitter_flag = 0;
#endif

	no_move_cnt = 0;

	for (i = 0; i < SCROLLING_WIDTH * SCROLLING_HEIGHT; i++) {
		image_temp = buf[i] - fp_bkg_intensity[i];
		image_temp *= 2;
		if (image_temp > 255)
			image_temp = 255;
		if (image_temp < 0)
			image_temp = 0;
		buf[i] = image_temp;
	}
	memcpy(last_frame, buf, SCROLLING_WIDTH * SCROLLING_HEIGHT);

	if (!fp_global->scroll_enable) {
		FP_LOG_INFO("scroll enable = %d, goto end\n", fp_global->scroll_enable);
    	goto end;
	}

	while (fp_global->scroll_enable) {
		if (fp_fetch_image(buf, SCROLLING_WIDTH, SCROLLING_HEIGHT) != 0) {
			FP_LOG_ERROR("failed to fetch image, goto end\n");
			goto end;
		}

		if (!fp_finger_on(buf, SCROLLING_WIDTH, SCROLLING_HEIGHT, true)) {
			FP_LOG_INFO("goto FingerDetect\n");
			goto FingerDetect;
		}

		for(i = 0; i < SCROLLING_WIDTH * SCROLLING_HEIGHT; i++) {
			image_temp = buf[i] - fp_bkg_intensity[i];
			image_temp *= 2;
			if (image_temp > 255)
				image_temp = 255;
			if (image_temp < 0)
				image_temp = 0;
			buf[i] = image_temp;
		}

		if (CalcNavOffset(last_frame, buf, SCROLLING_WIDTH, SCROLLING_HEIGHT, &dx, &dy, max_diff)) {
			//FP_LOG_INFO("dx = %d\n", dx);

			//limited movement
			if (dx == 0) {
				if (pre_state == 1 || pre_state == 2) {
					pre_state = 0;
					msleep(200);
					continue;
				}
#ifdef SCROLL_FILTER
				jitter_cnt++;
				if (jitter_cnt > fp_global->scroll_param.jitter_limit)
					jitter_cnt = 0;
#endif
				no_move_cnt++;
				if(no_move_cnt > 10) {
					//FP_LOG_INFO("no move jitter_flag = %d\n", jitter_flag);
					if ((jitter_flag == 1) && (fp_global->int_desc.interrupt_state & INTERRUPT_STATE_SCROLL)) {
						input_report_key(fp_global->key_input_dev, KEY_VOLUMEDOWN, 1);
						input_sync(fp_global->key_input_dev);
						input_report_key(fp_global->key_input_dev, KEY_VOLUMEDOWN, 0);
						input_sync(fp_global->key_input_dev);
						no_move_cnt = 0;
					} else if((jitter_flag == 2) && (fp_global->int_desc.interrupt_state & INTERRUPT_STATE_SCROLL)) {
						input_report_key(fp_global->key_input_dev, KEY_VOLUMEUP, 1);
						input_sync(fp_global->key_input_dev);
						input_report_key(fp_global->key_input_dev, KEY_VOLUMEUP, 0);
						input_sync(fp_global->key_input_dev);
						no_move_cnt = 0;
					} else if((jitter_flag == 0) &&
						(no_move_cnt > fp_global->scroll_param.no_move_th)
						&& (fp_global->int_desc.interrupt_state & INTERRUPT_STATE_SEND_KEY)) {
							//wake_lock_timeout(&(fp_global->fp_wakelock.lock), msecs_to_jiffies(2000));
							FP_LOG_INFO("Send wake up key event = %d\n", jitter_flag);
							input_report_key(fp_global->key_input_dev, fp_global->int_desc.interrupt_key_code, 1);
							input_sync(fp_global->key_input_dev);
							input_report_key(fp_global->key_input_dev, fp_global->int_desc.interrupt_key_code, 0);
							input_sync(fp_global->key_input_dev);
							//fp_global->int_desc.interrupt_state &= ~INTERRUPT_STATE_SEND_KEY;
							goto end;
					}
				}
				pre_state = 0;
				continue; //no movement detected
			}

			no_move_cnt = 0;

			if (!(fp_global->int_desc.interrupt_state & INTERRUPT_STATE_SCROLL))
				continue;

			//DoOnNavigation(dx, dy, TRUE);
			tot_dx += dx;

			//FP_LOG_INFO("start direction dx = %d tot_dx = %d\n", dx, tot_dx);

			if (abs(tot_dx) < fp_global->scroll_param.jitter_threshold) {

				pre_state = -1;
#ifdef SCROLL_FILTER
				if (jitter_flag != 0) {
					jitter_cnt++;
					if (jitter_cnt > fp_global->scroll_param.jitter_limit)
						jitter_cnt = 0;
					memcpy(last_frame, buf, SCROLLING_WIDTH * SCROLLING_HEIGHT);
					continue;
				}
#endif
			} else if(tot_dx > 0) {
#ifdef SCROLL_FILTER
				if ((jitter_flag == 1) && (jitter_cnt < fp_global->scroll_param.jitter_limit)) {
					jitter_cnt++;
					//FP_LOG_INFO("jitter_cnt = %d\n", jitter_cnt);
					memcpy(last_frame, buf, SCROLLING_WIDTH * SCROLLING_HEIGHT);
					continue;
				} else if(jitter_cnt >= fp_global->scroll_param.jitter_limit) {
					jitter_cnt = 0;
				}

				jitter_flag = 1;

				//FP_LOG_INFO("jitter_cnt = %d\n", jitter_cnt);
#endif
				if ((dir >= 0) && ((fp_global->int_desc.interrupt_state & INTERRUPT_STATE_SCROLL))) {
					input_report_key(fp_global->key_input_dev, KEY_VOLUMEDOWN, 1);
					input_sync(fp_global->key_input_dev);
					input_report_key(fp_global->key_input_dev, KEY_VOLUMEDOWN, 0);
					input_sync(fp_global->key_input_dev);
					dir = 1;
				} else {
					dir = 0;
					invalid_count++;
				}

				tot_dx = 0;
				pre_state = 1;
			} else {
#ifdef SCROLL_FILTER
				if ((jitter_flag == 2) && (jitter_cnt < fp_global->scroll_param.jitter_limit)) {
					jitter_cnt++;
					//FP_LOG_INFO("jitter_cnt = %d\n", jitter_cnt);
					memcpy(last_frame, buf, SCROLLING_WIDTH * SCROLLING_HEIGHT);
					continue;
				} else if(jitter_cnt >= fp_global->scroll_param.jitter_limit) {
					jitter_cnt = 0;
				}

				jitter_flag = 2;
#endif

				if ((dir <= 0) && ((fp_global->int_desc.interrupt_state & INTERRUPT_STATE_SCROLL))) {
					input_report_key(fp_global->key_input_dev, KEY_VOLUMEUP, 1);
					input_sync(fp_global->key_input_dev);
					input_report_key(fp_global->key_input_dev, KEY_VOLUMEUP, 0);
					input_sync(fp_global->key_input_dev);
					dir = -1;
				} else {
					dir = 0;
					invalid_count++;
				}

				tot_dx = 0;
				pre_state = 2;
			}
		} //otherwiae, movement too large
		memcpy(last_frame, buf, SCROLLING_WIDTH * SCROLLING_HEIGHT);
	}

end:
	if(last_frame)
		kfree(last_frame);
	if(buf)
		kfree(buf);

	fp_set_detect_mode();

exit_enable:
	if (fp_global->scroll_enable)
		fp_irq_op(fp_global->int_desc.irq, FP_INT_ENABLE);
	fp_wakelock_ops(&(fp_global->fp_wakelock), false);
	mutex_unlock(&fp_global->scroll_lock);

	FP_LOG_INFO("end\n");
	return;
}
EXPORT_SYMBOL(fp_scrolling);

int fp_getkey()
{
	unsigned char *buf = NULL;
	int i = 0;
	int score = 0;
	int result[2] = { 0 };

	mutex_lock(&fp_global->getkey_lock);

	buf = kzalloc(SCROLLING_WIDTH * 1, GFP_KERNEL);
	if((buf == NULL)) {
		FP_LOG_ERROR("failed to kzalloc\n");
		goto end;
	}

	fp_set_sensor_mode();
	fp_write_register_external(V2LC0_ET310_ADDR, 0x30);
	fp_write_register_external(SRBA_ET310_ADDR, (SCROLLING_HEIGHT >> 1) - 1);
	fp_write_register_external(SREA_ET310_ADDR, (SCROLLING_HEIGHT >> 1) - 1);
	fp_write_register_external(SCBA_ET310_ADDR, 0);
	fp_write_register_external(SCEA_ET310_ADDR, SCROLLING_WIDTH - 1);

	FP_LOG_INFO("start FingerDetect\n");

	if (fp_fetch_image(buf, SCROLLING_WIDTH, 1)) {
		FP_LOG_ERROR("failed to fetch image, goto end\n");
		goto end;
	}

	if (!fp_getkey_finger_on(buf, SCROLLING_WIDTH, 50, result)) {
		FP_LOG_INFO("has no finger, goto end\n");
		goto end;
	}

	score = 0;
	for (i = 0; i < 2; i++)
		score += result[i];

	FP_LOG_INFO("score = %d\n", score);

	if (score > 0) {
		FP_LOG_INFO("g_has_finfer[0] = %d g_has_finger[1] = %d\n",
			result[0], result[1]);

		if ((result[0] == 1) && (result[1] == 1)) {
			FP_LOG_INFO("both are touched\n");
			goto end;
		}

		if (result[0] == 1) {
			input_report_key(fp_global->key_input_dev, KEY_VOLUMEUP, 1);
			input_sync(fp_global->key_input_dev);
			input_report_key(fp_global->key_input_dev, KEY_VOLUMEUP, 0);
			input_sync(fp_global->key_input_dev);
		} else if (result[1] == 1) {
			input_report_key(fp_global->key_input_dev, KEY_VOLUMEDOWN, 1);
			input_sync(fp_global->key_input_dev);
			input_report_key(fp_global->key_input_dev, KEY_VOLUMEDOWN, 0);
			input_sync(fp_global->key_input_dev);
		}
	}

end:
	if(buf != NULL)
		kfree(buf);

	fp_set_detect_mode();
	msleep(300);
	fp_irq_op(fp_global->int_desc.irq, FP_INT_ENABLE);
	mutex_unlock(&fp_global->getkey_lock);

	FP_LOG_INFO("end\n");

	return 0;
}
EXPORT_SYMBOL(fp_getkey);
