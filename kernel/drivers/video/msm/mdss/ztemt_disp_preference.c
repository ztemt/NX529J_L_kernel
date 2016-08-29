/*
 * ztemt_disp_preference.c - ztemt lcd display color enhancement and temperature setting
 *	      Linux kernel modules for mdss
 *
 * Copyright (c) 2015 ztemt <nubia@zte.com.cn>
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

/*
 * Supports ZTEMT lcd display color enhancement and color temperature setting
 */

/*------------------------------ header file --------------------------------*/
#include "mdss_dsi_cmd.h"
#include "mdss_dsi.h"
#include "ztemt_disp_preference.h"
#include <linux/delay.h>
struct mdp_pcc_cfg_data sharp_nt35595_1080p_5p0_pcc_cfg_warm = {
	.block = 0x10,
	.ops = 0x5,
	{
		.c = 0,
		.r = 0x8000,
		.g = 0,
		.b = 0,
		.rr = 0,
		.gg = 0,
		.bb = 0,
		.rg = 0,
		.gb = 0,
		.rb = 0,
		.rgb_0 = 0,
		.rgb_1 = 0
	},
	{
		.c = 0,
		.r = 0,
		.g = 0x8000,
		.b = 0,
		.rr = 0,
		.gg = 0,
		.bb = 0,
		.rg = 0,
		.gb = 0,
		.rb = 0,
		.rgb_0 = 0,
		.rgb_1 = 0
	},
	{
		.c = 0,
		.r = 0,
		.g = 0,
		.b = 0x8000,
		.rr = 0,
		.gg = 0,
		.bb = 0,
		.rg = 0,
		.gb = 0,
		.rb = 0,
		.rgb_0 = 0,
		.rgb_1 = 0
	},
};

struct mdp_pcc_cfg_data sharp_nt35595_1080p_5p0_pcc_cfg_natural = {
	.block = 0x10,
	.ops = 0x5,
	{
		.c = 0,
		.r = 0x7704,
		.g = 0,
		.b = 0,
		.rr = 0,
		.gg = 0,
		.bb = 0,
		.rg = 0,
		.gb = 0,
		.rb = 0,
		.rgb_0 = 0,
		.rgb_1 = 0
	},
	{
		.c = 0,
		.r = 0,
		.g = 0x7c18,
		.b = 0,
		.rr = 0,
		.gg = 0,
		.bb = 0,
		.rg = 0,
		.gb = 0,
		.rb = 0,
		.rgb_0 = 0,
		.rgb_1 = 0
	},
	{
		.c = 0,
		.r = 0,
		.g = 0,
		.b = 0x8000,
		.rr = 0,
		.gg = 0,
		.bb = 0,
		.rg = 0,
		.gb = 0,
		.rb = 0,
		.rgb_0 = 0,
		.rgb_1 = 0
	},
};

struct mdp_pcc_cfg_data sharp_nt35595_1080p_5p0_pcc_cfg_cool = {
	.block = 0x10,
	.ops = 0x5,
	{
		.c = 0,
		.r = 0x7254,
		.g = 0,
		.b = 0,
	},
	{
		.c = 0,
		.r = 0,
		.g = 0x763c,
		.b = 0,
	},
	{
		.c = 0,
		.r = 0,
		.g = 0,
		.b = 0x8000,
	},
};


 /*------------------------------- variables ---------------------------------*/

/*------------------------------- variables ---------------------------------*/
static struct kobject *enhance_kobj = NULL;
static struct mdss_dsi_ctrl_pdata *ztemt_mdss_dsi_ctrl = NULL;
static int boot_flag = 0;

static struct ztemt_disp_type ztemt_disp_val = {
	.en_cabc = 1,
	.cabc = CABC_LEVER2,
	.en_saturation = 1,
	.saturation = SATURATION_STD,
	.en_colortmp = 1,
	.colortmp =  COLORTMP_NORMAL,
	.shield = 0,
};

/* used for set shield as 0 after a short time added by nubia */
struct hrtimer shield_timer;

