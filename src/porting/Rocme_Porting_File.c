/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_file.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "signal.h"
#include <stdarg.h>
#include <math.h>
#include <memory.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/mman.h>
	//#include <asm/page.h> 
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/statfs.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
	
#include <dirent.h>
#include <utime.h>
#include <ctype.h>
	
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/if.h> 
#include <net/if_arp.h> 
#include <net/route.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if.h> 
#include <net/if_arp.h> 

#include "hi_type.h"


#include "porter_rocme.h"


typedef enum
{
    ROCME_FILE_SEEK_SET 			= 0, 
    ROCME_FILE_SEEK_CUR 			= 1,
    ROCME_FILE_SEEK_END 			= 2,

}ROCME_FILE_TYPE_e;

typedef struct File_Openlist //��¼�򿪵���ͨ�ļ���fd�ʹ�ģʽ
{
	INT32_T fd;
	CHAR_T mode[4];
	struct File_Openlist *next;
}File_Openlist_t;

typedef struct Dir_Openlist	//��¼�򿪵�Ŀ¼�ļ��Ĳ���
{
	INT32_T dd;	//��ʱ�����һ������ֵ��Ϊ��Ŀ¼�ķ���ֵ
	DIR *pDir;	//opendir�����ķ���ֵ
	Roc_File_List_t *filelist;  //��¼Ŀ¼�µ������ļ����ƺ����͵������׵�ַ
	struct Dir_Openlist *next;	//ָ��򿪵���һ��Ŀ¼
}Dir_Openlist_t;


static File_Openlist_t *File_Openlist_head = NULL; 	//���ļ���������׵�ַ
static Dir_Openlist_t *Dir_Openlist_head = NULL; 	//��Ŀ¼��������׵�ַ
static INT32_T DirBit = 1;	//������¼�ѷ����������dd


static char* rocme_dir_path0 ="/flashfile/c";
static char* rocme_dir_temp ="/tmp";

static char g_cFileRd[1024];


/***************************************************************************
����˵����
    ��ָ���ļ���
����˵����
    ���������
    [      filename]�ļ���
    [          mode]��ģʽ
    ���������
        ��.
��    �أ� 
    �ɹ� : �ļ����
    ʧ�� : -1

ע����ģʽ
"rb": ��ģʽ�����Ҫ�򿪵��ļ��Ѵ��ڣ���򿪳ɹ���������ļ�ʧ�ܡ�
"wb": дģʽ�����Ҫ�򿪵��ļ��Ѵ��ڣ�����ԭ�������ݣ��������filename������һ������Ϊ�յ��ļ������·���д�����Ŀ¼δ�����������δ�����ЩĿ¼��

�ο�ʵ�֣�
        rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_open(const CHAR_T *filename, const CHAR_T *mode)
{
ROCME_TEST_PRINT

		INT32_T fd, flags,i;
		flags = O_RDONLY;
		File_Openlist_t *p,*q,*tail,*tmp;
		CHAR_T* token;
		CHAR_T dirPath[256] = {0};
		INT32_T errCode;
		HI_CHAR aszPath[256] = {0}; 
		
		
		if((NULL == filename)||(NULL == mode))
		{	
			ROCME_PRINTF(ROCME_LOG_ERROR,"params error \n");
			return -1;
		}
		
		ROCME_PRINTF(ROCME_LOG_INFO,"filename = %s,openmode = %s \n",filename,mode);

		strcpy(aszPath, filename);

		if((strcmp(mode, "a") == 0) ||strcmp(mode, "ab") == 0)
		flags = O_APPEND;
		else if((strcmp(mode, "r") == 0) ||strcmp(mode, "rb") == 0)
		flags = O_RDONLY;
		else if(strcmp(mode, "r+") == 0 ||strcmp(mode, "r+b") == 0)
		flags = O_RDWR;
		else if(strcmp(mode, "w") == 0 ||strcmp(mode, "wb") == 0)
		/*edit 2011.03.03:add O_TRUNC,if file exist,this will clear the file.*/
		flags = O_WRONLY|O_CREAT|O_TRUNC;
		else if(strcmp(mode, "bb") == 0)
		{
			  flags = O_RDONLY;
		}
		else 
		{
			return -1;
		}

		strcpy(g_cFileRd, aszPath);
		token = strtok(g_cFileRd, "/");
		while(token != NULL) 
		{ 
			strcat(dirPath, "/");
			strcat(dirPath, token);
			errCode = access(dirPath, F_OK);
			if(errCode != 0)
			{
				mkdir(dirPath, 0777);
			}
			token = strtok(NULL, "/");
		} 

		struct stat info;
		stat(dirPath,&info);
		if(S_ISDIR(info.st_mode))
		{
			errCode = rmdir(dirPath);
			if(errCode != 0)
			{
				ROCME_PRINTF(ROCME_LOG_ERROR,"rmdir failed\n");
			}
		}
		else
		{
			if(strcmp(mode, "w") == 0 ||strcmp(mode, "wb") == 0)
			{
				INT32_T result;
				result = remove(aszPath);
				if(result == -1)
				{
					ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_delete fail!");
					return -1;
				}
			}
		}
		fd = open(aszPath, flags);
		if(fd == -1)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_open fail!\n");
			return -1;
		}
	
		p = q = tail = File_Openlist_head;
		while(p != NULL)	//������β�ڵ�
		{
			tail = p;
			q = p->next;
			p = q;
		}
	
		i = 0;
		while((tmp = (File_Openlist_t *)malloc(sizeof(File_Openlist_t))) == NULL)
		{
			i++;
			if(i == 3)
				break;
		}
		
		if(tmp == NULL)
		{
			i = 0;
			while(close(fd)!=0)
			{
				i++;
				if(i == 3)
					return -1;
			}
			return -1;	
		}
		else
		{
			tmp->fd = fd;
			strcpy(tmp->mode,mode);
			tmp->next =NULL;
			
			if(File_Openlist_head == NULL) //��һ�δ��ļ�
			{
				File_Openlist_head = tmp;
			}
			else
			{
				tail->next = tmp;
			}
		}
		
		return fd;

}

