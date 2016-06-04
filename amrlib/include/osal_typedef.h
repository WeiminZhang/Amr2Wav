/************************************************************************
*  文件名:      OSAL_types.h
*  描述:            基本数据类型声明
*  作者:            杨澍
*  版权:		深圳市源通世纪科技有限公司 2010 	   
*  历史记录: 
************************************************************************/
#ifndef _osal_typedef_H_
#define _osal_typedef_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;
	
#define OSCL_UNUSED_ARG(x) (void)(x)


#define OSCL_IMPORT_REF
#define OSCL_EXPORT_REF

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _osal_typedef_H_ */

