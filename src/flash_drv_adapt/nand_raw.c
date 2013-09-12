/******************************************************************************
*    Copyright (c) 2009-2010 by Hisilicon.
*    All rights reserved.
* ***
*    Create by Cai ZhiYong. 2010-12-07
*
*    instruction:
*        1. mtd address cannot allow: mtd1[0,1M], mtd2[5M,10M];
******************************************************************************/

#ifndef _EMLUATOR_PC

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "nand.h"
#include "nand_raw.h"
/*****************************************************************************/

#define MAX_MTD_PARTITION          (32)
#define DEV_MTDBASE                "/dev/mtd"

static struct nand_raw_ctrl * nandraw_ctrl = NULL;

/*****************************************************************************/

static int get_max_partition(void);

static int check_skip_badblock(struct mtd_partition *ptn, int *blockindex,
    int blocksize); 

static int offshift(unsigned long n);
/*****************************************************************************/

int nand_raw_init(void)
{
    int ix;
    int dev;
    int readonly;
    int max_partition;
    //struct stat status;
    struct mtd_partition *ptn;
    struct mtd_info_user mtdinfo;

    char buf[sizeof(DEV_MTDBASE) + 5] = DEV_MTDBASE;
    char *ptr = buf + sizeof(DEV_MTDBASE) - 1;

    if (nandraw_ctrl)
        return 0;

    if (!(max_partition = get_max_partition()))
    {
        printf("Can't find mtd device at /dev/mtdx.\n");
        return -1;
    }

    if (++max_partition >= MAX_MTD_PARTITION)
    {
        printf("partition maybe more than %d, please increase MAX_MTD_PARTITION.\n", MAX_MTD_PARTITION);
    }

    nandraw_ctrl = (struct nand_raw_ctrl *)malloc(sizeof(struct nand_raw_ctrl) 
        + max_partition * sizeof(struct mtd_partition));

    if (!nandraw_ctrl)
    {
        printf("Not enough memory.\n");
        return -ENOMEM;
    }

    nandraw_ctrl->num_partition = 0;
    nandraw_ctrl->size = 0;
    ptn = nandraw_ctrl->partition;

    for (ix = 0; ix < max_partition; ix++)
    {
        readonly = 0;
        sprintf(ptr, "%d", ix);
        if ((dev = open(buf, O_RDWR)) == -1)
        {
            if ((dev = open(buf, O_RDONLY)) == -1)
            {
                printf("Can't open \"%s\"\n", buf);
                goto init_fail;
            }
            readonly = 1;
        }

        if (ioctl(dev, MEMGETINFO, &mtdinfo))
        {
            printf("Can't get \"%s\" information.\n", buf);
            goto init_fail;
        }

        if (mtdinfo.type != MTD_NANDFLASH)
        {
            close(dev);
            continue;
        }

        strcpy(ptn->mtddev, buf);
        ptn->fd = dev;
        ptn->readonly = readonly;
        ptn->start = nandraw_ctrl->size;
        nandraw_ctrl->size += mtdinfo.size;
        ptn->end   = nandraw_ctrl->size - 1;
        nandraw_ctrl->num_partition++;

        ptn++;

        if (nandraw_ctrl->num_partition == 1)
        {
            nandraw_ctrl->pagesize  = mtdinfo.writesize;
            nandraw_ctrl->blocksize = mtdinfo.erasesize;
            nandraw_ctrl->pagemask  = (mtdinfo.writesize - 1);
            nandraw_ctrl->blockmask = (mtdinfo.erasesize - 1);
            nandraw_ctrl->oobsize   = mtdinfo.oobsize;

            nandraw_ctrl->pageshift  = offshift(mtdinfo.writesize);
            nandraw_ctrl->blockshift = offshift(mtdinfo.erasesize); 
        }
    }

    if (!nandraw_ctrl->num_partition)
    {
        printf("Can't find nand type mtd device at /dev/mtdx\n");
        free(nandraw_ctrl);
        nandraw_ctrl = NULL;
    }

    return 0;

init_fail:
    for (ix = 0; ix < nandraw_ctrl->num_partition; ix++)
    {
        close(nandraw_ctrl->partition[ix].fd);
    }
    free(nandraw_ctrl);
    nandraw_ctrl = NULL;

    return -1;
}

