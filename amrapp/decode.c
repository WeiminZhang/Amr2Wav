/****************************************************************************
 * File Name:       decodec.c
 * Target:			Codec for AMR file
 * Summary:			This file contains the functions to decompress amr to wav
 *	 
 * Change Note:     
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedef.h"
#include "frmbtord.h"
#include "amrfile.h"
#include "wavefile.h"
#include "amr_if.h"

/****************************************************************************
 *	Function		:	DecodeAmrToWav
 *	Purpose 		:	Decode AMR to wave 
 *	Entry			:	AmrName -- char* , The input Amr file file name 
 *						WavName -- char* , The output wave sample file name ( no head )
 *	Return			:	static void
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 *****************************************************************************/
int decodeOneAmrFile( char* AmrName , char* WavNAme )
{
	typedef void Speech_Decode_FrameState ; 

	AMRStruct*	AmrStruct = 0 ;  	
	WAVStruct*	WavStruct = 0 ;
	Speech_Decode_FrameState *speech_decoder_state = NULL;

	Word16* synth0[6] = {0};        // L_FRAME    /* Synthesis                     */
	Word16* synthBuffer = 0  ;
	Word16* synth ;
	Word32 frame;

	Word16	n ;
    Word32 frametype = 0;
    Word32 size = 0;
	
	AmrStruct = OpenAmrFile( AmrName , 0 , 0 , 0 )  ;  	
	if( !AmrStruct )
		goto error ;
	size = AmrStruct->nChannels * (int)L_FRAME * sizeof( Word16 );
	synthBuffer = (Word16* ) malloc(size) ;
	if( !synthBuffer )
		goto error ;
	for( n = 0 ;  n < AmrStruct->nChannels ; n ++ )	
		synth0[ n ] = synthBuffer + n*L_FRAME ;	
	WavStruct = CreateWaveFile( WavNAme, AmrStruct->nChannels , 16 , AmrStruct->SampleRate ) ;
	if( !WavStruct )
		goto error ;
	speech_decoder_state = (Speech_Decode_FrameState *)AMRCODEC_init(MR515) ;//Decoder_Interface_init() ;
	if (!speech_decoder_state)
		goto error ;
	  

	/*-----------------------------------------------------------------------*
	* process serial bitstream frame by frame                               *
	*-----------------------------------------------------------------------*/
	frame = 0;
	while ( ReadOneFrameBlock( AmrStruct )  ) {
		++frame;
		for( n = 0 ; n < AmrStruct->nChannels ; n ++ ){
			synth = synth0[n] ;
			frametype  =  (AmrStruct->ChannelBuffer[n][0] >> 3 )&15 ;
			AMRCODEC_dec( speech_decoder_state , AmrStruct->ChannelBuffer[n], (bit_Byte_Number[frametype][1])+1 , (void*)synth);
		}
		WriteSeparateWaveFile( WavStruct , (unsigned char**)synth0 , AmrStruct->SampleRate/50 , AmrStruct->nChannels ) ;
	}

	/*-----------------------------------------------------------------------*
	* Close down speech decoder                                             *
	*-----------------------------------------------------------------------*/
//	Speech_Decode_Frame_exit(&speech_decoder_state);
	AMRCODEC_end(speech_decoder_state);
	CloseWaveFile( WavStruct );
	CloseAmrFile( AmrStruct ); 
	if(synthBuffer)
		free(synthBuffer);

	return 1;

error:
	if( WavStruct )
		CloseWaveFile( WavStruct );
	if( AmrStruct )
		CloseAmrFile( AmrStruct ); 
	if( synthBuffer )
		free(synthBuffer );
	if(speech_decoder_state )
		AMRCODEC_end(speech_decoder_state);
	return 0 ;
}