extern int zte_mdss_dsi_panel_cmds_send(struct mdss_dsi_ctrl_pdata *ctrl,
			struct dsi_panel_cmds *pcmds);
#if ZTEMT_DISP_COLORTMP_DEBUG
static struct mdp_pcc_cfg_data ztemt_colortmp_debug = {
	.block = 0x10,
	.ops = 0x5,
	{
	  .c = 0,
	  .r = 0x8000,
	  .g = 0,
	  .b = 0,
	  .rr = 0,
	  .gg = 0,
	  .bb = 0,
	  .rg = 0,
	  .gb = 0,
	  .rb = 0,
	  .rgb_0 = 0,
	  .rgb_1 = 0
	},
	{
	  .c = 0,
	  .r = 0,
	  .g = 0x8000,
	  .b = 0,
	  .rr = 0,
	  .gg = 0,
	  .bb = 0,
	  .rg = 0,
	  .gb = 0,
	  .rb = 0,
	  .rgb_0 = 0,
	  .rgb_1 = 0
	},
	{
	  .c = 0,
	  .r = 0,
	  .g = 0,
	  .b = 0x8000,
	  .rr = 0,
	  .gg = 0,
	  .bb = 0,
	  .rg = 0,
	  .gb = 0,
	  .rb = 0,
	  .rgb_0 = 0,
	  .rgb_1 = 0
	},
};
#endif

static int ztemt_set_ce_cabc(int sat_val, int cabc_val)
{
	int ret=0;
	switch(sat_val){
		case    SATURATION_OFF:
                        switch(cabc_val){
                                case    CABC_OFF:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds0.cmd_cnt)
                                                ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds0);
                                        break;
                                case    CABC_LEVER1:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds1.cmd_cnt)
                                                ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds1);
                                        break;
                                case    CABC_LEVER2:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds2.cmd_cnt)
                                                ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds2);
                                        break;
                                case    CABC_LEVER3:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds3.cmd_cnt)
                                                ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds3);
                                        break;
                        }
                        break;
		case	SATURATION_SOFT:
			switch(cabc_val){
                                case    CABC_OFF:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds4.cmd_cnt)
                                        	ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds4);
                                        break;
                                case    CABC_LEVER1:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds5.cmd_cnt)
	                                   ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds5);
                                        break;
                                case    CABC_LEVER2:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds6.cmd_cnt)
                                        	ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds6);
                                        break;
                                case    CABC_LEVER3:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds7.cmd_cnt)
                                        	ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds7);
                                        break;
			}
                     break;
		case SATURATION_STD:
			switch(cabc_val){
                                case    CABC_OFF:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds8.cmd_cnt)
                                        	ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds8);
                                        break;
                                case    CABC_LEVER1:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds9.cmd_cnt)
                                        	ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds9);
                                        break;
                                case    CABC_LEVER2:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds10.cmd_cnt)
                                        	ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds10);
                                        break;
                                case    CABC_LEVER3:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds11.cmd_cnt)
                                        	ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds11);
                                        break;
			}
                     break;
		case    SATURATION_GLOW:
                        switch(cabc_val){
                                case    CABC_OFF:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds12.cmd_cnt)
                                                ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds12);
                                        break;
                                case    CABC_LEVER1:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds13.cmd_cnt)
                                                ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds13);
                                        break;
                                case    CABC_LEVER2:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds14.cmd_cnt)
                                                ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds14);
                                        break;
                                case    CABC_LEVER3:
                                        if (ztemt_mdss_dsi_ctrl->ce_cabc_cmds15.cmd_cnt)
                                                ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cabc_cmds15);
                                        break;
                        }
                        break;

	}
	if(ret == 0)
		ZTEMT_DISP_DEBUG("success to set sat as = %d ,cabc as = %d\n", sat_val ,cabc_val);
	else
		ZTEMT_DISP_DEBUG("failed to set sat and cabc");
	return ret;
}

