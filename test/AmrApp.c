#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "typedef.h"

static char g_avrpath[16] = "./111.amr";
static char g_wavpath[16] = "./222.wav";

int decodeOneAmrFile( char* AmrName , char* WavNAme );
/*
********************************************************************************
*                             MAIN PROGRAM
********************************************************************************
*/
int main (int argc, char *argv[])
{
    //if( argc < 3 ){
    //    return 0 ;
    //}

    //decodeOneAmrFile (  argv[1] , argv[2] ) ;
      decodeOneAmrFile (  g_avrpath , g_wavpath ) ;

    return EXIT_SUCCESS;
}
