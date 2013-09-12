/*******************************************************************************
File name   : rocme_porting_graphics.h

Author		: DSM

Description : The poriting interface & macro definition for GUI , VIDEO and OSD module.
	          
Copyright (C) BeiJing SUMAVision, Inc., 2010 .All rights reserved.

History		:
				2010.11.30  		Created 					
*******************************************************************************/
#ifndef _ROCME_PORTING_GRAPHICS_H_
#define _ROCME_PORTING_GRAPHICS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/
//������Ͷ���
typedef enum Roc_Plane_Type
{
    ROC_PLANE_BACKGROUND        = 0x00,         //������
    ROC_PLANE_STILLPICTURE      = 0x01,         //��̬ͼ���
    ROC_PLANE_VIDEO             = 0x02,         //��Ƶ��
    ROC_PLANE_GRAPHICS          = 0x03,         //OSD��
    ROC_PLANE_CURSOR            = 0x04,         //����
    ROC_PLANE_RESERVE
}Roc_Plane_Type_e;

//������ɨ�����Ͷ���
typedef enum Roc_Plane_Scan_Type
{
    ROC_PLANE_SCANTYPE_PROGRESSIVE = 1,         //����ɨ��
    ROC_PLANE_SCANTYPE_INTERLACED  = 2,         //����ɨ��
    ROC_PLANE_SCANTYPE_RESERVE
}Roc_Plane_Scan_Type_e;

//����ʾ��ͼƬ���Ͷ���
typedef enum Roc_Plane_Pic_Type
{
    ROC_PLANE_PIC_I_MPEG2_F         = 0x00,     //I֡
    ROC_PLANE_PIC_BMP               = 0x01,     //bitmapλͼ
    ROC_PLANE_PIC_JPEG              = 0x02,     //jpegͼƬ
    ROC_PLANE_PIC_PNG               = 0x03,     //pngͼƬ
    ROC_PLANE_PIC_GIF               = 0x04,     //gifͼƬ
    ROC_PLANE_PIC_RESERVE
}Roc_Plane_Pic_Type_e;

//�����������������
typedef enum Roc_Plane_Aspect_Ratio
{
    ROC_PLANE_AR_4TO3               = 0x00,     //4��3����
    ROC_PLANE_AR_16TO9              = 0x01,     //16��9����
    ROC_PLANE_AR_16TO10             = 0x02,     //16��10����
    ROC_PLANE_AR_1TO1               = 0x03,     //1��1����
    ROC_PLANE_AR_SESERVE0,
    ROC_PLANE_AR_SESERVE1,
    ROC_PLANE_AR_SESERVE2,
    ROC_PLANE_AR_SESERVE3
}Roc_Plane_Aspect_Ratio_e;

//�������ֱ��ʶ���
typedef enum Roc_Plane_Resolution
{
    ROC_PLANE_RS_480_320            = 0x00,     //480*320�ķֱ���
    ROC_PLANE_RS_720_576            = 0x01,     //720*576�ķֱ���
    ROC_PLANE_RS_1280_720           = 0x02,     //1280*720�ķֱ���
    ROC_PLANE_RS_1920_1080          = 0x03,     //1920*1080�ķֱ���
    ROC_PLANE_RS_SESERVE0,
    ROC_PLANE_RS_SESERVE1,
    ROC_PLANE_RS_SESERVE2,
    ROC_PLANE_RS_SESERVE3   
}Roc_Plane_Resolution_e;

/*7101ƽ̨ʹ��BLIT�������ӵ����ݽṹ*/
typedef enum Roc_Blit_Mode
{
    ROC_BLIT_CLEAR              = 0,
    ROC_BLIT_AND                = 1,
    ROC_BLIT_AND_REV            = 2,
    ROC_BLIT_COPY               = 3,
    ROC_BLIT_AND_INVERT         = 4,
    ROC_BLIT_NOOP               = 5,
    ROC_BLIT_XOR                = 6,
    ROC_BLIT_OR                 = 7,
    ROC_BLIT_NOR                = 8,
    ROC_BLIT_EQUIV              = 9,
    ROC_BLIT_NVERT              = 10,
    ROC_BLIT_OR_REVERSE         = 11,
    ROC_BLIT_COPY_INVERT        = 12,
    ROC_BLIT_OR_INVERT          = 13,
    ROC_BLIT_NAND               = 14,
    ROC_BLIT_SET                = 15,
    ROC_BLIT_ALPHA_BLEND        = 16,
    ROC_BLIT_ALPHA_BLEND_B      = 17
	/*...*/
}Roc_Blit_Mode_e;

