/******************************************************************************
*    Copyright (c) 2009-2010 by Hisilicon.
*    All rights reserved.
* ***
*    Create by Cai ZhiYong. 2010-12-08
*
******************************************************************************/
#ifndef NANDH
#define NANDH
/******************************************************************************/

#define MTD_ABSENT		0
#define MTD_RAM			1
#define MTD_ROM			2
#define MTD_NORFLASH		3
#define MTD_NANDFLASH		4
#define MTD_DATAFLASH		6
#define MTD_UBIVOLUME		7

typedef long long   __kernel_loff_t;
/*****************************************************************************/

struct mtd_info_user {
	unsigned char type;
	unsigned long flags;
	unsigned long size;
	unsigned long erasesize;
	unsigned long writesize;
	unsigned long oobsize;
	unsigned long ecctype;
	unsigned long eccsize;
};
#define MEMGETINFO		_IOR('M', 1, struct mtd_info_user)

struct erase_info_user64 {
	unsigned long long start;
	unsigned long long length;
};
#define MEMERASE64		_IOW('M', 20, struct erase_info_user64)


struct mtd_oob_buf {
	unsigned long start;
	unsigned long length;
	unsigned char *ptr;
};
#define MEMREADOOB		_IOWR('M', 4, struct mtd_oob_buf)


struct mtd_epage_buf {
    unsigned long long start;        
    unsigned long data_len;
    unsigned long oob_len;
    unsigned char *data_ptr;
    unsigned char *oob_ptr; 
};
#define MEMEWRITEPAGE		_IOWR('M', 23, struct mtd_epage_buf)

#define MEMGETBADBLOCK		_IOW('M', 11, __kernel_loff_t)

#define MEMSETBADBLOCK		_IOW('M', 12, __kernel_loff_t)

#define MEMFORCEERASEBLOCK	_IOW('M', 128, __kernel_loff_t)  

/*****************************************************************************/

struct mtd_partition
{
    unsigned long long start;
    unsigned long long end;
    int readonly;
    char mtddev[12];
    int fd;
};

struct nand_raw_ctrl
{
    int num_partition;
    unsigned long long size;
	
    unsigned long pagesize;
    unsigned long blocksize;
    unsigned long oobsize;
	
    unsigned long pageshift;
    unsigned long blockshift;
	
    unsigned long pagemask;
    unsigned long blockmask;
	
    struct mtd_partition partition[1];
};

/******************************************************************************/
#endif /* NANDH */

