// Header: ARM bufor komunikacji
// File Name: Buffer.c
// Author: MACIEJ S£OCIÑSKI
// Date: 1.09.2013

#include "LPC24xx.h"
#include "Type.h"
#include "UART1.h"
#include "Buffer.h"

static volatile BYTE abBuffIn[256];
static volatile BYTE bWrIn=0;
static volatile BYTE bRdIn=0;

static volatile BYTE abBuffOut[256];
static volatile BYTE bWrOut=0;
static volatile BYTE bRdOut=0;


/*FUNKCJE S£U¯¥CE DO OBS£UGI BUFORU WYSY£AJ¥CEGO DANE Z ARM'A PO UARC'IE*/

/*Funkcja ReadBufferOut s³u¿y do odczytywania z buforu bajtów tu¿ przed ich wy³aniem po UARTcie i*/
/*powinna byæ wywo³ywana tylko w przerwaniu od UART'a.*/
BYTE ReadBufferOut(void)
{
	return (bWrOut != bRdOut )? abBuffOut[++bRdOut] : 0; 
}

/*Funkcja WriteBufferOut s³u¿y do zapisywania do buforu bajtów, które chcemy wys³aæ po uarcie,*/
/*zalecane jest wykorzystywanie jej zamiast funkcji SendChar itp.*/
void WriteBufferOut(BYTE bData)
{
	if( (BYTE)(bWrOut+1) != bRdOut ) abBuffOut[++bWrOut]=bData;
}

/*Funkcja WriteBufferNOut s³u¿y do zapisywania do buforu bajtów, które chcemy wys³aæ po uarcie,*/
/*zalecane jest wykorzystywanie jej zamiast funkcji SendNChar itp. Jeœli uart jest gotowy (tzn. */
/*nie ma ¿adnych danych w 16 bajtowym buforze sprzêtowym i w ostatnim przerwaniu od nadawczego*/
/*pustego bufora sprzêtowego nie zosta³ wys³any ¿adny bajt) funkcja wysy³a dane od razu, najpierw*/
/*wysy³aj¹c ewentualnie bajty z bufora abBuffOut, a nastêpnie z tablicy bData. W ten sposób jest*/
/*spe³niany warunek przerwania od pustego sprzêtowego bufora nadawczego (tzn. conajmniej 2 bajty*/
/*zapisane w kolejce bufora U1THR). Nie wys³ane od razu bajty z tablicy bData, s¹ zapisywane do*/
/*buforu abBuffOut z którego zostan¹ odczytane i wys³ane w przerwaniu.*/
void WriteBufferNOut(BYTE* bData, BYTE bLength)	/*bLength -iloœæ bajtów do wys³ania z tablicy bData*/
{
	BYTE k=0x0F;											/*iloœæ bajtów w buforze sprzêtowym*/
	if( CheckUartReady() )	  /*CheckUartReady to funkcja inline testuj¹ca, czy uart jest gotowy*/
	{
		/*Dopóki jest miejsce w buforze sprzêtowym i dopóki w buforze abBuffOut s¹ bajty, wysy³aj*/
		/*bajty z bufora abBuffOut.*/
		while( --k && (bWrOut!=bRdOut) ) SendRawChar( abBuffOut[++bRdOut] );
		/*Dopóki jest miejsce w buforze sprzêtowym i dopóki w tablicy bData s¹ bajty, wysy³aj*/
		/*bajty z tablicy bData.*/
		
		while( k-- && bLength )
		{
			SendRawChar( *bData );
			++bData; --bLength;
		}
	}
	while( bLength-- )						/*Dopóki s¹ nieodczytane bajty w tablicy bData...*/
	{
		while( (BYTE)(bWrOut+1)==bRdOut );	/*czekaj a¿ bêdzie dosyæ miejsca w buforze abBuffOut...*/
		abBuffOut[++bWrOut]= *bData++;		/*i zapisuj bajty z bData do buforu abBuffOut.*/
	}	
}

/*Funkcja ByteInBufferIn s³u¿y do sprawdzania ile bajtów czeka w buforze na wys³anie. W przypadku*/
/*gdy, jest ich 255, nie nale¿y u¿ywaæ funkcji WriteBufferOut, poniewa¿ nie ma wtedy miejsca w*/
/*w buforze na kolejny znak.*/
BYTE ByteInBufferOut(void)
{
	return bWrOut-bRdOut;
}

/*FUNKCJE S£U¯¥CE DO OBS£UGI BUFORU ODCZYTUJ¥CEGO DANE PRZYCHODZ¥CE DO ARM'A PO UARC'IE*/

/*Funkcja ReadBufferIn s³u¿y do odczytywania z buforu przychodz¹cych po UARTcie bajtów.*/
BYTE ReadBufferIn(void)
{
	return (bWrIn != bRdIn )? abBuffIn[++bRdIn] : 0; 
}

/*Funkcja WriteBufferIn s³u¿y do zapisywania w przerwaniu przychodz¹cych po UARTcie bajtów*/
/*nie zalecane jest u¿ywanie jej w jakimkolwiek innym miejscu, poza ewentualnymi testami*/
/*dekodowania rozkazów i samej komunikacji.*/
void WriteBufferIn(BYTE bData)
{
	if((BYTE)(bWrIn+1) != bRdIn ) abBuffIn[++bWrIn]=bData;
}

/*Funkcja ByteInBufferIn s³u¿y do sprawdzania ile bajtów mo¿na odczytaæ z bufora i mo¿na*/
/*ni¹ sprawdzaæ, czy przysz³y jakieœ rozkazy w pêtlach z timerami.*/
BYTE ByteInBufferIn(void)
{
	return bWrIn-bRdIn;
}

