
#ifndef __AMR_IF_H__
#define __AMR_IF_H__

#define INVALID_AMR_HANDLE NULL

typedef void *AMRCODEC_HANDLE;

typedef enum { 
    E_AMR_MODE_MR475 = 0,
    E_AMR_MODE_MR515,
    E_AMR_MODE_MR59,
    E_AMR_MODE_MR67,
    E_AMR_MODE_MR74,
    E_AMR_MODE_MR795,
    E_AMR_MODE_MR102,
    E_AMR_MODE_MR122,
    E_AMR_MODE_MRDTX,
    E_AMR_MODE_MAX_MODES     /* number of (SPC) modes */
} AMR_MODE;

/*-------------------------------------------------------------------------
                接口声明
-------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************
 * AMRCODEC_init
 * 功能：AMRCODEC初始化相关资源
 * 输入: eEncodeMode     -amr 编码模式
 * 输出:  
 * 返回: 成功：返回有效的AMRCODEC句柄,失败：返回INVALID_AMR_HANDLE
 * 说明:  
****************************************************************************/
AMRCODEC_HANDLE AMRCODEC_init(AMR_MODE eEncodeMode);


/****************************************************************************
 * AMRCODEC_end
 * 功能：AMRCODEC结束，释放相关资源
 * 输入: hHandle     -AMRCODEC编解码句柄
 * 输出:  
 * 返回: 无
 * 说明:  
****************************************************************************/
void AMRCODEC_end(AMRCODEC_HANDLE hHandle);



/****************************************************************************
 * AMRCODEC_dec
 * 功能：amr 解码，调用一次解码一帧
 * 输入: pAmrBuf     -arm 数据
 		nAmrLen  --arm 数据长度
 				 
 * 输出: pPcmBuf     ---存放pcm的buffer
 * 返回: 
 * 说明: pAmrBuf 和 pPcmBuf 都是应用程序提供
****************************************************************************/
void AMRCODEC_dec(AMRCODEC_HANDLE hHandle, void* pAmrBuf, int nAmrLen, void* pPcmBuf);


/****************************************************************************
 * AMRCODEC_enc
 * 功能：pcm 编码，调用一次编码一帧
 * 输入: pPcmBuf     -pcm 数据buffer
 				 
 * 输出: pAmrBuf     ---存放amr的buffer
         pnAmrLen  ---amr的编码长度
         pnFrameType----amr 帧格式
 * 返回: 
 * 说明: pAmrBuf 和 pPcmBuf 都是应用程序提供
****************************************************************************/
void AMRCODEC_enc(AMRCODEC_HANDLE hHandle, void* pPcmBuf, void* pAmrBuf, int* pnAmrLen, int* pnFrameType);


#ifdef __cplusplus
}
#endif

#endif // __AMR_IF_H__

/***************************************************************************
			END
***************************************************************************/