static int ztemt_set_cabc(int cabc_val)
{
        int ret = 0;
	if (!ztemt_disp_val.en_cabc) {
                ret = -1;
                ZTEMT_DISP_ERROR("no cabc func\n");
                return ret;
        }

	if (!ztemt_mdss_dsi_ctrl->panel_data.panel_info.panel_name) {
                ret = -1;
                ZTEMT_DISP_ERROR("invalid ztemt_mdss_dsi_ctrl\n");
                return ret;
        } else {
                ZTEMT_DISP_DEBUG("lcd is %s\n", ztemt_mdss_dsi_ctrl->panel_data.panel_info.panel_name);
        }

        switch (cabc_val) {
		case CABC_OFF:
			if (ztemt_mdss_dsi_ctrl->cabc_cmds_off.cmd_cnt)
				ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->cabc_cmds_off);
			break;
		case CABC_LEVER1:
			if (ztemt_mdss_dsi_ctrl->cabc_cmds_lever1.cmd_cnt)
				ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->cabc_cmds_lever1);
			break;
		case CABC_LEVER2:
			if (ztemt_mdss_dsi_ctrl->cabc_cmds_lever2.cmd_cnt)
				ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->cabc_cmds_lever2);
			break;
		case CABC_LEVER3:
			if (ztemt_mdss_dsi_ctrl->cabc_cmds_lever3.cmd_cnt)
				ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->cabc_cmds_lever3);
			break;
        	default:
			if (ztemt_mdss_dsi_ctrl->cabc_cmds_lever3.cmd_cnt)
				ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->cabc_cmds_off);
			break;
	}
	ztemt_set_ce_cabc(ztemt_disp_val.saturation,cabc_val);
	return ret;
}

static ssize_t cabc_show(struct kobject *kobj,
        struct kobj_attribute *attr, char *buf)
{
       if (ztemt_disp_val.en_cabc)
                return snprintf(buf, PAGE_SIZE, "%d\n", ztemt_disp_val.cabc);
        else
                return snprintf(buf, PAGE_SIZE, "NULL\n");

}

static ssize_t cabc_store(struct kobject *kobj,
        struct kobj_attribute *attr, const char *buf, size_t size)
{
        uint32_t val = 0;
        int ret = 0;
	if(!ztemt_disp_val.en_cabc) {
                ZTEMT_DISP_ERROR("no cabc\n");
                return size;
        }

        sscanf(buf, "%d", &val);

        if ((val != CABC_OFF) && (val != CABC_LEVER1) &&
                (val != CABC_LEVER2) && (val != CABC_LEVER3)) {
                ZTEMT_DISP_ERROR("invalid cabc val = %d\n", val);
                return size;
        }

        ZTEMT_DISP_DEBUG("cabc value = %d\n", val);

        if(!boot_flag)
                return size;

        ret = ztemt_set_cabc(val);
        if (ret == 0) {
                ztemt_disp_val.cabc = val;
                ZTEMT_DISP_DEBUG("success to set cabc as = %d\n", val);
        }
        return size;
}

static int ztemt_set_saturation(int sat_val)
{
	int ret = 0;

	if (!ztemt_disp_val.en_saturation) {
		ret = -1;
		ZTEMT_DISP_ERROR("no saturation\n");
		return ret;
	}

	if (!ztemt_mdss_dsi_ctrl->panel_data.panel_info.panel_name) {
		ret = -1;
		ZTEMT_DISP_ERROR("invalid ztemt_mdss_dsi_ctrl\n");
		return ret;
	} else {
		ZTEMT_DISP_DEBUG("lcd is %s\n", ztemt_mdss_dsi_ctrl->panel_data.panel_info.panel_name);
	}
	switch (sat_val) {
		case SATURATION_OFF:
                        if (ztemt_mdss_dsi_ctrl->ce_cmds_off.cmd_cnt)
                                ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cmds_off);
                        break;
		case SATURATION_SOFT:
			if (ztemt_mdss_dsi_ctrl->ce_cmds_soft.cmd_cnt)
				ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cmds_soft);
			break;
		case SATURATION_STD:
			if (ztemt_mdss_dsi_ctrl->ce_cmds_std.cmd_cnt)
				ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cmds_std);
	       		break;
	       case SATURATION_GLOW:
			if (ztemt_mdss_dsi_ctrl->ce_cmds_glow.cmd_cnt)
				ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cmds_glow);
       			break;
	       default:
			if (ztemt_mdss_dsi_ctrl->ce_cmds_off.cmd_cnt)
				ret = zte_mdss_dsi_panel_cmds_send(ztemt_mdss_dsi_ctrl, &ztemt_mdss_dsi_ctrl->ce_cmds_off);
			break;
	}
	ztemt_set_ce_cabc(sat_val,ztemt_disp_val.cabc);
	return ret;
}

