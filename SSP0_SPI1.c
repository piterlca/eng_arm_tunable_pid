#include <lpc23xx.h> 
#include <stdlib.h>
#include <stdio.h>
#include "type.h"
#include "SSP0_SPI.h"

/* statistics of all the interrupts */
volatile DWORD interruptRxStat = 0;
volatile DWORD interruptOverRunStat = 0;
volatile DWORD interruptRxTimeoutStat = 0;

//-------------------------- Inicjowanie SPI na SSP0
void SSP0Init (void)
{
	BYTE i, Dummy=Dummy;
	PCONP |= (1 << 21); 					// Tylko dla porz¹dku, SSP jest w³¹czane z resetem. 
	PCLKSEL1 |= (0<<10)|(0<<11); 			// Równie¿ tylko dla porz¹dku, ustawiamy CCLK/4 czyli wartoœæ tak¹ jak przy resecie
	PINSEL3 |=0xC300;					    // P1.20 -> SCK0 P1.21 -> SSEL0, P1.23 -> MISO0
	IODIR1 |= (SSP0_SEL)|(SSP0_CNV);	     	// Ustawianie SSEL0 i CNV jako output		 	
	IOCLR1 |= (SSP0_CNV)|(SSP0_SEL);			// Przypisanie CNV i SEL wartoœci pocz¹tkowej LOW
	IOSET1 |= SSP0_SEL;
	SSP0CR0 = 0x8F;        					// DSS - 16bit, Frame format SPI, CPOL =0, CPHA =0, SCR 7
	SSP0CPSR = 0xff;						// max divisor 0xff
	SSP0CR1 =  SSPCR1_SSE; 					// w³¹czenie SSP0

	for ( i = 0; i < FIFOSIZE; i++ )
  	{
		Dummy = SSP0DR;						//czyszczenie RxFIFO
  	}
	return;
}

//-------------------------- SSP0Send
void SSP0Send( SWORD buf)
{
 	BYTE Dummy = Dummy;
	while ( (SSP0SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
	SSP0DR = buf;
	while ( SSP0SR & SSPSR_BSY );
  	return; 
}
//-------------------------- SSP0Receive
void SSP0Receive( SWORD* buf )
{
	SSP0DR = 0xFFFF;
	while ( (SSP0SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
   	*buf = SSP0DR;
}

