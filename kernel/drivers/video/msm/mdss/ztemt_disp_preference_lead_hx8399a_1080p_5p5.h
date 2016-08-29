#ifndef __ZTEMT_DISP_PREFERENCE_LEAD_HX8399A_1080P_5P5_H__
#define __ZTEMT_DISP_PREFERENCE_LEAD_HX8399A_1080P_5P5_H__

struct mdp_pcc_cfg_data ztemt_lead_hx8399a_colortmp_warm = {
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
		.g = 0x7A00,
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
		.b = 0x7900,
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

struct mdp_pcc_cfg_data ztemt_lead_hx8399a_colortmp_normal = {
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
struct mdp_pcc_cfg_data ztemt_lead_hx8399a_colortmp_cool = {
	.block = 0x10,
	.ops = 0x5,
    {
		.c = 0,
		.r = 0x7B00,
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

static char lead_glow_cmd[] = {
	0xE4, 0x01, 0x03,
};
static struct dsi_cmd_desc ztemt_lead_hx8399a_saturation_glow = {
	{ DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(lead_glow_cmd) }, lead_glow_cmd
};

static char lead_std_cmd[] = {
	0xE4, 0x01, 0x01,
};

static struct dsi_cmd_desc ztemt_lead_hx8399a_saturation_std = {
	{ DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(lead_std_cmd) }, lead_std_cmd
};

static char lead_soft_cmd[] = {
	0xE4, 0x00, 0x00,
};

static struct dsi_cmd_desc ztemt_lead_hx8399a_saturation_soft= {
	{ DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(lead_soft_cmd) }, lead_soft_cmd
};

#endif
