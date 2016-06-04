/**********************************************************************
 * File Name:       wavefile.c
 * Target:			Codec for AMR file
 * Summary:			This file contains the functions read/write wave file
 *	 
 * Change Note:     
 ************************************************************************/

/****************************************************
**************Wave file format***********************
	  __________________________
	| RIFF WAVE Chunk	   |
	|   groupID  = 'RIFF'      |
	|   riffType = 'WAVE'      |
	|    __________________    |
	|   | Format Chunk     |   |
	|   |	ckID = 'fmt '  |   |
	|   |__________________|   |
	|    __________________    |
	|   | Sound Data Chunk |   |
	|   |	ckID = 'data'  |   |
	|   |__________________|   |
	|__________________________|

****************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wavefile.h"


/********************************************************************************
 *	Function		:	OpenWaveFile
 *	Purpose 		:	Open a wave file 
 *	Entry			:	WavName -- wave file name 
 *	Return			:	WavStruct -- WAVStruct*
 *						The struct to collect wave file information
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 *********************************************************************************/


WAVStruct* OpenWaveFile( char* WavName ) 
{
	FILE*			fp = 0  ; 
	char			buf4[5] ;
	WAVStruct*		WavStruct = 0 ; 
	unsigned int	bytes ;
	fp = fopen( WavName , "rb" ) ;
	if( !fp )
		goto error;

	WavStruct = malloc( sizeof( WAVStruct ) ) ;
	if(!WavStruct )
		goto error;
	memset( WavStruct , 0 ,  sizeof( WAVStruct )  ) ; 
	bytes = fread( &(WavStruct->riff) , 1 , sizeof( WAVInfo ) ,   fp ) ;
	if( bytes != sizeof( WAVInfo ) )
		goto error;
	
	strcpy( buf4 , "RIFF" ) ;
	if( memcmp( WavStruct->riff.riffHead , buf4 ,4  ) != 0  )
		goto error;
	strcpy( buf4 , "WAVE" ) ;
	if( memcmp( WavStruct->riff.riffType, buf4,  4 ) != 0  )
		goto error;	
	strcpy( buf4 , "fmt " ) ;
	if( memcmp( WavStruct->foramt.chunkID, buf4, 4 ) != 0  )
		goto error;
	if( WavStruct->foramt.wFormatTag != WAVE_FORMAT_PCM )
		goto error;

	WavStruct->fp = fp ; 
	WavStruct->IsWrite = 0 ;
	return WavStruct ;
error:if( fp )
		  fclose( fp ) ;
	if( WavStruct )
		free( WavStruct ) ;
	return 0 ;
}


/*******************************************************************************
 *	Function		:	CreateWaveFile
 *	Purpose 		:	Create a wave file to writing
 *	Entry			:	WavName -- wave file name 
 *
 *	Return			:	WavStruct -- WAVStruct*
 *						The struct to collect wave file information 
 *						
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 *********************************************************************************/
WAVStruct* CreateWaveFile( char* WavName , short nChannel , short sampleBits , int sampleRate  ) 
{
	FILE*			fp = 0  ; 
	WAVStruct*		WavStruct = 0 ; 
	unsigned int	bytes ;
	fp = fopen( WavName , "wb" ) ;
	if( !fp )
		goto CreateWaveFile_error;

	WavStruct = malloc( sizeof( WAVStruct ) ) ;
	if(!WavStruct )
		goto CreateWaveFile_error;
	memset( WavStruct , 0 , sizeof( WAVStruct ) ) ;
	WavStruct->riff.riffHead[0] = 'R';
	WavStruct->riff.riffHead[1] = 'I';
	WavStruct->riff.riffHead[2] = 'F';
	WavStruct->riff.riffHead[3] = 'F';
	WavStruct->riff.riffType[0] = 'W';
	WavStruct->riff.riffType[1] = 'A';
	WavStruct->riff.riffType[2] = 'V';
	WavStruct->riff.riffType[3] = 'E';
	
	WavStruct->foramt.chunkID[0]= 'f';
	WavStruct->foramt.chunkID[1]= 'm';
	WavStruct->foramt.chunkID[2]= 't';
	WavStruct->foramt.chunkID[3]= ' ';
	WavStruct->foramt.chunkSize = sizeof(FormatChunk) - 8 ;
	WavStruct->riff.length =  20 + WavStruct->foramt.chunkSize ;
	WavStruct->foramt.wFormatTag =  WAVE_FORMAT_PCM ;
	WavStruct->foramt.wChannels =  nChannel  ;
	WavStruct->foramt.dwSamplesPerSec = sampleRate ;
	WavStruct->foramt.dwAvgBytesPerSec = sampleRate*sampleBits*nChannel/8 ;
	WavStruct->foramt.wBlockAlign = sampleBits*nChannel/8;
	WavStruct->foramt.wBitsPerSample = sampleBits ;
	WavStruct->data.chunkID[0] = 'd';
	WavStruct->data.chunkID[1] = 'a';
	WavStruct->data.chunkID[2] = 't';
	WavStruct->data.chunkID[3] = 'a';

	bytes = fwrite( &WavStruct->riff , 1 , sizeof( WAVInfo ) ,   fp ) ;
	if( bytes != sizeof( WAVInfo ) )
		goto CreateWaveFile_error;
		
	WavStruct->fp = fp ; 
	WavStruct->IsWrite = 1  ;
	return WavStruct ;

CreateWaveFile_error:
	if( fp )
		  fclose( fp ) ;
	if( WavStruct )
		free( WavStruct ) ;
	return 0 ;
}

