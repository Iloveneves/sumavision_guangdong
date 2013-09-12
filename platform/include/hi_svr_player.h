/**
 \file
 \brief svr playerģ��
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author 
 \date 2010-02-10
 */

#ifndef __HI_SVR_PLAYER_H__
#define __HI_SVR_PLAYER_H__

#include "hi_type.h"
#include "hi_svr_format.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2 */
/** @{ */  /** <!-- ��Hiplayer���ݽṹ�� */

/** �Ƿ���� */
#define HI_SVR_PLAYER_INVALID_HDL        (0)   
/** �����ٶȲ��� */  
#define HI_SVR_PLAYER_PLAY_SPEED_NORMAL  (1024)  

/** ���õ��ļ����� */
typedef enum hiSVR_PLAYER_MEDIA_PARAM_E
{
    HI_SVR_PLAYER_MEDIA_STREAMFILE = (1 << 0),    /**< ����Ƶý���ļ� */
    HI_SVR_PLAYER_MEDIA_SUBTITLE   = (1 << 1),    /**< ��Ļ�ļ� */
    HI_SVR_PLAYER_MEDIA_BUTT       = (1 << 2)
} HI_SVR_PLAYER_MEDIA_PARAM_E;

/** ����������ID */
typedef enum hiSVR_PLAYER_ATTR_E
{
    HI_SVR_PLAYER_ATTR_STREAMID = 0x0,         /**< ����/��ȡ����ţ���������Զ���Ƶ������Ƶ�������������Ϊ::HI_SVR_PLAYER_STREAMID_S */
    HI_SVR_PLAYER_ATTR_WINDOW_HDL,             /**< ��ȡwindow id������ΪHI_U32���� */
    HI_SVR_PLAYER_ATTR_AVPLAYER_HDL,           /**< ��ȡAVPlayer���������ΪHI_HANDLE���� */
    HI_SVR_PLAYER_ATTR_SO_HDL,                 /**< ��ȡso���������ΪHI_HANDLE���� */
    HI_SVR_PLAYER_ATTR_BUTT
} HI_SVR_PLAYER_ATTR_E;

/** PLAYER״̬ */
typedef enum hiSVR_PLAYER_STATE_E
{
    HI_SVR_PLAYER_STATE_INI = 0,    /**< ��������ǰ���ڳ�ʼ״̬��create�󲥷�������ini״̬ */
    HI_SVR_PLAYER_STATE_DEINI,      /**< �������Ѿ�ȥ��ʼ״̬ */
    HI_SVR_PLAYER_STATE_PLAY,       /**< ��������ǰ���ڲ���״̬ */
    HI_SVR_PLAYER_STATE_FORWARD,    /**< ��������ǰ���ڿ��״̬ */
    HI_SVR_PLAYER_STATE_BACKWARD,   /**< ��������ǰ���ڿ���״̬ */
    HI_SVR_PLAYER_STATE_PAUSE,      /**< ��������ǰ������ͣ״̬ */
    HI_SVR_PLAYER_STATE_STOP,       /**< ��������ǰ����ֹͣ״̬ */
    HI_SVR_PLAYER_STATE_BUTT
} HI_SVR_PLAYER_STATE_E;

/** �¼����� */
typedef enum hiSVR_PLAYER_EVENT_E
{
    HI_SVR_PLAYER_EVENT_STATE = 0x0,   /**< ������״̬ת���¼�������ֵΪ::HI_SVR_PLAYER_STATE_E */
    HI_SVR_PLAYER_EVENT_SOF,           /**< �ļ���ʼ���Ż���˵��ļ�ͷ�¼�����������ΪHI_U32��
                                            ֵΪ::HI_SVR_PLAYER_STATE_PLAY��ʾ��ʼ���ţ�����ֵΪ::HI_SVR_PLAYER_STATE_BACKWARD��ʾ���˵��ļ�ͷ */
    HI_SVR_PLAYER_EVENT_EOF,           /**< �ļ����ŵ�β�¼����޲��� */
    HI_SVR_PLAYER_EVENT_PROGRESS,      /**< ��������ǰ���Ž����¼���ÿ��500ms�ϱ�һ�θ��¼�������ֵΪHI_U32���ͱ�����ֵ0-100 */
    HI_SVR_PLAYER_EVENT_STREAMID_CHG,  /**< stream id �����仯�¼�������Ϊ::HI_SVR_PLAYER_STREAMID_S */
    HI_SVR_PLAYER_EVENT_BUTT
} HI_SVR_PLAYER_EVENT_E;