typedef struct Roc_Blit_Context
{
	Roc_Blit_Mode_e 	emBlitMode;
	ROC_BOOL 	        bColorKeyEnable;
	INT32_T             nColorKeyValue;
	UINT8_T             ucGlobalAlpha;
}Roc_Blit_Context_t;

//��Ļ�������������
typedef struct Roc_Plane_Buff
{
    INT32_T     width;
    INT32_T     height;
    INT32_T     pitch;
    void        *buff_ptr;      //����޷��ṩ������Ϊ��
    INT32_T     buff_len;
}Roc_Plane_Buff_t;

//�������λ����
typedef struct Roc_Plane_Area
{
    INT32_T     offset_x;
    INT32_T     offset_y;
    INT32_T     width;
    INT32_T     height;
}Roc_Plane_Area_t;

//��ɫ���Ͷ���
typedef enum Roc_Plane_Color_Type
{
    ROC_PLANE_COLOR_TYPE_ARGB8888                 = 0x00,
    ROC_PLANE_COLOR_TYPE_RGB888                   = 0x01,
    ROC_PLANE_COLOR_TYPE_ARGB8565                 = 0x02,
    ROC_PLANE_COLOR_TYPE_RGB565                   = 0x03,
    ROC_PLANE_COLOR_TYPE_ARGB1555                 = 0x04,
    ROC_PLANE_COLOR_TYPE_ARGB4444                 = 0x05,
    ROC_PLANE_COLOR_TYPE_CLUT8                    = 0x06,
    ROC_PLANE_COLOR_TYPE_CLUT4                    = 0x07,
    ROC_PLANE_COLOR_TYPE_CLUT2                    = 0x08,
    ROC_PLANE_COLOR_TYPE_CLUT1                    = 0x09,
    ROC_PLANE_COLOR_TYPE_ACLUT88                  = 0x0A,
    ROC_PLANE_COLOR_TYPE_ACLUT44                  = 0x0B,
    ROC_PLANE_COLOR_TYPE_SIGNED_YCBCR888_444      = 0x0C,
    ROC_PLANE_COLOR_TYPE_UNSIGNED_YCBCR888_444    = 0x0D,
    ROC_PLANE_COLOR_TYPE_SIGNED_YCBCR888_422      = 0x0E,
    ROC_PLANE_COLOR_TYPE_UNSIGNED_YCBCR888_422    = 0x0F,
    ROC_PLANE_COLOR_TYPE_SIGNED_YCBCR888_420      = 0x10,
    ROC_PLANE_COLOR_TYPE_UNSIGNED_YCBCR888_420    = 0x11,
    ROC_PLANE_COLOR_TYPE_UNSIGNED_AYCBCR6888_444  = 0x12,
    ROC_PLANE_COLOR_TYPE_SIGNED_AYCBCR8888        = 0x13,
    ROC_PLANE_COLOR_TYPE_UNSIGNED_AYCBCR8888      = 0x14,
    ROC_PLANE_COLOR_TYPE_ALPHA1                   = 0x15,
    ROC_PLANE_COLOR_TYPE_ALPHA4                   = 0x16,
    ROC_PLANE_COLOR_TYPE_ALPHA8                   = 0x17,
    ROC_PLANE_COLOR_TYPE_BYTE                     = 0x18,
    ROC_PLANE_COLOR_TYPE_ARGB7888                 = 0x1D,

	ROC_PLANE_COLOR_TYPE_PARGB8888,
	ROC_PLANE_COLOR_TYPE_RGBA8888,

    ROC_PLANE_COLOR_RESERVE                       = 0xFF
}Roc_Plane_Color_Type_e;

