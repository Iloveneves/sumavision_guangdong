/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_graphics.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
*************************************************************************/

#if 0
#include "hi_go.h"
#include "hi_struct.h"
#include "hi_unf_disp.h"
#include "hi_unf_hdmi.h"



//#include "debug_common.h"
#include "rocme_porting_graphics.h"
#include "porter_rocme.h"

#define OSD_WIDTH			(1280)
#define OSD_HEIGHT			(720)

#define WIN_480_SCREEN_W	(720)
#define WIN_480_SCREEN_H	(480)

#define WIN_576_SCREEN_W	(720)
#define WIN_576_SCREEN_H	(576)

#define WIN_720_SCREEN_W	(1280)
#define WIN_720_SCREEN_H	(720)

#define WIN_1080_SCREEN_W	(1920)
#define WIN_1080_SCREEN_H	(1080)



#define GUI_DEBUG_
#ifdef GUI_DEBUG
#define GUI_PRINT printf
#else
#define GUI_PRINT
#endif


#if 0
#define CUR_NOT_SUPPORT()\
{\
    printf("sorry, %s current not support.\n",__FUNCTION__);\
    return ROC_OK;\
}
#else
#define CUR_NOT_SUPPORT()	printf("aaa, avplay func = %s, line = %d\n", __FUNCTION__, __LINE__)
#endif


/*width and height of the osd surface to user.*/
#define OSD_WIDTH (1920)
#define OSD_HEIGHT (1080)

#define CHECK_NULL_POINT(ptr)\
if(ptr ==  NULL)\
{\
    GUI_PRINT("Error happens.in fun=%s,line=%d.null point.\n",__FUNCTION__,__LINE__);\
    return ROC_ERR;\
}

#define DO_FAIL_BREAK(fun,nRet,setRet)\
{\
    nRet = (fun);\
    if(ROC_OK != nRet)\
    {\
        GUI_PRINT("Error happens.in fun=%s,line=%d.nRet=%#x.\n",__FUNCTION__,__LINE__,nRet);\
        nRet = setRet;\
        break;\
    }\
}

#define PLANE_VIDEO_ID  1
#define PLANE_LAYER_ID1  2
#define PLANE_LAYER_ID2  3

typedef struct tagGUI_INFO_S
{
    HI_BOOL bInit;
    HI_HANDLE hHdLayer;
    
    HI_HANDLE hOsd2Surface;
    HI_BOOL bOsd2Show;
    HI_BOOL bOsd2RealTime;
    void* pvOsd2Buf;
    /*sd layer surface share to use hHdSurface
    HI_HANDLE hSdSurface;*/

    HI_HANDLE  hVideoSurface;
    HI_BOOL bVideoShow;
    HI_BOOL bVideoRealTime;
    void* pvVideoBuf;
    
    HI_HANDLE hOsd1Surface;
    HI_BOOL bOsd1Show;
    HI_BOOL bOsd1RealTime;
    void* pvOsd1Buf;
}GUI_INFO_S;

static GUI_INFO_S s_stGuiInfo;

static INT32_T GetVideoCfg(Roc_Plane_Cfg_t* pstCfg)
{
    pstCfg->plane_id = PLANE_VIDEO_ID;//?
    pstCfg->plane_type = ROC_PLANE_VIDEO;
    pstCfg->is_complex_pic = ROC_TRUE;
    pstCfg->is_still_image = ROC_TRUE;
    pstCfg->is_flicker_filter = ROC_TRUE;
    pstCfg->area.offset_x = 0;
    pstCfg->area.offset_y = 0;
    pstCfg->area.width = OSD_WIDTH;
    pstCfg->area.height = OSD_HEIGHT;
    pstCfg->buff_parm.width = OSD_WIDTH;
    pstCfg->buff_parm.height = OSD_HEIGHT;
    pstCfg->buff_parm.pitch = OSD_WIDTH*4;
    pstCfg->buff_parm.buff_ptr = s_stGuiInfo.pvVideoBuf;
    pstCfg->buff_parm.buff_len = pstCfg->buff_parm.pitch*pstCfg->buff_parm.height;
    pstCfg->color = ROC_PLANE_COLOR_TYPE_ARGB8888;
    pstCfg->color_depth = 32;/*argb8888*/
    pstCfg->scan_type = ROC_PLANE_SCANTYPE_PROGRESSIVE; 
    pstCfg->aspectratio = ROC_PLANE_AR_16TO9;
    pstCfg->resolution = ROC_PLANE_RS_1920_1080;
    pstCfg->realtime = ROC_FALSE;
    //pstCfg->reserve = 0;

    return ROC_OK;
}

static INT32_T GetOsd1Cfg(Roc_Plane_Cfg_t* pstCfg)
{
    pstCfg->plane_id = PLANE_LAYER_ID1;//?
     pstCfg->plane_type = ROC_PLANE_GRAPHICS;
    pstCfg->is_complex_pic = ROC_TRUE;
    pstCfg->is_still_image = ROC_TRUE;
    pstCfg->is_flicker_filter = ROC_TRUE;
    pstCfg->area.offset_x = 0;
    pstCfg->area.offset_y = 0;
    pstCfg->area.width = OSD_WIDTH;
    pstCfg->area.height = OSD_HEIGHT;
    pstCfg->buff_parm.width = OSD_WIDTH;
    pstCfg->buff_parm.height = OSD_HEIGHT;
    pstCfg->buff_parm.pitch = OSD_WIDTH*4;
    pstCfg->buff_parm.buff_ptr = s_stGuiInfo.pvOsd1Buf;
    pstCfg->buff_parm.buff_len = pstCfg->buff_parm.pitch*pstCfg->buff_parm.height;
    pstCfg->color = ROC_PLANE_COLOR_TYPE_ARGB8888;
    pstCfg->color_depth = 32;/*argb8888*/
    pstCfg->scan_type = ROC_PLANE_SCANTYPE_PROGRESSIVE; 
    pstCfg->aspectratio = ROC_PLANE_AR_16TO9;
    pstCfg->resolution = ROC_PLANE_RS_1920_1080;
    pstCfg->realtime = ROC_FALSE;
    //pstCfg->reserve = 0;

    return ROC_OK;
}


static INT32_T GetOsd2Cfg(Roc_Plane_Cfg_t* pstCfg)
{
    pstCfg->plane_id = PLANE_LAYER_ID2;//?
    pstCfg->plane_type = ROC_PLANE_GRAPHICS;
    pstCfg->is_complex_pic = ROC_TRUE;
    pstCfg->is_still_image = ROC_TRUE;
    pstCfg->is_flicker_filter = ROC_TRUE;
    pstCfg->area.offset_x = 0;
    pstCfg->area.offset_y = 0;
    pstCfg->area.width = OSD_WIDTH;
    pstCfg->area.height = OSD_HEIGHT;
    pstCfg->buff_parm.width = OSD_WIDTH;
    pstCfg->buff_parm.height = OSD_HEIGHT;
    pstCfg->buff_parm.pitch = OSD_WIDTH*4;
    pstCfg->buff_parm.buff_ptr = s_stGuiInfo.pvOsd2Buf;
    pstCfg->buff_parm.buff_len = pstCfg->buff_parm.pitch*pstCfg->buff_parm.height;
    pstCfg->color = ROC_PLANE_COLOR_TYPE_ARGB8888;
    pstCfg->color_depth = 32;/*argb8888*/
    pstCfg->scan_type = ROC_PLANE_SCANTYPE_PROGRESSIVE; 
    pstCfg->aspectratio = ROC_PLANE_AR_16TO9;
    pstCfg->resolution = ROC_PLANE_RS_1920_1080;
    pstCfg->realtime = ROC_FALSE;
    //pstCfg->reserve = 0;

    return ROC_OK;
}


HI_HANDLE Get_Osd_Handle()
{
	return s_stGuiInfo.hHdLayer;
}

static HIGO_PF_E RocColorType2Hisi(Roc_Plane_Color_Type_e enRocColorType)
{
    HIGO_PF_E enHisiColor;
    
    switch(enRocColorType)
    {
        case ROC_PLANE_COLOR_TYPE_ARGB8888 :
            enHisiColor = HIGO_PF_8888;
            break;
        case ROC_PLANE_COLOR_TYPE_ARGB1555:
            enHisiColor = HIGO_PF_1555;
            break;
        case ROC_PLANE_COLOR_TYPE_ARGB8565:
            enHisiColor = HIGO_PF_8565;
            break;
        case ROC_PLANE_COLOR_TYPE_RGB565:
            enHisiColor = HIGO_PF_565;
            break;
        case ROC_PLANE_COLOR_TYPE_ARGB4444:
            enHisiColor = HIGO_PF_4444;
            break;
        case ROC_PLANE_COLOR_TYPE_ALPHA1:
            enHisiColor = HIGO_PF_CLUT1;
            break;
        case ROC_PLANE_COLOR_TYPE_ALPHA4:
            enHisiColor = HIGO_PF_CLUT4;
            break;
        case ROC_PLANE_COLOR_TYPE_ALPHA8:
        case ROC_PLANE_COLOR_TYPE_BYTE:
            enHisiColor = HIGO_PF_CLUT8;
            break;
        case ROC_PLANE_COLOR_TYPE_SIGNED_AYCBCR8888:
        case ROC_PLANE_COLOR_TYPE_UNSIGNED_AYCBCR8888:
        case ROC_PLANE_COLOR_TYPE_PARGB8888:
        case ROC_PLANE_COLOR_TYPE_RGBA8888:
        default:
            enHisiColor =  HIGO_PF_BUTT;
            GUI_PRINT("Error happens.in fun=%s,line=%d.\n",__FUNCTION__,__LINE__);
    }

    return enHisiColor;
}