/** ע��Ķ�̬������ */
typedef enum hiSVR_PLAYER_DLLTYPE_E
{
    HI_SVR_PLAYER_DLL_PARSER = 0x0,    /**< ����Ƶý���ļ���������Ļ������̬�� */
    HI_SVR_PLAYER_DLL_BUTT
} HI_SVR_PLAYER_DLLTYPE_E;

/** �����ٶȱ�ʶ */
typedef enum hiSVR_PLAYER_PLAY_SPEED_E
{
    HI_SVR_PLAYER_PLAY_SPEED_2X_FAST_FORWARD   = 2 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,      /**< 2���ٿ�� */
    HI_SVR_PLAYER_PLAY_SPEED_4X_FAST_FORWARD   = 4 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,      /**< 4���ٿ�� */
    HI_SVR_PLAYER_PLAY_SPEED_8X_FAST_FORWARD   = 8 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,      /**< 8���ٿ�� */
    HI_SVR_PLAYER_PLAY_SPEED_16X_FAST_FORWARD  = 16 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,     /**< 16���ٿ�� */
    HI_SVR_PLAYER_PLAY_SPEED_32X_FAST_FORWARD  = 32 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,     /**< 32���ٿ�� */
    HI_SVR_PLAYER_PLAY_SPEED_2X_FAST_BACKWARD  = -2 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,     /**< 2���ٿ��� */
    HI_SVR_PLAYER_PLAY_SPEED_4X_FAST_BACKWARD  = -4 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,     /**< 4���ٿ��� */
    HI_SVR_PLAYER_PLAY_SPEED_8X_FAST_BACKWARD  = -8 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,     /**< 8���ٿ��� */
    HI_SVR_PLAYER_PLAY_SPEED_16X_FAST_BACKWARD = -16 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,    /**< 16���ٿ��� */
    HI_SVR_PLAYER_PLAY_SPEED_32X_FAST_BACKWARD = -32 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,    /**< 32���ٿ��� */
    HI_SVR_PLAYER_PLAY_SPEED_BUTT                                                          /**< ��Ч���ٶ�ֵ */
} HI_SVR_PLAYER_PLAY_SPEED_E;

/** �������򿪲��� */
typedef struct hiSVR_PLAYER_PARAM_S
{
    HI_U32  u32DmxId;                 /**< dmx id������ts��ʱ�����øò��� */
    HI_U32  u32PortId;                /**< port id������ts��ʱ�����øò��� */
    HI_U32  x, y, w, h;               /**< ��Ƶ����������꼰��ߣ�hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL���ò�����Ч */
    HI_U32  u32MixHeight;             /**< ��Ƶ�������Ȩ��0-100��hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL���ò�����Ч */
    HI_HANDLE hAVPlayer;              /**< �ⲿ�Ѿ�������avplay������window,sound�������ú�window�Ĵ�Сλ�ã�sound��������
                                           ���Խ�avplay�������HiPlayer��HiPlayer����ʹ�ø�avplay���š�����ò�������Ϊ
                                           HI_SVR_PLAYER_INVALID_HDL��HiPlayer�ڲ����Զ�����avplayer��window */
} HI_SVR_PLAYER_PARAM_S;

/** �����ý���ļ� */
typedef struct hiSVR_PLAYER_MEDIA_S
{
    HI_CHAR  aszUrl[HI_FORMAT_MAX_URL_LEN];          /**< �ļ�·��������·������/mnt/filename.ts */
    HI_U32   u32SubTitileNum;                        /**< ��Ļ�ļ����� */
    HI_CHAR  aszSubTitle[HI_FORMAT_MAX_LANG_NUM][HI_FORMAT_MAX_URL_LEN];  /**< ��Ļ�ļ�·��������·������/mnt/filename.ts */
} HI_SVR_PLAYER_MEDIA_S;

