// Header: UART
// File Name:  UART.h
// Author: Pawe³ Biczysko
// Date: 13.08.2013r.


#ifndef UART_h
#define UART_h 
#define TBUF_SIZE   256	     
#define RBUF_SIZE   256     
#define SIZE 100


void UART_init (void);
char get_char (void);
char put_char (char c);
void put_string (char* tablica);
void get_string (char* tab);
void com_baudrate (unsigned int baudrate);
//int putchar();
//int _getkey (void); 
#endif 
