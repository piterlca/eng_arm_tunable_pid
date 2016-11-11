// Header: MIKROSKOP NA ARMIE 2468 Inicjalizacja UART
// File Name: UART1.h
// Author: MACIEJ S£OCIÑSKI
// Date: 22.03.2013

#ifndef __UART1_H 
#define __UART1_H

#include "LPC24xx.h"
#include "Type.h"

#define PCLK_UART1	(Fcclk/1) 		/*UWAGA wartoœæ PCLK_UART1 zale¿y od wartoœci rejestru*/
						 		 	/*PCLKSEL0 ustawianym w Uart.c w funkcji Uart1_init!!!*/
#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

#define BUFSIZE		0xF			/*Wielkoœæ buforu sprzêtowego*/

extern volatile BYTE bByteToSend;


/*Wysy³anie bajtu bez kontroli, czy bufor sprzêtowy (16 bajtowy) jest pusty*/
__inline void SendRawChar(BYTE bChar)
{
	U1THR=bChar;	
}

/*Sprawdzenie czy uart jest gotowy do wysy³ania danych. Jeœli tak, to funkcja zwraca 1*/
/*jeœli nie to CheckUartReady zwraca 0.*/
__inline BYTE CheckUartReady( void )
{
	return ((U1LSR & LSR_TEMT) && !bByteToSend);	
}

/*Wysy³anie jednego bajta z kontrol¹, jest to dosyæ powolna funkcja, jeœli ktoœ chcia³by*/
/*j¹ u¿ywaæ w pêtli. Raczej odradzam jej u¿ywanie poza aplikacjami testowymi/tymczasowymi.*/
void SendChar(BYTE bChar);

/*Wysy³a string zakoñczony zerem, program stoi w pêtli dopóki nie wyœle wszystkich znaków*/
/*z tablicy. W przypadku jakby ktoœ jako argument u¿y³ tablicê bez ¿adnego zera, program*/
/*bêdzie dzia³a³ niew³aœciwie i w sposób niekontrolowany! Raczej odradzam jej u¿ywanie */
/*poza aplikacjami testowymi/tymczasowymi.*/
void SendStrByte(BYTE *str);

/*Inicjalizuje UART'a, ustawia wszystkie rejestry, konfiguruje UART itd. Jako argument*/
/*przyjmuje szybkoœæ transmisji w bitach na sekundê.*/
DWORD Uart1Init(DWORD dBAUD);

/*Funkcja przerwania w której wnêtrzu nastêpuje zapis bajtów przychodz¹cych do bufforaIN*/
/*i wysy³anie bajtów z buforaOUT*/
void Inter_Uart(void) __irq;

/*Funkcja countFDR pobiera ulamek (fFract) opisujacy stosunek DIVVAL/MULVAL, bêd¹cy miar¹*/
/*rozbie¿noœci miêdzy prêdkoœci¹ transferu rzeczywist¹ i dan¹ jako docelow¹ (tzn zmienn¹ dBAUD).*/
/*A zwraca w odpowiednim formacie (gotowym do zapisu w rejestrze FDR) wartoœci MULVAL i DIVADVAL*/
/*gdzie: 1<=MULVAL<=15, a 0<=DIVADVAL<MULVAL*/
DWORD countFDR(float fFract);

/*Funkcje wykorzystywane tylko do debugowania i wyœwietlania tam czegoœ na terminalu*/
/*Radzê nie uzywaæ ich nigdzie w kodzie w³aœciwym, poniewa¿ s¹ dosyæ powolne i WYSY£AJ¥*/
/*LICZBY W KODZIE ASCII!*/
void SendByte(BYTE bNumber);
void SendSByte(SBYTE sbNumber);
void SendWord(WORD wNumber);
void SendSWord(SWORD sNumber);
void SendDWord(DWORD dNumber);
void SendSDWord(SDWORD sdNumber);

//Blokuj¹ce funkcje odczytywania i zapisywania do portu szeregowego
void SendData(BYTE* tab, int size);
void ReadData(BYTE* tab, int size);

//Nieblokuj¹ce funkcje odczytywania i zapisywania do portu szeregowego
void InitSendDataFree(BYTE* tab, int size);
void InitReadDataFree(BYTE* tab, int size);
int SendDataFree();
int ReadDataFree();
#endif 
