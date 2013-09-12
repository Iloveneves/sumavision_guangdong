
#ifndef _PORTER_ROCME_H_
#define _PORTER_ROCME_H_


#define HISI_WIN_1080_SCREEN_W    (1920)
#define HISI_WIN_1080_SCREEN_H    (1080)
#define HISI_WIN_720_SCREEN_W     (1280)
#define HISI_WIN_720_SCREEN_H     (720)
#define HISI_WIN_576_SCREEN_W     (720)
#define HISI_WIN_576_SCREEN_H     (576)
#define HISI_WIN_480_SCREEN_W     (720)
#define HISI_WIN_480_SCREEN_H     (480)


#define ROCME_DEBUG_FLAG	(1)
#define ROCME_LOG_INFO		(0)
#define ROCME_LOG_WARN		(1)
#define ROCME_LOG_ERROR		(2)
#define ROCME_LOG_FORCE		(3)
#define ROCME_LOG_LEVEL		(ROCME_LOG_INFO)

#if ROCME_DEBUG_FLAG

#define ROCME_PRINTF(level, fmt, arg...) \
	if( level >= ROCME_LOG_LEVEL ) \
	{ \
		switch( level ) \
		{ \
		case ROCME_LOG_INFO: \
			printf("[--INFO--] "); \
			break; \
		case ROCME_LOG_WARN: \
			printf("[--WARN--] "); \
			break; \
		case ROCME_LOG_ERROR: \
			printf("[--ERROR--] "); \
			break; \
		case ROCME_LOG_FORCE: \
			printf("[--FORCE--] "); \
			break; \
		} \
		printf("line: %d, func: %s ", __LINE__, __FUNCTION__); \
		printf(fmt, ##arg); \
	}

#define ROCME_PRINTF0(level, fmt, arg...) \
	if( level > ROCME_LOG_LEVEL ) \
	{ \
		printf(fmt, ##arg); \
	}

#else

#define ROCME_PRINTF(level, fmt, arg...)
#define ROCME_PRINTF0(level, fmt, arg...)

#endif

#define ROCME_TEST_PRINT ROCME_PRINTF(ROCME_LOG_INFO,"call this func\r\n");

// 如果func执行失败，只打印出错信息
#define DOFUNC(func) \
	do { \
		int ret = func; \
		if( 0 != ret ) \
		{ \
			ROCME_PRINTF(ROCME_LOG_ERROR, "%s failed. ret = %#x\r\n", #func, ret); \
		} \
	} while(0)

// 如果func执行失败，则直接返回
#define DOFUNC_RETURN(func) \
	do { \
		int ret = func; \
		if( 0 != ret ) \
		{ \
			ROCME_PRINTF(ROCME_LOG_ERROR, "%s failed. ret = %#x\r\n", #func, ret); \
			return ret; \
		} \
	} while(0)

// 如果func执行失败，则直接返回err
#define DOFUNC_RETURN_ERR(func, err) \
	do { \
		int ret = func; \
		if( 0 != ret ) \
		{ \
			ROCME_PRINTF(ROCME_LOG_ERROR, "%s failed. ret = %#x\r\n", #func, ret); \
			return err; \
		} \
	} while(0)

// 如果func执行失败，则直接空返回
#define DOFUNC_RETURN_VOID(func) \
	do { \
		int ret = func; \
		if( 0 != ret ) \
		{ \
			ROCME_PRINTF(ROCME_LOG_ERROR, "%s failed. ret = %#x\r\n", #func, ret); \
			return ;\
		} \
	} while(0)

// 如果func执行失败，则直接返回
#define CHK_RETURN(val, ret) \
	do { \
		if( !(val) ) \
		{ \
			ROCME_PRINTF(ROCME_LOG_ERROR, "failed. ret = %#x\r\n", ret); \
			return ret; \
		} \
	} while(0)



#include "rocme_porting_typedef.h"
#include "rocme_porting_api.h"
#include "rocme_porting_av.h"
#include "rocme_porting_base.h"
#include "rocme_porting_cas.h"
#include "rocme_porting_demux.h"
#include "rocme_porting_eeprom.h"
#include "rocme_porting_errno.h"
#include "rocme_porting_event.h"
#include "rocme_porting_file.h"
#include "rocme_porting_flash.h"
#include "rocme_porting_frontpanel.h"
#include "rocme_porting_graphics.h"
#include "rocme_porting_media.h"
#include "rocme_porting_mediaplayer.h"
#include "rocme_porting_network.h"
#include "rocme_porting_osp.h"
#include "rocme_porting_product.h"
#include "rocme_porting_smartcard.h"
#include "rocme_porting_socket.h"
#include "rocme_porting_stbInfo.h"
#include "rocme_porting_tuner.h"
#include "rocme_porting_upgrade.h"
#include "rocme_porting_player.h"



#endif //_PORTER_ROCME_H_
