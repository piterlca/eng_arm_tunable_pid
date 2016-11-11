// Header: MIKROSKOP NA ARMIE 2468 Konfiguracja PLL
// File Name: PLL.c
// Author: MACIEJ S£OCIÑSKI
// Date: 13.04.2013

#include "LPC24xx.h"
#include "Type.h"
#include "PLL.h"

void PllInit ( void )
{
	DWORD MValue, NValue;

	if ( PLLSTAT & (1 << 25) ) /*Sprawdza czy PLL'ka jest zegarem rdzenia arm'a*/
	{
		PLLCON = (1<<0)|		/*W³¹cza PLL'ke*/
				 (0<<1);		/*Od³¹cza PLLkê od rdzenia arma, rdzeñ jest teraz*/
			 				/*taktowany bezpoœrednio wczeœniejszym Ÿród³em PLLki*/
/*OD TERAZ RDZEÑ JEST TAKTOWANY ZEGAREM KTÓRY BY£ RÓD£EM DLA PLLki*/
		PLLFEED = 0xaa;			/*Procedura zabezpieczaj¹ca*/
		PLLFEED = 0x55;			/*Procedura zabezpieczaj¹ca*/
	}
	PLLCON = 0;					/*Wy³¹cza PLL'ke zupe³nie*/
	PLLFEED = 0xaa;				/*Procedura zabezpieczaj¹ca*/
	PLLFEED = 0x55;				/*Procedura zabezpieczaj¹ca*/

	SCS |= (1<<5);				/* W³¹czenie g³ównego oscylatora*/
	while( !(SCS & (1<<6)) );	/* Sprawdza czy main oscylator ju¿ siê rozpêdzi³*/

	CLKSRCSEL = 0x1;			/* Ustawia main oscylator jako Ÿród³o PLL'ki */

  /*OD TERAZ RDZEÑ JEST TAKTOWANY G£ÓWNYM OSCYLATOREM*/

  	MAMCR	=	0;							/*Wy³¹cza przyspieszenie pamiêci, jeœli wy³¹czymy*/
  											/*obs³ugê MAM w czasie dzia³ania PLLki, arm siê zwiesi*/
    MAMTIM	=	0x4;						/*Ustawia odczyt z pamiêci flash na poziomie 4 cclk*/
    MAMCR	=	0x2;						/*W³¹cza pe³n¹ obs³ugê przyspieszenia pamiêci*/
											/*00->wy³ 01->czêœciowo w³¹cz. 10 - w³¹cz.*/
	PLLCFG = PLL_MValue | (PLL_NValue << 16); /*Wartoœæi PLL_MValue i N s¹ zdefiniowane*/
	PLLFEED = 0xaa;							/*w target.h, tu ustawiamy czêstotliwoœæ:*/
	PLLFEED = 0x55;							/*Fcco = (2 × (M+1) × Fin) / (N+1), Fin=12MHz*/

	PLLCON = 1;								/*W³¹czamy PLL'kê */
	PLLFEED = 0xaa;							/*Procedura zabezpieczaj¹ca*/
	PLLFEED = 0x55;							/*Procedura zabezpieczaj¹ca*/
	CCLKCFG = CCLKDivValue;					/*Ustawiamy czêstotliwoœæ rdzenia */
											/*Fcclk=Fcco/(CCLKDivValue+1)*/
	USBCLKCFG = USBCLKDivValue;				/* usbclk = Fcco/USBCLKDivValue = 48 MHz */

	while ( ((PLLSTAT & (1 << 26)) == 0) ); /* Sprawdza czy PLLka siê ju¿ rozpêdzi³a */
											/* dopiero wtedy opuœcimy pêtlê */

	MValue = PLLSTAT & 0x00007FFF;			/* Odczytuje jakie wartoœci M i N s¹ ustalone*/
	NValue = (PLLSTAT & 0x00FF0000) >> 16;

/*Pu³apka jeœli PLLka siê ustali³a jakimœ cudem na inn¹ czêstotliwoœæ ni¿ ustawiliœmy*/
/*tzn s¹ inne wartoœci MValue i NValue, to wpadniemy w t¹ pêtlê*/
	while ((MValue != PLL_MValue) && ( NValue != PLL_NValue) );
	PLLCON = 3;				/* W³¹cza PLLkê i pod³¹cza j¹ jako Ÿród³o dla rdzenia ARMa */
	PLLFEED = 0xaa;			/*Procedura zabezpieczaj¹ca*/
	PLLFEED = 0x55;			/*Procedura zabezpieczaj¹ca*/

/*OD TERAZ RDZEÑ JEST TAKTOWANY PLLk¹! Gratulujê*/
	while ( ((PLLSTAT & (1 << 25)) == 0) );	/* Sprawdza czy PLLka ju¿ jest zegarem rdzenia*/
}
