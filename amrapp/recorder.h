#ifndef _RECORDER_H__
#define _RECORDER_H__



#define MODE_R475	0
#define MODE_MR515	1             
#define MODE_MR59	2
#define MODE_MR67	3
#define MODE_MR74	4
#define MODE_MR795	5
#define MODE_MR102	6
#define MODE_MR122	7        

#define CAN_CONTINUE			1
#define CANNOT_CONTINUE			0
			
typedef void* AMRHandle ; 


/* For encoding amr  */
AMRHandle StartEncodeAmr( int bitsPerSample,  int channels , int SampleRate )  ; // Init
int GetPerFrameByteNumber( int mode )  ; //Get the the byte number per frame of this mode, should be called after init
char* GetAmrFileHead( AMRHandle AmrHandle ,  int * length ) ; //should be called after init
int EncodeSomeFrame(AMRHandle AmrHandle , int mode ,char*  in ,int SampleNum ,  char* out , int* outLength   ) ;
void EndEncodeAmr( AMRHandle handle) ; //End 

unsigned char* ConvertGsmToAmr(unsigned char* GsmData , int GsmDataLen , int AmrMode , int* AmrDataLen ) ;


#endif