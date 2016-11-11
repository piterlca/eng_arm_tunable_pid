
#ifndef __SBUFFER_H
#define __SBUFFER_H
#include "Type.h"
typedef struct
{
	BYTE* buf;
	int capacity;
	int w,r;
} SBUFFER;

SBUFFER create_sbuffer(BYTE* buf, int cap);
BOOL put_sbuffer(SBUFFER *b,BYTE data);
int write_sbuffer(SBUFFER *b,BYTE *tab, int num);
int read_sbuffer(SBUFFER *b,BYTE *tab, int num);
BOOL get_sbuffer(SBUFFER *b, BYTE* data); 
int sbuffer_len(SBUFFER *b);

#endif
