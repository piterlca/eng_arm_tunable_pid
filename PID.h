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


