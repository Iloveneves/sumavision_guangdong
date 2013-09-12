/**
 \file
 \brief Subtitle outputģ��
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author 
 \date 2010-03-10
 */

#ifndef __HI_UNF_SO_H__
#define __HI_UNF_SO_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Macro Definition ****************************/
#define HI_UNF_SO_PALETTE_ENTRY (256)    /**< ��ɫ����ɫ���� */
#define HI_UNF_SO_NO_PTS        (-1)

/*************************** Structure Definition ****************************/

/** ��Ļ���� */
typedef enum hiUNF_SO_SUBTITLE_TYPE_E
{
    HI_UNF_SUBTITLE_BITMAP = 0x0,  /**< ͼ����Ļ */
    HI_UNF_SUBTITLE_TEXT,          /**< string��Ļ */
    HI_UNF_SUBTITLE_ASS,           /**< ass��Ļ */
    HI_UNF_SUBTITLE_BUTT
} HI_UNF_SO_SUBTITLE_TYPE_E;

/** ��ʾ��Ϣ������teltext������ʾ�Ͳ���������Ϣ */
typedef enum hiUNF_SO_DISP_MSG_TYPE_E
{
	HI_UNF_SO_DISP_MSG_NORM  = 0x0,     /**< ������ʾ���� */
	HI_UNF_SO_DISP_MSG_ERASE,           /**< ���� */
	HI_UNF_SO_DISP_MSG_END              /**< ��ҳ��ʾ���� */
} HI_UNF_SO_DISP_MSG_TYPE_E;

/** ��ɫ�ṹ */
typedef struct hiUNF_SO_COLOR_S
{
    HI_U8 u8Red;      /**< R������ɫֵ */
    HI_U8 u8Green;    /**< G������ɫֵ */
    HI_U8 u8Blue;     /**< B������ɫֵ */
    HI_U8 u8Alpha;    /**< ͸���� */
} HI_UNF_SO_COLOR_S;

/** ͼ����Ļ��Ϣ */
typedef struct hiUNF_SO_GFX_S
{
    HI_S64 s64Pts;         /**< ��ʾʱ��� */
	HI_U32 u32Duration;    /**< ��ʾʱ�� */
    HI_U32 u32Len;         /**< ���ݳ��� */
	HI_U8  *pu8PixData;    /**< ͼ������ */

    HI_UNF_SO_DISP_MSG_TYPE_E enMsgType;                   /**< ��ʾ��Ϣ���� */  
    HI_UNF_SO_COLOR_S stPalette[HI_UNF_SO_PALETTE_ENTRY];  /**< ��ɫ�� */
	HI_S32 s32BitWidth;    /**< ����λ�� , ����Ϊ 2,4,8λ*/
    HI_U32 x, y, w, h;     /**< ��ʾλ�ú͸߿���Ϣ */
} HI_UNF_SO_GFX_S;

/** �ı���Ļ��Ϣ */
typedef struct hiUNF_SO_TEXT_S
{
    HI_S64 s64Pts;              /**< ��ʾʱ��� */
    HI_U32 u32Duration;         /**< ��ʾʱ�� */
    HI_U32 u32Len;              /**< ��Ļ���ݳ��� */
    HI_U8 *pu8Data;             /**< ��Ļ���� */

    HI_U32 x, y, w, h;          /**< ��ʾλ�ú͸߿���Ϣ */
} HI_UNF_SO_TEXT_S;

/** ass��Ļ��Ϣ */
typedef struct hiUNF_SO_ASS_S
{
    HI_S64 s64Pts;                /**< ��ʾʱ��� */
    HI_U32 u32Duration;           /**< ��ʾʱ�� */
    HI_U32 u32FrameLen;           /**< ֡���� */
    HI_U8  *pu8EventData;         /**< ֡���� */
    HI_U32 u32ExtradataSize;      /**< ��չ���ݳ��� */
    HI_U8  *pu8Extradata;         /**< ��չ���� */
} HI_UNF_SO_ASS_S;

typedef struct hiUNF_SO_SUBTITLE_INFO_S
{
    HI_UNF_SO_SUBTITLE_TYPE_E eType;

    union
    {
        HI_UNF_SO_GFX_S  stGfx;
        HI_UNF_SO_TEXT_S stText;
        HI_UNF_SO_ASS_S  stAss;
    } unSubtitleParam;
} HI_UNF_SO_SUBTITLE_INFO_S;

/** 
\brief ��ȡ��ǰ����֡��ʱ����������ǰʱ����Ч��ps64CurrentPts��ֵΪHI_UNF_SO_NO_PTS
\attention \n
��
\param[in] u32UserData ע�ᴫ����û�����
\param[out] ps64CurrentPts ��ǰ����֡ʱ�������λms 

\retval ::HI_SUCCESS

\see \n
��
*/
typedef HI_S32 (*HI_UNF_SO_GETPTS_FN)(HI_U32 u32UserData, HI_S64 *ps64CurrentPts);

/** 
\brief ��Ļ��ͼ�ص�����
\attention \n
��
\param[in] u32UserData ע�ᴫ����û�����
\param[in] pstInfo ��Ļ��Ϣ
\param[in] pArg ��չ����

\retval ::HI_SUCCESS

\see \n
��
*/
typedef HI_S32 (*HI_UNF_SO_ONDRAW_FN)(HI_U32 u32UserData, const HI_UNF_SO_SUBTITLE_INFO_S *pstInfo, HI_VOID *pArg);