/** ����Ƶ����ĻID�л����� */
typedef struct hiSVR_PLAYER_STREAMID_S
{
    HI_U32 u32ProgramId;   /**< ��Ŀid��ֵΪ::HI_FORMAT_FILE_INFO_S�ṹastProgramInfo�����±꣬0-(u32ProgramNum - 1) */
    HI_U32 u32VStreamId;   /**< ��Ƶ��id��ֵ��u32ProgramId��� */
    HI_U32 u32AStreamId;   /**< ��Ƶ��id��ֵΪ::HI_FORMAT_PROGRAM_INFO_S�ṹastAudStream�����±꣬0-(u32AudStreamNum - 1)*/
    HI_U32 u32SubTitleId;  /**< ��Ļid��ֵΪ::HI_FORMAT_PROGRAM_INFO_S�ṹastSubTitle�����±꣬0-(u32SubTitleNum - 1) */
} HI_SVR_PLAYER_STREAMID_S;

/** �������¼��ص����� */
typedef struct hiSVR_PLAYER_EVENT_S
{
    HI_SVR_PLAYER_EVENT_E  eEvent;    /**< �¼����� */
    HI_U32  u32Len;                   /**< �¼��������ȣ��ֽ�Ϊ��λ */
    HI_U8   *pu8Data;                 /**< �¼�����������ʼ��ַ */
} HI_SVR_PLAYER_EVENT_S;

/** ��������Ϣ */
typedef struct hiSVR_PLAYER_INFO_S
{
    HI_U32  u32Progress;                 /**< ���Űٷֱȣ�0-100 */
    HI_U64  u64TimePlayed;               /**< �Ѳ���ʱ�䣬��λms */
    HI_S32  s32Speed;                    /**< �������� */
    HI_SVR_PLAYER_STATE_E  eStatus;      /**< ����״̬ */
} HI_SVR_PLAYER_INFO_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_1 */
/** @{ */  /** <!-- ��Hiplayer�� */

/** 
\brief �������¼��ص�����������::HI_SVR_PLAYER_RegCallback�ӿ�ע��ûص�����
\attention \n
��
\param[out] hPlayer ���������
\param[out] pstruEvent �¼�����

\retval ::HI_SUCCESS

\see \n
��
*/
typedef HI_S32 (*HI_SVR_PLAYER_EVENT_FN)(HI_HANDLE hPlayer, HI_SVR_PLAYER_EVENT_S *pstruEvent);

