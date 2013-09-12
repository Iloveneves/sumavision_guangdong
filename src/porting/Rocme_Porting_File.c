/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_file.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
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

typedef struct File_Openlist //记录打开的普通文件的fd和打开模式
{
	INT32_T fd;
	CHAR_T mode[4];
	struct File_Openlist *next;
}File_Openlist_t;

typedef struct Dir_Openlist	//记录打开的目录文件的参数
{
	INT32_T dd;	//临时分配的一个整数值作为打开目录的返回值
	DIR *pDir;	//opendir函数的返回值
	Roc_File_List_t *filelist;  //记录目录下的所有文件名称和类型的链表首地址
	struct Dir_Openlist *next;	//指向打开的下一个目录
}Dir_Openlist_t;


static File_Openlist_t *File_Openlist_head = NULL; 	//打开文件的链表的首地址
static Dir_Openlist_t *Dir_Openlist_head = NULL; 	//打开目录的链表的首地址
static INT32_T DirBit = 1;	//用来记录已分配的描述符dd


static char* rocme_dir_path0 ="/flashfile/c";
static char* rocme_dir_temp ="/tmp";

static char g_cFileRd[1024];


/***************************************************************************
功能说明：
    打开指定文件。
参数说明：
    输入参数：
    [      filename]文件名
    [          mode]打开模式
    输出参数：
        无.
返    回： 
    成功 : 文件句柄
    失败 : -1

注：打开模式
"rb": 读模式，如果要打开的文件已存在，则打开成功，否则打开文件失败。
"wb": 写模式，如果要打开的文件已存在，则丢弃原来的内容，否则根据filename创建出一个内容为空的文件；如果路径中存在有目录未创建，则依次创建这些目录。

参考实现：
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
		while(p != NULL)	//找链表尾节点
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
			
			if(File_Openlist_head == NULL) //第一次打开文件
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
功能说明：
    关闭指定文件.
参数说明：
    输入参数：
    [             fd]文件句柄
    输出参数：
       无
返    回： 
    成功 : 0            
    失败 : -1
    	
参考实现：
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_close(INT32_T fd)
{
ROCME_TEST_PRINT
	INT32_T result;
	File_Openlist_t *p,*q,*tmp;

	p = q = tmp = File_Openlist_head;
	while(p != NULL)	//查找fd所在的节点
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
功能说明：
    读取指定文件的数据，通过buffer传送给调用者，读取长度为nbytes
参数说明：
    输入参数：
		[              fd] 文件句柄
		[          buffer] 返回的数据指针，此内存由调用者申请
		[          nbytes] 需要读取的字节数


    输出参数：无
返    回： 
    成功：实际读取到的文件长度（Byte）,0或小于nbytes，表示到文件结尾了。
	失败：-1
注意：成功返回值等于nbytes

参考实现：
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
功能说明：
		将buffer中的数据写入到指定的文件中，写入长度为nbytes
参数说明：
    输入参数：
    [              fd] 文件句柄
		[          buffer] 写入的数据所在内存地址
		[          nbytes] 需要写入的字节数

    输出参数：无
返    回： 
    成功：实际写入的字节数
	失败：0
注意：成功返回值等于nbytes。

参考实现：
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
功能说明：
    定位指定文件到指定位置,位置由off和origin指定.
参数说明：
    输入参数：
    [              fd] 文件句柄
		[             off] 要偏移的字节数
		[          origin] 偏移的起始位置,
		                   0表示从文件头部偏移off个字节,
		                   1表示从文件当前位置偏移off个字节,
		                   2表示从文件尾部偏移off个字节
    输出参数：
返    回： 
    成功 : 0        
    失败 : -1
注意：origin=0时,要求off>0; orgin=2时,要求off<0;

参考实现：
    rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_seek(INT32_T fd, INT32_T off, INT32_T origin)
{
ROCME_TEST_PRINT
	INT32_T result, where;

/* 应该是数码库有问题，要暂时注释掉，这样能显示开机画面 */	
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
功能说明：
得到文件当前位置相对于文件首的偏移字节数.
参数说明：
输入参数：
[              fd] 文件句柄
输出参数：
返    回： 
    成功: 置相对于文件首的偏移字节数.
    失败: -1
