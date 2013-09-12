/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_eeprom.h

Author      : DSM

Description : The poriting interface & macro definition for EEPROM module.

History     :
              2009.12.20          Created         Jason
              2010.01.08          Modified        DSM
*******************************************************************************/
#ifndef _ROCME_PORTING_EEPROM_H_
#define _ROCME_PORTING_EEPROM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/

typedef enum
{
    ROCME_NVRAM_DATA_BASIC         = 0,  /* ����FFS, ������Ҫ���������仯������(��, Ƶ���������) */
    ROCME_NVRAM_DATA_SKIN          = 1,  /* Skinר�� */
    ROCME_NVRAM_DATA_THIRD_PART    = 2,  /* ���������� */
    ROCME_NVRAM_DATA_QUICK         = 3,  /* ����д���NVRAM */
    ROCME_NVRAM_DATA_APPMGR        = 4,  /* ��������Ӧ�ó��� */
    ROCME_NVRAM_DATA_USERDEF       = 5,  /* �����м�����ص��û��Զ�������*/
    ROCME_NVRAM_DATA_AUX           = 6,  /* ����FFS, ������Զ�ʧ�Ҿ���д������(��, cookie) */
	ROCME_NVRAM_DATA_BOOT          = 7,  /* BOOT���� */
	ROCME_NVRAM_DATA_LOADER        = 8,  /* LOADER���� */
    ROCME_NVRAM_DATA_ROOTFFS       = 9,  /* Rootfs for Application 0 */
    ROCME_NVRAM_DATA_SYSTEM        = 10, /* Kernel or OS for Application 0 */
    ROCME_NVRAM_DATA_APPSOFT       = 11, /* Application 0 */
    ROCME_NVRAM_DATA_UPGRADE_PARAM = 12, /* ipanel IP LOADER������������ */
    ROCME_NVRAM_DATA_ROOTFFS_1     = 13, /* Rootfs for Application 1 */
    ROCME_NVRAM_DATA_SYSTEM_1      = 14, /* Kernel or OS for Application 1 */
    ROCME_NVRAM_DATA_APPSOFT_1     = 15, /* Application 1 */
	ROCME_NVRAM_DATA_AD            = 16, /* �������*/
	ROCME_NVRAM_DATA_INITVIDEO     = 17, /* ������Ƶ*/
	ROCME_NVRAM_DATA_INITIFRAME    = 18, /* ����I֡*/
	ROCME_NVRAM_DATA_BASIC_EXT     = 19, /*BASIC�ı�������������BASIC����ȫ��ͬ������˫�������ݡ�ע�⣺BASIC_EXT �ĳ��ȱ�����BASIC��һ���������м���ᱨ��*/
	ROCME_NVRAM_DATA_QUICK_EXT     = 20, /*QUICK�ı�������������QUICK����ȫ��ͬ������˫�������ݡ�ע�⣺QUICK _EXT �ĳ��ȱ�����QUICK��һ���������м���ᱨ��*/
	ROCME_NVRAM_DATA_SYSINFO		= 100,/*system update info*/
	ROCME_NVRAM_DATA_TEST			= 101,
	ROCME_NVRAM_DATA_UNKNOWN
} ROCME_NVRAM_DATA_TYPE_e;
/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/

/**************************************************************************
��������: 
            rocme_porting_eeprom_init
����˵��: 
            eeprom�洢�豸��ʼ�����м����������ʱ���ô˺��������������м��
        ֮ǰ�������Ѿ�������eeprom�豸�ĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            void
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ʼ���ɹ� )
    ʧ�� : -1 �� ������ ( ��ʼ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_eeprom_init(void); 

/**************************************************************************
��������: 
            rocme_porting_eeprom_info
����˵��: 
            ���eeprom�洢�ռ����ʼ��ַ��������ÿ��ĳ��ȣ�eeprom����С
        �ռ䲻��С��1k��
����˵����
    ���������
            ��
    ���������
            [ *eep_addr   ] : ������м����eeprom����ʼ��ַͷָ��
            [ num_of_sect ] : ������м����eeprom���ܿ���
            [ sect_size   ] : ������м����eeprom��ÿ��Ĵ�С
��    �أ� 
    �ɹ� : 0            ( eeprom������Ϣ��ȡ�ɹ� )
    ʧ�� : -1 �� ������ ( eeprom������Ϣ��ȡʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_eeprom_info(UINT8_T **eep_addr, INT32_T *num_of_sect,  INT32_T *sect_size);

/**************************************************************************
��������: 
            rocme_porting_eeprom_read
����˵��: 
            ��ָ����eeprom�洢�ռ��ָ����ַ��ȡ���ݵ�ָ�������ݻ������С�
����˵����
    ���������
            [ eep_addr    ] : �м����ȡeeprom��Ŀ���ַ
            [ *buff_addr  ] : ��ȡ���ݵĴ洢������ͷָ��
            [ nbytes      ] : ��Ҫ��ȡ�ĳ���
    ���������
            ��
��    �أ� 
    �ɹ� : >=0����ֵ    ( ʵ�ʶ�ȡ�����ݳ���  )
    ʧ�� : -1 �� ������ ( ��ȡeeprom����ʧ��  )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_eeprom_read(UINT32_T eep_addr, UINT8_T *buff_addr, INT32_T nbytes);

/**************************************************************************
��������: 
            rocme_porting_eeprom_burn
����˵��: 
            ��ָ��������д�뵽ָ����eeprom�洢���У�ʵ��Ϊͬ����ʽд�롣
����˵����
    ���������
            [ eep_addr    ] : �м��д��flash��Ŀ���ַ
            [ *buff_addr  ] : д�����ݵĴ洢������ͷָ��
            [ nbytes      ] : ��Ҫд��ĳ���
    ���������
            ��
��    �أ� 
    �ɹ� : >=0����ֵ    ( ʵ��д������ݳ��� )
    ʧ�� : -1 �� ������ ( д��eeprom����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_eeprom_burn(UINT32_T eep_addr, const INT8_T *buff_addr, INT32_T nbytes);

/**************************************************************************
��������: 
            rocme_porting_eeprom_status
����˵��: 
            �жϵ�ǰeeprom��д��״̬���˺���Ŀǰ����Ҫ�󣬿���ʵ��Ϊ�գ�ֱ�ӷ�
        ���Ѿ�д�ɹ�( 1 )���ɡ�
����˵����
    ���������
            [ eep_addr    ] : �м��д��eeprom��Ŀ���ַ
            [ nbytes      ] : д��ĳ���
    ���������
            ��
��    �أ� 
    ����д :  0
    д�ɹ� :  1
    дʧ�� : -1 
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_eeprom_status(UINT32_T eep_addr, INT32_T nbytes);

/**************************************************************************
��������: 
            rocme_porting_eeprom_erase
����˵��: 
            ����ָ��eeprom�洢�ռ��е����ݡ�
����˵����
    ���������
            [ eep_addr    ] : �м����Ҫ����eeprom��Ŀ���ַ
            [ nbytes      ] : �����ĳ���
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( eeprom�����ɹ� )
    ʧ�� : -1 �� ������ ( eeprom����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_eeprom_erase(UINT32_T eep_addr, INT32_T nbytes);


#ifdef __cplusplus
}
#endif

#endif
