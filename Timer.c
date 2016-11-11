// Header: MIKROSKOP NA ARMIE 2468 Timery
// File Name: Timer.c
// Author: MACIEJ S�OCI�SKI
// Date: 16.04.2013

#include "LPC24xx.h"
#include "Type.h"
#include "IRQ.h"
#include "Timer.h"
#include "sys_buf.h"


void Timer1Init( void ) 
{
	PCONP	|=	(0x1<<2); 							/*W��cza zasilanie na Timerze 1*/
	PCLKSEL0 =	(PCLKSEL0 & (0xFFFFFFFF^(0x3<<4)))|	/* UWAGA PCLK_TIMER1=CCLK/n,*/
				(0x1<<4);							/* 01->n=1;10->n=2;11->n=8;00->n=4*/
	T1MCR	=	(0<<0)|(0<<1)|(1<<2);		/* !!je�li TC == MR0 liczniki si� zatrzymaj� i TCR[0]=0*/
	T1CCR	=	0x0;				/* Nie pracujemy w trybie licznika na pinach wi�c 0*/				
	T1CTCR	=	0x0;				/* Praca w trybie Timer - tzn zliczamy impulsy pclk*/
	T1PR	=	1;					/*Prescaler, tzn co ile cykli ma si� zwi�ksza� licznik TC*/
	T1IR  	=	0xFF;
}


void Timer0Init( void* timer0_irq, DWORD T ) 
{
	PCONP	|=	(0x1<<2); 							/*W��cza zasilanie na Timerze 1*/
	PCLKSEL0 =	(PCLKSEL0 & (~(0x3<<2)))|	/* UWAGA PCLK_TIMER1=CCLK/n,*/
				(0x1<<2);							/* 01->n=1;10->n=2;11->n=8;00->n=4*/
	T0MCR	=	(1<<0)|(1<<1)|(0<<2);		/* !!je�li TC == MR0 liczniki si� zatrzymaj� i TCR[0]=0*/
	T0MR0 = T;
	T0CCR	=	0x0;				/* Nie pracu{jemy w trybie licznika na pinach wi�c 0*/				
	T0CTCR	=	0x0;				/* Praca w trybie Timer - tzn zliczamy impulsy pclk*/
	T0PR	=	0;					/*Prescaler, tzn co ile cykli ma si� zwi�ksza� licznik TC*/
	T0IR  	=	0xFF;
	T0TCR=0x2;
	while(T0TC!=0);
	T0TCR=0x00;
	install_irq( TIMER0_INT, timer0_irq, LOWEST_PRIORITY-6 );
}

void Timer0Start(void)
{
	T0TCR=0x1;
}

void Timer0Restart(void)
{
	T0TCR=0x2;
	while(T0TC!=0);
	T0TCR=0x1;
}	


void Timer0Stop(void)
{
	T0TCR=0x0;	
}

void DelayCclk(DWORD dDelayInCclk)
{								  
	T1TCR = 0x02;						/* Rest timera  i zastopowanie licznik�w */
	T1PR  = 0;							/* Ustawienie wzorst licznika co 1 pclk*/
	T1IR  = 0xFF;						/* wpisanie jedynek czy�ci bity przerwania */
	T1MR0 = dDelayInCclk;				/* Obliczenie warto�ci licznika*/
	T1TCR = 0x01;						/* start timer */
	while (T1TCR & 0x01);
}

void DelayUs(DWORD dDelayInUs)
{
	T1TCR = 0x02;						/* Rest timera  i zastopowanie licznik�w */
	T1PR  = (PCLK_TIMER1/1000000)-1;	/* Ustawienie wzorst licznika co 1 pclk*/
	T1IR  = 0xFF;						/* wpisanie jedynek czy�ci bity przerwania */
	T1MR0 = dDelayInUs;					/* Obliczenie warto�ci licznika*/
	T1TCR = 0x01;						/* start timer */
	while (T1TCR & 0x01);
}

void DelayMs(DWORD dDelayInMs)
{
	T1TCR = 0x02;						/* Rest timera  i zastopowanie licznik�w */
	T1PR  = (PCLK_TIMER1/1000)-1;		/* Ustawienie wzorst licznika co 1 pclk*/
	T1IR  = 0xFF;						/* wpisanie jedynek czy�ci bity przerwania */
	T1MR0 = dDelayInMs;					/* Obliczenie warto�ci licznika*/
	T1TCR = 0x01;						/* start timer */
	while (T1TCR & 0x01);
}

void StoperUsStart(void)
{
	T1TCR = 0x02;			  			/* Rest timera  i zastopowanie licznik�w */
	T1IR  = 0xFF;						/* wpisanie jedynek czy�ci bity przerwania */
	T1PR  = (PCLK_TIMER1/1000000)-1;	/* Ustawienie wzorst licznika co n pclk*/
	T1MR0 = 0xFFFFFFFF;					/* Wpisanie warto�ci licznika*/
	T1TCR = 0x01;						/* start timer */
}

void StoperUsStop(void)
{
	T1TCR = 0x02;						/* Rest timera  i zastopowanie licznik�w */
	T1IR  = 0xFF;						/* czyszczenie flag przerwania */  
}




