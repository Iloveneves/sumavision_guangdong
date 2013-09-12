/*******************************************************************************
File name   : rocme_porting_typedef.h

Author		: XXX			

Description : The generic macro definition for variable type.
	          All of the module concluded in RocMe MW must use same definition
	          as following.
	          
Copyright (C) BeiJing SUMAVision, Inc., 2009 .All rights reserved.

History		:
				2009.7.17		Created 						
*******************************************************************************/
#ifndef _ROCME_PORTING_TYPEDEF_H_
#define _ROCME_PORTING_TYPEDEF_H_



#define INT8_T 	 char
#define INT16_T  short
#define INT32_T  int
#define UINT8_T  unsigned char
#define UINT16_T unsigned short
#define UINT32_T unsigned int

typedef INT32_T  ROC_ERR_T;

#ifndef CHAR_T
#define CHAR_T   INT8_T
#endif

#ifdef HAVE_INT64_SUPPORT

#define UINT64_T unsigned long long
#define INT64_T long long

#else

#ifndef UINT64_T
typedef struct
{
    UINT32_T uint64_32h;
    UINT32_T uint64_32l;
}UINT64_T;
#endif

#ifndef INT64_T
typedef struct
{
    INT32_T  sint64_32h;
    UINT32_T uint64_32l;
}INT64_T;
#endif

#endif

#ifndef ROC_BOOL
#define ROC_BOOL INT32_T
#endif

#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif


#ifndef ROC_HANDLE
#define ROC_HANDLE void* 
#endif

#if !defined(ROC_TRUE) || (ROC_TRUE != 1)
#undef ROC_TRUE
#define ROC_TRUE (1==1)
#endif

#if !defined(ROC_FALSE) || (ROC_FALSE != 0)
#undef ROC_FALSE
#define ROC_FALSE (!ROC_TRUE)
#endif

#ifndef ROC_OK
#define ROC_OK (0)
#endif

#ifndef ROC_ERR
#define ROC_ERR (-1)
#endif

#ifndef   _SIZE_T_DEFINED   
#ifdef     _WIN64   
typedef   unsigned   __int64         size_t;   
#else
#ifndef size_t   
typedef   unsigned   int       size_t;
#endif   
#endif   
#define   _SIZE_T_DEFINED 
  
#endif 


#endif
