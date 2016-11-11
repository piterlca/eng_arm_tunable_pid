// Header: CYFROWY REGULATOR PID SSP1
// File Name: SSP1_SPI.c
// Author: PAWE£ BICZYSKO
// Date: 10.11.2013

#include <lpc23xx.h> 
#include <stdlib.h>
#include <stdio.h>
#include "type.h"
#include "SSP1_SPI.h"


//-------------------------- Inicjowanie SPI na SSP1
void SSP1Init (void)
{
	BYTE i, Dummy=Dummy;
	PCONP |= (1 << 10); 					// Tylko dla porz¹dku, SSP jest w³¹czane z resetem. 
	PCLKSEL0 |= (0<<21)|(1<<20); 			// Ustawiamy CCLK/2
	PINSEL0 |=0x8A000;					    // P0.7 -> SCK1, P0.9 -> MOSI1
	IODIR0 |= (SSP1_SEL)|(SSP1_LDAC);	    // Ustawianie SSEL1 i LDAC jako output		 	
	IOSET0 |= (SSP1_LDAC)|(SSP1_SEL);		// Przypisanie SSEL1 i LDAC wartoœci pocz¹tkowej LOW
	SSP1CR0 = 0xF;        					// DSS - 16bit, Frame format SPI, CPOL =0, CPHA =0, SCR 0
	SSP1CPSR = 0x02;						// Min divisor 0x2
	SSP1CR1 =  SSPCR1_SSE; 					// W³¹czenie SSP1

	for ( i = 0; i < FIFOSIZE; i++ )
  	{
		Dummy = SSP1DR;						//czyszczenie RxFIFO
  	}
	return;
}

//-------------------------- SSP1Send
void SSP1Send( WORD buf)
{
	/*Oczekiwanie a¿ flaga BUSY = 0 i bufor TX FIFO nie jest pe³ny*/
	while ( (SSP1SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
	/*Poczekaj a¿ flaga BUSY zostanie wyzerowana*/
	SSP1DR = buf;
	while ( SSP1SR & SSPSR_BSY );
  	return; 
}
//-------------------------- SSP1Receive
void SSP1Receive( SWORD* buf )
{
	/*Wpisanie wartoœci losowej dla rozpoczêcia transmisji*/
	SSP1DR = 0xFF;
	/*Oczekiwanie na wyzerowanie flagi BUSY*/
	while ( (SSP1SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
   	*buf = SSP1DR;
}

