#ifndef _PID_H_
#define _PID_H_


#include "type.h"
typedef struct 
{
	WORD kp,ki,kd;
	BYTE dkp,dki,dkd;
	SBYTE sign;
	BYTE syn;
} PIDSTRUCT;
void PID_Init(void);
WORD PID(SWORD ADCbuf,PIDSTRUCT* factors,SDWORD off);

#endif