//��Ļ������ö���
typedef struct Roc_Plane_Cfg
{
    INT32_T                     plane_id;           //�˲��id��ʶ,������С��0
    Roc_Plane_Type_e            plane_type;         //�˲������
    ROC_BOOL                    is_complex_pic;     //�Ƿ�֧�ָ���ͼ�����ʾ, ROC_TRUE:֧�� \ ROC_FALSE:��֧��(��֧����ʾ��ɫ)
    ROC_BOOL                    is_still_image;     //�Ƿ�֧����ʾ��̬ͼ��, ROC_TRUE:֧�� \ ROC_FALSE:��֧��
    ROC_BOOL                    is_flicker_filter;  //�Ƿ�֧�ַ���˸(�����ص����ֵ���˸,��������м���淶�������豸 ��3���� ��¼A.2.2.2.3)
    Roc_Plane_Area_t            area;               //�˲����ʼ���꼰����
    Roc_Plane_Buff_t            buff_parm;          //�˲��buff�Ĳ���,
    Roc_Plane_Color_Type_e      color;              //�˲㵱ǰ����ɫ����
    INT32_T                     color_depth;        //�˲�ĵ�ǰ��ɫ���
    Roc_Plane_Scan_Type_e       scan_type;          //�˲������ɨ������
    Roc_Plane_Aspect_Ratio_e    aspectratio;        //�˲㵱ǰ����Ļ������(4:3,16:9�ȵ�)
    Roc_Plane_Resolution_e      resolution;         //�˲㵱ǰ����ķֱ���(720*576,480*320�ȵ�)
    ROC_BOOL                    realtime;           //�Դ˲������Ĳ����Ƿ���������Ч��(��ΪROC_FALSE����ı�˲����Ҫ����rocme_porting_plane_update()����ʹ֮��Ч),����Ҫ˫�����������ΪROC_FALSE
    INT32_T                     reserve;
}Roc_Plane_Cfg_t;
#if 0
#define MAX_LAYER_COUNT 16 //ÿ���豸��������
#define MAX_FRONTPANEL_CHARACTER_SUPPORT 40

typedef enum Roc_Cursor_Bitmap_Type
{
    ROC_CURSOR_BMP,
    ROC_CURSOR_GIF,
    ROC_CURSOR_JPEG,
    ROC_CURSOR_PNG
}Roc_Cursor_Bitmap_Type_e;

typedef struct Roc_Cursor_Configuration
{
    Roc_Cursor_Bitmap_Type_e bmpType;    //����֧�ֵ�ͼƬ��ʽ
    ROC_BOOL isInterlacedSupported;      //�Ƿ�֧�ָ���ɨ��
    ROC_BOOL isAntiflickerSupported;     //�Ƿ�֧�ֿ���˸
    INT32_T x;                           //����������ӫĻ�����x����
    INT32_T y;                           //����������ӫĻ�����y����
    INT32_T width;                       //�����
    INT32_T height;                      //�����
    Roc_Plane_Color_Type_e colorType;      //������ɫ��ʽ
    Roc_Plane_Aspect_Ratio_e aspectRation; //��߱�
}Roc_Cursor_Configuration;
/**
ǰ����������Ϣ
*/
typedef struct Roc_FrontPanel_Configuration{

	INT16_T displayCharAmount;/*��ʾ������*/
	INT16_T characterSetCount;/*֧����ʾ���ַ���*/
	CHAR_T supportChar[MAX_FRONTPANEL_CHARACTER_SUPPORT];/*֧�ֵ��ַ�*/
	

} Roc_FrontPanel_Configuration_fp;

typedef struct Roc_Graphics_Configuration
{
    
    ROC_BOOL isInterlacedSupported;      //�Ƿ�֧�ָ���ɨ��
    ROC_BOOL isAntiflickerSupported;     //�Ƿ�֧�ֿ���˸
    void* pBuffer;                       //ͼ�����ʾ���棨ʵʱ��Ч��������޷��ṩ������Ϊ�ա�
    INT32_T x;                           //����������ӫĻ�����x����
    INT32_T y;                           //����������ӫĻ�����y����
    INT32_T width;                       //ͼ����
    INT32_T height;                      //ͼ����
    INT32_T pitch;                       //ͼ���ÿ��ռ�ݵ��ֽ���
    Roc_Plane_Color_Type_e colorType;      //ͼ�����ɫ��ʽ
    Roc_Plane_Aspect_Ratio_e aspectRation; //��߱�
}Roc_Graphics_Configuration;

typedef struct Roc_Video_Configuration
{

    ROC_BOOL isInterlacedSupported;      //�Ƿ�֧�ָ���ɨ��
    ROC_BOOL isAntiflickerSupported;     //�Ƿ�֧�ֿ���˸
    INT32_T x;                           //����������ӫĻ�����x����
    INT32_T y;                           //����������ӫĻ�����y����
    INT32_T width;                       //��Ƶ���
    INT32_T height;                      //��Ƶ���
    Roc_Plane_Color_Type_e colorType;      //��Ƶ����ɫ��ʽ
    Roc_Plane_Aspect_Ratio_e aspectRation; //��߱�
}Roc_Video_Configuration;