void nand_raw_get_info
(
    unsigned long long *totalsize, 
    unsigned long *pagesize, 
    unsigned long *blocksize, 
    unsigned long *oobsize,
    unsigned long *blockshift)
{
    *totalsize  = nandraw_ctrl->size;
    *pagesize   = nandraw_ctrl->pagesize;
    *blocksize  = nandraw_ctrl->blocksize;
    *oobsize    = nandraw_ctrl->oobsize;
    *blockshift = nandraw_ctrl->blockshift;
}

/*****************************************************************************/
/* 
 * warning:
 *    1. if open SPI/NOR FLASH, return 0
      2. if dev_name cannot match nandraw_ctrl, return error_valid;
 */
unsigned long long nand_raw_get_start_addr(char *dev_name, unsigned long blocksize, int *value_valid)
{
    struct mtd_partition *ptn;
    int max_partition;
    int ix;

    ptn = nandraw_ctrl->partition;

    if (!(max_partition = get_max_partition()))
    {
        printf("Can't find mtd device at /dev/mtdx.\n");
        return 0;
    }

    if (nandraw_ctrl->blocksize != blocksize)
    {
        *value_valid = 1;
        return 0;
    }

    for (ix = 0; ix <= max_partition; ix++)
    {
        if (!strcmp(ptn->mtddev, dev_name))
        {
            break;
        }
        ptn++;
    }
    
    if (max_partition < ix)
    {
        *value_valid = 0;
        return 0;
    }
    else
    {
        *value_valid = 1;
        return ptn->start;
    }
}
/*****************************************************************************/
/* 
 * warning:
 *    1. startaddr should be alignment with pagesize 
 */

int nand_raw_read
(
    int fd,
    unsigned long long *startaddr, /* this address maybe change when meet bad block */
    unsigned char      *buffer, 
    unsigned long       length,    /* if HI_FLASH_RW_FLAG_WITH_OOB, include oob*/
    unsigned long long  openaddr,
    unsigned long long  limit_leng,
    int                 read_oob, 
    int                 skip_badblock)
{
    int ix;
    int rel;
    int totalread = 0;
    int num_read  = 0;
    struct mtd_partition *ptn;
    unsigned long long offset = *startaddr;

    if (!nandraw_ctrl)
    {
        printf("Please initialize before use this function.\n");
        return -1;
    }

    if (offset >= nandraw_ctrl->size || !length)
    {
        return 0;
    }

    if ((unsigned long)offset & nandraw_ctrl->pagemask)
    {
        printf("startaddr should be align with pagesize(0x%lX)\n",
            nandraw_ctrl->pagesize);
        return -1;
    }

    for (ix = 0; ix < nandraw_ctrl->num_partition && length; ix++)
    {
        ptn = &nandraw_ctrl->partition[ix];

        while ((ptn->start <= offset) && (offset < ptn->end) && length)
        {
            //DBG_OUT("dev: \"%s\", from: 0x%llX, length: 0x%lX\n",
                //ptn->mtddev, (offset - ptn->start), length);
            if (skip_badblock)
            {
                int blockindex = (int)((offset - ptn->start) / nandraw_ctrl->blocksize);

                rel = check_skip_badblock(ptn, &blockindex, nandraw_ctrl->blocksize);
                if (rel < 0)
                    return rel;

                if (rel > 0)
                {
                    /* move to start address of the block */
                    offset += (rel << nandraw_ctrl->blockshift);
                    offset &= (unsigned long long)~nandraw_ctrl->blockmask;
                    continue;
                }
                
                /* rel == 0, no bad block */ 
            }

            DBG_OUT(">ptn->fd=%d, length=%#lx, *startaddr=%#llx, offset=%#llx\n", ptn->fd, length, *startaddr, offset);

            if (offset - openaddr >= limit_leng)
            {
                printf("bad block cause read end(beyond limit_leng =%#llx)!\n", limit_leng);
                return HI_FLASH_END_DUETO_BADBLOCK;
            }

            /* read all pages in one block */
            do
            {
                /* read one page one by one */
                num_read = (length >= nandraw_ctrl->pagesize ? nandraw_ctrl->pagesize : length);
                if (lseek(ptn->fd, (unsigned long)(offset - ptn->start), SEEK_SET) != -1
                    && read(ptn->fd, buffer, num_read) != num_read)
                {
                    printf("read \"%s\" fail. %s\n",
                        ptn->mtddev, strerror(errno));
                    return -errno;
                }

                buffer    += num_read;
                length    -= num_read;
                totalread += num_read;

                if (read_oob)
                {
                    struct mtd_oob_buf oob;

                    if (length >= nandraw_ctrl->oobsize)
                    {
                        oob.start  = offset - ptn->start;
                        oob.length = nandraw_ctrl->oobsize;
                        oob.ptr    = (unsigned char *)buffer;

                        if (ioctl(ptn->fd, MEMREADOOB, &oob)) 
                        {
                            printf("read oob \"%s\" fail. %s\n",
                                ptn->mtddev, strerror(errno));
                            return -errno;
                        }

                        buffer    += nandraw_ctrl->oobsize;
                        length    -= nandraw_ctrl->oobsize;
                        totalread += nandraw_ctrl->oobsize;
                    }
                    else
                    {
                        /* read end when length less than oobsize. */
                        length = 0;
                    }
                }
                offset += num_read;

            } while (length && ((unsigned long)offset & nandraw_ctrl->blockmask));
        }
    }
    *startaddr = offset;

    return totalread;
}
/*****************************************************************************/
/* 
 * warning:
 *    1. offset should be alignment with blocksize 
 *    2. if there is a bad block, length should subtract.
 */