/*********************************************************************************
 *	Function		:	WriteCombineSamplesWaveFile
 *	Purpose 		:	write sample into file 
 *	Entry			:	WavStruct -- WAVStruct*
 *						The struct to collect wave file information 
 *						samples -- unsigned char* , to store sample data with format:
 *						data of all channels in one sample is stored in the same location
 *						for example : two channels ,16bit/channel is placed as :
 *						l-ch-by0 , l-ch-by1;r-ch-by0, r-ch-by1;l-ch-by0,l-ch-by1;r-ch-by0,r-ch-by1
 *	Return			:	
 *						
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 *********************************************************************************/
short WriteCombineSamplesWaveFile( WAVStruct* WavStruct , unsigned char* samples , int sampleNum ) 
{
	int bytes ;
	int sampleBytes = sampleNum * WavStruct->foramt.wBlockAlign  ;		
	bytes = fwrite( samples , 1 , sampleBytes ,WavStruct->fp ) ;
	WavStruct->data.chunkSize += bytes ;
	if( bytes != sampleBytes )
		return 0 ;

	return 1 ;
}


/*************************************************************************************************
 *	Function		:	WriteSeparateWaveFile
 *	Purpose 		:	write sample into file 
 *	Entry			:	WavStruct -- WAVStruct*
 *							The struct to collect wave file information 
 *						samples -- unsigned char** , to a pointer group that has nChannel unsigned char
 *									buffer to store each channel samples	
 *						data of each channels is stored separate
 *						for example : two channels ,16bit/channel is placed as :
 *						samples[0] is left channel data , samples[1] is right channel data
 *	Return			:
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 *********************************************************************************/
short WriteSeparateWaveFile( WAVStruct* WavStruct , unsigned char** samples , int  sampleNum , short nChannel ) 
{
	int bytes ;
	unsigned char buf0[48] ;
	unsigned char* buf ;
	unsigned char* samplesTmp[12] ;
	int bytesEachChannel;
	int n , k ; 
	
	if( nChannel != WavStruct->foramt.wChannels ) 
		return 0 ; 

	memcpy( samplesTmp , samples , nChannel*sizeof( unsigned char* ) ) ;	
	bytesEachChannel = WavStruct->foramt.wBitsPerSample/8 ;
	
	buf = buf0 ;
	for( n = 0 ; n < sampleNum ; n ++  ){
		for( k = 0 ; k < nChannel ; k ++ ){
			memcpy( buf , samplesTmp[k]  , bytesEachChannel ) ;
			samplesTmp[k] += bytesEachChannel ;
			buf += bytesEachChannel ;
		}
		buf = buf0 ;
		bytes = fwrite( buf , 1 , WavStruct->foramt.wBlockAlign , WavStruct->fp ) ;
		WavStruct->data.chunkSize += bytes ;
	}
		
	return 1 ;
}