/***************************************************************************
����˵����
    �ر�ָ���ļ�.
����˵����
    ���������
    [             fd]�ļ����
    ���������
       ��
��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1
    	
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_close(INT32_T fd)
{
ROCME_TEST_PRINT
	INT32_T result;
	File_Openlist_t *p,*q,*tmp;

	p = q = tmp = File_Openlist_head;
	while(p != NULL)	//����fd���ڵĽڵ�
	{
		if(p->fd == fd)
		{
			result = close(fd);
			if(result == -1)
			{
				ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_close fail!");
				return -1;
			}

			if(p == File_Openlist_head)
			{
				File_Openlist_head = p->next;
			}
			else
			{
				tmp->next = p->next;
			}

			free(p);
			return 0;
		}
		else
		{
			tmp = p;
			q = p->next;
			p = q;
		}
	}

	ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_close not open or already closed!");
	return -1;

}

/***************************************************************************
����˵����
    ��ȡָ���ļ������ݣ�ͨ��buffer���͸������ߣ���ȡ����Ϊnbytes
����˵����
    ���������
		[              fd] �ļ����
		[          buffer] ���ص�����ָ�룬���ڴ��ɵ���������
		[          nbytes] ��Ҫ��ȡ���ֽ���


    �����������
��    �أ� 
    �ɹ���ʵ�ʶ�ȡ�����ļ����ȣ�Byte��,0��С��nbytes����ʾ���ļ���β�ˡ�
	ʧ�ܣ�-1
ע�⣺�ɹ�����ֵ����nbytes

�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_read(INT32_T fd, CHAR_T* buffer, INT32_T nbytes)
{
ROCME_TEST_PRINT	
	INT32_T result;
	result = read(fd, buffer, nbytes);
	if(result == -1)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_read fail!");
		return -1;
	}
    return result;

}

/***************************************************************************
����˵����
		��buffer�е�����д�뵽ָ�����ļ��У�д�볤��Ϊnbytes
����˵����
    ���������
    [              fd] �ļ����
		[          buffer] д������������ڴ��ַ
		[          nbytes] ��Ҫд����ֽ���

    �����������
��    �أ� 
    �ɹ���ʵ��д����ֽ���
	ʧ�ܣ�0
ע�⣺�ɹ�����ֵ����nbytes��

�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_write(INT32_T fd, const INT8_T* buffer, INT32_T nbytes)
{
ROCME_TEST_PRINT
	INT32_T result;
	result = write(fd, buffer, nbytes);
	if(result == -1)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_write fail!");
		return 0;
	}
    return result;

}

/***************************************************************************
����˵����
    ��λָ���ļ���ָ��λ��,λ����off��originָ��.
����˵����
    ���������
    [              fd] �ļ����
		[             off] Ҫƫ�Ƶ��ֽ���
		[          origin] ƫ�Ƶ���ʼλ��,
		                   0��ʾ���ļ�ͷ��ƫ��off���ֽ�,
		                   1��ʾ���ļ���ǰλ��ƫ��off���ֽ�,
		                   2��ʾ���ļ�β��ƫ��off���ֽ�
    ���������
��    �أ� 
    �ɹ� : 0        
    ʧ�� : -1
ע�⣺origin=0ʱ,Ҫ��off>0; orgin=2ʱ,Ҫ��off<0;

�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_seek(INT32_T fd, INT32_T off, INT32_T origin)
{
ROCME_TEST_PRINT
	INT32_T result, where;

/* Ӧ��������������⣬Ҫ��ʱע�͵�����������ʾ�������� */	
#if 1
	if((origin < 0) || (origin > 2))
	{
		return -1;
	}
	
	if(((origin == 0)&&(off <= 0))||((origin == 2)&&(off >=0)))
		return -1;