typedef struct Roc_StillPicture_Configuration
{
    ROC_BOOL isStillComplPlot;           //��ֹͼ����Ƿ�֧�ָ��ӻ�ͼ�Ļ�ͼ����
    ROC_BOOL isInterlacedSupported;      //�Ƿ�֧�ָ���ɨ��
    ROC_BOOL isAntiflickerSupported;     //�Ƿ�֧�ֿ���˸
    INT32_T x;                           //����������ӫĻ�����x����
    INT32_T y;                           //����������ӫĻ�����y����
    INT32_T width;                       //��ֹͼ����
    INT32_T height;                      //��ֹͼ����
    Roc_Plane_Color_Type_e colorType;      //��ֹͼ�����ɫ��ʽ
    Roc_Plane_Aspect_Ratio_e aspectRation; //��߱�
}Roc_StillPicture_Configuration;

typedef struct Roc_Background_Configuration
{
    ROC_BOOL isBgComplPlot;                //�������Ƿ�֧�ָ��ӻ�ͼ�Ļ�ͼ����
    ROC_BOOL isBgColorAreaFilledSupported ;//�������Ƿ�֧���������
    ROC_BOOL isColorChangeable;            //�Ƿ�֧�ָı������ɫ
    ROC_BOOL isInterlacedSupported;        //�Ƿ�֧�ָ���ɨ��
    ROC_BOOL isAntiflickerSupported;       //�Ƿ�֧�ֿ���˸
    INT32_T x;                             //����������ӫĻ�����x����
    INT32_T y;                             //����������ӫĻ�����y����
    INT32_T width;                         //�������
    INT32_T height;                        //�������
    Roc_Plane_Color_Type_e colorType;        //��������ɫ��ʽ
    Roc_Plane_Aspect_Ratio_e aspectRation;   //��߱�
}Roc_Background_Configuration;

typedef struct Roc_Layer_Context
{
    INT32_T frontpanelLayerCount;     //ǰ����豸������
    INT32_T cursorLayerCount;         //����Ĳ�����
    Roc_Cursor_Configuration       cursorConf[MAX_LAYER_COUNT];          //�������ã������͵Ĳ��ں󣨿��Ա��ڵ���
    INT32_T graphicsLayerCount;       //ͼ���Ĳ�����
    Roc_Graphics_Configuration     graphicsConf[MAX_LAYER_COUNT];        //ͼ������ã������͵Ĳ��ں󣨿��Ա��ڵ�����ͼ�ο⽫ʹ������Ϊ0�Ĳ�
    INT32_T videoLayerCount;          //��Ƶ��Ĳ�����
    Roc_Video_Configuration        videoConf[MAX_LAYER_COUNT];           //��Ƶ�����ã������͵Ĳ��ں󣨿��Ա��ڵ���
    INT32_T stillPictureLayerCount;   //��ֹͼ���Ĳ�����
    Roc_StillPicture_Configuration stillPictureConf[MAX_LAYER_COUNT];    //��ֹͼ������ã������͵Ĳ��ں󣨿��Ա��ڵ���
    INT32_T backgroundLayerCount;     //������Ĳ�����
    Roc_Background_Configuration   backgroundConf[MAX_LAYER_COUNT];      //���������ã������͵Ĳ��ں󣨿��Ա��ڵ���
}Roc_Layer_Context_t;
#endif
/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/

/**************************************************************************
��������: 
            rocme_porting_plane_init
����˵��: 
            ��ʼ��������ʾ����Ϣ
����˵����
    ���������
            ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ʼ���ɹ� )
    ʧ�� : -1 	 ( ʧ�� )
�ο�ʵ�֣�

����˵��:

**************************************************************************/
INT32_T rocme_porting_plane_init( void );

/**************************************************************************
��������: 
            rocme_porting_plane_get_info
����˵��: 
            ��ȡָ����ʾ��ײ��Ƿ�֧�ֵ���Ϣ
����˵����
    ���������
            [plane_type  ] : ָ���Ĳ�
    ���������
            [ *number    ] : �ײ��Ƿ�֧�ִ˲�, <=0 ��֧�֣�>0Ϊ֧�ֵĲ���
��    �أ� 
    �ɹ� : 0            ( ��ȡӲ��ƽ̨��Ϣ�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡӲ��ƽ̨��Ϣʧ�� )
�ο�ʵ�֣�

����˵��:

**************************************************************************/
INT32_T rocme_porting_plane_get_info( Roc_Plane_Type_e plane_type , INT32_T *number );