static ssize_t saturation_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	if (ztemt_disp_val.en_saturation)
		return snprintf(buf, PAGE_SIZE, "%d\n",	ztemt_disp_val.saturation);
	else
		return snprintf(buf, PAGE_SIZE, "NULL\n");
}

static ssize_t saturation_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	uint32_t val = 0;
	int ret = 0;

	if(!ztemt_disp_val.en_saturation) {
		ZTEMT_DISP_ERROR("no saturation\n");
		return size;
	}

	sscanf(buf, "%d", &val);

	if ((val != SATURATION_OFF) && (val != SATURATION_SOFT) && (val != SATURATION_STD) &&
		(val != SATURATION_GLOW)) {
		ZTEMT_DISP_ERROR("invalid saturation val = %d\n", val);
		return size;
	}

	ZTEMT_DISP_DEBUG("saturation value = %d\n", val);

	if(!boot_flag)
		return size;

	ret = ztemt_set_saturation(val);
	if (ret == 0) {
		ztemt_disp_val.saturation = val;
		ZTEMT_DISP_DEBUG("success to set saturation as = %d\n", val);
	}
	return size;
}

static int ztemt_set_colortmp(int ctmp_val)
{
	int ret = 0;

	if ((!ztemt_disp_val.en_colortmp) || (NULL == ztemt_mdss_dsi_ctrl)) {
		ret = -1;
		ZTEMT_DISP_ERROR("invalid param\n");
		return ret;
	}

	if (!ztemt_mdss_dsi_ctrl->panel_data.panel_info.panel_name) {
		ret = -1;
		ZTEMT_DISP_ERROR("invalid ztemt_mdss_dsi_ctrl\n");
		return ret;
	} else {
		ZTEMT_DISP_DEBUG("lcd is %s\n", ztemt_mdss_dsi_ctrl->panel_data.panel_info.panel_name);
	}

	switch (ctmp_val) {
		case COLORTMP_WARM:
			ret = ztemt_mdss_pcc_config(&sharp_nt35595_1080p_5p0_pcc_cfg_warm);
	       		break;
       		case COLORTMP_NORMAL:
			ret = ztemt_mdss_pcc_config(&sharp_nt35595_1080p_5p0_pcc_cfg_natural);
       			break;
	       	case COLORTMP_COOL:
			ret = ztemt_mdss_pcc_config(&sharp_nt35595_1080p_5p0_pcc_cfg_cool);
       			break;
	       	default:
			ret = ztemt_mdss_pcc_config(&sharp_nt35595_1080p_5p0_pcc_cfg_natural);
			break;
		}
	return ret;
}

static ssize_t colortmp_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	if (ztemt_disp_val.en_colortmp)
		return snprintf(buf, PAGE_SIZE, "%d\n",	ztemt_disp_val.colortmp);
	else
		return snprintf(buf, PAGE_SIZE, "NULL\n");
}

