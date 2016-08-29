#ifndef __ZTEMT_DISP_PREFERENCE_TIANMA_OTM1901A_1080P_5P5_H__
#define __ZTEMT_DISP_PREFERENCE_TIANMA_OTM1901A_1080P_5P5_H__

struct mdp_pcc_cfg_data ztemt_tianma_otm1901a_colortmp_warm = {
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
		.g = 0x7CFF,
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
		.b = 0x7C80,
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

struct mdp_pcc_cfg_data ztemt_tianma_otm1901a_colortmp_normal = {
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
struct mdp_pcc_cfg_data ztemt_tianma_otm1901a_colortmp_cool = {
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

static char tianma_glowc_cmd[] = {
	0x81, 0x83
};
static struct dsi_cmd_desc ztemt_tianma_otm1901a_saturation_glow = {
	{ DTYPE_GEN_LWRITE, 1, 0, 0, 1, sizeof( tianma_glowc_cmd) }, tianma_glowc_cmd
};

static char tianma_std_cmd[] = {
	0x81, 0x81
};

static struct dsi_cmd_desc ztemt_tianma_otm1901a_saturation_std = {
	{ DTYPE_GEN_LWRITE, 1, 0, 0, 1, sizeof( tianma_std_cmd) }, tianma_std_cmd
};

static char tianma_soft_cmd[] = {
	0x81, 0x80
};

static struct dsi_cmd_desc ztemt_tianma_otm1901a_saturation_soft = {
	{ DTYPE_GEN_LWRITE, 1, 0, 0, 1, sizeof( tianma_soft_cmd) }, tianma_soft_cmd
};

#endif
