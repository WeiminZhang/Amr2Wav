/* **************************************************************************************
 * File Name:       amrfile.c
 * Target:			Codec for AMR file
 * Summary:			This file contains the functions to decompress amr to wav
 *					Ref document:
 *					1. << draft-ietf-avt-rtp-amr-12.txt >> 	
 *					2. << 3GPP TS 26.101 V4.20(2002-3) , AMR Speech Codec Frame Structure>> 
 *	 
 * Change Note:     
 *****************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdio.h>
#include "amrfile.h"
#include "frmbtord.h"

/************************************************************************************
 *	Function		:	OpenAmrFile
 *	Purpose 		:	Open a amr file 
 *	Entry			:	AmrName -- Amr file name 
 *
 *	Return			:	AmrStruct -- AMRStruct*
 *						The struct to collect amr file information
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 ************************************************************************************/
/* The start string of AMR file : Norrow-band single-channel, Norrow-band single-channel,
   Wide-band single-channel,  Wide-band multi-channel */
const char* amrStr[4] = { "#!AMR\n" , "#!AMR-WB\n" , "#!AMR_MC1.0\n" , "#!AMR-WB_MC1.0\n" } ;
AMRStruct* OpenAmrFile(char* AmrName , unsigned int* pid , int isIdFile , int offsetForIdFile ) 
{
	char buf[15] = {0} ;
	unsigned int bytes = 0;
	
	int	fd = -1 ;
	AMRStruct* AmrStruct = 0  ;
	enum AmrFileType AmrType ;
	short n ;

	if( !isIdFile  )
#ifdef WIN32
	    fd = open( AmrName , O_RDONLY|O_BINARY ) ;

#else
	    fd = open( AmrName , O_RDONLY ) ; 
#endif

	if( fd == -1 )
		goto error ;

	bytes = read( fd , buf , 15) ;
	AmrType =  AMR_NB_SC ;
	while (bytes && AmrType < AMR_TYPE_NUM ){
		if( memcmp( buf , amrStr[AmrType] ,  strlen( amrStr[AmrType] ) ) == 0 )
			break ;
		AmrType ++  ;
	}
	
	if( AmrType >= AMR_TYPE_NUM ){
		goto error ;
	}

	if( !isIdFile  ){
		lseek( fd , strlen( amrStr[AmrType] )  , SEEK_SET );
	}
	else{
		lseek( fd , strlen( amrStr[AmrType] ) + offsetForIdFile  , SEEK_SET );
	}

	AmrStruct = (AMRStruct*)malloc( sizeof( AMRStruct ) ) ;
	if( !AmrStruct )
		goto error ;
	memset( AmrStruct , 0 , sizeof( AMRStruct ) ) ;
	AmrStruct->AmrType = AmrType ;
	AmrStruct->fd  = fd ; 
	if( AmrType >=  AMR_NB_MC ){
		read( fd , &(AmrStruct->nChannels ) , 2  )  ;
		read( fd , &(AmrStruct->nChannels ) , 2  )  ;

		if( AmrStruct->nChannels < 4 )
			AmrStruct->Channel_Struct ++ ;
	}
	else{
		AmrStruct->nChannels = 1  ;
		AmrStruct->Channel_Struct = SINGLE_CHANNEL ;
	}
	AmrStruct->ChannelBuffer[0]  = AmrStruct->BufferPointer ;
	for( n = 1  ; n <  AmrStruct->nChannels ; n ++ )
		AmrStruct->ChannelBuffer[n] = AmrStruct->ChannelBuffer[n-1] + MAXBYTESOFONFRAME ;	

	if( (AmrType == AMR_WB_SC ) || (AmrType == AMR_WB_MC) )
		AmrStruct->SampleRate = 16000 ;
	else
		AmrStruct->SampleRate = 8000 ;

	InitFrameBitOrder() ;
	return AmrStruct ;

error: 
	   if( fd ){
		   close( fd ) ;
		   fd = -1;
	   }

	   if( !AmrStruct ){
		   free( AmrStruct ) ;
		   AmrStruct = 0;
	   }

	   return 0 ;	
}


/**************************************************************************
 *	Function		:	CreateAmrFile
 *	Purpose 		:	Create a new  a amr file for writing 
 *	Entry			:	AmrName -- Amr file name 
 *
 *	Return			:	AmrStruct -- AMRStruct*
 *						The struct to collect amr file information
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 **************************************************************************/
/* The start string of AMR file : Norrow-band single-channel, Norrow-band single-channel,
   Wide-band single-channel,  Wide-band multi-channel */
