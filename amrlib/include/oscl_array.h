#ifndef OSCL_ARRAY
#define OSCL_ARRAY

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define OSCL_ARRAY_NEW(size,len) malloc((size)*(len))
#define OSCL_ARRAY_DELETE(p) free(p)
#define OSCL_LEAVE(p)		\
	do{						\
		printf("%s\n", p);	\
		exit(0);			\
	}while(0)

#endif
