// Header: CYFROWY REGULATOR PID SSP0
// File Name: SSP0_SPI.c
// Author: PAWE£ BICZYSKO
// Date: 10.11.2013

#include <lpc23xx.h> 
#include <stdlib.h>
#include <stdio.h>
#include "type.h"
#include "SSP0_SPI.h"

//-------------------------- Inicjowanie SPI na SSP0
void SSP0Init (void)
{
	BYTE i, Dummy=Dummy;

	PCONP |= 	(1 << 21); 					// Tylko dla porz¹dku, SSP jest w³¹czane z resetem. 
	PCLKSEL1 |= (1<<10)|(0<<11);			// Ustawiamy CCLK/2 											
	PINSEL3 |=  (0xC300);					// P1.20 -> SCK0, P1.23 -> MISO0				    
	IODIR1 |= (SSP0_SEL)|(SSP0_CNV);		// Ustawianie SSEL0 i CNV jako output		  	    		
	IOSET1 |= (SSP0_CNV)|(SSP0_SEL);		// Przypisanie CNV i SEL wartoœci pocz¹tkowej LOW		  
	SSP0CR0 = 0x8F;        					// DSS - 16bit, Frame format SPI, CPOL =0, CPHA =1, SCR 0
	SSP0CPSR = 0x02;						// Min divior 0x2
	SSP0CR1 =  SSPCR1_SSE; 					// W³¹czenie SSP0

	for ( i = 0; i < FIFOSIZE; i++ )
  	{
		Dummy = SSP0DR;						//Czyszczenie RxFIFO
  	}
	return;
}

//-------------------------- SSP0Send
void SSP0Send( WORD buf)
{
 	BYTE Dummy = Dummy;
	/*Oczekiwanie a¿ flaga BUSY = 0 i bufor TX FIFO nie jest pe³ny*/
	while ( (SSP0SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
	SSP0DR = buf;
	/*Poczekaj a¿ flaga BUSY zostanie wyzerowana*/
	while ( SSP0SR & SSPSR_BSY );
  	return; 
}
//-------------------------- SSP0Receive
void SSP0Receive( SWORD* buf )
{
	/*Wpisanie wartoœci losowej dla rozpoczêcia transmisji*/
	SSP0DR = 0xFF;
	/*Oczekiwanie na wyzerowanie flagi BUSY*/
	while ( (SSP0SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
   	*buf = SSP0DR;
}

