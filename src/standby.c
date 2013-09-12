#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include <time.h>
#include "hi_unf_ecs.h"


HI_S32  main(int argc, char *argv[])
{
	HI_S32  i;
	HI_S32  ret;
	HI_U32  tmp;
	time_t  time0;
	struct tm *time1;
	HI_UNF_PMOC_MODE_E  mode;
	HI_UNF_PMOC_WKUP_S  wakeup = {0}; 
	HI_UNF_PMOC_DEV_TYPE_S devType = {0};
	HI_UNF_PMOC_ACTUAL_WKUP_E  actual ;  
	HI_UNF_PMOC_STANDBY_MODE_S  standbyMode = {0};

	memset(&devType, 0, sizeof(HI_UNF_PMOC_DEV_TYPE_S));
	devType.irtype = HI_UNF_IR_CODE_RAW;
	devType.kltype = HI_UNF_KEYLED_TYPE_CT1642;

	memset(&wakeup, 0, sizeof(HI_UNF_PMOC_WKUP_S));
	wakeup.u32WakeUpTime = -1;

	wakeup.u32IrPmocNum = 2;
	wakeup.u32IrPowerKey0[0] = 0x58535754;
	wakeup.u32IrPowerKey1[0] = 0x00005750;
	wakeup.u32IrPowerKey0[1] = 0x44415047;
	wakeup.u32IrPowerKey1[1] = 0x000000af;
	wakeup.u32KeypadPowerKey = 0x8;

	memset(&standbyMode, 0, sizeof(HI_UNF_PMOC_STANDBY_MODE_S));
	standbyMode.u32Mode = 0;

	ret = HI_UNF_PMOC_Init();
	if (HI_SUCCESS != ret)
	{
		printf("HI_UNF_PMOC_Init err, 0x%08x !\n", ret);
		return ret;
	}

	ret = HI_UNF_PMOC_SetDevType(&devType);
	if (HI_SUCCESS != ret)
	{
		printf("HI_UNF_PMOC_SetDevType err, 0x%08x !\n", ret);
		HI_UNF_PMOC_DeInit();
		return ret;
	}

	ret = HI_UNF_PMOC_SetScene(HI_UNF_PMOC_SCENE_STANDARD);
	if (HI_SUCCESS != ret)
	{
		printf("HI_UNF_PMOC_SetScene err, 0x%08x !\n", ret);
		HI_UNF_PMOC_DeInit();
		return ret;
	}

	do
	{
		ret = HI_UNF_PMOC_SetWakeUpAttr(&wakeup);
		if (HI_SUCCESS != ret)
		{
			printf("HI_UNF_PMOC_SetWakeUpAttr err, 0x%08x !\n", ret);
			HI_UNF_PMOC_DeInit();
			return ret;
		}

		ret = HI_UNF_PMOC_SetStandbyDispMode(&standbyMode);
		if (HI_SUCCESS != ret)
		{
			printf("HI_UNF_PMOC_SetStandbyDispMode err, 0x%08x !\n", ret);
			HI_UNF_PMOC_DeInit();
			return ret;
		}

		mode = HI_UNF_PMOC_MODE_SLOW;
		ret = HI_UNF_PMOC_SwitchSystemMode(mode, &actual);
		if (HI_SUCCESS != ret)
		{
			printf("HI_UNF_PMOC_SwitchSystemMode err, 0x%08x !\n", ret);
			HI_UNF_PMOC_DeInit();
			return ret;
		}

		if(actual == HI_UNF_PMOC_WKUP_IR){
			printf("wakeup by ir !!!\n");
		}else if(actual == HI_UNF_PMOC_WKUP_KEYLED){
			printf("wakeup by key !!!\n");
		}else if(actual == HI_UNF_PMOC_WKUP_TIMEOUT){
			printf("wakeup by timeout !!!\n");
		}else{
			printf("wakeup by no mode ??? \n");
		}

		printf("%%%%%%%% cnt = %d %%%%%%%% \n", i);
	} while(0);
	HI_UNF_PMOC_DeInit();
    return HI_SUCCESS;
}



