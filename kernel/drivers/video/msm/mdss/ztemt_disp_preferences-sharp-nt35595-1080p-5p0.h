#ifndef __ZTE_DISP_PREFERENCES_SHARP_NT35595_1080P_5P0
#define __ZTE_DISP_PREFERENCES_SHARP_NT35595_1080P_5P0

#define SHARP_NT35595_1080P_5P0_STD_CMD_COUNT (sizeof(sharp_nt35595_1080p_5p0_standard)/sizeof(sharp_nt35595_1080p_5p0_standard[0]))
#define SHARP_NT35595_1080P_5P0_GLOW_CMD_COUNT (sizeof(sharp_nt35595_1080p_5p0_glow)/sizeof(sharp_nt35595_1080p_5p0_glow[0]))
#define SHARP_NT35595_1080P_5P0_SOFT_CMD_COUNT (sizeof(sharp_nt35595_1080p_5p0_soft)/sizeof(sharp_nt35595_1080p_5p0_soft[0]))
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


static char nt35595_55B0[] = {0x55, 0x90};
static char nt35595_5580[] = {0x55, 0x80};
static char nt35595_5500[] = {0x55, 0x00};

static char nt35595_FF03[] = {0xFF, 0x22};
static char nt35595_14[] = {0x14, 0x07};
static char nt35595_15[] = {0x15, 0x08};
static char nt35595_1A[] = {0x1A, 0x77};
static char nt35595_56[] = {0x56, 0x00};
static char nt35595_68[] = {0x68, 0x00};
static char nt35595_FB[] = {0xFB, 0x01};
static char nt35595_FF00[] = {0xFF, 0x10};
static struct dsi_cmd_desc sharp_nt35595_1080p_5p0_glow[] = {
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_FF03)}, nt35595_FF03},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_14)}, nt35595_14},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_15)}, nt35595_15},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_1A)}, nt35595_1A},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_56)}, nt35595_56},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_68)}, nt35595_68},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_FB)}, nt35595_FB},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_FF00)}, nt35595_FF00},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_55B0)}, nt35595_55B0},

};
static struct dsi_cmd_desc sharp_nt35595_1080p_5p0_soft[] = {
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_5500)}, nt35595_5500},

};
static struct dsi_cmd_desc sharp_nt35595_1080p_5p0_standard[] = {
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_FF03)}, nt35595_FF03},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_14)}, nt35595_14},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_15)}, nt35595_15},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_1A)}, nt35595_1A},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_56)}, nt35595_56},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_68)}, nt35595_68},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_FB)}, nt35595_FB},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_FF00)}, nt35595_FF00},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35595_5580)}, nt35595_5580},
};
#endif
