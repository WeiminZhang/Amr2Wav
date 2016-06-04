/*****************************************************************************
 *  TS 26.104
 *  R99   V3.4.0 2002-02
 *  REL-4 V4.3.0 2002-02
 *  3GPP AMR Floating-point Speech Codec
 *
 *****************************************************************************/
/* This is valid for PC */

#ifndef _TYPEDEF_H
#define _TYPEDEF_H

typedef char Word8;
typedef unsigned char UWord8;
typedef short Word16;
typedef int Word32;
typedef float Float32;
typedef double Float64;


#define M               10      /* Order of LP filter */
#define MP1             (M+1)   /* Order of LP filter + 1 */
#define L_WINDOW        240     /* Window size in LP analysis */
#define L_NEXT          40      /* Overhead in LP analysis */
#define LTPG_MEM_SIZE   5       /* number of stored past LTP coding gains + 1 */
#define N_FRAME         7       /* old pitch gains in average calculation */
#define DTX_HIST_SIZE   8       /* DTX history size */
#define L_TOTAL         320     /* Total size of speech buffer. */
#define L_FRAME         160     /* Frame size */
#define L_FRAME_BY2     80      /* Frame size divided by 2 */
#define L_SUBFR         40      /* Subframe size */
#define L_CODE          40      /* codevector length */
#define PIT_MAX         143     /* Maximum pitch lag */
#define PIT_MIN         20      /* Minimum pitch lag */
#define PIT_MIN_MR122   18      /* Minimum pitch lag (MR122 mode) */
#define L_INTERPOL      (10+1)  /* Length of filter for interpolation */
#define NPRED 4                 /* number of prediction taps */
#define SHARPMIN  0             /* Minimum value of pitch sharpening */
#define MAX_PRM_SIZE    57      /* max. num. of params */
#define L_INTER_SRCH    4           /* Length of filter for CL LTP search interpolation */
#define GP_CLIP         0.95F   /* Pitch gain clipping */
#define UP_SAMP_MAX     6
#define NB_TRACK        5       /* number of tracks */
#define NB_TRACK_MR102  4       /* number of tracks mode mr102 */
#define STEP            5       /* codebook step size */
#define STEP_MR102      4       /* codebook step size mode mr102 */
#define NC              M/2     /* Order of LP filter divided by 2 */


enum TXFrameType { TX_SPEECH_GOOD = 0,
                   TX_SID_FIRST,
                   TX_SID_UPDATE,
                   TX_NO_DATA,
                   TX_SPEECH_DEGRADED,
                   TX_SPEECH_BAD,
                   TX_SID_BAD,
                   TX_ONSET,
                   TX_N_FRAMETYPES     /* number of frame types */
};

/* Declaration recieved frame types */
enum RXFrameType { RX_SPEECH_GOOD = 0,
                   RX_SPEECH_DEGRADED,
                   RX_ONSET,
                   RX_SPEECH_BAD,
                   RX_SID_FIRST,
                   RX_SID_UPDATE,
                   RX_SID_BAD,
                   RX_NO_DATA,
                   RX_N_FRAMETYPES     /* number of frame types */
};

enum Mode { MR475 = 0,
            MR515,
            MR59,
            MR67,
            MR74,
            MR795,
            MR102,
            MR122,
            MRDTX,
            N_MODES     /* number of (SPC) modes */
};



#endif