//int nand_raw_erase(unsigned long long offset, unsigned long long length, unsigned long long limit_leng)
int nand_raw_erase
(
	int fd, 
    unsigned long long startaddr, 
    unsigned long long length, 
    unsigned long long openaddr, 
    unsigned long long limit_leng)
{
    int ix;
    int rel;
    unsigned long long offset = startaddr;
    int blockindex;
    struct mtd_partition *ptn;

    if (!nandraw_ctrl)
    {
        printf("Please initialize before use this function.\n");
        return -1;
    }

    if (offset >= nandraw_ctrl->size || !length)
    {
        return 0;
    }

    if (((unsigned long)offset & nandraw_ctrl->blockmask)
        || ((unsigned long)length & nandraw_ctrl->blockmask))
    {
        printf("offset or length should be alignment with blocksize(0x%X)\n",
            (unsigned int)nandraw_ctrl->blocksize);
        return -1;
    }

    if (offset + length > nandraw_ctrl->size)
        length = nandraw_ctrl->size - offset;

    for (ix = 0; ix < nandraw_ctrl->num_partition && length; ix++)
    {
        ptn = &nandraw_ctrl->partition[ix];

        if (ptn->readonly)
        {
            printf("erase a read only partition \"%s\".\n", ptn->mtddev);
            return -1;
        }

        while ((ptn->start <= offset) && (offset < ptn->end) && length)
        {
            //DBG_OUT("dev: \"%s\", from: 0x%llX, length: 0x%llX\n",
                //ptn->mtddev, (offset - ptn->start), length);
            if (offset - openaddr >= limit_leng)
            {
                printf("1bad block cause erase end(beyond limit_leng =%#llx)!\n", limit_leng);
                return HI_FLASH_END_DUETO_BADBLOCK;
            }    

            blockindex = (int)((offset - ptn->start) >> nandraw_ctrl->blockshift);

            rel = check_skip_badblock(ptn, &blockindex, nandraw_ctrl->blocksize);

            /* no bad block */
            if (!rel) 
            {
                struct erase_info_user64 eraseinfo;

                eraseinfo.start  = (unsigned long long)(offset - ptn->start);
                eraseinfo.length = (unsigned long long)(nandraw_ctrl->blocksize);

                DBG_OUT(">ptn->fd=%d, length=%#llx, *startaddr=%#llx, offset=%#llx\n", ptn->fd, length, startaddr, offset);

                /* the block will be marked bad when erase error, so don't deal with */
                if (ioctl(ptn->fd, MEMERASE64, &eraseinfo))
                { 
                    printf("Erase 0x%llx failed!\n", offset);
                }
                rel = 1;
                length -= (rel << nandraw_ctrl->blockshift);
            }

            if (rel < 0)
                return rel;

            /* rel > 0 */
            offset += (rel << nandraw_ctrl->blockshift);            
        }
    }
    return 0;
}

