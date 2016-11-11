#ifndef SYS_BUF_H
#define SYS_BUF_H
#include "type.h"

BOOL get_sysbuf_word(WORD* v);
BOOL get_sysbuf_sword(SWORD* v);

BOOL put_sysbuf_word(WORD v);
BOOL put_sysbuf_sword(SWORD v);


#endif