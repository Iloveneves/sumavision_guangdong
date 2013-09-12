/******************************************************************************
*    Copyright (c) 2009-2010 by Hisilicon.
*    All rights reserved.
* ***
*    Create by Cai ZhiYong. 2010-12-07
*
******************************************************************************/

#ifndef NAND_RAWH
#define NAND_RAWH
/******************************************************************************/

#include "nand.h"

#define  SPAN_PART_HANDLE 1000
#define  HI_FLASH_END_DUETO_BADBLOCK    -10

int nand_raw_init(void);

int nand_raw_read( int fd, unsigned long long *startaddr, unsigned char *buffer, 
    unsigned long length, unsigned long long openaddr, unsigned long long limit_leng, int read_oob, int skip_badblock);

int nand_raw_write(int fd, unsigned long long *startaddr, unsigned char *buffer, 
    unsigned long length, unsigned long long openaddr, unsigned long long limit_leng, int write_oob);

int nand_raw_erase(int fd, unsigned long long startaddr, 
    unsigned long long length, unsigned long long openaddr, unsigned long long limit_leng);

int nand_raw_force_erase(unsigned long long offset);

int nand_mark_badblock(unsigned long long offset, unsigned long long length);

int nand_show_badblock(unsigned long long offset, unsigned long long length);

int nand_raw_info(struct mtd_info_user *mtdinfo);

int nand_raw_dump_partition(void);

int nand_raw_destroy(void);

unsigned long long nand_raw_get_start_addr(char *dev_name, unsigned long blocksize, int *value_valid);

void nand_raw_get_info(unsigned long long *totalsize, unsigned long *pagesize, unsigned long *blocksize, 
    unsigned long *oobsize, unsigned long *blockshift);

int  nand_raw_get_physical_index(unsigned long long startaddr, int *blockindex, int blocksize);
/*****************************************************************************/

char *int_to_size(unsigned long long size);

#if 0
#  define DBG_OUT(fmt, arg...) \
    printf("  %s[%d]: " fmt, __FUNCTION__, __LINE__, ##arg)
#else
#  define DBG_OUT(fmt, arg...)
#endif

/******************************************************************************/
#endif /* NAND_RAWH */

