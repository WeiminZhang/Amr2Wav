/*
 * File Name:       amr2wav.h
 * Author:			weimin.zhang
 * Start Date:		2015.8.28
 * Language:          C/C+
 * Target:			decode for AMR file
 * Summary:			This file contains the functions to decompress amr to wav
 *
 * Change Note:
 */


/****************************************************************************
 * decodeOneAmrFile
 * Function   : decode amr to wav
 * Input      : char* AmrName = paths + amr filename
 *              char* WavNAme = paths + wav filename
 * Output     :
 * return     :  1: Success 0:Failure
 * Description:
****************************************************************************/
int decodeOneAmrFile( char* AmrName , char* WavNAme );
