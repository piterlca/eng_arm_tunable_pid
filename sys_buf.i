#line 1 "sys_buf.c"
#line 1 "sys_buf.h"
#line 1 "type.h"




















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







#line 4 "sys_buf.h"

BOOL get_sysbuf_word(WORD* v);
BOOL get_sysbuf_sword(SWORD* v);

BOOL put_sysbuf_word(WORD v);
BOOL put_sysbuf_sword(SWORD v);


#line 2 "sys_buf.c"

WORD SYSBUFWORD[16];
WORD wordbuf_posw=0,wordbuf_posr=0;

SWORD SYSBUFSWORD[16];
WORD swordbuf_posw=0,swordbuf_posr=0;				  

BOOL get_sysbuf_word(WORD* v)				   
{
	   if( wordbuf_posw==wordbuf_posr)
	   		return (1);
	   *v=SYSBUFWORD[wordbuf_posr];
	   wordbuf_posr++;
	   wordbuf_posr&=0xf;
	   return (0);

}

BOOL get_sysbuf_sword(SWORD* v)
{
	   if(swordbuf_posw==swordbuf_posr)
	   		return (1);
	   *v=SYSBUFSWORD[swordbuf_posr];
	   swordbuf_posr++;
	   swordbuf_posr&=0xf;
	   return (0);
}

BOOL put_sysbuf_word(WORD v)
{
	if( (wordbuf_posw-wordbuf_posr)&0xf >0xe)
		return (1);
	SYSBUFWORD[wordbuf_posw]=v;
	wordbuf_posw++;
	wordbuf_posw&=0xf;
	return (0);
}

BOOL put_sysbuf_sword(SWORD v)
{
	if( (swordbuf_posw-swordbuf_posr)&0xf >0xe)
		return (1);
	SYSBUFSWORD[swordbuf_posw]=v;
	swordbuf_posw++;
	swordbuf_posw&=0xf;
	return (0);
}