/*****************************************************************************/
/* 
 * warning:
 *    1. offset should be alignment with blocksize
 */
int nand_raw_force_erase(unsigned long long offset)
{
    int ix;
    int rel;
    struct mtd_partition *ptn;
      
    if (!nandraw_ctrl)
    {
        printf("Please initialize before use this function.\n");
        return -1;
    }
    
    if (offset >= nandraw_ctrl->size)
    {
        return 0;
    }
    
    if ((unsigned long)offset & nandraw_ctrl->blockmask)
    {
        printf("offset should be alignment with blocksize(0x%X)\n", 
			(unsigned int)nandraw_ctrl->blocksize);
        return -1;
    }
    
    for (ix = 0; ix < nandraw_ctrl->num_partition; ix++)
    {
        ptn = &nandraw_ctrl->partition[ix];

        if (ptn->readonly)
        {
            printf("erase a read only partition \"%s\".\n", ptn->mtddev);
            return -1;
        }

        if ((ptn->start <= offset) && (offset < ptn->end))
        {
            DBG_OUT("dev: \"%s\", from: 0x%llX\n",
                ptn->mtddev, (offset - ptn->start));
        
            offset =offset - ptn->start;
            
            rel = ioctl(ptn->fd, MEMFORCEERASEBLOCK, &offset);
            if (rel)
            {
                printf("Force Erase 0x%llx failed!\n", offset);
                return rel;
            }
        }
    }
    return 0;
}   
/*****************************************************************************/
/* 
 * warning:
 *    1. startaddr should be alignment with pagesize 
 */
