#ifndef __ET310_LOG__
#define __ET310_LOG__

#define FP_LOG_TAG "FingerPrint"
#define FP_LOG_ON
//#define FP_DEBUG_ON

#ifdef  FP_LOG_ON
#define FP_LOG_ERROR(fmt, args...) printk(KERN_ERR "[%s] [%s: %d] "  fmt, \
	FP_LOG_TAG, __FUNCTION__, __LINE__, ##args)
#define FP_LOG_INFO(fmt, args...) printk(KERN_INFO "[%s] [%s: %d] "  fmt, \
	FP_LOG_TAG, __FUNCTION__, __LINE__, ##args)

    #ifdef  FP_DEBUG_ON
#define  FP_LOG_DEBUG(fmt, args...) printk(KERN_DEBUG "[%s] [%s: %d] "  fmt, \
	FP_LOG_TAG, __FUNCTION__, __LINE__, ##args)
    #else
#define FP_LOG_DEBUG(fmt, args...)
    #endif
#else
#define FP_LOG_ERROR(fmt, args...)
#define FP_LOG_INFO(fmt, args...)
#define FP_LOG_DEBUG(fmt, args...)
#endif

#endif