/** 
\brief ��ʼ��Player
\attention \n
��ʼ���ɹ����ٵ��øýӿڷ��سɹ�����֧�ֶ���̣����������ӿ�ǰ�����ȵ��øýӿ�
\param ��

\retval ::HI_SUCCESS ��ʼ���ɹ�
\retval ::HI_FAILURE ��ʼ��ʧ��

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_Init(HI_VOID);

/** 
\brief ȥ��ʼ��playerģ�飬����ʹ��playerģ�飬���øýӿ�ȥ��ʼ��playerģ��
\attention \n
�����ȵ���::HI_SVR_PLAYER_Destroy�ӿ��ͷŵ������Ĳ��������ٵ��øýӿڣ�����᷵��ʧ�ܣ�Deinit�������ͷ�\n
��������Դ��ȥ��ʼ���ɹ����ٵ��øýӿڷ��سɹ�
\param ��

\retval ::HI_SUCCESS ȥ��ʼ���ɹ�
\retval ::HI_FAILURE ȥ��ʼ��ʧ�ܣ�û���ͷŵ������Ĳ�����

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_Deinit(HI_VOID);

/** 
\brief ����һ��������
\attention \n
�ýӿڱ����ڳ�ʼ������ã�֧����ഴ��һ��������\n
\param[in] pstruParam ��������ʼ�����ԣ�����ts��������ָ�����õ�dmx id��port id
\param[out] phPlayer �����Ĳ��������

\retval ::HI_SUCCESS �����ɹ��������������Ч
\retval ::HI_FAILURE ����ʧ�ܣ������Ƿ�����Դ����

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_Create(const HI_SVR_PLAYER_PARAM_S *pstruParam, HI_HANDLE *phPlayer); 

/** 
\brief ����Ҫ���ŵ�ý���ļ�url��ַ��url��ʽΪ:����·��+ý���ļ���
\attention \n
ͬ���ӿڣ��ýӿڱ����ڵ���::HI_SVR_PLAYER_Create֮����ã����ߵ���::HI_SVR_PLAYER_Stop�ӿ�ֹͣ�����������
�ý���Ҫִ�����´���:
1�����ҽ������������õ�ý���ļ�
2�����û��ָ����Ļ�ļ����������Ļ�ļ�
3�����û��ָ��avplay��
   ����avplay�����ݽ��������ļ�������������Ƶ���ԣ�������Ƶ��������
   ����window������window����λ�ã���window�󶨵�avplay
   ��HI_UNF_SND_0�豸�󶨵�avplay
window��ʾλ�ã�HI_UNF_SND_0�󶨵�avplay���õ�mixheight(���avplay���ⲿָ��������ʾλ�ú�mixheight������Ч)��
�ڵ���::HI_SVR_PLAYER_Create�ӿ�ʱָ��������ǲ���ts���������������ָ����dmx id,port id����ts buffer

\param[in] hPlayer ����::HI_SVR_PLAYER_Create�ӿڴ����Ĳ��������
\param[in] eType ý���ļ���ָֻ������Ƶý���ļ�����ò�������ΪHI_SVR_PLAYER_MEDIA_STREAMFILE��\n
            �����ָ������Ļ�ļ�������(HI_SVR_PLAYER_MEDIA_STREAMFILE | HI_SVR_PLAYER_MEDIA_SUBTITLE)
\param[in] pstruMedia ý���ļ���Ϣ��ֻ֧�־���·�������û��������Ļ�ļ������������Զ�������Ƶý\n
            ���ļ�����Ŀ¼�²���������Ƶý���ļ�����ͬ����Ļ�ļ�

\retval ::HI_SUCCESS ý���ļ����óɹ�����ʱ����::HI_SVR_PLAYER_Play�ӿڿ��Կ�ʼ����
\retval ::HI_FAILURE ý���ļ�����ʧ��
\retval ::HI_ERRNO_NOT_SUPPORT_FORMAT ��֧�ֵ��ļ���ʽ
\retval ::HI_ERRNO_NOT_SUPPORT_PROTOCOL ��֧�ֵ�Э��

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_SetMedia(HI_HANDLE hPlayer, HI_U32 eType, HI_SVR_PLAYER_MEDIA_S *pstruMedia);

/** 
\brief ����һ��������ʵ��
\attention \n
����::HI_SVR_PLAYER_Create�����������󣬵��øýӿ����ٲ�������Դ
\param[in] hPlayer ���������

\retval ::HI_SUCCESS �������ͷųɹ�
\retval ::HI_FAILURE �Ƿ�����

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_Destroy(HI_HANDLE hPlayer);

/** 
\brief ���ò���������
\attention \n
֧�ֵĲ�������
::HI_SVR_PLAYER_ATTR_STREAMID : ���ò��ŵ���id�����ڵ���Ƶ������Ƶ�ļ�������ͨ���ò�������Ҫ���ŵ���Ƶ��\n
���Ź����е��øýӿ�Ϊ�첽����������ǰ��SetMedia����øýӿ�Ϊͬ���������첽��������ͨ���ӿڷ���ֵ���ж�\n
��id�Ƿ����óɹ�����������ͨ��::HI_SVR_PLAYER_EVENT_STREAMID_CHG�¼�֪ͨapp���¼�����Ϊ::HI_SVR_PLAYER_STREAMID_S

\param[in] hPlayer ���������
\param[in] eAttrId Ҫ���õĲ���������ID
\param[in] pArg Ҫ���õĲ���������

\retval ::HI_SUCCESS �������óɹ�
\retval ::HI_FAILURE ����ʧ��

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_SetParam(HI_HANDLE hPlayer, HI_SVR_PLAYER_ATTR_E eAttrId, const HI_VOID *pArg);

/** 
\brief ��ȡ����������
\attention \n
֧�ֵĲ�������
::HI_SVR_PLAYER_ATTR_STREAMID : ��ǰ���ŵ���id
::HI_SVR_PLAYER_ATTR_WINDOW_HDL : ������������window���
::HI_SVR_PLAYER_ATTR_AVPLAYER_HDL : ������������avplay���
::HI_SVR_PLAYER_ATTR_SO_HDL : ��������������Ļ���ģ��(so)���

\param[in] hPlayer ���������
\param[in] eAttrId ����������ID
\param[out] pArg ��ȡ�Ĳ���������

\retval ::HI_SUCCESS ��ȡ�����ɹ�
\retval ::HI_FAILURE ����ʧ��

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_GetParam(HI_HANDLE hPlayer, HI_SVR_PLAYER_ATTR_E eAttrId, HI_VOID *pArg);

/** 
\brief ע�Ქ�����¼��ص�����
\attention \n
�ú��������ڵ���::HI_SVR_PLAYER_Create�ӿں���ã��ýӿ��벥����״̬�޹�
\param[in] hPlayer ���������
\param[in] pfnCallback �������¼��ص��������ص���������::HI_SVR_PLAYER_EVENT_FN

\retval ::HI_SUCCESS ע��ɹ�
\retval ::HI_FAILURE ����ʧ��

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_RegCallback(HI_HANDLE hPlayer, HI_SVR_PLAYER_EVENT_FN pfnCallback);

/** 
\brief ��ʼ����
\attention \n
�첽�ӿڣ��ýӿڱ����ڵ���::HI_SVR_PLAYER_SetMedia�ӿں���ã����ųɹ����ٵ��øýӿڷ���HI_FAILURE��\n
����ͨ���ýӿڷ���ֵ���жϲ������Ƿ񲥷ųɹ�����������ͨ��::HI_SVR_PLAYER_EVENT_STATE�¼�֪ͨ\n
app���ųɹ����¼�����ֵΪ::HI_SVR_PLAYER_STATE_PLAY��ֹͣ���ź󣬿��Ե��øýӿ����²���

\param[in] hPlayer ���������

\retval ::HI_SUCCESS �Ϸ�����
\retval ::HI_FAILURE �Ƿ�����

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_Play(HI_HANDLE hPlayer);

/** 
\brief ֹͣ����
\attention \n
�첽�ӿڣ����š���������ˡ���ͣ�����ж����Ե��øýӿ�ֹͣ���ţ�����ͨ���ýӿڷ���ֵ���жϲ�����\n
�Ƿ�ֹͣ�ɹ�����������ͨ��::HI_SVR_PLAYER_EVENT_STATE�¼�֪ͨappֹͣ�ɹ����¼�����ֵΪ::HI_SVR_PLAYER_STATE_STOP��\n
ֹͣ���ź󣬿��Ե���::HI_SVR_PLAYER_Play�ӿ����²���

\param[in] hPlayer ���������

\retval ::HI_SUCCESS �Ϸ�����
\retval ::HI_FAILURE �Ƿ�����

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_Stop(HI_HANDLE hPlayer);

/** 
\brief ��ͣ����
\attention \n
�첽�ӿڣ����Ź����п��Ե��øýӿ���ͣ���ţ����������״̬�²��ܵ��øýӿڣ�����ͨ���ýӿڷ���ֵ���жϲ�����\n
�Ƿ���ͣ�ɹ�����������ͨ��::HI_SVR_PLAYER_EVENT_STATE�¼�֪ͨappֹͣ�ɹ����¼�����ֵΪ::HI_SVR_PLAYER_STATE_PAUSE��\n
��ͣ�ɹ��󣬿��Ե���::HI_SVR_PLAYER_Resume��������

\param[in] hPlayer ���������

\retval ::HI_SUCCESS �Ϸ�����
\retval ::HI_FAILURE �Ƿ�����

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_Pause(HI_HANDLE hPlayer);

/** 
\brief �ָ�����
\attention \n
�첽�ӿڣ���ͣ�����������״̬�£����øýӿڻָ��������ţ�����ͨ���ýӿڷ���ֵ���жϲ������Ƿ�ָ�����\n
��������ͨ��::HI_SVR_PLAYER_EVENT_STATE�¼�֪ͨapp�ָ��ɹ����¼�����ֵΪ::HI_SVR_PLAYER_STATE_PLAY��

\param[in] hPlayer ���������

\retval ::HI_SUCCESS �Ϸ�����
\retval ::HI_FAILURE �Ƿ�����

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_Resume(HI_HANDLE hPlayer);

/** 
\brief ���������
\attention \n
�첽�ӿڣ��ú����������::HI_SVR_PLAYER_Play����ã�s32SpeedΪ����ʾ���ˣ�Ϊ����ʾ���������ͨ���ýӿ�\n
����ֵ���ж��Ƿ�������˳ɹ�����������ͨ��::HI_SVR_PLAYER_EVENT_STATE�¼�֪ͨapp���¼�����ֵΪ\n
::HI_SVR_PLAYER_STATE_FORWARD��::HI_SVR_PLAYER_STATE_BACKWARD����������˺�ͨ������::HI_SVR_PLAYER_Resume\n
�ӿڻָ��������š�

\param[in] hPlayer ���������
\param[in] s32Speed ���ű���,ֵΪHI_SVR_PLAYER_PLAY_SPEED_E

\retval ::HI_SUCCESS �Ϸ�����
\retval ::HI_FAILURE �Ƿ�����

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_TPlay(HI_HANDLE hPlayer, HI_S32 s32Speed);

/** 
\brief ����ָ��λ�ò���
\attention \n
�첽�ӿڣ��ýӿڱ����ڵ���::HI_SVR_PLAYER_SetMedia�ӿں���ã����š�ֹͣ״̬�£����øýӿ�����ָ��ʱ��㲥��

\param[in] hPlayer ���������
\param[in] s64TimeInMs seekʱ�䣬��λms

\retval ::HI_SUCCESS Seek�ɹ�
\retval ::HI_FAILURE �Ƿ�����

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_Seek(HI_HANDLE hPlayer, HI_S64 s64TimeInMs);

/** 
\brief ��ȡ��ǰ���ļ���Ϣ�����ļ���С���ļ�����ʱ�������ʵȣ���Ƶ���ߣ������ʽ��֡�ʡ����ʣ���Ƶ���롢���ʵ�
\attention \n
�ú��������ڵ���::HI_SVR_PLAYER_SetMedia�ӿں����

\param[in] hPlayer ���������
\param[out] pstruInfo ��ȡ���ļ���Ϣ

\retval ::HI_SUCCESS ��ȡ���ļ���Ϣ
\retval ::HI_FAILURE ��ȡ�ļ���Ϣʧ��

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_GetFileInfo(HI_HANDLE hPlayer, HI_FORMAT_FILE_INFO_S *pstruInfo);

/** 
\brief ��ȡ��������Ϣ���統ǰ����״̬�����Ž��ȡ��Ѳ���ʱ���
\attention \n
�ú��������ڵ���::HI_SVR_PLAYER_Create�ӿں���ã����Ž��ȡ��Ѳ���ʱ��ֻ���ڵ���::HI_SVR_PLAYER_Play�ӿں���Ч

\param[in] hPlayer ���������
\param[out] pstruInfo ��������Ϣ

\retval ::HI_SUCCESS ��������Ϣ��ȡ�ɹ�
\retval ::HI_FAILURE ��������Ϣ��ȡʧ��

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_GetPlayerInfo(HI_HANDLE hPlayer, HI_SVR_PLAYER_INFO_S *pstruInfo);

/** 
\brief ע���ļ���������Ļ�������������������Ƕ�̬�⣬�Ұ�hi_svr_format.hͷ�ļ��淶ʵ��
\attention \n
�ýӿڱ����ڵ���::HI_SVR_PLAYER_Init�ӿں����
��̬�����/usr/libĿ¼�£���libformat.so������øýӿڷ�ʽΪ:
HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libformat.so")

\param[in] eDllType ��̬������
\param[in] dllName ��̬������

\retval ::HI_SUCCESS ��̬��ע��ɹ�
\retval ::HI_FAILURE ע��ʧ��

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLLTYPE_E eDllType, const HI_CHAR *dllName);

/** 
\brief ж�������ļ���������Ļ������̬��
\attention \n
�ýӿڱ����ڵ���::HI_SVR_PLAYER_Init�ӿں����

\param[in] eDllType ��̬������
\param[in] dllName ��̬�����ƣ������������ݲ�ʹ��

\retval ::HI_SUCCESS ж�سɹ�
\retval ::HI_FAILURE ж��ʧ��

\see \n
��
*/
HI_S32 HI_SVR_PLAYER_UnRegisterDynamic(HI_SVR_PLAYER_DLLTYPE_E eDllType, const HI_CHAR *dllName);

/** 
\brief ��/�ر�player dbg��Ϣ
\attention \n
�ýӿڿ������κ�״̬����

\param[in] bEnable ʹ��ֵ��HI_TRUE:��player��־��Ϣ��HI_FALSE:�ر���־��Ϣ

\retval :: ��

\see \n
��
*/
HI_VOID HI_SVR_PLAYER_EnableDbg(HI_BOOL bEnable);

/** 
\brief ��ȡ�������汾��
\attention \n
�ýӿڿ������κ�״̬����

\param[out] pstVersion �������汾��

\retval :: ��

\see \n
��
*/
HI_VOID HI_SVR_PLAYER_GetVersion(HI_FORMAT_LIB_VERSION_S *pstVersion);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_SVR_PLAYER_H__ */

