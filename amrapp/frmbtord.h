/*
 * File Name:       frmbtord.tab
 * Author:			Han Josen
 * Start Date:		Dec 03 , 2003
 * Language:        Microsoft Visual C++ 6.0
 * Target:			Codec for AMR file
 * Summary:			This file contains the tables that map encoder out bits to frame bits
 *					The tables is created according to Table B.1 through Table B.8 in 
 *					<< 3GPP TS 26.101 V4.20(2002-3) , AMR Speech Codec Frame Structure>> 
 * Change Note:     
 */



#ifdef __cplusplus
extern "C" {
#endif

extern short bit_Byte_Number[16][2] ;
extern short* table0__7[8] ;
extern void InitFrameBitOrder() ;


#ifdef __cplusplus
}
#endif