/**************************************************************************************
 *	Function		:	ReadCombineSamplesWaveFile
 *	Purpose 		:	Read sample into file 
 *	Entry			:	WavStruct -- WAVStruct*
 *						The struct to collect wave file information 
 *						samples -- unsigned char* , to store sample data with format:
 *						data of all channels in one sample is stored in the same location
 *						for example : two channels ,16bit/channel is placed as :
 *						l-ch-by0 , l-ch-by1;r-ch-by0, r-ch-by1;l-ch-by0,l-ch-by1;r-ch-by0,r-ch-by1
 *	Return			:
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 *********************************************************************************/
short ReadCombineSamplesWaveFile( WAVStruct* WavStruct , unsigned char* samples , int* sampleNum ) 
{
	int bytes ;
	int sampleBytes = *sampleNum * WavStruct->foramt.wBlockAlign  ;		
	bytes = fread( samples , 1 , sampleBytes ,WavStruct->fp ) ;
	if( bytes < sampleBytes )
		* sampleNum = bytes/WavStruct->foramt.wBlockAlign ;

	return 1 ;
}

/*************************************************************************************
 *	Function		:	ReadSeparateWaveFile
 *	Purpose 		:	Read sample into file 
 *	Entry			:	WavStruct -- WAVStruct*
 *							The struct to collect wave file information 
 *						samples -- unsigned char** , to a pointer group that has nChannel unsigned char
 *									buffer to store each channel samples	
 *						data of each channels is stored separate
 *						for example : two channels ,16bit/channel is placed as :
 *						samples[0] is left channel data , samples[1] is right channel data
 *	Return			:
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 *********************************************************************************/
short ReadSeparateWaveFile( WAVStruct* WavStruct , unsigned char** samples , int  *sampleNum , short nChannel ) 
{
	int bytes ;
	unsigned char buf0[48] ;
	unsigned char* buf ;
	unsigned char* samplesTmp[12] ;
	int bytesEachChannel;
	int n , k ; 
	int  sampleNum1 = *sampleNum ;
	
	if( nChannel != WavStruct->foramt.wChannels ) 
		return 0 ; 

	memcpy( samplesTmp , samples , nChannel*sizeof( unsigned char* ) ) ;	
	bytesEachChannel = WavStruct->foramt.wBitsPerSample/8 ;

	*sampleNum = 0 ;
	for( n = 0 ; n < sampleNum1 ; n ++  ){
		buf = buf0 ;
		bytes = fread( buf , 1 , WavStruct->foramt.wBlockAlign , WavStruct->fp ) ;
		if( bytes != WavStruct->foramt.wBlockAlign )
			return 0 ;
		for( k = 0 ; k < nChannel ; k ++ ){
			memcpy( samplesTmp[k]  , buf   , bytesEachChannel ) ;
			samplesTmp[k] += bytesEachChannel ;
			buf += bytesEachChannel ;
		}
		(*sampleNum )++ ;
	}
	if( *sampleNum  == sampleNum1 )
		return 1 ;

	return 0 ;
}

/*******************************************************************************
 *	Function		:	CloseWaveFile
 *	Purpose 		:	Close a wave file
 *	Entry			:	WavName -- wave file name 
 *	Return			:	WavStruct -- WAVStruct*
 *						The struct to collect wave file information
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 *********************************************************************************/
short CloseWaveFile( WAVStruct* WavStruct )
{
	if( !WavStruct->IsWrite ){
		fclose( WavStruct->fp) ;
		free( WavStruct ) ;
	}
	else{
		WavStruct->riff.length += WavStruct->data.chunkSize ;
		fseek( WavStruct->fp , 0 , SEEK_SET ) ;
		fwrite( &(WavStruct->riff) , 1 , sizeof(WAVInfo) , WavStruct->fp  ) ;
		fclose( WavStruct->fp) ;
		free( WavStruct ) ;
	}

	return 1 ;
}