/** 
\brief ��Ļ��ʾ��ʱ�������
\attention \n
��
\param[in] u32UserData ע�ᴫ����û�����

\retval ::HI_SUCCESS

\see \n
��
*/
typedef HI_S32 (*HI_UNF_SO_ONCLEAR_FN)(HI_U32 u32UserData);

/******************************* API declaration *****************************/

/**
\brief  subtitle outputģ���ʼ��
\attention \n
��
\param ��

\retval ::HI_SUCCESS  ��ʼ���ɹ�
\retval ::HI_FAILURE  ��ʼ��ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_Init(HI_VOID);

/**
\brief  subtitle outputģ��ȥ��ʼ��
\attention \n
��
\param ��

\retval ::HI_SUCCESS  ȥ��ʼ���ɹ�
\retval ::HI_FAILURE  ȥ��ʼ��ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_DeInit(HI_VOID);

/**
\brief  ����һ��soʵ��
\attention \n
��
\param[out] phdl ������ʵ��

\retval ::HI_SUCCESS  �����ɹ��������Ч
\retval ::HI_FAILURE  ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_Create(HI_HANDLE *phdl);

/**
\brief  ����һ��soʵ��
\attention \n
��
\param[in] handle soʵ�����

\retval ::HI_SUCCESS  ���ٳɹ�
\retval ::HI_FAILURE  ����ʧ�ܣ������Ƿ�

\see \n
��
*/
HI_S32 HI_UNF_SO_Destroy(HI_HANDLE handle);

/**
\brief  ע��ʱ�����ȡ�ص�������soͨ����ȡ��ǰ����ʱ���ͬ����Ļ
\attention \n
��
\param[in] handle soʵ�����
\param[in] pstCallback �ص���������
\param[in] u32UserData �û�����

\retval ::HI_SUCCESS  ע��ɹ�
\retval ::HI_FAILURE  ע��ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_RegGetPtsCb(HI_HANDLE handle, HI_UNF_SO_GETPTS_FN pstCallback, HI_U32 u32UserData);

/**
\brief  ע����Ļ��������ص���������������˸ú�������soʹ�øú���ʵ����Ļ�����
        ��Ļ��ʾʱ�������so�����������֪ͨ���
\attention \n
��
\param[in] handle soʵ�����
\param[in] pfnOnDraw ���ƺ���
\param[in] pfnOnClear �������
\param[in] u32UserData �û�����

\retval ::HI_SUCCESS  ע��ɹ�
\retval ::HI_FAILURE  ע��ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_RegOnDrawCb(HI_HANDLE handle, HI_UNF_SO_ONDRAW_FN pfnOnDraw,
                                          HI_UNF_SO_ONCLEAR_FN pfnOnClear, HI_U32 u32UserData);

/**
\brief  ������Ļ���ƻ�����������û������ondraw�ص���������soʹ�����õĻ�����������Ļ
\attention \n
��
\param[in] handle soʵ�����
\param[in] hSurfaceHandle �������

\retval ::HI_SUCCESS  ���óɹ�
\retval ::HI_FAILURE  ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_SetDrawSurface(HI_HANDLE handle, HI_HANDLE hSurfaceHandle);

/**
\brief  ������Ļ��ʾ���壬�����ý������û��������Ļ�ķ�ʽ������
\attention \n
��
\param[in] handle soʵ�����
\param[in] hFont ������������

\retval ::HI_SUCCESS  ���óɹ�
\retval ::HI_FAILURE  ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_SetFont(HI_HANDLE handle, HI_HANDLE hFont);

/**
\brief  ������Ļ��ʾ��ɫ�������ý������û��������Ļ�ķ�ʽ������
\attention \n
��
\param[in] handle soʵ�����
\param[in] u32Color ��ɫֵ

\retval ::HI_SUCCESS  ���óɹ�
\retval ::HI_FAILURE  ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_SetColor(HI_HANDLE handle, HI_U32 u32Color);

/**
\brief  ������Ļ��ʾ���꣬�����ý������û��������Ļ�ķ�ʽ������
\attention \n
��
\param[in] handle soʵ�����
\param[in] u32x x����
\param[in] u32y y����

\retval ::HI_SUCCESS  ���óɹ�
\retval ::HI_FAILURE  ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_SetPos(HI_HANDLE handle, HI_U32 u32x, HI_U32 u32y);

/**
\brief  ��ȡ����buffer��δ��ʾ����Ļ���ݸ���
\attention \n
��
\param[in] handle soʵ�����
\param[out] pu32SubNum ������Ļ����

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_GetSubNumInBuff(HI_HANDLE handle, HI_U32 *pu32SubNum);

/**
\brief  �����Ļ�����е����ݣ���Ļ�л�ʱ������øýӿ����so��Ļ����
\attention \n
��
\param[in] handle soʵ�����

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_ResetSubBuf(HI_HANDLE handle);

/**
\brief  ������Ļ���ݸ�so
\attention \n
��
\param[in] handle soʵ�����
\param[in] pstSubInfo ��Ļ��Ϣ
\param[in] u32TimeOut ���ͳ�ʱʱ�䣬��λms

\retval ::HI_SUCCESS  ���ͳɹ�
\retval ::HI_FAILURE  ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_SO_SendData(HI_HANDLE handle, const HI_UNF_SO_SUBTITLE_INFO_S *pstSubInfo, HI_U32 u32TimeOutMs);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_SO_H__ */

