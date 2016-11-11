// Header: ARM bufor komunikacji
// File Name: Buffer.c
// Author: MACIEJ S�OCI�SKI
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


/*FUNKCJE S�U��CE DO OBS�UGI BUFORU WYSY�AJ�CEGO DANE Z ARM'A PO UARC'IE*/

/*Funkcja ReadBufferOut s�u�y do odczytywania z buforu bajt�w tu� przed ich wy�aniem po UARTcie i*/
/*powinna by� wywo�ywana tylko w przerwaniu od UART'a.*/
BYTE ReadBufferOut(void)
{
	return (bWrOut != bRdOut )? abBuffOut[++bRdOut] : 0; 
}

/*Funkcja WriteBufferOut s�u�y do zapisywania do buforu bajt�w, kt�re chcemy wys�a� po uarcie,*/
/*zalecane jest wykorzystywanie jej zamiast funkcji SendChar itp.*/
void WriteBufferOut(BYTE bData)
{
	if( (BYTE)(bWrOut+1) != bRdOut ) abBuffOut[++bWrOut]=bData;
}

/*Funkcja WriteBufferNOut s�u�y do zapisywania do buforu bajt�w, kt�re chcemy wys�a� po uarcie,*/
/*zalecane jest wykorzystywanie jej zamiast funkcji SendNChar itp. Je�li uart jest gotowy (tzn. */
/*nie ma �adnych danych w 16 bajtowym buforze sprz�towym i w ostatnim przerwaniu od nadawczego*/
/*pustego bufora sprz�towego nie zosta� wys�any �adny bajt) funkcja wysy�a dane od razu, najpierw*/
/*wysy�aj�c ewentualnie bajty z bufora abBuffOut, a nast�pnie z tablicy bData. W ten spos�b jest*/
/*spe�niany warunek przerwania od pustego sprz�towego bufora nadawczego (tzn. conajmniej 2 bajty*/
/*zapisane w kolejce bufora U1THR). Nie wys�ane od razu bajty z tablicy bData, s� zapisywane do*/
/*buforu abBuffOut z kt�rego zostan� odczytane i wys�ane w przerwaniu.*/
void WriteBufferNOut(BYTE* bData, BYTE bLength)	/*bLength -ilo�� bajt�w do wys�ania z tablicy bData*/
{
	BYTE k=0x0F;											/*ilo�� bajt�w w buforze sprz�towym*/
	if( CheckUartReady() )	  /*CheckUartReady to funkcja inline testuj�ca, czy uart jest gotowy*/
	{
		/*Dop�ki jest miejsce w buforze sprz�towym i dop�ki w buforze abBuffOut s� bajty, wysy�aj*/
		/*bajty z bufora abBuffOut.*/
		while( --k && (bWrOut!=bRdOut) ) SendRawChar( abBuffOut[++bRdOut] );
		/*Dop�ki jest miejsce w buforze sprz�towym i dop�ki w tablicy bData s� bajty, wysy�aj*/
		/*bajty z tablicy bData.*/
		
		while( k-- && bLength )
		{
			SendRawChar( *bData );
			++bData; --bLength;
		}
	}
	while( bLength-- )						/*Dop�ki s� nieodczytane bajty w tablicy bData...*/
	{
		while( (BYTE)(bWrOut+1)==bRdOut );	/*czekaj a� b�dzie dosy� miejsca w buforze abBuffOut...*/
		abBuffOut[++bWrOut]= *bData++;		/*i zapisuj bajty z bData do buforu abBuffOut.*/
	}	
}

/*Funkcja ByteInBufferIn s�u�y do sprawdzania ile bajt�w czeka w buforze na wys�anie. W przypadku*/
/*gdy, jest ich 255, nie nale�y u�ywa� funkcji WriteBufferOut, poniewa� nie ma wtedy miejsca w*/
/*w buforze na kolejny znak.*/
BYTE ByteInBufferOut(void)
{
	return bWrOut-bRdOut;
}

/*FUNKCJE S�U��CE DO OBS�UGI BUFORU ODCZYTUJ�CEGO DANE PRZYCHODZ�CE DO ARM'A PO UARC'IE*/

/*Funkcja ReadBufferIn s�u�y do odczytywania z buforu przychodz�cych po UARTcie bajt�w.*/
BYTE ReadBufferIn(void)
{
	return (bWrIn != bRdIn )? abBuffIn[++bRdIn] : 0; 
}

/*Funkcja WriteBufferIn s�u�y do zapisywania w przerwaniu przychodz�cych po UARTcie bajt�w*/
/*nie zalecane jest u�ywanie jej w jakimkolwiek innym miejscu, poza ewentualnymi testami*/
/*dekodowania rozkaz�w i samej komunikacji.*/
void WriteBufferIn(BYTE bData)
{
	if((BYTE)(bWrIn+1) != bRdIn ) abBuffIn[++bWrIn]=bData;
}

/*Funkcja ByteInBufferIn s�u�y do sprawdzania ile bajt�w mo�na odczyta� z bufora i mo�na*/
/*ni� sprawdza�, czy przysz�y jakie� rozkazy w p�tlach z timerami.*/
BYTE ByteInBufferIn(void)
{
	return bWrIn-bRdIn;
}