static HI_S32 CreateSurface(Roc_Plane_Buff_t* pstBuf, Roc_Plane_Color_Type_e enColorType,HI_HANDLE * phSurface)
{
    INT32_T nRet = ROC_OK;
    
    HI_U32 u32PhyAddr;
    HI_U32 u32Size;
    HIGO_SURINFO_S stSurInfo;

    do
    {
        if(pstBuf->buff_ptr == s_stGuiInfo.pvVideoBuf)
        {
            *phSurface = s_stGuiInfo.hVideoSurface;
            break;
        }
        
        if (pstBuf->buff_ptr == s_stGuiInfo.pvOsd1Buf)
        {
            *phSurface = s_stGuiInfo.hOsd1Surface;
            break;
        }

        if(pstBuf->buff_ptr == s_stGuiInfo.pvOsd2Buf)
        {
            *phSurface = s_stGuiInfo.hOsd2Surface;
            break;
        }
    	
        DO_FAIL_BREAK(HI_MMZ_GetPhyaddr(pstBuf->buff_ptr, &u32PhyAddr, &u32Size), nRet, ROC_ERR);

        //printf("pstBuf->buff_ptr=0x%x  nPhyAddr=0x%x\n", (int)pstBuf->buff_ptr, nPhyAddr);
        
        memset(&stSurInfo,0,sizeof(stSurInfo));
        stSurInfo.Width = pstBuf->width;
        stSurInfo.Height = pstBuf->height;
        stSurInfo.Pitch[0] = pstBuf->pitch;
        stSurInfo.pVirAddr[0] = pstBuf->buff_ptr;
        stSurInfo.pPhyAddr[0] = u32PhyAddr;
        stSurInfo.PixelFormat = RocColorType2Hisi(enColorType);
        DO_FAIL_BREAK(HI_GO_CreateSurfaceFromMem(&stSurInfo, phSurface), nRet, ROC_ERR);
    }while(0);

    return nRet;
}

static INT32_T ReleaseSurface(HI_HANDLE hSurface)
{
    if(hSurface == s_stGuiInfo.hVideoSurface)
    {
        return ROC_OK;
    }
    
    if(hSurface == s_stGuiInfo.hOsd1Surface)
    {
        return ROC_OK;
    }

    if(hSurface == s_stGuiInfo.hOsd2Surface)
    {
        return ROC_OK;
    }
    
    if (HI_SUCCESS != HI_GO_FreeSurface(hSurface))
    {
        GUI_PRINT("Error happens.in fun=%s,line=%d.\n",__FUNCTION__,__LINE__);
        return ROC_ERR;
    }

    return ROC_OK;
}

