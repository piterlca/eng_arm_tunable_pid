// Header: MIKROSKOP NA ARMIE 2468 Konfiguracja PLL
// File Name: pll.h
// Author: MACIEJ S£OCIÑSKI
// Date: 13.04.2013


#ifndef __PLL_H 
#define __PLL_H

#define PLL_MValue			19
#define PLL_NValue			0
#define CCLKDivValue		5
#define USBCLKDivValue		9

#define Fosc	12000000	/*Taktowanie g³ównego oscylatora 12MHz*/
#define Fcclk	80000000	/*Taktowanie rdzenia arm'a 80MHz*/
#define Fcco	480000000	/*Taktowanie PLL'ki 480MHz*/

void PllInit ( void );

#endif
