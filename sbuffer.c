#include "sbuffer.h"
//*****************************************************************
//Grzegorz JóŸwiak
//Circular buffer implementation
//*****************************************************************




// Creates circular buffer using pointer to the array "buf" of size "cap". 
// Function return structure SBUFFER defined in "sbuffer.h"
SBUFFER create_sbuffer(BYTE* buf, int cap)
{
	SBUFFER sbuf;
	sbuf.buf=buf; sbuf.capacity=cap-1; sbuf.w=0; sbuf.r=0;
	return sbuf;
}
// Function that puts a byte to the buffer pointed by b
// Function return TRUE if buffer is full
 volatile BYTE blablabla=0;
BOOL put_sbuffer(SBUFFER *b,BYTE data)
{
	if(((b->w+1) & (b->capacity)) != (b->r))
	{
		b->buf[b->w]=data;
		b->w=(b->w+1) & b->capacity;
		return FALSE;
	}else
		return TRUE;
}
// Function that gets a byte from the the buffer pointed by b
// Function returns TRUE if buffer is empty

BOOL get_sbuffer(SBUFFER *b, BYTE* data)
{
	if(b->w != b->r)
	{
		*data=b->buf[b->r];
		b->r=(b->r+1) & b->capacity;
		return FALSE;
	}else
		return TRUE;
}
// Function that returns the current number of bytes in the buffer "b"

int sbuffer_len(SBUFFER *b)
{
	return ((b->w-b->r) & b->capacity);
}

int write_sbuffer(SBUFFER *b,BYTE *tab, int num)
{
	int i;
	int len = b->capacity-sbuffer_len(b);
	len=len<num?len:num;
	for(i=0;i<len;i++)
	{
		b->buf[b->w]=tab[i];
		b->w=(b->w+1)& b->capacity;
	}
	return len;
}
int read_sbuffer(SBUFFER *b,BYTE *tab, int num)
{
	 int i;
	 int len = sbuffer_len(b);
	 len=len<num?len:num;
   	for(i=0;i<len;i++)
	{
		tab[i]=b->buf[b->r];
		b->r=(b->r+1)& b->capacity;
	}
	return len;
}