//const char* amrStr[4] = { "#!AMR\n" , "#!AMR-WB\n" , "#!AMR_MC1.0\n" , "#!AMR-WB_MC1.0\n" } ;
AMRStruct* CreateAmrFile(char* AmrName , enum AmrFileType amrfiletype , enum ChannelStruct channelstruct , int bCreateFile ) 
{
	FILE* fp = 0  ; 	
	unsigned int bytes ;
	AMRStruct* AmrStruct = 0  ;
	if( bCreateFile ){
		fp = fopen( AmrName , "wb" ) ;
		if( !fp ) 
			goto error  ;
	}

	AmrStruct =(AMRStruct*) malloc( sizeof( AMRStruct ) ) ;
	if( ! AmrStruct ){
		goto error;
	}
	memset( AmrStruct , 0 , sizeof( AMRStruct ) ) ;

	strcpy( (char*)AmrStruct->AmrFileHead ,  amrStr[amrfiletype] ) ;
	AmrStruct->AmrFileHeadLength = strlen( amrStr[ amrfiletype] ) ;
	if ( (amrfiletype == AMR_NB_MC)  || (amrfiletype == AMR_WB_MC) ){
		bytes = channelstruct ;
		memcpy( AmrStruct->AmrFileHead + strlen( amrStr[ amrfiletype] ),   &bytes , 4  );
		AmrStruct->AmrFileHeadLength += 4 ;
	}

	if( bCreateFile ){
		bytes = fwrite( AmrStruct->AmrFileHead , 1 , AmrStruct->AmrFileHeadLength , fp ) ;
		if( bytes != AmrStruct->AmrFileHeadLength ){
			goto error;
		}
	}

	AmrStruct->AmrType =  amrfiletype ; 
	AmrStruct->fp = fp ; 
	AmrStruct->Channel_Struct = channelstruct ;
	AmrStruct->nChannels = channelstruct + 1 ;
	AmrStruct->ChannelBuffer[0] = AmrStruct->BufferPointer ; 
	for( bytes = 1 ; bytes <   AmrStruct->nChannels  ; bytes ++ ){
		AmrStruct->ChannelBuffer[bytes] = AmrStruct->ChannelBuffer[bytes-1] + MAXBYTESOFONFRAME ;
	}
	 
	InitFrameBitOrder();
	return  AmrStruct ;

error:
	if( fp ){
		fclose(fp);
		fp = -1;
	}

	if( AmrStruct ){
		free( AmrStruct ) ;
		AmrStruct = 0;
	}
	return 0 ;

}

/**************************************************************************************
 *	Function		:	ReadOneFrameBlock
 *	Purpose 		:	Get the bytes  of one frame block  from amr file
 *	Entry			:	AmrStruct -- AMRStruct , The struct to collect amr file information 
 *
 *	Return			:	short
 *						1, if success
 *						0, if Fail
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 ********************************************************************************************/
short ReadOneFrameBlock( AMRStruct* AmrStruct  ) 
{
	unsigned int bytes ;
	int frametype  ;
	int  nF  ;

	for(nF  = 0 ; nF < AmrStruct->nChannels ;  nF ++ ){
		bytes  = read( AmrStruct->fd , AmrStruct->ChannelBuffer[nF] , 1);
		if( bytes <= 0 ){
			return 0 ;
		}

		frametype  =  (AmrStruct->ChannelBuffer[nF][0] >> 3 )&15 ;
		bytes  = read(  AmrStruct->fd ,  &AmrStruct->ChannelBuffer[nF][1] ,  bit_Byte_Number[frametype][1] );
		if( bytes != bit_Byte_Number[frametype][1] ){
			return 0 ;
		}
	}
	return 1 ;
}


/****************************************************************************************
 *	Function		:	WriteOneFrameBlock
 *	Purpose 		:	Write the bytes  of one frame block  from amr file
 *	Entry			:	AmrStruct -- AMRStruct , The struct to collect amr file information 
 *
 *	Return			:	short
 *						1, if success
 *						0, if Fail
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 ****************************************************************************************/
short WriteOneFrameBlock( AMRStruct* AmrStruct  ) 
{
	unsigned int bytes = 0;
	int frametype = 0;
	int  nF  = 0;

	if(!AmrStruct){
		return 0;
	}

	for(  nF  = 0 ; nF < AmrStruct->nChannels ;  nF ++ ){
		bytes  = fwrite( AmrStruct->ChannelBuffer[nF] , 1 , 1 , AmrStruct->fp );
		if( bytes <= 0 )
			return 0 ;

		frametype  =  (AmrStruct->ChannelBuffer[nF][0] >> 3 )&15 ;
		bytes  = fwrite( &AmrStruct->ChannelBuffer[nF][1] , 1 , bit_Byte_Number[frametype][1] , AmrStruct->fp );
		if( bytes != bit_Byte_Number[frametype][1] ){
			return 0 ;
		}
	}

	return 1 ;
}


/**********************************************************************************
 *	Function		:	CloseAmrFile
 *	Purpose 		:	Close amrfile
 *	Entry			:	AmrStruct -- AMRStruct , The struct to collect amr file information 
 *	Return			:	short
 *						1, if success
 *						0, if Fail
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 ************************************************************************************/
short CloseAmrFile( AMRStruct* AmrStruct ) 
{
	int ret = -1;

	if(AmrStruct){
		return 0;
	}

	if(AmrStruct->fp)
		ret = fclose( AmrStruct->fp ) ; 
	if( AmrStruct->fd )
		ret += close( AmrStruct->fd ) ;
	free( AmrStruct ); //need to check if memory leak

	return (!ret?1:0)   ;
}

