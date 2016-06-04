#ifndef OSCL_MEM
#define OSCL_MEM

#include <memory.h>
#include <stdlib.h>

#define oscl_memmove(x,y,z) memmove(x,y,z)
#define oscl_memcpy(x,y,z) memcpy(x,y,z)
#define oscl_memset(x,y,z) memset(x,y,z)

#define oscl_malloc(x) malloc(x)
#define oscl_free(x) free(x)

#endif