#endif
	switch(origin)
	{
		case 0:	where = SEEK_SET;
				break;
		case 1: where = SEEK_CUR;
				break;
		case 2: where = SEEK_END;
				break;
		default:where = SEEK_SET;
				break;
	}
	result = lseek(fd, off, where);
	if(result == -1)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_seek fail!");
		return -1;
	}
    return 0;
}

/***************************************************************************
����˵����
�õ��ļ���ǰλ��������ļ��׵�ƫ���ֽ���.
����˵����
���������
[              fd] �ļ����
���������
��    �أ� 
    �ɹ�: ��������ļ��׵�ƫ���ֽ���.
    ʧ��: -1
�ο�ʵ�֣�
rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_tell(INT32_T fd)
{
ROCME_TEST_PRINT
	INT32_T off = 0;
	File_Openlist_t *p,*q;
	FILE *fp = NULL;
		
	p = q = File_Openlist_head;
	while(p != NULL)	//����fd���ڵĽڵ㣬��ȡ�ļ���ʱ�Ĵ�ģʽ
	{
		if(p->fd == fd)
		{
			break;
		}
		else
		{
			q = p->next;
			p = q;
		}
	}

	if(p == NULL)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_tell not open or already closed!");
		return -1;
	}

	fp = fdopen(fd,p->mode);
	if(fp == NULL)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_tell fdopen fail!");
		return -1;
	}

	off = ftell(fp);
	if(off == -1)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_tell ftell fail!");
		return -1;
	}
	
	return off;

}

/***************************************************************************
����˵����
�жϵ�ǰ�ļ�ָ���Ƿ񵽴��ļ���β.
����˵����
���������
[              fd] �ļ����
���������
��    �أ� 
    �ɹ�: ָ���Ѿ������ļ���β������0�����򣬷���һ��������
    ʧ��: �ļ�δ�򿪵�ʱ����-1
�ο�ʵ�֣�
rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_eof(INT32_T fd)
{
ROCME_TEST_PRINT
	INT32_T off;
	File_Openlist_t *p,*q;
	FILE *fp = NULL;

	p = q = File_Openlist_head;
	while(p != NULL)	//����fd���ڵĽڵ㣬��ȡ�ļ���ʱ�Ĵ�ģʽ
	{
		if(p->fd == fd)
		{
			break;
		}
		else
		{
			q = p->next;
			p = q;
		}
	}

	if(p == NULL)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_eof not open or already closed!");
		return -1;
	}

	fp = fdopen(fd,p->mode);
	if(fp == NULL)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_eof fdopen fail!");
		return -1;
	}

	if(fgetc(fp) != EOF)
	{
		off = ftell(fp);
		if(off == -1)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_eof ftell fail!");
			return -1;
		}
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_eof not end ok!");
		return off;
	}
	
	return 0;

}

/***************************************************************************
����˵����
		�ж�ָ���ļ��Ƿ����
����˵����
    ���������
    [        filename] �ļ���	
    �����������
��    �أ� 
    ����   : 1
    ������ : 0
    	
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
ROC_BOOL rocme_porting_file_is_exist(const CHAR_T *filename)
{
ROCME_TEST_PRINT
	INT32_T flg = ROC_FALSE;
	if(NULL == filename)
	{	
		ROCME_PRINTF(ROCME_LOG_ERROR,"path error \n");
		return -1;
	}

	if(access(filename,F_OK)==0)
	{
		struct stat buf = {0};
	    if(!stat(filename, &buf))
	    {
	    	if(S_ISREG(buf.st_mode))
	    	{
	    		flg = ROC_TRUE;
	    	}
	    }
		if(flg == ROC_FALSE)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_file_is_exist not!");
			return 0;
		}
		return 1;
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_file_is_exist] no this file \n");
		return 0;
	}

}

/***************************************************************************
����˵����
    ��ָ�����ļ�������
����˵����
    ���������
    [        filename] ԭʼ�ļ���
    [         newname] ���ļ���	
    �����������
��    �أ� 
    �ɹ� : 0           
    ʧ�� : -1 �� ������
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_rename(const CHAR_T* filename, const CHAR_T* newname)
{
ROCME_TEST_PRINT

	if((NULL == filename)||(NULL == newname))
	{	
		ROCME_PRINTF(ROCME_LOG_ERROR,"path error \n");
		return -1;
	}

	if(rename(filename,newname)==0)
	{
		return 0;
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rename file err \n");
		return -1;
	}
}

/***************************************************************************
����˵����
    ɾ��ָ�����ļ�
����˵����
    ���������
    [        filename] �ļ�����
    ���������
��    �أ� 
    �ɹ� : 0
    ʧ�� : -1 �� ������
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_delete(const CHAR_T* filename)
{
ROCME_TEST_PRINT
	if(remove(filename)==0)
	{
		return ROC_OK;
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"remove file err \n");
		return ROC_ERR;
	}
}

/***************************************************************************
����˵����
		��ȡָ���ļ���״̬����
����˵����
    ���������
    [              fd] �ļ����
    ���������
    [        filestatus] �ļ���״̬���ݽṹ
��    �أ� 
    �ɹ� : 0
    ʧ�� : -1 �� ������
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_get_status(const CHAR_T* filename, Roc_File_Status_t *filestatus)
{
ROCME_TEST_PRINT
	HI_CHAR aszPath[256]={0};
	if((filename == NULL)||(filestatus == NULL))
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"path error \n");
		return -1;
	}
	printf("the file name =%s\n",filename);

	struct stat buf;
	
	strcpy(aszPath, filename);
	if(stat(aszPath,&buf) != -1)
	{
		if(S_ISDIR(buf.st_mode)) //�ж��Ƿ���Ŀ¼�ļ�
		{
			filestatus->file_mode = ROC_FILE_MODE_DIR;
		}
		
		if(S_ISREG(buf.st_mode)) //�ж��Ƿ�����ͨ�ļ�
		{
		//�ж�USER�Ķ�дȨ�ޣ����ļ�Ϊ�Ƕ�дȨ�ޣ���Ĭ��Ϊ�ɶ�Ȩ��
			switch((buf.st_mode&0x180)>>7)
			{
			case 0: 	filestatus->file_mode = ROC_FILE_MODE_R;
						break;
			case 1: 	filestatus->file_mode = ROC_FILE_MODE_W; 
						break;
			case 2: 	filestatus->file_mode = ROC_FILE_MODE_R; 
						break;
			case 3: 	filestatus->file_mode = ROC_FILE_MODE_RW; 
						break;
			default: 	break;				
			}
		}

		filestatus->file_size = buf.st_size;
		filestatus->file_blksize = buf.st_blocks;
		filestatus->file_atime = buf.st_atime;
		filestatus->file_mtime = buf.st_mtime;
		filestatus->file_ctime = buf.st_ctime;
		return 0;
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"stat file err \n");
		return -1;
	}
}


/***************************************************************************
����˵����
		��ָ�����ļ�Ŀ¼
����˵����
    ���������
    [            path] Ŀ¼���ƣ�ָ��Ŀ¼������������������׺�ɴ�/������·��
    �����������
��    �أ� 
    �ɹ� : Ŀ¼���
    ʧ�� : -1
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_dir_open(const CHAR_T *path)
{
ROCME_TEST_PRINT
	DIR *dir;
	INT32_T i = 0;
	INT32_T DirBit_tmp = DirBit;
	Dir_Openlist_t *p,*q,*tail,*tmp;
    HI_CHAR aszPath[256]={0};

	if(path == NULL)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"path error \n");
		return -1;
	}

    strcpy(aszPath, path);
	printf("rocme_porting_dir_open  the path = %s\n",aszPath);
	dir=opendir(aszPath);
	if(dir == NULL)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_dir_open fail!");
		return -1;
	}

	p = q = tail = Dir_Openlist_head;
	while(p != NULL)
	{
		tail = p;
		q = p->next;
		p = q;			
	}

	i = 0;
	while((tmp = (Dir_Openlist_t *)malloc(sizeof(Dir_Openlist_t))) == NULL)
	{
		i++;
		if(i == 3)
			break;
	}
	
	if(tmp == NULL)
	{
		printf("rocme_porting_dir_ope  nmalloc err\n");
		i = 0;
		while(closedir(dir)!=0)
		{
			i++;
			if(i == 3)
			{
				return -1;
			}
				
		}
		return -1;	
	}
	else
	{	
		i = 0;
		while(DirBit_tmp&0x1)
		{
			DirBit_tmp = (DirBit_tmp >> 1);
			i++;
		}
		DirBit |= (1 << i);
		tmp->dd = i;
		tmp->pDir = dir;
		tmp->filelist = NULL;
		tmp->next = NULL;

		if(Dir_Openlist_head == NULL) //��һ�δ�Ŀ¼
		{
			Dir_Openlist_head = tmp;
		}
		else
		{
			tail->next = tmp;
		}
	}
	
	return tmp->dd;

}


/***************************************************************************
����˵����
		�ر�ָ�����ļ�Ŀ¼
����˵����
    ���������
    [            fd] Ŀ¼���
    �����������
��    �أ� 
    �ɹ� : 0
    ʧ�� : -1 �� ������
ע :
    ɾ���ļ�����������ÿ���ڵ㲢�ͷ��ڴ�
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_dir_close(INT32_T dd)
{
ROCME_TEST_PRINT
	INT32_T result;
	DIR *dir;
	Roc_File_List_t *head, *next;
	Dir_Openlist_t *p,*q,*tmp;

	p = q = tmp = Dir_Openlist_head;
	while(p != NULL)
	{
		if(p->dd == dd)
		{
			dir = p->pDir;
			head = next = p->filelist;	
			result = closedir(dir);
			if(result == -1)
			{
				ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_dir_close fail!");
				return -1;
			}

			while(head != NULL)
			{
				next = head;
				free(head);
				head = next->nextfile;
			}

			if(p == Dir_Openlist_head)
			{
				Dir_Openlist_head = p->next;
			}
			else
			{
				tmp->next = p->next;
			}
			
			DirBit &= ~(1 << dd);
			free(p);

			return 0;
		}
		else
		{
			tmp = p;
			q = p->next;
			p = q;
		}
	}

	ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_dir_close not open or already closed!");
	return -1;

	
}


/***************************************************************************
����˵����
		��ȡָ�����ļ�Ŀ¼��Ϣ
����˵����
    ���������
    [             dd] Ŀ¼���
    [       filelist]Ŀ¼���ļ����������ָ��
��    �أ� 
    �ɹ� : 0
    ʧ�� : -1 �� ������
ע :
    �����ļ�����������ÿ���ڵ㲢�����ڴ�
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_dir_read(INT32_T dd, Roc_File_List_t **filelist)
{
ROCME_TEST_PRINT
	{
		DIR *pDir;
		struct dirent *ptr;
		Roc_File_List_t *pFile, *next;
		Dir_Openlist_t *p,*q;
		INT32_T filecount = 0;
		CHAR_T i, flag;
		i = 0;
		flag = 0;
		next = pFile =NULL;
		if(filelist == NULL)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"path error \n");
			return -1;
		}
	
		p = q = Dir_Openlist_head;
		while(p != NULL)  //����Ŀ¼�ڵ�
		{
			if(p->dd == dd)//�ҵ�������ѭ��
			{
				break;
			}
			else
			{
				q = p->next;
				p = q;
			}
		}
	
		if(p == NULL)  //�ж�Ŀ¼�Ƿ��Ѿ��򿪣���δ�򿪣��򷵻أ���֮�����ȡ���нڵ�
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_dir_read not open or already closed!\n");
			return -1;
		}
	
		*filelist = NULL;
		pDir = p->pDir;
		while(((ptr=readdir(pDir))!=NULL)) //��ȡĿ¼
		{
			if((strcmp(ptr->d_name, ".")==0)||(strcmp(ptr->d_name, "..")==0))
				continue;
			//�������Ľڵ�����ڴ棬Ŭ���ĴΣ���ʧ�ܣ�������νڵ㣬������ȡ��һ�ڵ�
			while((pFile=(Roc_File_List_t *)malloc(sizeof(Roc_File_List_t))) == NULL)
			{
				i++;
				if(i == 3)
					break;
			}
			
			if(pFile != NULL)
			{
				memset(pFile,0,sizeof(Roc_File_List_t));
				printf("rocme_porting_dir_read the %d file name = %s\n",filecount,ptr->d_name);
				filecount++; //��¼�ɹ���ȡ������洢�ռ�Ľڵ����
				strcpy(pFile->filename,ptr->d_name);
				//�ж���Ŀ¼������ͨ�ļ���������ͨ�ļ�����ȷ�϶�дȨ��(��USERֻ��ִ��Ȩ�ޣ�����Ϊ�ɶ�Ȩ��)
				//printf("file=%32s.type=%10d.\n",ptr->d_name,ptr->d_type);//DT_DIR
				if((ptr->d_type & 4) == 4)
				{
					pFile->filemode = ROC_FILE_MODE_DIR;
				}
	
				if((ptr->d_type & 8) == 8)
				{
					flag = 0;
					if(access(ptr->d_name,W_OK) == 0)
					{
						flag |=0x1;
					}
					if(access(ptr->d_name,R_OK) == 0)
					{
						flag |=0x2;
					}
					switch(flag)
					{
						case 0: 	pFile->filemode = ROC_FILE_MODE_R;
									break;
						case 1: 	pFile->filemode = ROC_FILE_MODE_W; 
									break;
						case 2: 	pFile->filemode = ROC_FILE_MODE_R; 
									break;
						case 3: 	pFile->filemode = ROC_FILE_MODE_RW; 
									break;
						default:	break;				
					}
				}
	
				pFile->nextfile = NULL;
				if(filecount == 1)	//��¼��һ�ڵ�
				{
					next = pFile;
					*filelist = pFile;
					p->filelist = pFile;
				}
				else
				{
					next->nextfile = pFile;
					next = pFile;
				}
			}
		}
#if 0		
		Roc_File_List_t *dfile = NULL;
		dfile = *filelist;
		while(dfile)
		{
			printf("the file name =%s\n",dfile->filename);
			dfile =dfile->nextfile;
		}
#endif
		return 0;
	}

}


/***************************************************************************
����˵����
		����ָ�����ļ�Ŀ¼����Ҫָ������·�������·���д��ڶ༶Ŀ¼δ�����������δ�����
����˵����
    ���������
    [            dir] Ŀ¼�ļ�
    �����������
��    �أ� 
    �ɹ� : 0
    ʧ�� : -1 �� ������
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_dir_mkdir(CHAR_T *dir)
{
ROCME_TEST_PRINT

	INT32_T result;
	CHAR_T* token;
	CHAR_T dirPath[256] = {0};
    HI_CHAR aszPath[256] = {0};
	
	if(dir == NULL)
	{	
		ROCME_PRINTF(ROCME_LOG_ERROR,"dir err \n");
		return -1;
	}
	
    strcpy(aszPath, dir);
	
    result = access(dir, F_OK);
    if (result == 0)
    {
		ROCME_PRINTF(ROCME_LOG_INFO,"dir exist\n");
        return 0;
    }
    
    strcpy(g_cFileRd, dir);
    token = strtok(g_cFileRd, "/");
    while(token != NULL) 
    { 
        strcat(aszPath, "/");
        strcat(aszPath, token);
        result = access(aszPath, F_OK);
        if(result != 0)
        {
			result = mkdir(aszPath, O_CREAT);
			if(result == -1)
			{
				ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_dir_mkdir fail!");
				return -1;
			}
        }
        token = strtok(NULL, "/");
    } 
    return 0;

}


/***************************************************************************
����˵����
    �ж�ָ�����ļ�Ŀ¼�Ƿ����
����˵����
    ���������
    [         dirname] Ŀ¼�ļ�����
    �����������
��    �أ� 
    ����   : 1
    ������ : 0
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
ROC_BOOL rocme_porting_dir_is_exist(const CHAR_T *dirname)
{
ROCME_TEST_PRINT

	INT32_T result;
	int flg = ROC_FALSE;
	
    if(dirname == NULL)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"path error \n");
		return 0;
	}
	printf("the dir name = %s\n",dirname);
	result = access(dirname,F_OK);
	if (result == 0)
	{
		struct stat buf = {0};
		if(!stat(dirname, &buf))
		{
	    	if(S_ISDIR(buf.st_mode))
	    	{
	    	    flg = ROC_TRUE; 
	    	}
    	}
	}
	if(flg == ROC_FALSE)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"dir not exist \n");
		return 0;
	}
    return 1;

}


/***************************************************************************
����˵����
		������ָ�����ļ�Ŀ¼Ϊnewname
����˵����
    ���������
    [         dirname] Ŀ¼����
    [         newname] �µ�Ŀ¼����
    �����������
��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_dir_rename(const CHAR_T* dirname, const CHAR_T* newname)
{
	ROCME_TEST_PRINT
	INT32_T result;
	
	if((NULL == dirname)||(NULL == newname))
	{	
		ROCME_PRINTF(ROCME_LOG_ERROR,"path error \n");
		return -1;
	}
	result = rename(dirname, newname);
	if(result == -1)
	{	
		ROCME_PRINTF(ROCME_LOG_ERROR,"rename err \n");
		return -1;
	}
    return 0;
}


/***************************************************************************
����˵����
    ɾ��ָ��Ŀ¼
����˵����
    ���������
    [         dirname] Ŀ¼����
    �����������
��    �أ� 
    �ɹ� : 0           
    ʧ�� : -1 �� ������
�ο�ʵ�֣�
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_dir_delete(const CHAR_T* dirname)
{
ROCME_TEST_PRINT

	INT32_T result;
	char cmd[512] = {0};
	
	if(dirname == NULL)
	{	
		ROCME_PRINTF(ROCME_LOG_ERROR, "name param err\r\n");
		return -1;
	}
	if(1 != rocme_porting_dir_is_exist(dirname))
	{
	    return -1;
	}

    strcpy(cmd, "rm -rf ");
    strcat(cmd, dirname);
    result = system(cmd);
	if(result == -1)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "rocme_porting_dir_delete fail!");
		return -1;
	}
    return 0;

}


/***************************************************************************
����˵����
    ��ȡָ����ŵ�flash��дĿ¼����Ŀ¼������flash�ϣ�
    �ϵ�����ݲ��ᶪʧ��
����˵����
    ���������
    [         index]��дĿ¼���
    [         name]��дĿ¼�ľ���·��
    �����������
��    �أ� 
    �ɹ� : 0           
    ʧ�� : -1
��ע��
    ��Ӧ����˵��ֻ�ܷ��ʼ��޸�ָ��Ŀ¼�µ��ļ����ļ��У�
    ��Ŀ¼������flash�ϣ��ϵ�����ݲ��ᶪʧ��
    ����Ŀ¼������Ҫ�ṩһ����һ��Ҳֻ��Ҫһ��������ʵ��
    ����������0��ʼ���ε������м����Ȼ��ȡindexΪ0�Ŀ�дĿ¼��
***************************************************************************/
INT32_T rocme_porting_get_local_dir(INT32_T index, CHAR_T* name)
{
ROCME_TEST_PRINT
	switch(index)
	{
		case 0:
		case 1:
			strcpy(name,rocme_dir_path0);
			return 0;

		default:
			return -1;
	}
}


/***************************************************************************
����˵����
    ��ȡ��ʱ�ļ�ϵͳ�е� ��дĿ¼����Ŀ¼�������ڴ��У�
    �ϵ�����ݿ��Զ�ʧ��
����˵����
    ���������
    [         name]��ʱ�ļ�ϵͳ�п�дĿ¼�ľ���·��
    �����������
��    �أ� 
    �ɹ� : 0           
    ʧ�� : -1
��ע��
    ���м����˵��ĳЩ������Ҫһ����ʱ�ļ��У�
    ���������еĹ����У����ļ��п���������д���ʣ�
    ���ᶪʧ���ϵ����������ա�
    �����ʱ�ļ��в���Ҫ������flash�ϣ������ڴ��ļ�ϵͳ��
***************************************************************************/
INT32_T rocme_porting_get_tmp_dir(CHAR_T* name)
{
ROCME_TEST_PRINT
	strcpy(name,rocme_dir_temp);
	return 0;
}

