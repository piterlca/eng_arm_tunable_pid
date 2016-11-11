// Header: ARM bufor komunikacji
// File Name: Buffer.h
// Author: MACIEJ S�OCI�SKI
// Date: 1.09.2013

#ifndef __BUFFER_H
#define __BUFFER_H

#include "Type.h"

/*FUNKCJE S�U��CE DO OBS�UGI BUFORU WYSY�AJ�CEGO DANE Z ARM'A PO UARC'IE*/

/*Funkcja ReadBufferOut s�u�y do odczytywania z buforu bajt�w tu� przed ich wy�aniem po UARTcie i*/
/*powinna by� wywo�ywana tylko w przerwaniu od UART'a.*/
BYTE ReadBufferOut(void);


/*Funkcja WriteBufferOut s�u�y do zapisywania do buforu bajt�w, kt�re chcemy wys�a� po uarcie,*/
/*zalecane jest wykorzystywanie jej zamiast funkcji SendChar itp. UWAGA przed wywo�aniem tej*/
/*funkcji radzi�bym sprawdzi�, czy w buforze jest miejsce na kolejny bajt! (ByteInBufferOut)*/
/*W chwili obecnej, gdy wysy�amy bajty w przerwaniu, to pos�uguj�c si� t� funkcj� samemu trzeba */
/*zadba�, by bufor si� oczy�ci�. (przerwanie si� uruchamia tylko je�eli wcze�niej by�y */
/*conajmniej 3 znaki w kolejce fifo). Wygodny zamiennik sam dbaj�cy o powy�sze warunki to*/
/* funkcja WriteBufferNOut.*/
void WriteBufferOut(BYTE bData);

/*Funkcja WriteBufferNOut s�u�y do zapisywania do buforu bajt�w, kt�re chcemy wys�a� po uarcie,*/
/*zalecane jest wykorzystywanie jej zamiast funkcji SendChar itp., przyjmuje*/
void WriteBufferNOut(BYTE* bData, BYTE bLength);

/*Funkcja ByteInBufferIn s�u�y do sprawdzania ile bajt�w czeka w buforze na wys�anie. W przypadku*/
/*gdy, jest ich 255, nie nale�y u�ywa� funkcji WriteBufferOut, poniewa� nie ma wtedy miejsca w*/
/*w buforze na kolejny znak.*/
BYTE ByteInBufferOut(void);



/*FUNKCJE S�U��CE DO OBS�UGI BUFORU ODCZYTUJ�CEGO DANE PRZYCHODZ�CE DO ARM'A PO UARC'IE*/

/*Funkcja ReadBufferIn s�u�y do odczytywania z buforu przychodz�cych po UARTcie bajt�w.*/
BYTE ReadBufferIn(void);

/*Funkcja WriteBufferIn s�u�y do zapisywania w przerwaniu przychodz�cych po UARTcie bajt�w*/
/*nie zalecane jest u�ywanie jej w jakimkolwiek innym miejscu, poza ewentualnymi testami.*/
void WriteBufferIn(BYTE bData);

/*Funkcja ByteInBufferIn s�u�y do sprawdzania ile bajt�w mo�na odczyta� z bufora i mo�na*/
/*ni� sprawdza�, czy przysz�y jakie� rozkazy w p�tlach z timerami.*/
BYTE ByteInBufferIn(void);

#endif