static ssize_t colortmp_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0, ret = 0;

	if(!ztemt_disp_val.en_colortmp) {
		ZTEMT_DISP_ERROR("no colortmp\n");
		return size;
	}

	sscanf(buf, "%d", &val);

	if ((val != COLORTMP_WARM) && (val != COLORTMP_NORMAL)
		&& (val != COLORTMP_COOL)) {
		ZTEMT_DISP_ERROR("invalid colortmp val\n");
		return size;
	}

	ZTEMT_DISP_DEBUG("colortmp val = %d\n", val);

	ret = ztemt_set_colortmp(val);
	if (ret == 0) {
		ztemt_disp_val.colortmp = val;
		ZTEMT_DISP_DEBUG("success to set colortmp as = %d\n", val);
	}

	return size;
}

int ztemt_get_shield()
{
	ZTEMT_DISP_DEBUG("get shield = %d\n", ztemt_disp_val.shield);
	return ztemt_disp_val.shield;
}

void ztemt_set_shield(int shield)
{
	if ((shield != 0) && (shield != 1))
		return;
	else
		ztemt_disp_val.shield = shield;

	ZTEMT_DISP_INFO("set shield = %d\n", shield);
}

static ssize_t shield_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n",	ztemt_disp_val.shield);
}

static ssize_t shield_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0;

	sscanf(buf, "%d", &val);

	if ((val != 0) && (val != 1)) {
		ZTEMT_DISP_ERROR("failed as invalid shield val\n");
		return size;
	}

	if (val == 1) {
		hrtimer_start(&shield_timer, ktime_set(1, 500000000), HRTIMER_MODE_REL);
	} else {
		hrtimer_cancel(&shield_timer);
	}

	ztemt_set_shield(val);
	ZTEMT_DISP_INFO("success to set shield as %d\n", val);

	return size;
}

#if ZTEMT_DISP_COLORTMP_DEBUG
static ssize_t colortmp_r_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "0x%4x\n", ztemt_colortmp_debug.r.r);
}

static ssize_t colortmp_r_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	uint32_t val = 0;

	sscanf(buf, "%x", &val);

	ztemt_colortmp_debug.r.r = val;

	return size;
}

static ssize_t colortmp_g_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "0x%4x\n", ztemt_colortmp_debug.g.g);
}

static ssize_t colortmp_g_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	uint32_t val = 0;

	sscanf(buf, "%x", &val);

	ztemt_colortmp_debug.g.g = val;

	return size;
}

static ssize_t colortmp_b_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "0x%4x\n", ztemt_colortmp_debug.b.b);
}

static ssize_t colortmp_b_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	uint32_t val = 0;

	sscanf(buf, "%x", &val);

	ztemt_colortmp_debug.b.b = val;

	return size;
}

static ssize_t colortmp_debug_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "r = 0x%4x, g = 0x%4x, b = 0x%4x\n",
		ztemt_colortmp_debug.r.r, ztemt_colortmp_debug.g.g, ztemt_colortmp_debug.b.b);
}

static ssize_t colortmp_debug_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val = 0,ret;

	if(!ztemt_disp_val.en_colortmp) {
		ZTEMT_DISP_ERROR("no colortmp\n");
	     return size;
	}

	sscanf(buf, "%d", &val);

	ZTEMT_DISP_DEBUG("colortmp debug val = %d\n", val);

	if (val == 1)
		ret = ztemt_mdss_pcc_config(&ztemt_colortmp_debug);

	return size;
}
#endif

