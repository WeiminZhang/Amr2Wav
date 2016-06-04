/****************************************************************************
 * File Name:       wavefile.h
 * Target:			Codec for AMR file
 * Summary:			This file contains the functions read/write wave file
 *	 
 * Change Note:     
 **************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif



#define WAVE_FORMAT_PCM     1
//WAVEFORMAT



typedef struct {
	char	riffHead[4];
	int	length;
	char	riffType[4] ;
}RiffStrut;

typedef struct {
  char           chunkID[4];
  int           chunkSize;

  short          wFormatTag;
  unsigned short wChannels;
  unsigned int  dwSamplesPerSec;
  unsigned int  dwAvgBytesPerSec;
  unsigned short wBlockAlign;
  unsigned short wBitsPerSample;
/* Note: there may be additional fields here, depending upon wFormatTag. */
} FormatChunk ;

typedef struct {
	char	chunkID[4] ;
	int    chunkSize;
} DataChunk ;


typedef struct tagWAVStruct
{
	FILE*			fp ; 
	short			IsWrite ;
	RiffStrut		riff ;
	FormatChunk		foramt ;
	DataChunk		data ;
}WAVStruct ;


typedef struct tagWAVInfo
{
	RiffStrut		riff ;
	FormatChunk		foramt ;
	DataChunk		data ;
}WAVInfo ;

WAVStruct* OpenWaveFile( char* WavName )  ;
WAVStruct* CreateWaveFile( char* WavName , short nChannel , short sampleBits , int sampleRate  ) ;
short WriteCombineSamplesWaveFile( WAVStruct* WavStruct , unsigned char* samples , int sampleNum ) ; 
short WriteSeparateWaveFile( WAVStruct* WavStruct , unsigned char** samples , int  sampleNum , short nChannel )  ;
short ReadCombineSamplesWaveFile( WAVStruct* WavStruct , unsigned char* samples , int* sampleNum ) ;
short ReadSeparateWaveFile( WAVStruct* WavStruct , unsigned char** samples , int  *sampleNum , short nChannel )  ;
short CloseWaveFile( WAVStruct* WavStruct );


typedef struct _WaveDevConfig
{
	unsigned int bufferSize ;
	int			  bufferCount ;
	int			  writeMode ;	
}WaveDevConfig, *PWaveDevConfig ;

typedef struct _WaveConfig
{
	unsigned int sampleRate ;
	unsigned int dataBits ;
	unsigned int channels ;
}WaveConfig, *PWaveConfig ;



#ifdef __cplusplus
}
#endif

