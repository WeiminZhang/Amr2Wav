/*************************************************************************************
 * File Name:       frmbtord.tab
 * Target:			Codec for AMR file
 * Summary:			This file contains the tables that map encoder out bits to frame bits
 *					The tables is created according to Table B.1 through Table B.8 in 
 *					<< 3GPP TS 26.101 V4.20(2002-3) , AMR Speech Codec Frame Structure>> 
 * Change Note:     
 **************************************************************************************/
#include "frmbtord.tab"

short* table0__7[8] ;

/*************************************************************************************
 *	Function		:	InitFrameBitOrder
 *	Purpose 		:	Inititate table0~table7 of reordering 
 *	Entry			:	
 *	Return			:	void 
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *	Note			:	
 **************************************************************************************/
void InitFrameBitOrder()
{
	int i ; 
	for( i = 0 ; i < 16; i  ++ )
		bit_Byte_Number[i][1] = (bit_Byte_Number[i][0]+7)/8 ;		
	
	table0__7[0] =(short*) BitOrderOfMR475 ;
	table0__7[1] =(short*) BitOrderOfMR515 ;
	table0__7[2] =(short*) BitOrderOfMR590 ;
	table0__7[3] =(short*) BitOrderOfMR670 ;
	table0__7[4] =(short*) BitOrderOfMR740 ;
	table0__7[5] =(short*) BitOrderOfMR795 ;
	table0__7[6] =(short*) BitOrderOfMR1020 ;
	table0__7[7] =(short*) BitOrderOfMR1220 ;
}