参考实现：
rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_tell(INT32_T fd)
{
ROCME_TEST_PRINT
	INT32_T off = 0;
	File_Openlist_t *p,*q;
	FILE *fp = NULL;
		
	p = q = File_Openlist_head;
	while(p != NULL)	//查找fd所在的节点，读取文件当时的打开模式
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
功能说明：
判断当前文件指针是否到达文件结尾.
参数说明：
输入参数：
[              fd] 文件句柄
输出参数：
返    回： 
    成功: 指针已经到达文件结尾，返回0；否则，返回一个正数。
    失败: 文件未打开等时返回-1
参考实现：
rocme_file.c
***************************************************************************/
INT32_T rocme_porting_file_eof(INT32_T fd)
{
ROCME_TEST_PRINT
	INT32_T off;
	File_Openlist_t *p,*q;
	FILE *fp = NULL;

	p = q = File_Openlist_head;
	while(p != NULL)	//查找fd所在的节点，读取文件当时的打开模式
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
功能说明：
		判断指定文件是否存在
参数说明：
    输入参数：
    [        filename] 文件名	
    输出参数：无
返    回： 
    存在   : 1
    不存在 : 0
    	
参考实现：
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
功能说明：
    给指定的文件重命名
参数说明：
    输入参数：
    [        filename] 原始文件名
    [         newname] 新文件名	
    输出参数：无
返    回： 
    成功 : 0           
    失败 : -1 或 错误码
参考实现：
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
功能说明：
    删除指定的文件
参数说明：
    输入参数：
    [        filename] 文件名称
    输出参数：
返    回： 
    成功 : 0
    失败 : -1 或 错误码
参考实现：
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
功能说明：
		获取指定文件的状态属性
参数说明：
    输入参数：
    [              fd] 文件句柄
    输出参数：
    [        filestatus] 文件的状态数据结构
返    回： 
    成功 : 0
    失败 : -1 或 错误码
参考实现：
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
		if(S_ISDIR(buf.st_mode)) //判断是否是目录文件
		{
			filestatus->file_mode = ROC_FILE_MODE_DIR;
		}
		
		if(S_ISREG(buf.st_mode)) //判断是否是普通文件
		{
		//判断USER的读写权限，若文件为非读写权限，则默认为可读权限
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
功能说明：
		打开指定的文件目录
参数说明：
    输入参数：
    [            path] 目录名称，指定目录，不带驱动器符，后缀可带/，绝对路径
    输出参数：无
返    回： 
    成功 : 目录句柄
    失败 : -1
参考实现：
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

		if(Dir_Openlist_head == NULL) //第一次打开目录
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
功能说明：
		关闭指定的文件目录
参数说明：
    输入参数：
    [            fd] 目录句柄
    输出参数：无
返    回： 
    成功 : 0
    失败 : -1 或 错误码
注 :
    删除文件描述链表中每个节点并释放内存
参考实现：
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
功能说明：
		读取指定的文件目录信息
参数说明：
    输入参数：
    [             dd] 目录句柄
    [       filelist]目录下文件描述链表的指针
返    回： 
    成功 : 0
    失败 : -1 或 错误码
注 :
    创建文件描述链表中每个节点并分配内存
参考实现：
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
		while(p != NULL)  //查找目录节点
		{
			if(p->dd == dd)//找到就跳出循环
			{
				break;
			}
			else
			{
				q = p->next;
				p = q;
			}
		}
	
		if(p == NULL)  //判断目录是否已经打开，若未打开，则返回；反之，则读取所有节点
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_dir_read not open or already closed!\n");
			return -1;
		}
	
		*filelist = NULL;
		pDir = p->pDir;
		while(((ptr=readdir(pDir))!=NULL)) //读取目录
		{
			if((strcmp(ptr->d_name, ".")==0)||(strcmp(ptr->d_name, "..")==0))
				continue;
			//给读到的节点分配内存，努力四次，若失败，则放弃次节点，继续读取下一节点
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
				filecount++; //记录成功读取并分配存储空间的节点个数
				strcpy(pFile->filename,ptr->d_name);
				//判断是目录还是普通文件；若是普通文件，则确认读写权限(若USER只有执行权限，则设为可读权限)
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
				if(filecount == 1)	//记录第一节点
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
功能说明：
		创建指定的文件目录，需要指定绝对路径，如果路径中存在多级目录未创建，则依次创建。
参数说明：
    输入参数：
    [            dir] 目录文件
    输出参数：无
返    回： 
    成功 : 0
    失败 : -1 或 错误码
参考实现：
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
功能说明：
    判断指定的文件目录是否存在
参数说明：
    输入参数：
    [         dirname] 目录文件名称
    输出参数：无
返    回： 
    存在   : 1
    不存在 : 0
参考实现：
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
功能说明：
		重命名指定的文件目录为newname
参数说明：
    输入参数：
    [         dirname] 目录名称
    [         newname] 新的目录名称
    输出参数：无
返    回： 
    成功 : 0            
    失败 : -1 或 错误码
参考实现：
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
功能说明：
    删除指定目录
参数说明：
    输入参数：
    [         dirname] 目录名称
    输出参数：无
返    回： 
    成功 : 0           
    失败 : -1 或 错误码
参考实现：
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
功能说明：
    获取指定编号的flash可写目录，该目录存在于flash上，
    断电后数据不会丢失。
参数说明：
    输入参数：
    [         index]可写目录编号
    [         name]可写目录的绝对路径
    输出参数：无
返    回： 
    成功 : 0           
    失败 : -1
备注：
    对应用来说，只能访问及修改指定目录下的文件或文件夹，
    该目录存在于flash上，断电后数据不会丢失。
    这种目录至少需要提供一个，一般也只需要一个，根据实际
    的需求编号由0开始依次递增，中间首先会获取index为0的可写目录。
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
功能说明：
    获取临时文件系统中的 可写目录，该目录存在于内存中，
    断电后数据可以丢失。
参数说明：
    输入参数：
    [         name]临时文件系统中可写目录的绝对路径
    输出参数：无
返    回： 
    成功 : 0           
    失败 : -1
备注：
    对中间件来说，某些操作需要一个临时文件夹，
    在启动运行的过程中，该文件夹可以正常读写访问，
    不会丢失，断电后内容则被清空。
    这个临时文件夹不须要保存在flash上，例如内存文件系统。
***************************************************************************/
INT32_T rocme_porting_get_tmp_dir(CHAR_T* name)
{
ROCME_TEST_PRINT
	strcpy(name,rocme_dir_temp);
	return 0;
}

