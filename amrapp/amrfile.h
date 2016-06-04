

#ifdef __cplusplus
extern "C" {
#endif

enum AmrFileType
{
	AMR_NB_SC,
	AMR_WB_SC,
	AMR_NB_MC,
	AMR_WB_MC,
	AMR_TYPE_NUM
};
enum ChannelStruct
{
	// l : left , r: right , c : central , s : surround , f : front , r : rear
	SINGLE_CHANNEL = 0 ,
	L_R = 1 ,//left , right 
	L_R_C, //left , right , central 
	FL_FR_RL_RR , // quadrophonic 
	L_C_R_S, 
	FL_FR_FC_SL_SR,
	L_LC_C_R_RC_S
};

#define MAXBYTESOFONFRAME 32
typedef struct tagAMRStruct
{
	enum AmrFileType		AmrType ;
	int				SampleRate ;
	FILE*				fp ; // File pointer
	int				fd ; // File handle
	short				nChannels ; // number of channels	
	unsigned char*		ChannelBuffer[6] ;/*The buffer for channel ( most channel is 6 )
										  The first bytes is the frame header */
	unsigned char		BufferPointer[MAXBYTESOFONFRAME*6] ; // the memory pointer when alloced	
	enum ChannelStruct  Channel_Struct ; // channel information 
	short				CurrMode[6] ;  // To store current mode of each frame
	unsigned char		AmrFileHead[24];//stotre the file head in this buffer
	int					AmrFileHeadLength ;
}AMRStruct ;

//AMRStruct* OpenAmrFile(char* AmrName ) ;
AMRStruct* OpenAmrFile(char* AmrName , unsigned int* pid , int isIdFile , int offsetForIdFile )  ; 
AMRStruct* CreateAmrFile(char* AmrName , enum AmrFileType , enum ChannelStruct , int bCreateFile )  ;
short ReadOneFrameBlock( AMRStruct* AmrStruct  ) ;
short WriteOneFrameBlock( AMRStruct* AmrStruct  ) ;
short CloseAmrFile( AMRStruct* AmrStruct ) ;

#ifdef __cplusplus
}
#endif
