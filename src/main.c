#include "porter_rocme.h"
 #include <unistd.h>

extern void *rocme_create(UINT32_T size);
#define ROCME_SIZE 32*1024*1024
int main(int argc, char **argv)
{
	void *handle =NULL;
	rocme_porting_flash_init();
	rocme_porting_task_init_static_state();
    /*eeprom init*/
   	rocme_porting_eeprom_init();
	rocme_porting_plane_init();
	rocme_porting_frontpanel_init();
	rocme_porting_udisk_init();
	rocme_porting_network_init();

	handle=rocme_create(NULL);
	if(NULL== handle)
	{
		printf("test1\n");
		return 1;
	}
	while(1)
	{
		sleep(2);
	}
	printf("test\n");
	return 0;
}

