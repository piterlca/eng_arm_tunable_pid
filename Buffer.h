// Header: ARM bufor komunikacji
// File Name: Buffer.h
// Author: MACIEJ S£OCIÑSKI
// Date: 1.09.2013

#ifndef __BUFFER_H
#define __BUFFER_H

#include "Type.h"

/*FUNKCJE S£U¯¥CE DO OBS£UGI BUFORU WYSY£AJ¥CEGO DANE Z ARM'A PO UARC'IE*/

/*Funkcja ReadBufferOut s³u¿y do odczytywania z buforu bajtów tu¿ przed ich wy³aniem po UARTcie i*/
/*powinna byæ wywo³ywana tylko w przerwaniu od UART'a.*/
BYTE ReadBufferOut(void);


/*Funkcja WriteBufferOut s³u¿y do zapisywania do buforu bajtów, które chcemy wys³aæ po uarcie,*/
/*zalecane jest wykorzystywanie jej zamiast funkcji SendChar itp. UWAGA przed wywo³aniem tej*/
/*funkcji radzi³bym sprawdziæ, czy w buforze jest miejsce na kolejny bajt! (ByteInBufferOut)*/
/*W chwili obecnej, gdy wysy³amy bajty w przerwaniu, to pos³uguj¹c siê t¹ funkcj¹ samemu trzeba */
/*zadbaæ, by bufor siê oczyœci³. (przerwanie siê uruchamia tylko je¿eli wczeœniej by³y */
/*conajmniej 3 znaki w kolejce fifo). Wygodny zamiennik sam dbaj¹cy o powy¿sze warunki to*/
/* funkcja WriteBufferNOut.*/
void WriteBufferOut(BYTE bData);

/*Funkcja WriteBufferNOut s³u¿y do zapisywania do buforu bajtów, które chcemy wys³aæ po uarcie,*/
/*zalecane jest wykorzystywanie jej zamiast funkcji SendChar itp., przyjmuje*/
void WriteBufferNOut(BYTE* bData, BYTE bLength);

/*Funkcja ByteInBufferIn s³u¿y do sprawdzania ile bajtów czeka w buforze na wys³anie. W przypadku*/
/*gdy, jest ich 255, nie nale¿y u¿ywaæ funkcji WriteBufferOut, poniewa¿ nie ma wtedy miejsca w*/
/*w buforze na kolejny znak.*/
BYTE ByteInBufferOut(void);



/*FUNKCJE S£U¯¥CE DO OBS£UGI BUFORU ODCZYTUJ¥CEGO DANE PRZYCHODZ¥CE DO ARM'A PO UARC'IE*/

/*Funkcja ReadBufferIn s³u¿y do odczytywania z buforu przychodz¹cych po UARTcie bajtów.*/
BYTE ReadBufferIn(void);

/*Funkcja WriteBufferIn s³u¿y do zapisywania w przerwaniu przychodz¹cych po UARTcie bajtów*/
/*nie zalecane jest u¿ywanie jej w jakimkolwiek innym miejscu, poza ewentualnymi testami.*/
void WriteBufferIn(BYTE bData);

/*Funkcja ByteInBufferIn s³u¿y do sprawdzania ile bajtów mo¿na odczytaæ z bufora i mo¿na*/
/*ni¹ sprawdzaæ, czy przysz³y jakieœ rozkazy w pêtlach z timerami.*/
BYTE ByteInBufferIn(void);

#endif
