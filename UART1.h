// Header: MIKROSKOP NA ARMIE 2468 Inicjalizacja UART
// File Name: UART1.h
// Author: MACIEJ S�OCI�SKI
// Date: 22.03.2013

#ifndef __UART1_H 
#define __UART1_H

#include "LPC24xx.h"
#include "Type.h"

#define PCLK_UART1	(Fcclk/1) 		/*UWAGA warto�� PCLK_UART1 zale�y od warto�ci rejestru*/
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

#define BUFSIZE		0xF			/*Wielko�� buforu sprz�towego*/

extern volatile BYTE bByteToSend;


/*Wysy�anie bajtu bez kontroli, czy bufor sprz�towy (16 bajtowy) jest pusty*/
__inline void SendRawChar(BYTE bChar)
{
	U1THR=bChar;	
}

/*Sprawdzenie czy uart jest gotowy do wysy�ania danych. Je�li tak, to funkcja zwraca 1*/
/*je�li nie to CheckUartReady zwraca 0.*/
__inline BYTE CheckUartReady( void )
{
	return ((U1LSR & LSR_TEMT) && !bByteToSend);	
}

/*Wysy�anie jednego bajta z kontrol�, jest to dosy� powolna funkcja, je�li kto� chcia�by*/
/*j� u�ywa� w p�tli. Raczej odradzam jej u�ywanie poza aplikacjami testowymi/tymczasowymi.*/
void SendChar(BYTE bChar);

/*Wysy�a string zako�czony zerem, program stoi w p�tli dop�ki nie wy�le wszystkich znak�w*/
/*z tablicy. W przypadku jakby kto� jako argument u�y� tablic� bez �adnego zera, program*/
/*b�dzie dzia�a� niew�a�ciwie i w spos�b niekontrolowany! Raczej odradzam jej u�ywanie */
/*poza aplikacjami testowymi/tymczasowymi.*/
void SendStrByte(BYTE *str);

/*Inicjalizuje UART'a, ustawia wszystkie rejestry, konfiguruje UART itd. Jako argument*/
/*przyjmuje szybko�� transmisji w bitach na sekund�.*/
DWORD Uart1Init(DWORD dBAUD);

/*Funkcja przerwania w kt�rej wn�trzu nast�puje zapis bajt�w przychodz�cych do bufforaIN*/
/*i wysy�anie bajt�w z buforaOUT*/
void Inter_Uart(void) __irq;

/*Funkcja countFDR pobiera ulamek (fFract) opisujacy stosunek DIVVAL/MULVAL, b�d�cy miar�*/
/*rozbie�no�ci mi�dzy pr�dko�ci� transferu rzeczywist� i dan� jako docelow� (tzn zmienn� dBAUD).*/
/*A zwraca w odpowiednim formacie (gotowym do zapisu w rejestrze FDR) warto�ci MULVAL i DIVADVAL*/
/*gdzie: 1<=MULVAL<=15, a 0<=DIVADVAL<MULVAL*/
DWORD countFDR(float fFract);

/*Funkcje wykorzystywane tylko do debugowania i wy�wietlania tam czego� na terminalu*/
/*Radz� nie uzywa� ich nigdzie w kodzie w�a�ciwym, poniewa� s� dosy� powolne i WYSY�AJ�*/
/*LICZBY W KODZIE ASCII!*/
void SendByte(BYTE bNumber);
void SendSByte(SBYTE sbNumber);
void SendWord(WORD wNumber);
void SendSWord(SWORD sNumber);
void SendDWord(DWORD dNumber);
void SendSDWord(SDWORD sdNumber);

//Blokuj�ce funkcje odczytywania i zapisywania do portu szeregowego
void SendData(BYTE* tab, int size);
void ReadData(BYTE* tab, int size);

//Nieblokuj�ce funkcje odczytywania i zapisywania do portu szeregowego
void InitSendDataFree(BYTE* tab, int size);
void InitReadDataFree(BYTE* tab, int size);
int SendDataFree();
int ReadDataFree();
#endif 