#define COUNT_CH 2000
static ssize_t lcd_debug_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	size_t ret=0;
	int i=0,j=0,k=0;
	char str[3],sntr[COUNT_CH];
	struct dsi_panel_cmds *on_cmds=NULL;
	struct dsi_cmd_desc *dsi_cmd=NULL;
	char *ch=NULL;

	on_cmds = &ztemt_mdss_dsi_ctrl->on_cmds;
	if(on_cmds==NULL){
		pr_err("on_cmds==NULL");
		return ret;
	}

	dsi_cmd=on_cmds->cmds;
	if(dsi_cmd==NULL){
		pr_err("dsi_cmd==NULL\n");
		return ret;
	}

	for(i=0;i<on_cmds->cmd_cnt;i++){
		pr_err("debug dsi_cmd->dchdr.dlen = %x\n",dsi_cmd->dchdr.dlen);

		sprintf(str,"%02x",i);
		if(k<(COUNT_CH-1))
			sntr[k++]=str[0];
		if(k<(COUNT_CH-1))
			sntr[k++]=str[1];
		if(k<(COUNT_CH-1))
			sntr[k++]=' ';
		sprintf(str,"%02x",dsi_cmd->dchdr.dlen);
		if(k<(COUNT_CH-1))
			sntr[k++]=str[0];
		if(k<(COUNT_CH-1))
			sntr[k++]=str[1];
		if(k<(COUNT_CH-1))
			sntr[k++]=' ';

		ch=dsi_cmd->payload;
		for(j=0;j<dsi_cmd->dchdr.dlen;j++){
			if(ch==NULL){
				pr_err("ch==NULL i = %x ,j = %x\n",i,j);
				if(k<COUNT_CH)
					sntr[k]='\0';
				pr_err("%s",sntr);
				ret = snprintf(buf, PAGE_SIZE, sntr);
				return ret;
			}
			sprintf(str,"%02x",*(ch));
			if(k<(COUNT_CH-1))
				sntr[k++]=str[0];
			if(k<(COUNT_CH-1))
				sntr[k++]=str[1];
			if(k<(COUNT_CH-1))
				sntr[k++]=' ';
			ch++;
		}
		if(k<(COUNT_CH-1))
			sntr[k++]='\n';
		dsi_cmd++;
	}
	pr_err("k = %x\n",k);
	if(k<COUNT_CH)
		sntr[k]='\0';
	pr_err("%s",sntr);
	ret = snprintf(buf, PAGE_SIZE, sntr);
	//no. len cmd ...
	return ret;
}

static ssize_t lcd_debug_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t size)
{
	int val[256];
	int len,i;
	struct dsi_panel_cmds *on_cmds=NULL;
	struct dsi_cmd_desc *dsi_cmd=NULL;
	char *ch=NULL;

	on_cmds = &ztemt_mdss_dsi_ctrl->on_cmds;
	if(on_cmds==NULL){
		pr_err("on_cmds==NULL\n");
		return size;
	}
	//no. len cmd ...
	len = sscanf(buf, "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x",&val[0], &val[1], &val[2], &val[3], &val[4], &val[5], &val[6], &val[7], &val[8], &val[9],&val[10], &val[11], &val[12], &val[13], &val[14], &val[15], &val[16], &val[17], &val[18], &val[19],&val[20], &val[21], &val[22], &val[23], &val[24], &val[25], &val[26], &val[27], &val[28], &val[29],&val[30], &val[31], &val[32], &val[33], &val[34], &val[35], &val[36], &val[37], &val[38], &val[39],&val[40], &val[41], &val[42], &val[43], &val[44], &val[45], &val[46], &val[47], &val[48], &val[49]);

	pr_err("debug len %x\n",len);
	for(i=0;i<len;i++)
		pr_err("debug %x\n",val[i]);

	if(val[0]>=on_cmds->cmd_cnt){
		pr_err("val[0]>=on_cmds->cmd_cnt\n");
		return size;
	}

	dsi_cmd=on_cmds->cmds;
	if(dsi_cmd==NULL){
		pr_err("dsi_cmd==NULL\n");
		return size;
	}

	for(i=0;i<val[0];i++)
		dsi_cmd++;
	if(dsi_cmd==NULL){
		pr_err("dsi_cmd==NULL\n");
		return size;
	}

	if(val[1]>dsi_cmd->dchdr.dlen){
		pr_err("val[1]>dsi_cmd->dchdr.dlen");
		return size;
	}

	ch=dsi_cmd->payload;
	for(i=0;i<val[1] && i<len-2;i++){
		if(ch==NULL){
			pr_err("ch==NULL,i = %x\n",i);
			return size;
		}
		*ch=val[i+2];
		ch++;
	}

	return size;
}