int nand_raw_write
(   
	int fd, 
    unsigned long long *startaddr, 
    unsigned char *buffer, 
    unsigned long length, 
    unsigned long long openaddr, 
    unsigned long long limit_leng, 
    int write_oob)
{
    int ix;
    int rel;
    int totalwrite = 0;
    int num_write = 0;
    int blockindex;
    unsigned char databuf[8192];
    unsigned char oobbuf[512];
    struct mtd_partition *ptn;
    struct mtd_epage_buf epage_buf;
    unsigned long long offset = *startaddr;

    if (!nandraw_ctrl)
    {
        printf("Please initialize before use this function.\n");
        return -1;
    }

    if (offset >= nandraw_ctrl->size || !length)
    {
        return -1;
    }

    if ((unsigned long)offset & nandraw_ctrl->pagemask)
    {
        printf("Startaddr should be alignment with pagesize(0x%lX)\n",
            nandraw_ctrl->pagesize);
        return -1;
    }

    /* if write_oob is used, align with (oobsize + pagesize) */
    if (write_oob && (length % (nandraw_ctrl->pagesize + nandraw_ctrl->oobsize)))
    {
        printf("Length should be alignment with pagesize + oobsize when write oob.\n");
        return -1;
    }

    if (!write_oob)
    {
        if (sizeof(oobbuf) < nandraw_ctrl->oobsize)
        {
            printf("%s: BUG program need enough oobbuf.\n",
                __FUNCTION__);
            return -1;
        }
        memset(oobbuf, 0xFF, sizeof(oobbuf));
    }

    if (sizeof(databuf) < nandraw_ctrl->pagesize)
    {
        printf("%s: BUG program need enough databuf.\n",
            __FUNCTION__);
        return -1;
    }

    for (ix = 0; ix < nandraw_ctrl->num_partition && length; ix++)
    {
        ptn = &nandraw_ctrl->partition[ix];
        if (ptn->readonly)
        {
            printf("Write a read only partition \"%s\".\n", ptn->mtddev);
            return -1;
        }

        while ((ptn->start <= offset) && (offset < ptn->end) && length)
        {
            /* must skip bad block when write */
            blockindex = (int)((offset - ptn->start) >> nandraw_ctrl->blockshift);

            rel = check_skip_badblock(ptn, &blockindex, nandraw_ctrl->blocksize);
            if (rel < 0)
                return rel;

            if (rel > 0)
            {
                /* move to start address of the block */
                offset += (rel << nandraw_ctrl->blockshift);
                offset &= (unsigned long long)~nandraw_ctrl->blockmask;
                continue;
            } 

            /* rel == 0, no bad block */

            DBG_OUT(">ptn->fd=%d, length=%#lx, *startaddr=%#llx, offset=%#llx\n", ptn->fd, length, *startaddr, offset);

            if (offset - openaddr >= limit_leng)
            {
                printf("bad block cause write end(beyond limit_leng =%#llx)!\n", limit_leng);
                return HI_FLASH_END_DUETO_BADBLOCK;
            }

            /* write all pages in one block */
            do
            {
                num_write = (length >= nandraw_ctrl->pagesize ? nandraw_ctrl->pagesize : length);
                
                epage_buf.start = offset - ptn->start;
                if (num_write < nandraw_ctrl->pagesize)
                {
                    /* less than one pagesize */
                    memset(databuf, 0xFF, sizeof(databuf));
                    memcpy(databuf, buffer, num_write);
                    epage_buf.data_ptr = databuf;
                }
                else
                {
                    epage_buf.data_ptr = buffer;
                }
                epage_buf.data_len = nandraw_ctrl->pagesize;

                offset     += num_write;
                length     -= num_write;
                buffer     += num_write;
                totalwrite += num_write;

                if (write_oob) /* if write_oob */
                {
                    if (length < nandraw_ctrl->oobsize)
                    {
                        printf("%s(%d): buf not align error!\n", __FILE__, __LINE__);
                        return -1;
                    }
                    
                    epage_buf.oob_ptr = buffer;

                    buffer     += nandraw_ctrl->oobsize;
                    length     -= nandraw_ctrl->oobsize;
                    totalwrite += nandraw_ctrl->oobsize;
                }
                else 
                {
                    epage_buf.oob_ptr = oobbuf;
                }
                epage_buf.oob_len = nandraw_ctrl->oobsize;

                /* avoid mark bad block unexpected. */
                if (*(unsigned short*)epage_buf.oob_ptr != 0xFFFF)
                {
                    printf("Please check input data, it maybe mark bad block. value:0x%04X\n",
                        *(unsigned short*)epage_buf.oob_ptr);
                    return -1;
                }

                /* should reerase and write if write error when upgrade. */                
                if (ioctl(ptn->fd, MEMEWRITEPAGE, &epage_buf) != 0)
                {
                    printf("ioctl(%s, MEMEWRITEPAGE) fail. %s\n",
                        ptn->mtddev, strerror(errno));
                    return -errno;
                }

            } while (length && ((unsigned long)offset & nandraw_ctrl->blockmask));
        }
    }    

    *startaddr = offset;

    return totalwrite;
}
/*****************************************************************************/
/* 
 * warning:
 *    1. offset and length should be alignment with blocksize 
 */
int nand_mark_badblock(unsigned long long offset, unsigned long long length)
{
    int ix;
    unsigned long long blockoffset;
    struct mtd_partition *ptn;

    if (!nandraw_ctrl)
    {
        printf("Please initialize before use this function.\n");
        return -1;
    }

    if (offset >= nandraw_ctrl->size || !length)
    {
        return 0;
    }

    if (((unsigned long)offset & nandraw_ctrl->blockmask)
        || ((unsigned long)length & nandraw_ctrl->blockmask))
    {
        printf("offset or length should be alignment with blocksize(0x%X)\n",
            (unsigned int)nandraw_ctrl->blocksize);
        return -1;
    }

    if (offset + length > nandraw_ctrl->size)
        length = nandraw_ctrl->size - offset;

    for (ix = 0; ix < nandraw_ctrl->num_partition && length; ix++)
    {
        ptn = &nandraw_ctrl->partition[ix];

        while ((ptn->start <= offset) && (offset < ptn->end) && length)
        {
            if (ptn->readonly)
            {
                printf("mark bad block error, a read only partition \"%s\".\n", ptn->mtddev);
                return -1;
            }
            
            DBG_OUT("dev: \"%s\", from: 0x%llX, length: 0x%llX\n",
                ptn->mtddev, (offset - ptn->start), length);
         
            blockoffset = offset - ptn->start;

            if (ioctl(ptn->fd, MEMSETBADBLOCK, &blockoffset))
            {
                printf("Mark bad block 0x%llX failed!\n", offset);
            }

            offset += (1 << nandraw_ctrl->blockshift);
            length -= (1 << nandraw_ctrl->blockshift);
        }
    }
    return 0;
}
/*****************************************************************************/
/* 
 * warning:
 *    1. offset and length should be alignment with blocksize 
 */