static INT32_T RocAlpha2Hisi(INT32_T nRocAlpha)
{
    #define ROC_ALPHA_MIN 0
    #define ROC_ALPHA_MAX 100
    #define HISI_ALPHA_MIN 0
    #define HISI_ALPHA_MAX 255
    
    INT32_T nHisiAlpha;

    if(nRocAlpha < ROC_ALPHA_MIN) nRocAlpha=ROC_ALPHA_MIN;
    
    if(nRocAlpha > ROC_ALPHA_MAX) nRocAlpha=ROC_ALPHA_MAX;

    nHisiAlpha = (nRocAlpha-ROC_ALPHA_MIN)*(HISI_ALPHA_MAX-HISI_ALPHA_MIN)/(ROC_ALPHA_MAX-ROC_ALPHA_MIN)+HISI_ALPHA_MIN;

    return nHisiAlpha;
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_init
功能说明: 
            初始化各个显示层信息
参数说明：
    输入参数：
            无
    输出参数：
            无
返    回： 
    成功 : 0            ( 初始化成功 )
    失败 : -1 	 ( 失败 )
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_init( void )
{
    INT32_T nRet = ROC_OK;
	HI_U32 u32Width, u32Height;
	HI_UNF_DISP_BG_COLOR_S		BgColor;
	HI_UNF_DISP_INTERFACE_S 	DacMode;


	HI_UNF_ENC_FMT_E eEncFmt = HI_UNF_ENC_FMT_1080i_50;
    HI_PIXELDATA pstData;
    HIGO_LAYER_INFO_S stLayerInfo;

    do
    {


		u32Width = WIN_1080_SCREEN_W;
		u32Height = WIN_1080_SCREEN_H;
#if 1
		nRet = HI_UNF_DISP_Init();
		if (nRet != HI_SUCCESS)
		{
			return nRet;
		}
	
		BgColor.u8Red = 0;
		BgColor.u8Green =0;
		BgColor.u8Blue =0;
		HI_UNF_DISP_SetBgColor(HI_UNF_DISP_HD0, &BgColor);
		HI_UNF_DISP_SetIntfType(HI_UNF_DISP_HD0, HI_UNF_DISP_INTF_TYPE_TV);
		HI_UNF_DISP_SetFormat(HI_UNF_DISP_HD0, eEncFmt);  
	
		nRet = HI_UNF_DISP_GetFormat(HI_UNF_DISP_HD0, &eEncFmt);
		if( HI_SUCCESS == nRet )
		{
			switch( eEncFmt )
			{
			case HI_UNF_ENC_FMT_480P_60:
				u32Width = WIN_480_SCREEN_W;
				u32Height = WIN_480_SCREEN_H;
				break;
	
			case HI_UNF_ENC_FMT_576P_50:
				u32Width = WIN_576_SCREEN_W;
				u32Height = WIN_576_SCREEN_H;
				break;
	
			case HI_UNF_ENC_FMT_720P_50:
			case HI_UNF_ENC_FMT_720P_60:
				u32Width = WIN_720_SCREEN_W;
				u32Height = WIN_720_SCREEN_H;
				break;
	
			default:
				break;
			}
		}
	
		DacMode.bScartEnable = HI_FALSE;
		DacMode.bBt1120Enable = HI_FALSE;
		DacMode.bBt656Enable = HI_FALSE;
	
	//和sample\common\hi_adp_mpi.c中的设置一样,能够正常输出
		DacMode.enDacMode[0] = HI_UNF_DISP_DAC_MODE_HD_Y;
		DacMode.enDacMode[1] = HI_UNF_DISP_DAC_MODE_HD_PR;
		DacMode.enDacMode[2] = HI_UNF_DISP_DAC_MODE_HD_PB;
		DacMode.enDacMode[3] = HI_UNF_DISP_DAC_MODE_SILENCE;
		DacMode.enDacMode[4] = HI_UNF_DISP_DAC_MODE_SILENCE;
		DacMode.enDacMode[5] = HI_UNF_DISP_DAC_MODE_CVBS;  //为了降低功耗3路CVBS只打开一路。
		HI_UNF_DISP_SetDacMode(&DacMode);
		
		nRet = HI_UNF_DISP_Attach(HI_UNF_DISP_SD0, HI_UNF_DISP_HD0);
		if (nRet != HI_SUCCESS)
		{
			HI_UNF_DISP_DeInit();
			return nRet;
		}
		
		nRet = HI_UNF_DISP_Open(HI_UNF_DISP_HD0);
		if (nRet != HI_SUCCESS)
		{
			HI_UNF_DISP_DeInit();
			return nRet;
		}
		
		nRet = HI_UNF_DISP_Open(HI_UNF_DISP_SD0);
		if (nRet != HI_SUCCESS)
		{
			HI_UNF_DISP_Close(HI_UNF_DISP_HD0);
			HI_UNF_DISP_DeInit();
			return nRet;
		}
#endif

	
		nRet = HI_UNF_DISP_GetFormat(HI_UNF_DISP_HD0, &eEncFmt);
		if( HI_SUCCESS == nRet )
		{
			switch( eEncFmt )
			{
			case HI_UNF_ENC_FMT_480P_60:
				u32Width = WIN_480_SCREEN_W;
				u32Height = WIN_480_SCREEN_H;
				break;

			case HI_UNF_ENC_FMT_576P_50:
				u32Width = WIN_576_SCREEN_W;
				u32Height = WIN_576_SCREEN_H;
				break;

			case HI_UNF_ENC_FMT_720P_50:
			case HI_UNF_ENC_FMT_720P_60:
				u32Width = WIN_720_SCREEN_W;
				u32Height = WIN_720_SCREEN_H;
				break;

			default:
				break;
			}
		}
        if(s_stGuiInfo.bInit)
        {
            GUI_PRINT("Warning.fun=%s.line=%d.\n",__FUNCTION__,__LINE__);
            break;
        }

    	/*init disp and higo.*/
        //DO_FAIL_BREAK(HI_SYS_Init(), nRet, ROC_ERR);
        DO_FAIL_BREAK(HI_GO_Init(), nRet, ROC_ERR);
        //DO_FAIL_BREAK(HIADP_Disp_Init(HI_UNF_ENC_FMT_720P_50), nRet, ROC_ERR);

    	/*create hd layer*/
        DO_FAIL_BREAK(HI_GO_GetLayerDefaultParam(HIGO_LAYER_HD_0, &stLayerInfo), nRet, ROC_ERR);
        stLayerInfo.PixelFormat = HIGO_PF_8888;
        stLayerInfo.LayerFlushType = HIGO_LAYER_FLUSH_DOUBBUFER;
        stLayerInfo.ScreenWidth = OSD_WIDTH;
        stLayerInfo.ScreenHeight = OSD_HEIGHT;
        stLayerInfo.DisplayWidth = OSD_WIDTH;
        stLayerInfo.DisplayHeight = OSD_HEIGHT;
 
        DO_FAIL_BREAK(HI_GO_CreateLayer(&stLayerInfo,  &s_stGuiInfo.hHdLayer), nRet, ROC_ERR);
        DO_FAIL_BREAK(HI_GO_GetLayerSurface (s_stGuiInfo.hHdLayer,&s_stGuiInfo.hOsd2Surface), nRet, ROC_ERR);
        GUI_PRINT("fun=%s.line=%d.hd layer param.screen(%d,%d),canvers(%d,%d),disp(%d,%d),flushtype(%d),antil(%d),pixformat(%d),layerId(%d).\n",
            __FUNCTION__,__LINE__,stLayerInfo.ScreenWidth,stLayerInfo.ScreenHeight,
            stLayerInfo.CanvasWidth,stLayerInfo.CanvasHeight,stLayerInfo.DisplayWidth,stLayerInfo.DisplayHeight,
            stLayerInfo.LayerFlushType,stLayerInfo.AntiLevel,stLayerInfo.PixelFormat,stLayerInfo.LayerID);
        DO_FAIL_BREAK(HI_GO_LockSurface(s_stGuiInfo.hOsd2Surface, pstData, HI_TRUE ), nRet, ROC_ERR);
        s_stGuiInfo.pvOsd2Buf = pstData[0].pData;
        DO_FAIL_BREAK(HI_GO_UnlockSurface(s_stGuiInfo.hOsd2Surface), nRet, ROC_ERR);

        DO_FAIL_BREAK(HI_GO_CreateSurface(OSD_WIDTH, OSD_HEIGHT, HIGO_PF_8888, &s_stGuiInfo.hVideoSurface), nRet, ROC_ERR);
        DO_FAIL_BREAK(HI_GO_LockSurface(s_stGuiInfo.hVideoSurface, pstData, HI_TRUE ), nRet, ROC_ERR);
        s_stGuiInfo.pvVideoBuf = pstData[0].pData;
        DO_FAIL_BREAK(HI_GO_UnlockSurface(s_stGuiInfo.hVideoSurface), nRet, ROC_ERR);
        
        DO_FAIL_BREAK(HI_GO_CreateSurface(OSD_WIDTH, OSD_HEIGHT, HIGO_PF_8888, &s_stGuiInfo.hOsd1Surface), nRet, ROC_ERR);
        DO_FAIL_BREAK(HI_GO_LockSurface(s_stGuiInfo.hOsd1Surface, pstData, HI_TRUE ), nRet, ROC_ERR);
        s_stGuiInfo.pvOsd1Buf = pstData[0].pData;
        DO_FAIL_BREAK(HI_GO_UnlockSurface(s_stGuiInfo.hOsd1Surface), nRet, ROC_ERR);

        s_stGuiInfo.bOsd1RealTime = ROC_TRUE;
        s_stGuiInfo.bOsd1Show = ROC_TRUE;
        
        s_stGuiInfo.bOsd2RealTime = ROC_TRUE;
        s_stGuiInfo.bOsd2Show = ROC_TRUE;
        
        s_stGuiInfo.bVideoRealTime = ROC_TRUE;
        s_stGuiInfo.bVideoShow = ROC_TRUE;

        /*sill layer create here?*/
        
        s_stGuiInfo.bInit = ROC_TRUE;
    }while(0);

    return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_get_info
功能说明: 
            获取指定显示层底层是否支持的信息
参数说明：
    输入参数：
            [plane_type  ] : 指定的层
    输出参数：
            [ *number    ] : 底层是否支持此层, <=0 不支持，>0为支持的层数
返    回： 
    成功 : 0            ( 获取硬件平台信息成功 )
    失败 : -1 或 错误码 ( 获取硬件平台信息失败 )
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_get_info( Roc_Plane_Type_e plane_type , INT32_T *number )
{
    CHECK_NULL_POINT(number);

    *number = 0;
    switch(plane_type)
    {
        case ROC_PLANE_GRAPHICS:
            *number = 2;
            break;
        case ROC_PLANE_BACKGROUND:
        case ROC_PLANE_STILLPICTURE:
            break;
        case ROC_PLANE_VIDEO :
            *number = 1;
            break;
        case ROC_PLANE_CURSOR:
        default:
            GUI_PRINT("Warning. in fun=%s,line=%d.\n",__FUNCTION__,__LINE__);
            break;
    }

    return ROC_OK;
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_get_cfg
功能说明: 
            获取指定显示层的当前配置信息,number从1开始
参数说明：
    输入参数：
            [plane_type  ] : 指定的层
            [number      ] : 指定具体的某一层的索引，例如指定第二个osd层，此值为2
    输出参数：
            [*plane_cfg  ] : 指定层的具体配置信息
返    回： 
    成功 : 0            ( 获取硬件平台信息成功 )
    失败 : -1 或 错误码 ( 获取硬件平台信息失败 )
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_get_cfg( Roc_Plane_Type_e plane_type , INT32_T number , Roc_Plane_Cfg_t *plane_cfg )
{
    INT32_T nRet = ROC_ERR;
    
    CHECK_NULL_POINT(plane_cfg);

     switch(plane_type)
    {
        case ROC_PLANE_GRAPHICS:
            {
                if(1 == number)
                {
                    GetOsd1Cfg(plane_cfg);
                }
                else if(2 == number)
                {
                    GetOsd2Cfg(plane_cfg);
                }
            }
            break;
        case ROC_PLANE_BACKGROUND:
        case ROC_PLANE_STILLPICTURE:
            GUI_PRINT("Warning. in fun=%s,line=%d.\n",__FUNCTION__,__LINE__);
            break;
        case ROC_PLANE_VIDEO :
            GetVideoCfg(plane_cfg);
            break;
        case ROC_PLANE_CURSOR:
        default:
            GUI_PRINT("Warning. in fun=%s,line=%d.\n",__FUNCTION__,__LINE__);
            break;
    }

     return ROC_OK;
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_set_cfg
功能说明: 
            设置指定显示层的当前配置信息
参数说明：
    输入参数：
            [*plane_cfg  ] : 指定层的具体配置信息,其中的plane_cfg->plane_id和plane_cfg->plane_type
                             两个参数不可以改动。
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_set_cfg( Roc_Plane_Cfg_t *plane_cfg )
{
    if(PLANE_VIDEO_ID == plane_cfg->plane_id)
    {
        s_stGuiInfo.bVideoRealTime = plane_cfg->realtime;
    }
    if(PLANE_LAYER_ID1 == plane_cfg->plane_id)
    {
        s_stGuiInfo.bOsd1RealTime = plane_cfg->realtime;
    }
    else if(PLANE_LAYER_ID2 == plane_cfg->plane_id)
    {
        s_stGuiInfo.bOsd2RealTime = plane_cfg->realtime;
    }

    return ROC_OK;
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_display
功能说明: 
            开启或关闭指定层是否显示
参数说明：
    输入参数：
            [plane_id   ] : 指定的层的id标识
            [is_on      ] : 是否开启显示,ROC_TRUE~开启； ROC_FALSE~关闭，可以透视到下一层
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_display( const INT32_T plane_id , const ROC_BOOL is_on )
{
    INT32_T nRet = ROC_OK;
    HI_HANDLE hSurface = HI_INVALID_HANDLE;

    do
    {

        if(PLANE_VIDEO_ID == plane_id)
        {
            s_stGuiInfo.bVideoShow = is_on;
        }
        else if(PLANE_LAYER_ID1 == plane_id)
        {
            s_stGuiInfo.bOsd1Show = is_on;
        }
        else if(PLANE_LAYER_ID2 == plane_id)
        {
            s_stGuiInfo.bOsd2Show = is_on;
        }


        if(s_stGuiInfo.bOsd2Show)
        {
            hSurface = s_stGuiInfo.hOsd2Surface;
        }
        else if(s_stGuiInfo.bOsd1Show)
        {
            hSurface = s_stGuiInfo.hOsd1Surface;
        }
        else if(s_stGuiInfo.bVideoShow)
        {
            hSurface = s_stGuiInfo.hVideoSurface;
        }

        if(HI_INVALID_HANDLE == hSurface)
        {
            DO_FAIL_BREAK(HI_GO_ShowLayer(s_stGuiInfo.hHdLayer, HI_FALSE), nRet, ROC_ERR); 
        }
        else
        {
            DO_FAIL_BREAK(HI_GO_SetLayerSurface(s_stGuiInfo.hHdLayer, hSurface), nRet, ROC_ERR);
            DO_FAIL_BREAK(HI_GO_ShowLayer(s_stGuiInfo.hHdLayer, HI_TRUE), nRet, ROC_ERR);
            DO_FAIL_BREAK(HI_GO_RefreshLayer(s_stGuiInfo.hHdLayer,NULL), nRet, ROC_ERR);
        }
        
    }while(0);

    /*need to refresh layer?*/

    return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_remove
功能说明: 
            移除某层上正在显示的图像，并显示为黑场
参数说明：
    输入参数：
            [plane_id   ] : 指定的层的id标识
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_remove( const INT32_T plane_id )
{
    INT32_T nRet = ROC_OK;
    HI_HANDLE hSurface = HI_INVALID_HANDLE;
    HIGO_BLTOPT_S stBlitOpt;

    memset(&stBlitOpt,0,sizeof(HIGO_BLTOPT_S));
    /*need to check plane id?*/

    /*fill full surface black color.*/
    if(PLANE_VIDEO_ID == plane_id)
    {
        hSurface = s_stGuiInfo.hVideoSurface;
    }
    else if(PLANE_LAYER_ID1 == plane_id)
    {
        hSurface = s_stGuiInfo.hOsd1Surface;
    }
    else if(PLANE_LAYER_ID2 == plane_id)
    {
        hSurface  = s_stGuiInfo.hOsd2Surface;
    }


    do
    {
        DO_FAIL_BREAK(HI_GO_FillRect(hSurface, NULL, 0, HIGO_COMPOPT_NONE), nRet, ROC_ERR);

        //DO_FAIL_BREAK(HI_GO_RefreshLayer(s_stGuiInfo.hHdLayer, NULL), nRet, ROC_ERR);
    }while(0);

    return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_update
功能说明: 
            当函数rocme_porting_plane_get_cfg返回的参数plane_cfg->realtime=ROC_FALSE，
        说明此层不支持实时更新，需要在调用函数rocme_porting_plane_fill_color或函数ro-
        -cme_porting_plane_fill_picture后需要调用此函数进行显示的更新。或者当需要使用
        双缓冲机制时，应用可以改变参数plane_cfg->realtime=ROC_FALSE，表明需要实现双缓
        冲，当调用fill_color和fill_picture后会调用此函数显示。
参数说明：
    输入参数：
            [plane_id   ] : 指定的层的id标识
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_update( const INT32_T plane_id, const Roc_Plane_Area_t* area )
{
    INT32_T nRet = ROC_OK;
    HI_HANDLE hSrcSurface = HI_INVALID_HANDLE;

    CHECK_NULL_POINT(area);

    do
    {
         if(PLANE_VIDEO_ID == plane_id)
        {
            hSrcSurface = s_stGuiInfo.hVideoSurface;
        }
        else if(PLANE_LAYER_ID1 == plane_id)
        {
            hSrcSurface = s_stGuiInfo.hOsd1Surface;
        }
        else if(PLANE_LAYER_ID2 == plane_id)
        {
            hSrcSurface = s_stGuiInfo.hOsd2Surface;
        }
        
        DO_FAIL_BREAK(HI_GO_SetLayerSurface(s_stGuiInfo.hHdLayer, hSrcSurface), nRet, ROC_ERR);
        DO_FAIL_BREAK(HI_GO_RefreshLayer(s_stGuiInfo.hHdLayer, (HI_RECT*)area), nRet, ROC_ERR);
    }while(0);

    return nRet;
}

INT32_T rocme_porting_plane_update_ex( const INT32_T plane_id, const Roc_Plane_Area_t* srcArea, const Roc_Plane_Area_t* dstArea )
{
    INT32_T nRet = ROC_OK;
    HI_HANDLE hSrcSurface = HI_INVALID_HANDLE;

    do
    {
         if(PLANE_VIDEO_ID == plane_id)
        {
            hSrcSurface = s_stGuiInfo.hVideoSurface;
        }
        else if(PLANE_LAYER_ID1 == plane_id)
        {
            hSrcSurface = s_stGuiInfo.hOsd1Surface;
        }
        else if(PLANE_LAYER_ID2 == plane_id)
        {
            hSrcSurface = s_stGuiInfo.hOsd2Surface;
        }
        
        DO_FAIL_BREAK(HI_GO_SetLayerSurface(s_stGuiInfo.hHdLayer, hSrcSurface), nRet, ROC_ERR);
        DO_FAIL_BREAK(HI_GO_RefreshLayer(s_stGuiInfo.hHdLayer, NULL), nRet, ROC_ERR);
    }while(0);

    return nRet;
}


/**************************************************************************
函数名称: 
            rocme_porting_plane_fill_color
功能说明: 
            填充某层为一单色
参数说明：
    输入参数：
        [buffer		 ] :要绘图的buffer结构指针
        [color       ] :颜色值,0xaarrggbb格式
        [area        ] :需要填充的坐标及大小，若不支持区域填充则将整层填充
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_fill_color(const Roc_Plane_Buff_t*	buffer,const UINT32_T color, const Roc_Plane_Area_t* area )
{
    INT32_T nRet = ROC_OK;
    HIGO_BLTOPT_S stBlitOpt;

    HI_HANDLE hSurface;
    
    CHECK_NULL_POINT(buffer);
    CHECK_NULL_POINT(area);
    CHECK_NULL_POINT(buffer->buff_ptr);

    memset(&stBlitOpt,0,sizeof(HIGO_BLTOPT_S));
        
    do
    {
        /*need to check buffer param and area param?*/
        DO_FAIL_BREAK(CreateSurface(buffer, ROC_PLANE_COLOR_TYPE_ARGB8888,&hSurface), nRet, ROC_ERR);

        DO_FAIL_BREAK(HI_GO_FillRect(hSurface, (HI_RECT*)area,color,HIGO_COMPOPT_NONE), nRet, ROC_ERR);
        
        DO_FAIL_BREAK(ReleaseSurface(hSurface), nRet, ROC_ERR);

        //DO_FAIL_BREAK(HI_GO_RefreshLayer(s_stGuiInfo.hHdLayer, (HI_RECT*)area), nRet, ROC_ERR);
    }while(0);

    return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_fill_rectangle
功能说明: 
            向某层拷贝矩形bitmap数据
参数说明：
    输入参数：
        [plane_id    ] :指定的层的id标识
        [buff_parm   ] :需要显示填充的数据的参数，包括宽、高、pitch值和数据头指针
        [area        ] :需要填充的坐标及大小，若不支持区域填充则将整层填充
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_fill_rectangle( const INT32_T plane_id , const Roc_Plane_Buff_t *buff_parm , const Roc_Plane_Area_t *area  )
{
    INT32_T nRet = ROC_OK;

    HI_HANDLE hSrcSurface = HI_INVALID_HANDLE;
    HI_HANDLE hDstSurface = HI_INVALID_HANDLE;
    HIGO_BLTOPT_S stBlitOpt;

    CHECK_NULL_POINT(buff_parm);
    CHECK_NULL_POINT(area);
    CHECK_NULL_POINT(buff_parm->buff_ptr);
    
    do
    {
        /*need to check buffer param and area param?*/

        DO_FAIL_BREAK(CreateSurface(buff_parm, ROC_PLANE_COLOR_TYPE_ARGB8888, &hSrcSurface), nRet, ROC_ERR);
 
        memset(&stBlitOpt,0,sizeof(HIGO_BLTOPT_S));

        /*may not needed?*/
        if(PLANE_VIDEO_ID == plane_id)
        {
            hDstSurface = s_stGuiInfo.hVideoSurface;
        }
        if(PLANE_LAYER_ID1 == plane_id)
        {
            hDstSurface = s_stGuiInfo.hOsd1Surface;
        }
        else if(PLANE_LAYER_ID2 == plane_id)
        {
            hDstSurface = s_stGuiInfo.hOsd2Surface;
        }
        
        DO_FAIL_BREAK(HI_GO_Blit(hSrcSurface, (HI_RECT*)area, hDstSurface, (HI_RECT*)area, &stBlitOpt), nRet, ROC_ERR);
        
        DO_FAIL_BREAK(ReleaseSurface(hSrcSurface), nRet, ROC_ERR);

        //DO_FAIL_BREAK(HI_GO_RefreshLayer(s_stGuiInfo.hHdLayer, (HI_RECT*)area), nRet, ROC_ERR);
    }while(0);

    return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_set_alpha
功能说明: 
            设置某层的Alpha(透明度)的相对值，0 ~ 100, 0 - 最小，完全不可见；100 - 最大，OSD完全可见；
        其他值该函数不操作，直接返回-1
参数说明：
    输入参数：
        [plane_id    ] :指定的层的id标识
        [alpha       ] :指定的层的alpha值
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：
     
其他说明:
     
**************************************************************************/
INT32_T rocme_porting_plane_set_alpha( const INT32_T plane_id , const INT32_T alpha )
{
    HI_HANDLE hDstSurface = HI_INVALID_HANDLE;
    INT32_T nHisiAlpha;
    
    nHisiAlpha = RocAlpha2Hisi(alpha);
    
    if(HI_SUCCESS != HI_GO_SetLayerAlpha(s_stGuiInfo.hHdLayer, nHisiAlpha))
    {
        GUI_PRINT("Error happens.in fun=%s,line=%d.\n",__FUNCTION__,__LINE__);
        return ROC_ERR;
    }

    return ROC_OK;
}

/***************************************************************************
函数名称:
        rocme_porting_alpha_blend_blit
功能说明：
        实现硬件BLIT加速alpha混合。
参数说明：
    输入参数：
            [SrcBuf               ] : 源位图的数据存储buff的参数
            [SrcBmp               ] : 源位图的需要拷贝的区域
            [SrcBmpType           ] : 源位图类型 (类似ARGB8888这样的)
            [DstBuf               ] : 目的位图的buff参数
            [DstBmp               ] : 目的位图的需要做alpha_blend的区域
            [DstBmpType           ] : 目的位图类型(Roc_Plane_Color_Type_e)
            [BlitContext          ] : 配置BLIT参数的结构体
    输出参数：
            无
返    回： 
    成功 : 0            ( 填充成功 )
    失败 : -1 或 错误码 ( 填充失败 )
参考实现：
    rocme_graphics.c
其他说明:
    7101新增加的接口
***************************************************************************/
void *pMem = NULL; 
INT32_T rocme_porting_plane_alpha_blend_blit(
    const Roc_Plane_Buff_t *SrcBuf, 
    const Roc_Plane_Area_t *SrcBmp, 
    const Roc_Plane_Color_Type_e    SrcBmpType,             // 源位图类型 (类似ARGB8888这样的)
    const Roc_Plane_Buff_t *DstBuf, 
    const Roc_Plane_Area_t *DstBmp, 
    const Roc_Plane_Color_Type_e	DstBmpType,             // 目的位图类型(Roc_Plane_Color_Type_e)
    Roc_Blit_Context_t  *BlitContext	)
{
    INT32_T nRet = ROC_OK;
    
    HI_HANDLE hSrcSurface = 0;
    HI_HANDLE hDstSurface = 0;
    HI_RECT stSrcRect;
    HI_RECT stDstRect;
    HIGO_BLTOPT_S stBlitOpt;
    HI_PIXELDATA pstData;
    ROC_BOOL bRealTime = ROC_TRUE;
    
    CHECK_NULL_POINT(SrcBuf);
    CHECK_NULL_POINT(SrcBmp);
    CHECK_NULL_POINT(SrcBuf->buff_ptr);

    CHECK_NULL_POINT(DstBuf);
    CHECK_NULL_POINT(DstBmp);
    CHECK_NULL_POINT(DstBuf->buff_ptr);

    CHECK_NULL_POINT(BlitContext);  

    do
    {
        DO_FAIL_BREAK(CreateSurface(DstBuf,DstBmpType,&hDstSurface), nRet, ROC_ERR);
        DO_FAIL_BREAK(CreateSurface(SrcBuf,SrcBmpType,&hSrcSurface), nRet, ROC_ERR);
        

        stSrcRect = *(HI_RECT*)SrcBmp;
        stDstRect = *(HI_RECT*)DstBmp;

        memset(&stBlitOpt,0,sizeof(HIGO_BLTOPT_S));
        /*may not needed?*/

        stBlitOpt.EnableScale = ROC_TRUE;
        //stBlitOpt.EnableGlobalAlpha = ROC_TRUE;//BlitContext->ucGlobalAlpha;

        if(BlitContext->bColorKeyEnable)
        {
            stBlitOpt.ColorKeyFrom = HIGO_CKEY_SRC;
            HI_GO_EnableSurfaceColorKey(hSrcSurface,BlitContext->bColorKeyEnable);
            HI_GO_SetSurfaceColorKey(hSrcSurface,BlitContext->nColorKeyValue);
        }

        if(ROC_BLIT_ALPHA_BLEND==BlitContext->emBlitMode)
        {
                stBlitOpt.EnablePixelAlpha=1;
                stBlitOpt.PixelAlphaComp = HIGO_COMPOPT_SRCOVER;
        }

        DO_FAIL_BREAK(HI_GO_Blit(hSrcSurface, &stSrcRect, hDstSurface, &stDstRect, &stBlitOpt), nRet, ROC_ERR);	

        DO_FAIL_BREAK(ReleaseSurface(hSrcSurface), nRet, ROC_ERR);
        DO_FAIL_BREAK(ReleaseSurface(hDstSurface), nRet, ROC_ERR);

        //DO_FAIL_BREAK(HI_GO_RefreshLayer(s_stGuiInfo.hHdLayer,  &stDstRect), nRet, ROC_ERR);

    }while(0);
}

/***************************************************************************
函数名称:
        rocme_porting_avmem_allocate
功能说明：
        在AVMEM中申请显存空间
参数说明：
    输入参数：
            [         Size] : 需要申请显存空间的大小
            [    Alignment] : 申请显存空间的对齐字节数          
    输出参数：
            无
返    回： 
    成功 : 申请到的显存空间指针  ( 申请成功 )
    失败 : NULL ( 申请失败 )
参考实现：
    rocme_graphics.c
其他说明:
    7101新增加的接口    
***************************************************************************/ 
void * rocme_porting_avmem_allocate( UINT32_T Size, UINT32_T Alignment )
{
	ROCME_TEST_PRINT

    HI_MMZ_BUF_S stMmzBuf;

    
    strcpy(stMmzBuf.bufname, "guiBuf");
    stMmzBuf.bufsize = (Size-1+Alignment)/Alignment*Alignment;/*do Alignment*/

    if(HI_SUCCESS != HI_MMZ_Malloc(&stMmzBuf))
    {
		ROCME_PRINTF(ROCME_LOG_ERROR, "malloc err\n");
        return NULL;
    }

    return stMmzBuf.user_viraddr;

}

/***************************************************************************
函数名称:
        rocme_porting_avmem_deallocate
功能说明：
        释放在AVMEM中申请的显存空间
参数说明：
    输入参数：
            [       pBuffer] : 需要释放的显存空间的指针
    输出参数：
            无
返    回： 
            无
参考实现：
    rocme_graphics.c
其他说明:
    7101新增加的接口
***************************************************************************/ 
void  rocme_porting_avmem_deallocate( void* pBuffer )
{
    INT32_T nSize;
    INT32_T nPhyAddr;
    HI_MMZ_BUF_S stMmzBuf;

    /*this is not mmz mem.*/
    if (HI_SUCCESS != HI_MMZ_GetPhyaddr(pBuffer, &nPhyAddr, &nSize))
    {
        GUI_PRINT("Error happens.in fun=%s,line=%d.\n",__FUNCTION__,__LINE__);
        return;
    }

    stMmzBuf.user_viraddr = pBuffer;
    stMmzBuf.phyaddr = nPhyAddr;

    if(HI_SUCCESS != HI_MMZ_Free(&stMmzBuf))
    {
        GUI_PRINT("Error happens.in fun=%s,line=%d.\n",__FUNCTION__,__LINE__);
    }

    return;
}
#endif

#if 1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

#include "hi_type.h"
#include "hi_unf_disp.h"
#include "hi_go_surface.h"
#include "hi_go_gdev.h"
#include "hi_go_bliter.h"

#include "porter_rocme.h"


#define OSD_WIDTH			(1280)
#define OSD_HEIGHT			(720)

#define WIN_480_SCREEN_W	(720)
#define WIN_480_SCREEN_H	(480)

#define WIN_576_SCREEN_W	(720)
#define WIN_576_SCREEN_H	(576)

#define WIN_720_SCREEN_W	(1280)
#define WIN_720_SCREEN_H	(720)

#define WIN_1080_SCREEN_W	(1920)
#define WIN_1080_SCREEN_H	(1080)


typedef struct tagGFX_MOD_INFO_S
{
	HI_HANDLE		hHdLayer;
	HI_HANDLE		hHdSurface;
	HI_HANDLE		hMidSurface;
	HI_U8			*pOsdBuf;
	HI_U8			*pMidBuf;
	HI_S32			s32Alpha;
	HI_RECT			WinRect;
	pthread_mutex_t	mutex;
	HI_BOOL			bUpdateOsd;
} GFX_MOD_INFO_S;


static HI_BOOL g_GfxInited = HI_FALSE;
static GFX_MOD_INFO_S s_GfxModInfo;


#define GFX_MUTEX_LOCK		pthread_mutex_lock(&s_GfxModInfo.mutex)
#define GFX_MUTEX_UNLOCK	pthread_mutex_unlock(&s_GfxModInfo.mutex)


/**************************************************************************
函数名称: 
            rocme_porting_plane_init
功能说明: 
            初始化各个显示层信息
参数说明：
    输入参数：
            无
    输出参数：
            无
返    回： 
    成功 : 0            ( 初始化成功 )
    失败 : -1 	 ( 失败 )
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_init( void )
{
ROCME_TEST_PRINT
	HI_S32 ret;
	HI_U32 u32Width, u32Height;
	HI_HANDLE hLayer = 0;
	HI_PIXELDATA pData;
	HI_UNF_DISP_BG_COLOR_S		BgColor;
	HI_UNF_DISP_INTERFACE_S 	DacMode;


	HI_UNF_ENC_FMT_E eEncFmt = HI_UNF_ENC_FMT_1080i_50;
	HIGO_LAYER_INFO_S stLayerInfo;

	ROCME_PRINTF(ROCME_LOG_INFO, "call rocme_porting_plane_init\r\n");

	CHK_RETURN( (HI_FALSE == g_GfxInited), ROC_OK);

	memset(&s_GfxModInfo, 0, sizeof(s_GfxModInfo));
	pthread_mutex_init(&s_GfxModInfo.mutex, HI_NULL);
	s_GfxModInfo.bUpdateOsd = HI_FALSE;

	u32Width = WIN_1080_SCREEN_W;
	u32Height = WIN_1080_SCREEN_H;
#if 1
		ret = HI_UNF_DISP_Init();
		if (ret != HI_SUCCESS)
		{
			return ret;
		}
	
		BgColor.u8Red = 0;
		BgColor.u8Green =0;
		BgColor.u8Blue =0;
		HI_UNF_DISP_SetBgColor(HI_UNF_DISP_HD0, &BgColor);
		HI_UNF_DISP_SetIntfType(HI_UNF_DISP_HD0, HI_UNF_DISP_INTF_TYPE_TV);
		HI_UNF_DISP_SetFormat(HI_UNF_DISP_HD0, eEncFmt);  
	
		ret = HI_UNF_DISP_GetFormat(HI_UNF_DISP_HD0, &eEncFmt);
		if( HI_SUCCESS == ret )
		{
			switch( eEncFmt )
			{
			case HI_UNF_ENC_FMT_480P_60:
				u32Width = WIN_480_SCREEN_W;
				u32Height = WIN_480_SCREEN_H;
				break;
	
			case HI_UNF_ENC_FMT_576P_50:
				u32Width = WIN_576_SCREEN_W;
				u32Height = WIN_576_SCREEN_H;
				break;
	
			case HI_UNF_ENC_FMT_720P_50:
			case HI_UNF_ENC_FMT_720P_60:
				u32Width = WIN_720_SCREEN_W;
				u32Height = WIN_720_SCREEN_H;
				break;
	
			default:
				break;
			}
		}
	
		DacMode.bScartEnable = HI_FALSE;
		DacMode.bBt1120Enable = HI_FALSE;
		DacMode.bBt656Enable = HI_FALSE;
	
	//和sample\common\hi_adp_mpi.c中的设置一样,能够正常输出
		DacMode.enDacMode[0] = HI_UNF_DISP_DAC_MODE_HD_Y;
		DacMode.enDacMode[1] = HI_UNF_DISP_DAC_MODE_HD_PR;
		DacMode.enDacMode[2] = HI_UNF_DISP_DAC_MODE_HD_PB;
		DacMode.enDacMode[3] = HI_UNF_DISP_DAC_MODE_SILENCE;
		DacMode.enDacMode[4] = HI_UNF_DISP_DAC_MODE_SILENCE;
		DacMode.enDacMode[5] = HI_UNF_DISP_DAC_MODE_CVBS;  //为了降低功耗3路CVBS只打开一路。
		HI_UNF_DISP_SetDacMode(&DacMode);
		
		ret = HI_UNF_DISP_Attach(HI_UNF_DISP_SD0, HI_UNF_DISP_HD0);
		if (ret != HI_SUCCESS)
		{
			HI_UNF_DISP_DeInit();
			return ret;
		}
		
		ret = HI_UNF_DISP_Open(HI_UNF_DISP_HD0);
		if (ret != HI_SUCCESS)
		{
			HI_UNF_DISP_DeInit();
			return ret;
		}
		
		ret = HI_UNF_DISP_Open(HI_UNF_DISP_SD0);
		if (ret != HI_SUCCESS)
		{
			HI_UNF_DISP_Close(HI_UNF_DISP_HD0);
			HI_UNF_DISP_DeInit();
			return ret;
		}
	#endif

	
	ret = HI_UNF_DISP_GetFormat(HI_UNF_DISP_HD0, &eEncFmt);
	if( HI_SUCCESS == ret )
	{
		switch( eEncFmt )
		{
		case HI_UNF_ENC_FMT_480P_60:
			u32Width = WIN_480_SCREEN_W;
			u32Height = WIN_480_SCREEN_H;
			break;

		case HI_UNF_ENC_FMT_576P_50:
			u32Width = WIN_576_SCREEN_W;
			u32Height = WIN_576_SCREEN_H;
			break;

		case HI_UNF_ENC_FMT_720P_50:
		case HI_UNF_ENC_FMT_720P_60:
			u32Width = WIN_720_SCREEN_W;
			u32Height = WIN_720_SCREEN_H;
			break;

		default:
			break;
		}
	}

	DOFUNC_RETURN_ERR(HI_GO_Init(), ROC_ERR);
	DOFUNC_RETURN_ERR(HI_GO_GetLayerDefaultParam(HIGO_LAYER_HD_0, &stLayerInfo), ROC_ERR);

	stLayerInfo.LayerID = HIGO_LAYER_HD_0;
	stLayerInfo.PixelFormat = HIGO_PF_8888;

	stLayerInfo.CanvasWidth = OSD_WIDTH;
	stLayerInfo.CanvasHeight = OSD_HEIGHT;
	stLayerInfo.DisplayWidth = OSD_WIDTH;
	stLayerInfo.DisplayHeight = OSD_HEIGHT;
	stLayerInfo.ScreenWidth = u32Width;
	stLayerInfo.ScreenHeight = u32Height;

	s_GfxModInfo.WinRect.x = 0;
	s_GfxModInfo.WinRect.y = 0;
	s_GfxModInfo.WinRect.w = OSD_WIDTH;
	s_GfxModInfo.WinRect.h = OSD_HEIGHT;

	DOFUNC_RETURN_ERR(HI_GO_CreateLayer(&stLayerInfo, &hLayer), ROC_ERR);
	DOFUNC_RETURN_ERR(HI_GO_GetLayerSurface(hLayer, &s_GfxModInfo.hHdSurface), ROC_ERR);
	DOFUNC_RETURN_ERR(HI_GO_LockSurface(s_GfxModInfo.hHdSurface, pData, HI_TRUE), ROC_ERR);

	s_GfxModInfo.pOsdBuf = (HI_U8 *)(pData[0].pData);

	ROCME_PRINTF(ROCME_LOG_INFO, "GFX: osd buf addr: %#x\r\n", s_GfxModInfo.pOsdBuf);

	DOFUNC_RETURN_ERR(HI_GO_UnlockSurface(s_GfxModInfo.hHdSurface), ROC_ERR);

	// 创建中间转换的surface
	DOFUNC_RETURN_ERR(HI_GO_CreateSurface(OSD_WIDTH, OSD_HEIGHT, HIGO_PF_8888, &s_GfxModInfo.hMidSurface), ROC_ERR);
	DOFUNC_RETURN_ERR(HI_GO_FillRect(s_GfxModInfo.hMidSurface, NULL, 0, HIGO_COMPOPT_NONE), ROC_ERR);
	DOFUNC_RETURN_ERR(HI_GO_LockSurface(s_GfxModInfo.hMidSurface, pData, HI_TRUE), ROC_ERR);
	s_GfxModInfo.pMidBuf = (HI_U8 *)(pData[0].pData);
	DOFUNC_RETURN_ERR(HI_GO_UnlockSurface(s_GfxModInfo.hMidSurface), ROC_ERR);

	s_GfxModInfo.hHdLayer = hLayer;
	g_GfxInited = HI_TRUE;

	return ROC_OK;
}

HI_HANDLE Get_Osd_Handle()
{
	return s_GfxModInfo.hHdLayer;
}


/**************************************************************************
函数名称: 
            rocme_porting_plane_get_info
功能说明: 
            获取指定显示层底层是否支持的信息
参数说明：
    输入参数：
            [plane_type  ] : 指定的层
    输出参数：
            [ *number    ] : 底层是否支持此层, <=0 不支持，>0为支持的层数
返    回： 
    成功 : 0            ( 获取硬件平台信息成功 )
    失败 : -1 或 错误码 ( 获取硬件平台信息失败 )
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_get_info( Roc_Plane_Type_e plane_type , INT32_T *number )
{
ROCME_TEST_PRINT
	switch( plane_type )
	{
	case ROC_PLANE_GRAPHICS:
		*number = 1;
		break;
	case ROC_PLANE_VIDEO:
	case ROC_PLANE_BACKGROUND:
	case ROC_PLANE_STILLPICTURE:
	case ROC_PLANE_CURSOR:
	default:
		*number =0;
		break;
	}

	return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_plane_get_cfg
功能说明: 
            获取指定显示层的当前配置信息,number从1开始
参数说明：
    输入参数：
            [plane_type  ] : 指定的层
            [number      ] : 指定具体的某一层的索引，例如指定第二个osd层，此值为2
    输出参数：
            [*plane_cfg  ] : 指定层的具体配置信息
返    回： 
    成功 : 0            ( 获取硬件平台信息成功 )
    失败 : -1 或 错误码 ( 获取硬件平台信息失败 )
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_get_cfg( Roc_Plane_Type_e plane_type , INT32_T number , Roc_Plane_Cfg_t *plane_cfg )
{
ROCME_TEST_PRINT
	if( NULL == plane_cfg )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "error params\r\n");
		return ROC_ERR;
	}
	
	ROCME_PRINTF(ROCME_LOG_INFO, "the plane_type = %d, the number = %d\r\n",plane_type,number);
	switch(plane_type)
	{
	case ROC_PLANE_GRAPHICS:
#if 0
	if( number != 1 )
		{
			ROCME_PRINTF(ROCME_LOG_WARN, "ROC_PLANE_GRAPHICS number %d not support\r\n", ROC_PLANE_GRAPHICS);
			return ROC_ERR;
		}
#endif
		break;

	case ROC_PLANE_VIDEO:
	case ROC_PLANE_BACKGROUND:
	case ROC_PLANE_STILLPICTURE:
	case ROC_PLANE_CURSOR:
	default:
		ROCME_PRINTF(ROCME_LOG_WARN, "plane_type %d not support\r\n", plane_type);
		return ROC_ERR;
	}

	plane_cfg->plane_id = 0;
	plane_cfg->plane_type = ROC_PLANE_GRAPHICS;
	plane_cfg->is_complex_pic = ROC_TRUE;
	plane_cfg->is_still_image = ROC_TRUE;
	plane_cfg->is_flicker_filter = ROC_TRUE;

	plane_cfg->area.offset_x = 0;
	plane_cfg->area.offset_y = 0;
	plane_cfg->area.width = OSD_WIDTH;
	plane_cfg->area.height = OSD_HEIGHT;

	plane_cfg->buff_parm.width = OSD_WIDTH;
	plane_cfg->buff_parm.height = OSD_HEIGHT;
	plane_cfg->buff_parm.pitch = OSD_WIDTH * 4;
	plane_cfg->buff_parm.buff_len = OSD_WIDTH * OSD_HEIGHT * 4;
	plane_cfg->buff_parm.buff_ptr = s_GfxModInfo.pMidBuf;

	plane_cfg->color = ROC_PLANE_COLOR_TYPE_ARGB8888;
	plane_cfg->color_depth = 32;
	plane_cfg->scan_type = ROC_PLANE_SCANTYPE_PROGRESSIVE;
	plane_cfg->aspectratio = ROC_PLANE_AR_16TO9;
	plane_cfg->resolution = ROC_PLANE_RS_1280_720;
	plane_cfg->realtime = ROC_FALSE;

	return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_plane_set_cfg
功能说明: 
            设置指定显示层的当前配置信息
参数说明：
    输入参数：
            [*plane_cfg  ] : 指定层的具体配置信息,其中的plane_cfg->plane_id和plane_cfg->plane_type
                             两个参数不可以改动。
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_set_cfg( Roc_Plane_Cfg_t *plane_cfg )
{
ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_plane_display
功能说明: 
            开启或关闭指定层是否显示
参数说明：
    输入参数：
            [plane_id   ] : 指定的层的id标识
            [is_on      ] : 是否开启显示,ROC_TRUE~开启； ROC_FALSE~关闭，可以透视到下一层
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_display( const INT32_T plane_id , const ROC_BOOL is_on )
{
ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_INFO, " plane_id %d\r\n", plane_id);
	if( plane_id != 0 )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
		//return ROC_ERR;
	}

	GFX_MUTEX_LOCK;
	if(is_on)
	{
		HI_GO_SetLayerSurface(s_GfxModInfo.hHdLayer, s_GfxModInfo.hMidSurface);
		HI_GO_ShowLayer(s_GfxModInfo.hHdLayer, HI_TRUE);
		HI_GO_RefreshLayer(s_GfxModInfo.hHdLayer,NULL);
	}
	else
	{
		HI_GO_ShowLayer(s_GfxModInfo.hHdLayer, HI_FALSE);
	}
	GFX_MUTEX_UNLOCK;

	return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_plane_remove
功能说明: 
            移除某层上正在显示的图像，并显示为黑场
参数说明：
    输入参数：
            [plane_id   ] : 指定的层的id标识
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_remove( const INT32_T plane_id )
{
ROCME_TEST_PRINT
	if( plane_id != 0 )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
		//return ROC_ERR;
	}
	
	GFX_MUTEX_LOCK;
	HI_GO_FillRect(s_GfxModInfo.hMidSurface, NULL, 0, HIGO_COMPOPT_NONE);
	GFX_MUTEX_UNLOCK;
	
	return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_plane_update
功能说明: 
            当函数rocme_porting_plane_get_cfg返回的参数plane_cfg->realtime=ROC_FALSE，
        说明此层不支持实时更新，需要在调用函数rocme_porting_plane_fill_color或函数ro-
        -cme_porting_plane_fill_picture后需要调用此函数进行显示的更新。或者当需要使用
        双缓冲机制时，应用可以改变参数plane_cfg->realtime=ROC_FALSE，表明需要实现双缓
        冲，当调用fill_color和fill_picture后会调用此函数显示。
参数说明：
    输入参数：
            [plane_id   ] : 指定的层的id标识
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_update( const INT32_T plane_id, const Roc_Plane_Area_t* area )
{
//ROCME_TEST_PRINT
	int ret = 0;
	HI_RECT rect;
	HIGO_BLTOPT_S bltopt;

	if( plane_id != 0 )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
		//return ROC_ERR;
	}

	if( NULL == area )
	{
		rect.x = s_GfxModInfo.WinRect.x;
		rect.y = s_GfxModInfo.WinRect.y;
		rect.w = s_GfxModInfo.WinRect.w;
		rect.h = s_GfxModInfo.WinRect.h;
	}
	else
	{
		rect.x = area->offset_x;
		rect.y = area->offset_y;
		rect.w = area->width;
		rect.h = area->height;
	}

	GFX_MUTEX_LOCK;
	memset(&bltopt, 0, sizeof(bltopt));
	bltopt.EnablePixelAlpha = HI_FALSE;
	bltopt.PixelAlphaComp = HIGO_COMPOPT_NONE;
	
	ret = HI_GO_StretchBlit(s_GfxModInfo.hMidSurface, &rect, s_GfxModInfo.hHdSurface, &rect, &bltopt);
	if( HI_SUCCESS != ret )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_Blit error. ret = %#x\r\n", ret);
		GFX_MUTEX_UNLOCK;
	}

	ret = HI_GO_RefreshLayer(s_GfxModInfo.hHdLayer, &rect);
	if( HI_SUCCESS != ret )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_RefreshLayer error. ret = %#x\r\n", ret);
		GFX_MUTEX_UNLOCK;
	}

	GFX_MUTEX_UNLOCK;

	return ROC_OK;
}


INT32_T rocme_porting_plane_update_ex( const INT32_T plane_id, const Roc_Plane_Area_t* srcArea, const Roc_Plane_Area_t* dstArea )
{
//ROCME_TEST_PRINT
	int ret = 0;
	HI_RECT srcRect, dstRect;
	HIGO_BLTOPT_S bltopt;
	if( plane_id != 0 )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
		//return ROC_ERR;
	}
	
	if( NULL == srcArea )
	{
		srcRect.x = s_GfxModInfo.WinRect.x;
		srcRect.y = s_GfxModInfo.WinRect.y;
		srcRect.w = s_GfxModInfo.WinRect.w;
		srcRect.h = s_GfxModInfo.WinRect.h;
	}
	else
	{
		srcRect.x = srcArea->offset_x;
		srcRect.y = srcArea->offset_y;
		srcRect.w = srcArea->width;
		srcRect.h = srcArea->height;
	}

	if( NULL == dstArea )
	{
		dstRect.x = s_GfxModInfo.WinRect.x;
		dstRect.y = s_GfxModInfo.WinRect.y;
		dstRect.w = s_GfxModInfo.WinRect.w;
		dstRect.h = s_GfxModInfo.WinRect.h;
	}
	else
	{
		dstRect.x = dstArea->offset_x;
		dstRect.y = dstArea->offset_y;
		dstRect.w = dstArea->width;
		dstRect.h = dstArea->height;
	}

	GFX_MUTEX_LOCK;
	
	memset(&bltopt, 0, sizeof(bltopt));
	bltopt.EnablePixelAlpha = HI_FALSE;
	bltopt.PixelAlphaComp = HIGO_COMPOPT_NONE;
	bltopt.EnableScale = HI_TRUE;
	
	ret = HI_GO_StretchBlit(s_GfxModInfo.hMidSurface, &srcRect, s_GfxModInfo.hHdSurface, &dstRect, &bltopt);
	if( HI_SUCCESS != ret )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_Blit error. ret = %#x\r\n", ret);
		GFX_MUTEX_UNLOCK;
	}
	
	ret = HI_GO_RefreshLayer(s_GfxModInfo.hHdLayer, &dstRect);
	if( HI_SUCCESS != ret )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_RefreshLayer error. ret = %#x\r\n", ret);
		GFX_MUTEX_UNLOCK;
	}
	
	GFX_MUTEX_UNLOCK;
	
	return ROC_OK;
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_fill_color
功能说明: 
            填充某层为一单色
参数说明：
    输入参数：
        [buffer		 ] :要绘图的buffer结构指针
        [color       ] :颜色值,0xaarrggbb格式
        [area        ] :需要填充的坐标及大小，若不支持区域填充则将整层填充
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_fill_color( 
				   const Roc_Plane_Buff_t*	buffer, 
				   const UINT32_T			color, 
				   const Roc_Plane_Area_t*	area 
				   )
{
//ROCME_TEST_PRINT

		if(( NULL == area)||( NULL == buffer)||(NULL == buffer->buff_ptr))
		{
		
			ROCME_PRINTF(ROCME_LOG_ERROR, "param err \r\n");
			return ROC_ERR;
		}
		
#if 1
	HI_S32 ret = HI_SUCCESS;
	HI_HANDLE pSurface;
    HI_U32 u32PhyAddr;
    HI_U32 u32Size;

	HI_MMZ_GetPhyaddr(buffer->buff_ptr, &u32PhyAddr, &u32Size);

	HIGO_SURINFO_S	pSurInfo;
	pSurInfo.Height = buffer->height;
	pSurInfo.Width = buffer->width;
	pSurInfo.MemType = HIGO_MEMTYPE_MMZ;

	pSurInfo.PixelFormat = HIGO_PF_8888;
	pSurInfo.pVirAddr[0] = buffer->buff_ptr;
	pSurInfo.Pitch[0] = buffer->pitch;
	pSurInfo.pPhyAddr[0] = u32PhyAddr;
	

	GFX_MUTEX_LOCK;

	ret = HI_GO_CreateSurfaceFromMem(&pSurInfo,&pSurface);
	if( HI_SUCCESS != ret )
	{
		GFX_MUTEX_UNLOCK;
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_CreateSurfaceFromMem  ret = 0x%08x\n", ret);
		return ROC_ERR;
	}
	
	ret =HI_GO_FillRect(pSurface, (HI_RECT *)area, color, HIGO_COMPOPT_NONE);
	if(HI_SUCCESS != ret )
	{
		HI_GO_FreeSurface(pSurface);		
		GFX_MUTEX_UNLOCK;
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_FillRect  ret = 0x%08x,color = %d\n", ret,color);
		return ROC_ERR;
	}
	HI_GO_FreeSurface(pSurface);
	GFX_MUTEX_UNLOCK;
	return ROC_OK;
#endif
}

/**************************************************************************
函数名称: 
            rocme_porting_plane_fill_rectangle
功能说明: 
            向某层拷贝矩形bitmap数据
参数说明：
    输入参数：
        [plane_id    ] :指定的层的id标识
        [buff_parm   ] :需要显示填充的数据的参数，包括宽、高、pitch值和数据头指针
        [area        ] :需要填充的坐标及大小，若不支持区域填充则将整层填充
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_fill_rectangle( const INT32_T plane_id , const Roc_Plane_Buff_t *buff_parm , const Roc_Plane_Area_t *area  )
{
//ROCME_TEST_PRINT



	if(( NULL == area)||( NULL == buff_parm))
	{
	
		ROCME_PRINTF(ROCME_LOG_ERROR, "param err \r\n");
		return ROC_ERR;
	}


	if (HI_TRUE != g_GfxInited)
	{
		
		ROCME_PRINTF(ROCME_LOG_ERROR, "not init \r\n");
	    return ROC_ERR;
	}

	
	HI_RECT srcRect, desRect;
	HIGO_BLTOPT_S bltopt;
	HI_S32 ret = HI_SUCCESS;
	HIGO_PF_E pixel;
	HI_HANDLE pSurface;


	desRect.x = area->offset_x;
	desRect.y = area->offset_y;
	desRect.w = area->width;
	desRect.h = area->height;

	memset(&bltopt, 0, sizeof(HIGO_BLTOPT_S));
	bltopt.EnablePixelAlpha = HI_FALSE;
	bltopt.PixelAlphaComp = HIGO_COMPOPT_NONE;

  

	HIGO_SURINFO_S	pSurInfo;
	pSurInfo.Height = buff_parm->height;
	pSurInfo.Width = buff_parm->width;
	pSurInfo.MemType = HIGO_MEMTYPE_OS;

	pSurInfo.PixelFormat = HIGO_PF_8888;
	pSurInfo.pVirAddr[0] = buff_parm->buff_ptr;
	pSurInfo.Pitch[0] = buff_parm->pitch;
	
	GFX_MUTEX_LOCK;

	ret = HI_GO_CreateSurfaceFromMem(&pSurInfo,&pSurface);
	if( HI_SUCCESS != ret )
	{
		GFX_MUTEX_UNLOCK;
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_CreateSurfaceFromMem  ret = 0x%08x\n", ret);
		return ROC_ERR;
	}
	
	ret = HI_GO_StretchBlit(pSurface, NULL, s_GfxModInfo.hMidSurface, &desRect, &bltopt);
	if( HI_SUCCESS != ret )
	{
		GFX_MUTEX_UNLOCK;
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_Blit  ret = 0x%08x\n", ret);
		return ROC_ERR;
	}
	ret = HI_GO_FreeSurface(pSurface);
	GFX_MUTEX_UNLOCK;
	return ROC_OK;

}


/**************************************************************************
函数名称: 
            rocme_porting_plane_set_alpha
功能说明: 
            设置某层的Alpha(透明度)的相对值，0 ~ 100, 0 - 最小，完全不可见；100 - 最大，OSD完全可见；
        其他值该函数不操作，直接返回-1
参数说明：
    输入参数：
        [plane_id    ] :指定的层的id标识
        [alpha       ] :指定的层的alpha值
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：
     
其他说明:
     
**************************************************************************/
INT32_T rocme_porting_plane_set_alpha( const INT32_T plane_id , const INT32_T alpha )
{
//ROCME_TEST_PRINT
	int tmp = alpha;

	if( plane_id != 0 )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
		return ROC_ERR;
	}

	if( tmp < 0 || tmp > 100 )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "alpha should in (0 - 100), now: %d\r\n", alpha);
		return ROC_ERR;
	}

	tmp = tmp * 255 / 100;

	GFX_MUTEX_LOCK;
	HI_GO_SetLayerAlpha(s_GfxModInfo.hHdLayer, (HI_U8)tmp);
	GFX_MUTEX_UNLOCK;

	return ROC_OK;
}


HIGO_PF_E PixelFormatChange(Roc_Plane_Color_Type_e    SrcBmpType)
{
    HIGO_PF_E enHisiColor;
    
    switch(SrcBmpType)
    {
        case ROC_PLANE_COLOR_TYPE_ARGB8888 :
            enHisiColor = HIGO_PF_8888;
            break;
        case ROC_PLANE_COLOR_TYPE_ARGB1555:
            enHisiColor = HIGO_PF_1555;
            break;
        case ROC_PLANE_COLOR_TYPE_ARGB8565:
            enHisiColor = HIGO_PF_8565;
            break;
        case ROC_PLANE_COLOR_TYPE_RGB565:
            enHisiColor = HIGO_PF_565;
            break;
        case ROC_PLANE_COLOR_TYPE_ARGB4444:
            enHisiColor = HIGO_PF_4444;
            break;
        case ROC_PLANE_COLOR_TYPE_ALPHA1:
            enHisiColor = HIGO_PF_CLUT1;
            break;
        case ROC_PLANE_COLOR_TYPE_ALPHA4:
            enHisiColor = HIGO_PF_CLUT4;
            break;
        case ROC_PLANE_COLOR_TYPE_ALPHA8:
        case ROC_PLANE_COLOR_TYPE_BYTE:
            enHisiColor = HIGO_PF_CLUT8;
            break;
        case ROC_PLANE_COLOR_TYPE_SIGNED_AYCBCR8888:
        case ROC_PLANE_COLOR_TYPE_UNSIGNED_AYCBCR8888:
        case ROC_PLANE_COLOR_TYPE_PARGB8888:
        case ROC_PLANE_COLOR_TYPE_RGBA8888:
        default:
            enHisiColor =  HIGO_PF_BUTT;
    }

    return enHisiColor;

}



/***************************************************************************
函数名称:
        rocme_porting_alpha_blend_blit
功能说明：
        实现硬件BLIT加速alpha混合。
参数说明：
    输入参数：
            [SrcBuf               ] : 源位图的数据存储buff的参数
            [SrcBmp               ] : 源位图的需要拷贝的区域
            [SrcBmpType           ] : 源位图类型 (类似ARGB8888这样的)
            [DstBuf               ] : 目的位图的buff参数
            [DstBmp               ] : 目的位图的需要做alpha_blend的区域
            [DstBmpType           ] : 目的位图类型(Roc_Plane_Color_Type_e)
            [BlitContext          ] : 配置BLIT参数的结构体
    输出参数：
            无
返    回： 
    成功 : 0            ( 填充成功 )
    失败 : -1 或 错误码 ( 填充失败 )
参考实现：
    rocme_graphics.c
其他说明:
    7101新增加的接口
***************************************************************************/
INT32_T rocme_porting_plane_alpha_blend_blit(
                    const Roc_Plane_Buff_t          *SrcBuf,                 // 源位图的数据存储buff的参数
                    const Roc_Plane_Area_t          *SrcBmp,                 // 源位图的需要拷贝的区域
			        const Roc_Plane_Color_Type_e    SrcBmpType,             // 源位图类型 (类似ARGB8888这样的)
                    const Roc_Plane_Buff_t          *DstBuf,                 // 目的位图的buff参数
                    const Roc_Plane_Area_t          *DstBmp,                 // 目的位图的需要做alpha_blend的区域
                    const Roc_Plane_Color_Type_e	DstBmpType,             // 目的位图类型(Roc_Plane_Color_Type_e)
				    Roc_Blit_Context_t              *BlitContext			// 配置BLIT参数的结构体
					)
{
	//ROCME_TEST_PRINT
	//return ROC_ERR;

	if(( NULL == SrcBuf)||( NULL == DstBuf)||(NULL == SrcBmp)||(NULL == DstBmp))
	{
		
		ROCME_PRINTF(ROCME_LOG_ERROR, "param err\r\n");
		return ROC_ERR;
	}


	if (HI_TRUE != g_GfxInited)
	{	 
		ROCME_PRINTF(ROCME_LOG_ERROR, "not init \r\n");
	    return ROC_ERR;
	}

	
	HI_RECT srcRect, desRect;
	HIGO_BLTOPT_S bltopt;
	HI_S32 ret = HI_SUCCESS;
	HIGO_PF_E pixel;
	HI_U32 u32PhyAddr;
    HI_U32 u32Size;
	HI_HANDLE pSurface;
	HI_HANDLE pDstSurface;


	//ROCME_PRINTF(ROCME_LOG_INFO, "init src handle = 0x%08x,int dst handle = 0x%08x\n",s_GfxModInfo.pOsdBuf,s_GfxModInfo.pMidBuf);
	//ROCME_PRINTF(ROCME_LOG_INFO, "bit src handle = 0x%08x,bit dst handle = 0x%08x\n",SrcBuf->buff_ptr,DstBuf->buff_ptr);

	//ROCME_PRINTF(ROCME_LOG_INFO, "src x = 0x%08x,src y = 0x%08x,src w = 0x%08x,src h = 0x%08x\n",SrcBmp->offset_x,SrcBmp->offset_y,SrcBmp->width,SrcBmp->height);
	//ROCME_PRINTF(ROCME_LOG_INFO, "DstBmp x = 0x%08x,DstBmp y = 0x%08x,DstBmp w = 0x%08x,DstBmp h = 0x%08x,blitmode = %d\n",DstBmp->offset_x,DstBmp->offset_y,DstBmp->width,DstBmp->height,BlitContext->emBlitMode);
	
	srcRect.x = SrcBmp->offset_x;
	srcRect.y = SrcBmp->offset_y;
	srcRect.w = SrcBmp->width;
	srcRect.h = SrcBmp->height;

	desRect.x = DstBmp->offset_x;
	desRect.y = DstBmp->offset_y;
	desRect.w = DstBmp->width;
	desRect.h = DstBmp->height;
	

	pixel = PixelFormatChange(SrcBmpType);
	HI_MMZ_GetPhyaddr(SrcBuf->buff_ptr, &u32PhyAddr, &u32Size);

	HIGO_SURINFO_S	pSurInfo;
	memset(&pSurInfo,0,sizeof(HIGO_SURINFO_S));
	pSurInfo.Height = SrcBuf->height;
	pSurInfo.Width = SrcBuf->width;
	pSurInfo.PixelFormat = pixel;
	pSurInfo.pVirAddr[0] = SrcBuf->buff_ptr;
	pSurInfo.Pitch[0] = SrcBuf->pitch;
	pSurInfo.pPhyAddr[0] = u32PhyAddr;


	
	
	GFX_MUTEX_LOCK;

	ret = HI_GO_CreateSurfaceFromMem(&pSurInfo,&pSurface);
	if( HI_SUCCESS != ret )
	{
		GFX_MUTEX_UNLOCK;
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_CreateSurfaceFromMem  ret = 0x%08x\n", ret);
		return ROC_ERR;
	}

	memset(&bltopt, 0, sizeof(HIGO_BLTOPT_S));

  	if(BlitContext->emBlitMode ==ROC_BLIT_ALPHA_BLEND)
	{
		bltopt.EnablePixelAlpha = HI_TRUE;
		bltopt.PixelAlphaComp = HIGO_COMPOPT_SRCOVER;

	}
	if(BlitContext->bColorKeyEnable)
	{
		bltopt.ColorKeyFrom = HIGO_CKEY_SRC;
		HI_GO_EnableSurfaceColorKey(pSurface,BlitContext->bColorKeyEnable);
		HI_GO_SetSurfaceColorKey(pSurface,BlitContext->nColorKeyValue);
	}

	
	if(DstBuf->buff_ptr != s_GfxModInfo.pMidBuf)
	{
		pixel = PixelFormatChange(DstBmpType);
		HI_MMZ_GetPhyaddr(DstBuf->buff_ptr, &u32PhyAddr, &u32Size);

		HIGO_SURINFO_S	pDstSurInfo;
		memset(&pDstSurInfo,0,sizeof(HIGO_SURINFO_S));
		pDstSurInfo.Height = DstBuf->height;
		pDstSurInfo.Width = DstBuf->width;
		pDstSurInfo.PixelFormat = pixel;
		pDstSurInfo.pVirAddr[0] = DstBuf->buff_ptr;
		pDstSurInfo.Pitch[0] = DstBuf->pitch;
		pDstSurInfo.pPhyAddr[0] = u32PhyAddr;

		ret = HI_GO_CreateSurfaceFromMem(&pDstSurInfo,&pDstSurface);
		if( HI_SUCCESS != ret )
		{
			
			HI_GO_FreeSurface(pSurface);
			GFX_MUTEX_UNLOCK;
			ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_CreateSurfaceFromMem  ret = 0x%08x\n", ret);
			return ROC_ERR;
		}

		ret = HI_GO_Blit(pSurface, &srcRect, pDstSurface, &desRect, &bltopt);
		if( HI_SUCCESS != ret )
		{
			HI_GO_FreeSurface(pSurface);
			HI_GO_FreeSurface(pDstSurface);
			GFX_MUTEX_UNLOCK;
			ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_Blit  ret = 0x%08x\n", ret);
			return ROC_ERR;
		}
		else
		{
			HI_GO_FreeSurface(pSurface);
			HI_GO_FreeSurface(pDstSurface);
			GFX_MUTEX_UNLOCK;
			return ROC_OK;
		}
	}
	else
	{

		ret = HI_GO_Blit(pSurface, &srcRect, s_GfxModInfo.hMidSurface, &desRect, &bltopt);
		if( HI_SUCCESS != ret )
		{
			HI_GO_FreeSurface(pSurface);
			GFX_MUTEX_UNLOCK;
			ROCME_PRINTF(ROCME_LOG_ERROR, "HI_GO_Blit  ret = 0x%08x\n", ret);
			return ROC_ERR;
		}
		else
		{
			HI_GO_FreeSurface(pSurface);
			GFX_MUTEX_UNLOCK;
			return ROC_OK;
		}
	}


	
}




/***************************************************************************
函数名称:
        rocme_porting_avmem_allocate
功能说明：
        在AVMEM中申请显存空间
参数说明：
    输入参数：
            [         Size] : 需要申请显存空间的大小
            [    Alignment] : 申请显存空间的对齐字节数          
    输出参数：
            无
返    回： 
    成功 : 申请到的显存空间指针  ( 申请成功 )
    失败 : NULL ( 申请失败 )
参考实现：
    rocme_graphics.c
其他说明:
    7101新增加的接口    
***************************************************************************/ 
void * rocme_porting_avmem_allocate( UINT32_T Size, UINT32_T Alignment )
{
	//ROCME_TEST_PRINT

    HI_MMZ_BUF_S stMmzBuf;

    
    strcpy(stMmzBuf.bufname, "guiBuf");
    stMmzBuf.bufsize = (Size-1+Alignment)/Alignment*Alignment;/*do Alignment*/

    if(HI_SUCCESS != HI_MMZ_Malloc(&stMmzBuf))
    {
		ROCME_PRINTF(ROCME_LOG_ERROR, "malloc err\n");
        return NULL;
    }

    return stMmzBuf.user_viraddr;

}


/***************************************************************************
函数名称:
        rocme_porting_avmem_deallocate
功能说明：
        释放在AVMEM中申请的显存空间
参数说明：
    输入参数：
            [       pBuffer] : 需要释放的显存空间的指针
    输出参数：
            无
返    回： 
            无
参考实现：
    rocme_graphics.c
其他说明:
    7101新增加的接口
***************************************************************************/ 
void  rocme_porting_avmem_deallocate( void* pBuffer )
{
	//ROCME_TEST_PRINT
    INT32_T nSize;
    INT32_T nPhyAddr;
    HI_MMZ_BUF_S stMmzBuf;

    /*this is not mmz mem.*/
    if (HI_SUCCESS != HI_MMZ_GetPhyaddr(pBuffer, &nPhyAddr, &nSize))
    {
		ROCME_PRINTF(ROCME_LOG_ERROR, "this is not mmz mem\n");
        return;
    }

    stMmzBuf.user_viraddr = pBuffer;
    stMmzBuf.phyaddr = nPhyAddr;

    if(HI_SUCCESS != HI_MMZ_Free(&stMmzBuf))
    {
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_MMZ_Free  err\n");
    }

    return;

}
#endif