/**************************************************************************
��������: 
            rocme_porting_plane_get_cfg
����˵��: 
            ��ȡָ����ʾ��ĵ�ǰ������Ϣ,number��1��ʼ
����˵����
    ���������
            [plane_type  ] : ָ���Ĳ�
            [number      ] : ָ�������ĳһ�������������ָ���ڶ���osd�㣬��ֵΪ2
    ���������
            [*plane_cfg  ] : ָ����ľ���������Ϣ
��    �أ� 
    �ɹ� : 0            ( ��ȡӲ��ƽ̨��Ϣ�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡӲ��ƽ̨��Ϣʧ�� )
�ο�ʵ�֣�

����˵��:

**************************************************************************/
INT32_T rocme_porting_plane_get_cfg( Roc_Plane_Type_e plane_type , INT32_T number , Roc_Plane_Cfg_t *plane_cfg );

/**************************************************************************
��������: 
            rocme_porting_plane_set_cfg
����˵��: 
            ����ָ����ʾ��ĵ�ǰ������Ϣ
����˵����
    ���������
            [*plane_cfg  ] : ָ����ľ���������Ϣ,���е�plane_cfg->plane_id��plane_cfg->plane_type
                             �������������ԸĶ���
    ���������

��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�

����˵��:

**************************************************************************/
INT32_T rocme_porting_plane_set_cfg( Roc_Plane_Cfg_t *plane_cfg );

/**************************************************************************
��������: 
            rocme_porting_plane_display
����˵��: 
            ������ر�ָ�����Ƿ���ʾ
����˵����
    ���������
            [plane_id   ] : ָ���Ĳ��id��ʶ
            [is_on      ] : �Ƿ�����ʾ,ROC_TRUE~������ ROC_FALSE~�رգ�����͸�ӵ���һ��
    ���������

��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�

����˵��:

**************************************************************************/
INT32_T rocme_porting_plane_display( const INT32_T plane_id , const ROC_BOOL is_on );

/**************************************************************************
��������: 
            rocme_porting_plane_remove
����˵��: 
            �Ƴ�ĳ����������ʾ��ͼ�񣬲���ʾΪ�ڳ�
����˵����
    ���������
            [plane_id   ] : ָ���Ĳ��id��ʶ
    ���������

��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�

����˵��:

**************************************************************************/
INT32_T rocme_porting_plane_remove( const INT32_T plane_id );

/**************************************************************************
��������: 
            rocme_porting_plane_update
����˵��: 
            ������rocme_porting_plane_get_cfg���صĲ���plane_cfg->realtime=ROC_FALSE��
        ˵���˲㲻֧��ʵʱ���£���Ҫ�ڵ��ú���rocme_porting_plane_fill_color����ro-
        -cme_porting_plane_fill_picture����Ҫ���ô˺���������ʾ�ĸ��¡����ߵ���Ҫʹ��
        ˫�������ʱ��Ӧ�ÿ��Ըı����plane_cfg->realtime=ROC_FALSE��������Ҫʵ��˫��
        �壬������fill_color��fill_picture�����ô˺�����ʾ��
����˵����
    ���������
            [plane_id   ] : ָ���Ĳ��id��ʶ
    ���������

��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�

����˵��:

**************************************************************************/
INT32_T rocme_porting_plane_update( const INT32_T plane_id, const Roc_Plane_Area_t* area );
INT32_T rocme_porting_plane_update_ex( const INT32_T plane_id, const Roc_Plane_Area_t* srcArea, const Roc_Plane_Area_t* dstArea );

/**************************************************************************
��������: 
            rocme_porting_plane_fill_color
����˵��: 
            ���ĳ��Ϊһ��ɫ
����˵����
    ���������
        [buffer		 ] :Ҫ��ͼ��buffer�ṹָ��
        [color       ] :��ɫֵ,0xaarrggbb��ʽ
        [area        ] :��Ҫ�������꼰��С������֧������������������
    ���������

��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�

����˵��:

**************************************************************************/
INT32_T rocme_porting_plane_fill_color( 
				   const Roc_Plane_Buff_t*	buffer, 
				   const UINT32_T			color, 
				   const Roc_Plane_Area_t*	area 
				   );