int nand_show_badblock(unsigned long long offset, unsigned long long length)
{
    int ix;
    unsigned int badblock;
    unsigned long long blockoffset;
    struct mtd_partition *ptn;

    if (!nandraw_ctrl)
    {
        printf("Please initialize before use this function.\n");
        return -1;
    }

    if (offset >= nandraw_ctrl->size || !length)
    {
        return 0;
    }

    if (((unsigned long)offset & nandraw_ctrl->blockmask)
        || ((unsigned long)length & nandraw_ctrl->blockmask))
    {
        printf("offset or length should be alignment with blocksize(0x%X)\n",
            (unsigned int)nandraw_ctrl->blocksize);
        return -1;
    }

    if (offset + length > nandraw_ctrl->size)
        length = nandraw_ctrl->size - offset;

    for (ix = 0; ix < nandraw_ctrl->num_partition && length; ix++)
    {
        ptn = &nandraw_ctrl->partition[ix];

        while ((ptn->start <= offset) && (offset < ptn->end) && length)
        {
            DBG_OUT("dev: \"%s\", from: 0x%llX, length: 0x%llX\n",
                ptn->mtddev, (offset - ptn->start), length);
         
            blockoffset = offset - ptn->start;

            if ((badblock = ioctl(ptn->fd, MEMGETBADBLOCK, &blockoffset)) < 0)
            {
                printf("Get nand badblock fail. %s\n", strerror(errno));
                return -errno;
            }
            if (badblock == 1)
            {
                printf("Bad block at address: 0x%lX of \"%s\", absolute address: 0x%llX\n",
                    (unsigned long)blockoffset, ptn->mtddev, (unsigned long long)offset);
            }
        
            offset += (1 << nandraw_ctrl->blockshift);
            length -= (1 << nandraw_ctrl->blockshift);
        }
    }
    return 0;
}
/*****************************************************************************/

int nand_raw_info(struct mtd_info_user *mtdinfo)
{
    int rel;

    if (!nandraw_ctrl)
    {
        printf("Please initialize before use this function.\n");
        return -1;
    }

    rel = ioctl(nandraw_ctrl->partition[0].fd, MEMGETINFO, mtdinfo);

    if (rel)
    {
        printf("ioctl \"%s\" fail. %s\n",
            nandraw_ctrl->partition[0].mtddev, strerror(errno));
        return rel;
    }

    if (nandraw_ctrl->size > 0xFFFFFFFF)
    {
        printf("nand flash size out of range of an unsigned long.\n");
    }
    mtdinfo->size = (unsigned long)nandraw_ctrl->size;

    return 0;
}
/*****************************************************************************/

int nand_raw_dump_partition(void)
{
    int ix;
    struct mtd_partition *ptn;

    if (!nandraw_ctrl)
    {
        printf("Please initialize before use this function.\n");
        return -1;
    }

    printf("-------------------------\n");
    printf("mtd device   start length mode\n");
    for (ix = 0; ix < nandraw_ctrl->num_partition; ix++)
    {
        ptn = &nandraw_ctrl->partition[ix];

        printf("%-12s ", ptn->mtddev);
        printf("%5s ", int_to_size(ptn->start));
        printf("%6s ", int_to_size(ptn->end + 1 - ptn->start));
        printf("%2s ", ptn->readonly ? "r" : "rw");
        printf("\n");
    }

    return 0;
}
/*****************************************************************************/

