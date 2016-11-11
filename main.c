// Header: CYFROWY REGULATOR PID FUNKCJA G£ÓWNA
// File Name: main.c
// Author: PAWE£ BICZYSKO
// Date: 10.11.2013

#include <lpc24xx.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include "UART1.h"
#include "type.h"
#include "irq.h"
#include "SSP1_SPI.h"
#include "SSP0_SPI.h"
#include "timer.h"
#include "Buffer.h"
#include "PID.h"



//-------------------------- ADCSPI
/*Funkcja odczytu danych z ADC za poœrednictwem interfejsu SPI, odpowiednia 	  */
/*sekwencja ustawiania lini steruj¹cych gwarantuje stan niski lini SSP_MISO zaraz */
/*po zakoñczeniu konwersji wykorzystaæ to mo¿na do generacji przerwania. Dane 	  */
/*odczytane z ADC zapisywane s¹ do zmiennej ADCbuf typu SWORD					  */
void ADCSPI( SWORD* ADCbuf )
{

	IOSET1 |= SSP0_CNV;
	DelayCclk(1);
	IOCLR1 |= SSP0_SEL;
	SSP0Receive(ADCbuf);
	IOSET1 |= SSP0_SEL;
	IOCLR1 |= SSP0_CNV;
}

//-------------------------- DACSPI
/*Funkcja wys³ania danych na DAC, zapoœrednictwem interfejsu SPI wartoœæ do       */
/*generacji zapisywana jest w zmiennej DACbuf typu WORD 						  */
void DACSPI( WORD DACbuf )
{
	IOCLR0 |= SSP1_SEL;
    SSP1Send (DACbuf);
	IOSET0 |= SSP1_SEL; 
	IOCLR0 |= SSP1_LDAC;
	IOSET0 |= SSP1_LDAC;
}
typedef __packed struct{BYTE code; SWORD in; WORD out;} DATASTRUCT;


int i;
volatile PIDSTRUCT tPIDStruct,PIDStruct;
volatile WORD NumberOfSamples=0,tNumberOfSamples=0;
volatile BYTE nextM=0;
volatile BYTE synNOS=1;
volatile WORD volume=0;
volatile WORD tvolume=0;
volatile SWORD SetPoint=0;
volatile SWORD tSetPoint=0;
volatile BYTE synSP=0;
volatile SWORD ModAmp=0;
volatile SWORD tModAmp=0;
volatile WORD  ModPer=2500;
volatile WORD tModPer=2500;
volatile BYTE ModOn=0;
volatile BYTE tModOn=0;
volatile BYTE synMod=0;
DATASTRUCT data[1024];
int sample_cnt=0;

void pid_irq(void) __irq
{
		static WORD counter=0;
		static SWORD modifier=0;
			
		SWORD ADCbuf;
		SWORD oADCbuf;
		SWORD ornd;
		WORD DACbuf;
		SDWORD rnd;
		
		rnd=rand()-0x3fffffff;
		rnd>>=16;
		rnd*=tvolume;
		rnd>>=16;

		if(tPIDStruct.syn==1)
		{
			PIDStruct=tPIDStruct;
		}
		ADCSPI(&ADCbuf);
		oADCbuf=ADCbuf;
		if(synSP==1)
		{
			SetPoint=tSetPoint;
			synSP=0;
		}
		ADCbuf+=SetPoint;
		if(synMod==1)
		{	ModOn=tModOn; ModAmp=tModAmp; ModPer=tModPer;
			synMod=0;
		}
		if(ModOn==1)
		{
			counter++;
			if(counter==ModPer/2)
			{ 
				modifier=(modifier+1)&1;
			}
			if(counter==ModPer*2)
			{ 
				modifier=(modifier+1)&1;
				counter=0;
			}
			ADCbuf+=modifier?ModAmp:-ModAmp;
		}else
		{ 
			counter=0;
			modifier=0;
		}
		DACbuf=PID(ADCbuf,&PIDStruct,rnd);
		DACSPI(DACbuf);
		if(synNOS==1 && tNumberOfSamples==sample_cnt)
		{
		 	tNumberOfSamples=NumberOfSamples;
			tvolume=volume;
		}
		if(nextM==1)
		{
			sample_cnt=0;
			tNumberOfSamples=0;
			nextM=0;
		}
		if(sample_cnt<tNumberOfSamples)
		{
			data[sample_cnt].in=oADCbuf;
			data[sample_cnt].out=DACbuf;
			sample_cnt++;
		}
		T0IR=0xFF;
		VICVectAddr=0;
}
WORD stmptab[4000];
int main (void)
{
	int rstatus=0,sstatus=0;
	int cnt=0;
	BYTE ppp[11];
    PIDStruct.ki=25543; PIDStruct.kd=0; PIDStruct.kp=0;
	PIDStruct.dkp=31; PIDStruct.dkd=31; PIDStruct.dki=17;PIDStruct.sign=1;
	PllInit();	   
	SSP1Init();
	SSP0Init();
	init_VIC();
	Timer1Init();
	for(i=0;i<1024;++i)
	{
		data[i].code='D';
		data[i].in=i;
		data[i].out=i;
	}
	Uart1Init(115200);
	IOSET1 |= SSP0_SEL;

	Timer0Init((void*)pid_irq,20*80);
	Timer0Start();

//-------------------------- G³ówna pêtla
	memset(ppp,0,11);
	InitReadDataFree(ppp,11);    
	while(1)
	{
		rstatus=ReadDataFree();	
		if(rstatus)
		{
			if(ppp[0]=='P')
			{
				tPIDStruct.syn=0;
				memcpy((void*)&tPIDStruct,(void*)(ppp+1),11);
				if(tPIDStruct.kp==0 && tPIDStruct.ki==0 && tPIDStruct.kd==0)
					PID_Init();
				tPIDStruct.syn=1;
			}else if(ppp[0]=='M')
			{	
					synNOS=0;
					nextM=1;
					while(nextM);
					memcpy((void*)&NumberOfSamples,ppp+1,2);
					memcpy((void*)&volume,ppp+3,2);
					synNOS=1;
			}	
			else if(ppp[0]=='E')
			{
				synNOS=0;
				nextM=1;
				while(nextM);
				NumberOfSamples=0;
				volume=0;
				synNOS=1;
			}else if(ppp[0]=='S')
			{
			   memcpy((void*)&tSetPoint,ppp+1,2);
			   synSP=1;
			   while(synSP);
			}else if(ppp[0]=='F')
			{
				memcpy((void*)&tModOn,ppp+1,1);
				memcpy((void*)&tModAmp,ppp+2,2);
				memcpy((void*)&tModPer,ppp+4,2);
				synMod=1;
				while(synMod);
			}			
			InitReadDataFree(ppp,11);
		}

		if(sample_cnt!=0 && sample_cnt==tNumberOfSamples)
		{
			synNOS=0;
			data[NumberOfSamples].code='E';
			for(i=0;i<NumberOfSamples;i++)
				data[i].code='D';
			InitSendDataFree((BYTE*)data,(NumberOfSamples+1)*sizeof(DATASTRUCT));
			nextM=1;
			while(nextM);
			NumberOfSamples=0;
			volume=0;
			synNOS=1;
		}
		SendDataFree();
	}

}

// zero ma kod (0xffff/2-200);
//roznica ofsetow ukladow wejsciowych daje +340