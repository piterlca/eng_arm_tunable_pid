// Header: CYFROWY REGULATOR PID ALGORYTM REGULACJI
// File Name: PID.C
// Author: PAWE£ BICZYSKO
// Date: 10.11.2013

#include <lpc23xx.h> 
#include <math.h>
#include <stdlib.h>
#include "PID.h"
#include "type.h"

volatile WORD   kp,ki,kd;
SWORD  Error0,Error1,SumE_max, SumE_min, SumE;
SDWORD Integral_term, Proportional_term, Derivative_term,Sum,Cn; 
const WORD mask1=0x8000;


//-------------------------- PID_Init
SDWORD out_ki=0, out_kd=0,out_kp=0;
SDWORD in_data=0;
void PID_Init()
{
	//Inicjalizacja regulatora PID
 out_ki=0;
 in_data=0;
}
//-------------------------- PID
WORD PID(SWORD ADCbuf,PIDSTRUCT* factors,SDWORD off)
{
	SDWORD output;

//	output+=(out_kd*factors->kd)>>(factors->dkd);
//	output+=(out_kp*factors->kp)>>(factors->dkp);
	
	out_ki+=(((SDWORD)ADCbuf)*factors->ki)>>(factors->dki);
	out_ki=out_ki>(SDWORD)0x7fff?0x7fff:out_ki;
	out_ki=out_ki<(SDWORD)0xffff8001?0xffff8001:out_ki;

	out_kd=(SDWORD)ADCbuf;	out_kd-=in_data; 
	out_kd=(out_kd*factors->kd)>>(factors->dkd);
	in_data=(SDWORD)ADCbuf;
	
	out_kp=(((SDWORD)ADCbuf)*factors->kp)>>(factors->dkp);
	
	output=out_ki+out_kp+out_kd+off;
	output*=factors->sign;
	output=output>(SDWORD)0x7fff?0x7fff:output;
	output=output<(SDWORD)0xffff8001?0xffff8001:output;

	output+=0x7fff;
	return output;
}
