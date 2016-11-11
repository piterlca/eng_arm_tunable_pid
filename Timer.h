// Header: MIKROSKOP NA ARMIE 2468 Timery
// File Name: Timer.h
// Author: MACIEJ S�OCI�SKI
// Date: 16.04.2013


#ifndef __TIMER_H 
#define __TIMER_H

#include "LPC24xx.h"
#include "Type.h"
#include "PLL.h"
	
#define PCLK_TIMER1		(Fcclk/1)

/*Inicjalizuje Timera1, tzn zapisuje w�a�ciwe ustawienia w rejestrach ARM'a, by timer*/
/*dzi�a� w�a�ciwie.*/
void Timer1Init( void );
void Timer0Init( void* timer0_irq, DWORD T );
void Timer0Start(void);
void Timer0Stop(void);
void Timer0Restart(void);

/*Op�nienie liczone w cyklach zegara, przy 80MHz maksymalny czas op�nienia wynosi 53s*/
/*funkcji tej nie nale�y ���zy� z funkcj� Stoper'a, bo to ten sam timer!*/
void DelayCclk(DWORD dDelayInCclk);

 /*Op�nienie liczone w mikrosekundach, maksymalny czas op�nienia wynosi 1h 11 minut*/
/*funkcji tej nie nale�y ���zy� z funkcj� Stoper'a, bo to ten sam timer!*/
void DelayUs(DWORD dDelayInUs);

 /*Op�nienie liczone w mikrosekundach, maksymalny czas op�nienia wynosi 49 dni*/
/*funkcji tej nie nale�y ���zy� z funkcj� Stoper'a, bo to ten sam timer!*/
void DelayMs(DWORD dDelayInMs);

/*W��cza stoper w mikrosekundach, funkcja powi�zana: StoperUsClick b�dzie zwraca�a*/
/*czas, kt�ry min�� od momentu wywo�ania funkcji StoperUsStart. Po zako�czeniu u�ywania*/
/*stopera, nale�y wywo�a� funkcj� StoperUsStop. Nie nale�y ��czy� tej funkcji z funkcjami*/
/*Delay, bo to ten sam timer!*/
void StoperUsStart( void );

void StoperUsStop( void );

__inline DWORD StoperUsClick()
{
	return T1TC;
}

#endif
