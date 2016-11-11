// Header: MIKROSKOP NA ARMIE 2468 Timery
// File Name: Timer.h
// Author: MACIEJ S£OCIÑSKI
// Date: 16.04.2013


#ifndef __TIMER_H 
#define __TIMER_H

#include "LPC24xx.h"
#include "Type.h"
#include "PLL.h"
	
#define PCLK_TIMER1		(Fcclk/1)

/*Inicjalizuje Timera1, tzn zapisuje w³aœciwe ustawienia w rejestrach ARM'a, by timer*/
/*dzi³a³ w³aœciwie.*/
void Timer1Init( void );
void Timer0Init( void* timer0_irq, DWORD T );
void Timer0Start(void);
void Timer0Stop(void);
void Timer0Restart(void);

/*OpóŸnienie liczone w cyklach zegara, przy 80MHz maksymalny czas opóŸnienia wynosi 53s*/
/*funkcji tej nie nale¿y ³¹æzyæ z funkcj¹ Stoper'a, bo to ten sam timer!*/
void DelayCclk(DWORD dDelayInCclk);

 /*OpóŸnienie liczone w mikrosekundach, maksymalny czas opóŸnienia wynosi 1h 11 minut*/
/*funkcji tej nie nale¿y ³¹æzyæ z funkcj¹ Stoper'a, bo to ten sam timer!*/
void DelayUs(DWORD dDelayInUs);

 /*OpóŸnienie liczone w mikrosekundach, maksymalny czas opóŸnienia wynosi 49 dni*/
/*funkcji tej nie nale¿y ³¹æzyæ z funkcj¹ Stoper'a, bo to ten sam timer!*/
void DelayMs(DWORD dDelayInMs);

/*W³¹cza stoper w mikrosekundach, funkcja powi¹zana: StoperUsClick bêdzie zwraca³a*/
/*czas, który min¹³ od momentu wywo³ania funkcji StoperUsStart. Po zakoñczeniu u¿ywania*/
/*stopera, nale¿y wywo³aæ funkcjê StoperUsStop. Nie nale¿y ³¹czyæ tej funkcji z funkcjami*/
/*Delay, bo to ten sam timer!*/
void StoperUsStart( void );

void StoperUsStop( void );

__inline DWORD StoperUsClick()
{
	return T1TC;
}

#endif
