// Header: MIKROSKOP NA ARMIE 2468 Konfiguracja PLL
// File Name: PLL.c
// Author: MACIEJ S�OCI�SKI
// Date: 13.04.2013

#include "LPC24xx.h"
#include "Type.h"
#include "PLL.h"

void PllInit ( void )
{
	DWORD MValue, NValue;

	if ( PLLSTAT & (1 << 25) ) /*Sprawdza czy PLL'ka jest zegarem rdzenia arm'a*/
	{
		PLLCON = (1<<0)|		/*W��cza PLL'ke*/
				 (0<<1);		/*Od��cza PLLk� od rdzenia arma, rdze� jest teraz*/
			 				/*taktowany bezpo�rednio wcze�niejszym �r�d�em PLLki*/
/*OD TERAZ RDZE� JEST TAKTOWANY ZEGAREM KT�RY BY� �R�D�EM DLA PLLki*/
		PLLFEED = 0xaa;			/*Procedura zabezpieczaj�ca*/
		PLLFEED = 0x55;			/*Procedura zabezpieczaj�ca*/
	}
	PLLCON = 0;					/*Wy��cza PLL'ke zupe�nie*/
	PLLFEED = 0xaa;				/*Procedura zabezpieczaj�ca*/
	PLLFEED = 0x55;				/*Procedura zabezpieczaj�ca*/

	SCS |= (1<<5);				/* W��czenie g��wnego oscylatora*/
	while( !(SCS & (1<<6)) );	/* Sprawdza czy main oscylator ju� si� rozp�dzi�*/

	CLKSRCSEL = 0x1;			/* Ustawia main oscylator jako �r�d�o PLL'ki */

  /*OD TERAZ RDZE� JEST TAKTOWANY G��WNYM OSCYLATOREM*/

  	MAMCR	=	0;							/*Wy��cza przyspieszenie pami�ci, je�li wy��czymy*/
  											/*obs�ug� MAM w czasie dzia�ania PLLki, arm si� zwiesi*/
    MAMTIM	=	0x4;						/*Ustawia odczyt z pami�ci flash na poziomie 4 cclk*/
    MAMCR	=	0x2;						/*W��cza pe�n� obs�ug� przyspieszenia pami�ci*/
											/*00->wy� 01->cz�ciowo w��cz. 10 - w��cz.*/
	PLLCFG = PLL_MValue | (PLL_NValue << 16); /*Warto��i PLL_MValue i N s� zdefiniowane*/
	PLLFEED = 0xaa;							/*w target.h, tu ustawiamy cz�stotliwo��:*/
	PLLFEED = 0x55;							/*Fcco = (2 � (M+1) � Fin) / (N+1), Fin=12MHz*/

	PLLCON = 1;								/*W��czamy PLL'k� */
	PLLFEED = 0xaa;							/*Procedura zabezpieczaj�ca*/
	PLLFEED = 0x55;							/*Procedura zabezpieczaj�ca*/
	CCLKCFG = CCLKDivValue;					/*Ustawiamy cz�stotliwo�� rdzenia */
											/*Fcclk=Fcco/(CCLKDivValue+1)*/
	USBCLKCFG = USBCLKDivValue;				/* usbclk = Fcco/USBCLKDivValue = 48 MHz */

	while ( ((PLLSTAT & (1 << 26)) == 0) ); /* Sprawdza czy PLLka si� ju� rozp�dzi�a */
											/* dopiero wtedy opu�cimy p�tl� */

	MValue = PLLSTAT & 0x00007FFF;			/* Odczytuje jakie warto�ci M i N s� ustalone*/
	NValue = (PLLSTAT & 0x00FF0000) >> 16;

/*Pu�apka je�li PLLka si� ustali�a jakim� cudem na inn� cz�stotliwo�� ni� ustawili�my*/
/*tzn s� inne warto�ci MValue i NValue, to wpadniemy w t� p�tl�*/
	while ((MValue != PLL_MValue) && ( NValue != PLL_NValue) );
	PLLCON = 3;				/* W��cza PLLk� i pod��cza j� jako �r�d�o dla rdzenia ARMa */
	PLLFEED = 0xaa;			/*Procedura zabezpieczaj�ca*/
	PLLFEED = 0x55;			/*Procedura zabezpieczaj�ca*/

/*OD TERAZ RDZE� JEST TAKTOWANY PLLk�! Gratuluj�*/
	while ( ((PLLSTAT & (1 << 25)) == 0) );	/* Sprawdza czy PLLka ju� jest zegarem rdzenia*/
}
