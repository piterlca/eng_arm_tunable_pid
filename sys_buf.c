#include "sys_buf.h"

WORD SYSBUFWORD[16];
WORD wordbuf_posw=0,wordbuf_posr=0;

SWORD SYSBUFSWORD[16];
WORD swordbuf_posw=0,swordbuf_posr=0;				  

BOOL get_sysbuf_word(WORD* v)				   
{
	   if( wordbuf_posw==wordbuf_posr)
	   		return TRUE;
	   *v=SYSBUFWORD[wordbuf_posr];
	   wordbuf_posr++;
	   wordbuf_posr&=0xf;
	   return FALSE;

}

BOOL get_sysbuf_sword(SWORD* v)
{
	   if(swordbuf_posw==swordbuf_posr)
	   		return TRUE;
	   *v=SYSBUFSWORD[swordbuf_posr];
	   swordbuf_posr++;
	   swordbuf_posr&=0xf;
	   return FALSE;
}

BOOL put_sysbuf_word(WORD v)
{
	if( (wordbuf_posw-wordbuf_posr)&0xf >0xe)
		return TRUE;
	SYSBUFWORD[wordbuf_posw]=v;
	wordbuf_posw++;
	wordbuf_posw&=0xf;
	return FALSE;
}

BOOL put_sysbuf_sword(SWORD v)
{
	if( (swordbuf_posw-swordbuf_posr)&0xf >0xe)
		return TRUE;
	SYSBUFSWORD[swordbuf_posw]=v;
	swordbuf_posw++;
	swordbuf_posw&=0xf;
	return FALSE;
}