static struct kobj_attribute lcd_disp_attrs[] = {
	__ATTR(saturation,      0664, saturation_show,     saturation_store),
	__ATTR(colortmp,        0664, colortmp_show,       colortmp_store),
	__ATTR(cabc,            0664, cabc_show,           cabc_store),
	__ATTR(shield,          0664, shield_show,         shield_store),
#if ZTEMT_DISP_COLORTMP_DEBUG
	__ATTR(colortmp_r,      0664, colortmp_r_show,     colortmp_r_store),
	__ATTR(colortmp_g,      0664, colortmp_g_show,     colortmp_g_store),
	__ATTR(colortmp_b,      0664, colortmp_b_show,     colortmp_b_store),
	__ATTR(colortmp_debug,  0664, colortmp_debug_show, colortmp_debug_store),
#endif
	__ATTR(lcd_debug,  0664, lcd_debug_show, lcd_debug_store),
};

void ztemt_set_dsi_ctrl(struct mdss_dsi_ctrl_pdata * ctrl)
{
	ZTEMT_DISP_INFO("start\n");
	ztemt_mdss_dsi_ctrl = ctrl;
}
EXPORT_SYMBOL(ztemt_set_dsi_ctrl);

void ztemt_disp_preference(void)
{
	int ret = 0;

	ret = ztemt_set_saturation(ztemt_disp_val.saturation);
	if (ret == 0)
		ZTEMT_DISP_DEBUG("success to set saturation as = %d\n", ztemt_disp_val.saturation);
	if (!boot_flag){
		boot_flag = 1;
	}
	ret = ztemt_set_colortmp(ztemt_disp_val.colortmp);
	if (ret == 0)
                ZTEMT_DISP_DEBUG("success to set colortmp as = %d\n", ztemt_disp_val.colortmp);
}
EXPORT_SYMBOL(ztemt_disp_preference);

static enum hrtimer_restart ztemt_shield_timer_function(struct hrtimer *timer)
{
	ZTEMT_DISP_INFO("shield timer function\n");
	ztemt_set_shield(0);

	return HRTIMER_NORESTART;
}

static int __init ztemt_disp_preference_init(void)
{
	int retval = 0;
	int attr_count = 0;

	ZTEMT_DISP_INFO("start\n");

	enhance_kobj = kobject_create_and_add("lcd_enhance", kernel_kobj);

	if (!enhance_kobj) {
		ZTEMT_DISP_ERROR("failed to create and add kobject\n");
		return -ENOMEM;
	}

	/* Create attribute files associated with this kobject */
	for (attr_count = 0; attr_count < ARRAY_SIZE(lcd_disp_attrs); attr_count++) {
		retval = sysfs_create_file(enhance_kobj, &lcd_disp_attrs[attr_count].attr);
		if (retval < 0) {
			ZTEMT_DISP_ERROR("failed to create sysfs attributes\n");
			goto err_sys_creat;
		}
	}

	hrtimer_init(&shield_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	shield_timer.function = ztemt_shield_timer_function;

	ZTEMT_DISP_INFO("success\n");

	return retval;

err_sys_creat:
	for (--attr_count; attr_count >= 0; attr_count--)
		sysfs_remove_file(enhance_kobj, &lcd_disp_attrs[attr_count].attr);

	kobject_put(enhance_kobj);
	return retval;
}

static void __exit ztemt_disp_preference_exit(void)
{
	int attr_count = 0;

	for (attr_count = 0; attr_count < ARRAY_SIZE(lcd_disp_attrs); attr_count++)
		sysfs_remove_file(enhance_kobj, &lcd_disp_attrs[attr_count].attr);

	kobject_put(enhance_kobj);
	ztemt_mdss_dsi_ctrl = NULL;
}

MODULE_AUTHOR("ZTEMT LCD Driver Team Software");
MODULE_DESCRIPTION("ZTEMT LCD DISPLAY Color Saturation and Temperature Setting");
MODULE_LICENSE("GPL");
module_init(ztemt_disp_preference_init);
module_exit(ztemt_disp_preference_exit);
