#line 1 "sbuffer.c"
#line 1 "sbuffer.h"

#line 1 "Type.h"




















typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef unsigned long long  QWORD;
typedef unsigned int   BOOL;

typedef signed char SBYTE;
typedef signed short SWORD;
typedef signed long  SDWORD;
typedef signed long long  SQWORD;
typedef signed int   SBOOL;







#line 5 "sbuffer.h"
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

#line 2 "sbuffer.c"










SBUFFER create_sbuffer(BYTE* buf, int cap)
{
	SBUFFER sbuf;
	sbuf.buf=buf; sbuf.capacity=cap-1; sbuf.w=0; sbuf.r=0;
	return sbuf;
}


 volatile BYTE blablabla=0;
BOOL put_sbuffer(SBUFFER *b,BYTE data)
{
	if(((b->w+1) & (b->capacity)) != (b->r))
	{
		b->buf[b->w]=data;
		b->w=(b->w+1) & b->capacity;
		return (0);
	}else
		return (1);
}



BOOL get_sbuffer(SBUFFER *b, BYTE* data)
{
	if(b->w != b->r)
	{
		*data=b->buf[b->r];
		b->r=(b->r+1) & b->capacity;
		return (0);
	}else
		return (1);
}


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