/**************************************************************************
��������: 
            rocme_porting_plane_fill_rectangle
����˵��: 
            ��ĳ�㿽������bitmap����
����˵����
    ���������
        [plane_id    ] :ָ���Ĳ��id��ʶ
        [buff_parm   ] :��Ҫ��ʾ�������ݵĲ������������ߡ�pitchֵ������ͷָ��
        [area        ] :��Ҫ�������꼰��С������֧������������������
    ���������

��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�

����˵��:

**************************************************************************/
INT32_T rocme_porting_plane_fill_rectangle( const INT32_T plane_id , const Roc_Plane_Buff_t *buff_parm , const Roc_Plane_Area_t *area  );

/**************************************************************************
��������: 
            rocme_porting_plane_set_alpha
����˵��: 
            ����ĳ���Alpha(͸����)�����ֵ��0 ~ 100, 0 - ��С����ȫ���ɼ���100 - ���OSD��ȫ�ɼ���
        ����ֵ�ú�����������ֱ�ӷ���-1
����˵����
    ���������
        [plane_id    ] :ָ���Ĳ��id��ʶ
        [alpha       ] :ָ���Ĳ��alphaֵ
    ���������

��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�
     
����˵��:
     
**************************************************************************/
INT32_T rocme_porting_plane_set_alpha( const INT32_T plane_id , const INT32_T alpha );

/***************************************************************************
��������:
        rocme_porting_alpha_blend_blit
����˵����
        ʵ��Ӳ��BLIT����alpha��ϡ�
����˵����
    ���������
            [SrcBuf               ] : Դλͼ�����ݴ洢buff�Ĳ���
            [SrcBmp               ] : Դλͼ����Ҫ����������
            [SrcBmpType           ] : Դλͼ���� (����ARGB8888������)
            [DstBuf               ] : Ŀ��λͼ��buff����
            [DstBmp               ] : Ŀ��λͼ����Ҫ��alpha_blend������
            [DstBmpType           ] : Ŀ��λͼ����(Roc_Plane_Color_Type_e)
            [BlitContext          ] : ����BLIT�����Ľṹ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���ɹ� )
    ʧ�� : -1 �� ������ ( ���ʧ�� )
�ο�ʵ�֣�
    rocme_graphics.c
����˵��:
    7101�����ӵĽӿ�
***************************************************************************/
INT32_T rocme_porting_plane_alpha_blend_blit(
                    const Roc_Plane_Buff_t          *SrcBuf,                 // Դλͼ�����ݴ洢buff�Ĳ���
                    const Roc_Plane_Area_t          *SrcBmp,                 // Դλͼ����Ҫ����������
			        const Roc_Plane_Color_Type_e    SrcBmpType,             // Դλͼ���� (����ARGB8888������)
                    const Roc_Plane_Buff_t          *DstBuf,                 // Ŀ��λͼ��buff����
                    const Roc_Plane_Area_t          *DstBmp,                 // Ŀ��λͼ����Ҫ��alpha_blend������
                    const Roc_Plane_Color_Type_e	DstBmpType,             // Ŀ��λͼ����(Roc_Plane_Color_Type_e)
				    Roc_Blit_Context_t              *BlitContext			// ����BLIT�����Ľṹ��
					);

/***************************************************************************
��������:
        rocme_porting_avmem_allocate
����˵����
        ��AVMEM�������Դ�ռ�
����˵����
    ���������
            [         Size] : ��Ҫ�����Դ�ռ�Ĵ�С
            [    Alignment] : �����Դ�ռ�Ķ����ֽ���          
    ���������
            ��
��    �أ� 
    �ɹ� : ���뵽���Դ�ռ�ָ��  ( ����ɹ� )
    ʧ�� : NULL ( ����ʧ�� )
�ο�ʵ�֣�
    rocme_graphics.c
����˵��:
    7101�����ӵĽӿ�    
***************************************************************************/ 
void * rocme_porting_avmem_allocate( UINT32_T Size, UINT32_T Alignment );

/***************************************************************************
��������:
        rocme_porting_avmem_deallocate
����˵����
        �ͷ���AVMEM��������Դ�ռ�
����˵����
    ���������
            [       pBuffer] : ��Ҫ�ͷŵ��Դ�ռ��ָ��
    ���������
            ��
��    �أ� 
            ��
�ο�ʵ�֣�
    rocme_graphics.c
����˵��:
    7101�����ӵĽӿ�
***************************************************************************/ 
void  rocme_porting_avmem_deallocate( void* pBuffer );




#ifdef __cplusplus
}
#endif

#endif