int nand_raw_destroy(void)
{
    int ix;

    if (!nandraw_ctrl)
        return 0;

    for (ix = 0; ix < nandraw_ctrl->num_partition; ix++)
    {
        close(nandraw_ctrl->partition[ix].fd);
    }

    free(nandraw_ctrl);
    nandraw_ctrl = NULL;

    return 0;
}
/*****************************************************************************/
/* change length to string */
char *int_to_size(unsigned long long size)
{
    int ix;
    static char buffer[20]; 
    char *fmt[] = {"%u", "%uK", "%uM", "%uG", "%uT", "%uT"};

    for (ix = 0; (ix < 5) && !(size & 0x3FF) && size; ix++)
    {
        size = (size >> 10);
    }
    sprintf(buffer, fmt[ix], (unsigned int)size);
    return buffer;
}
/*****************************************************************************/

static int get_max_partition(void)
{
    int n0 = 0;
    int n1 = MAX_MTD_PARTITION;
    int n = ((n1 + n0) >> 1);

    struct stat status;
    char buf[sizeof(DEV_MTDBASE) + 5] = DEV_MTDBASE;
    char *ptr = buf + sizeof(DEV_MTDBASE) - 1;

    do
    {
        sprintf(ptr, "%d", n);
        if (stat(buf, &status) < 0)
        {
            n1 = n;
        }
        else
        {
            n0 = n;
        }
        n = ((n1 + n0) >> 1);
    } while (n != n0);

    return n;
}
/*****************************************************************************/
/* 
 *  > 0 skip bad block num.
 *  = 0 no bad block.
 *  < 0 error.
 */
static int check_skip_badblock(struct mtd_partition *ptn, int *blockindex, 
    int blocksize)
{
    int rel = 0;
    unsigned int badblock;
    unsigned long long size = ptn->end - ptn->start + 1;
    loff_t offset = (unsigned long)(*blockindex) * blocksize;

    do
    {
        if ((badblock = ioctl(ptn->fd, MEMGETBADBLOCK, &offset)) < 0)
        {
            printf("Get nand badblock fail. %s\n", strerror(errno));
            return -errno;
        }
        if (badblock == 1)
        {
            printf("Skip bad block at address: 0x%lX of \"%s\", absolute address: 0x%llX\n",
                (unsigned long)offset, ptn->mtddev, (unsigned long long)(offset + ptn->start));
            (*blockindex)++;
            rel++;
        }
        offset = (*blockindex) * blocksize;
    } while (badblock == 1 && offset < size);

    return rel;
}

//printf("\t> ptn->start=%#llx,end=%#llx,endaddr=%#llx,offset_addr=%#llx, offset=%#x, ptn->fd=%d\n", 
    //ptn->start, ptn->end, endaddr, offset_addr, (unsigned int)offset, ptn->fd); 
int nand_raw_get_physical_index(unsigned long long startaddr, int *blockindex, int blocksize)
{
    struct mtd_partition *ptn;    
    unsigned int badblock; 
    int ix, i = 0;
    
    loff_t offset = (unsigned long)0;
    unsigned long long offset_addr = startaddr;
    int logcial_index = *blockindex;
    int physical_index = 0;

    if (0 == logcial_index)
    {
        return 0;
    }

    for (ix = 0; i < logcial_index && ix < nandraw_ctrl->num_partition; ix++)
    {
        ptn = &nandraw_ctrl->partition[ix];

        if (ptn->end + 1 <= startaddr)
        {
            continue;
        }

        while ((i < logcial_index) && (offset_addr < ptn->end))
        {      
            offset = (unsigned long)(offset_addr - ptn->start);

            if ((badblock = ioctl(ptn->fd, MEMGETBADBLOCK, &offset)) < 0)
            {
                printf("Get nand badblock fail. %s\n", strerror(errno));
                return -errno;
            }
            if (0 == badblock)
            {
                //printf("> Skip bad block at address: 0x%lX of \"%s\", absolute address: 0x%llX\n",
                    //(unsigned long)offset, ptn->mtddev, (unsigned long long)(offset + ptn->start));
                i++;                
            }
            physical_index++;            
            offset_addr += blocksize;       
        }
    } 

    DBG_OUT("logcial_addr=%d, physical_addr=%d\n", logcial_index, physical_index);
        //(unsigned long long)physical_index << nandraw_ctrl->blockshift, physical_index);
    *blockindex = physical_index;
    
    return 0;
}

/*****************************************************************************/

static int offshift(unsigned long n)
{
    int shift = -1;
    while (n)
    {
        n = n >> 1;
        shift++;
    }
    return shift;
}

#endif