// Header: MIKROSKOP NA ARMIE 2468 Inicjalizacja UART
// File Name: UART1.c
// Author: MACIEJ S£OCIÑSKI, MODYFIKACJA PAWE£ BICZYSKO
// Date: 10.11.2013

#include "LPC24xx.h"
#include "Type.h"
#include "IRQ.h"
#include "PID.h"
#include "PLL.h"
#include "UART1.h"
#include "Buffer.h"
#include "sbuffer.h"
volatile SBUFFER UART_BUF_IN;
volatile SBUFFER UART_BUF_OUT;
#define UART_BUF_SIZE 512
volatile BYTE _UART_BUF_IN[UART_BUF_SIZE];
volatile BYTE _UART_BUF_OUT[UART_BUF_SIZE];
volatile BOOL boUartInterNext=0;
volatile BYTE bErrorAbort;
volatile BYTE bByteToSend=0;
volatile BYTE Buff[9]={0,0,0,0,0,0,0,0,0}; 
volatile int x=0;
volatile unsigned char index=0;
WORD kp1,ki1,kd1=0;
extern WORD kp,kd,ki;
volatile int numb=0;

//-------------------------- UART_PID

/*Funkcja komunikacyjna regulatora z aplikacj¹ steruj¹c¹ napisan¹ w LABVIEW*/
/*Funkcja ta wywo³ywana jest w przerwaniu od odbioru znaku przez interfej UART*/
/*
Schemat dzialania:
wysylane jest polecenie z aplikacji:                                  
[0xAA, 0x01, bajt polecenia, polecenie]      -> arm odsyla cala ramke jaka
												odebral, dokladnie bajt po bajcie

Aplikacja odsy³a komendê ¿e, dane zosta³y
poprawnie odes³ane:     
[0xAA, 0x02, bajt polecenia]                  -> arm odsyla cala ramke jaka odebral 
                                                 i przygotowuje sie do realizacji polecenia, 
                                                 po tym jak jest gotowy to staje i czeka na              
                                                [0xAA, 0x03] - polecenie startu  */
void UART_PID ()
{
	switch (Buff[2])
		{
			case 1:
				switch (Buff[1])
				{
					case 1:
					if(index==9)
					{
			 			kp1=Buff[3]<<8;
						kp1+=Buff[4];
						kd1=Buff[5]<<8;
						kd1+=Buff[6];
						ki1=Buff[7]<<8;
						ki1+=Buff[8];
						WriteBufferNOut (Buff,9);
						index=0;
						Buff[1]=Buff[2]=0;
					}
					break;
					case 2:
						WriteBufferNOut (Buff,3);
						index=0;
						Buff[1]=Buff[2]=0;
					break;
					case 3:
						kp=kp1;
						kd=kd1;
						ki=ki1;
						//Init();
						index=0;
						Buff[1]=Buff[2]=0;
					break;
				}
			break;
			case 2:
				switch (Buff[1])
				{
					case 1:
						WriteBufferNOut (Buff,3);
						index=0;
						Buff[1]=Buff[2]=0;
					break;
 					case 2:
						WriteBufferNOut (Buff,3);
						index=0;
						Buff[1]=Buff[2]=0;
					break;
					case 3:
						Buff[0]=kp1>>8;
						Buff[1]=kp1;
						Buff[2]=kd1>>8;
						Buff[3]=kd1;
						Buff[4]=ki1>>8;
						Buff[5]=ki1;
						WriteBufferNOut (Buff,6);
						index=0;
						Buff[1]=Buff[2]=0;
					break;
				}
			break;

		}
}		



void SendChar(BYTE bChar)
{
	while(!(U1LSR & LSR_TEMT));
		U1THR=bChar; 
}

void SendStrByte(BYTE *str)
{
	WORD uiCount=0x0;
	while(!(U1LSR & LSR_TEMT));
	while(*str)
	{
		if ( (uiCount>=BUFSIZE) )
		{
			while(!(U1LSR & LSR_TEMT));
			uiCount=0x0;
		}
		uiCount++;
		U1THR=(*str++);	
	}	
}

void Inter_Uart(void) __irq
{
	BYTE bIIRValue, bLSRValue;
	BYTE bData=0;
	int cnt=0;
	int i;
	BYTE data[BUFSIZE];
	bIIRValue = U1IIR;
	bIIRValue >>= 1;		/*W 1wszy bit =1 gdy inne przerwanie ni¿ od Uart chce siê wykonaæ*/
	bIIRValue &= 0x07;	/*W trzech ostatnich bitach jest opisana przyczyna przerwania*/
  	if ( bIIRValue == IIR_RLS )			 /*B³¹d w transmisji by³ przyczyn¹ przerwania*/
  	{									
		bLSRValue = U1LSR;	  			    /*Informacja o rodzaju b³edu jest w U1LSR*/
		if ( bLSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) ) 	  /*mo¿liwe b³êdy*/
		{
			bData=U1RBR;	 						/*Odczyt U1RBR czyœci przerwanie */
	  		bErrorAbort=bLSRValue & (0x3 | bData);	/*ale musimy skorzystaæ bDaty*/	
		}
		if ( bLSRValue & LSR_RDR ) 			/*Dla przypadku gdy przerwanie RDA jest*/
		{									/*co kilka znaków i wyst¹pi b³¹d - mo¿na*/
			//WriteBufferIn(U1RBR);			/*odczytaæ z kolejki FIFO wczeœniej popra-*/
		}									/*wnie przes³ane bajty. LSR_RDR=1 gdy jakieœ*/
	}										/*poprawne bajty s¹ w kolejce FIFO.*/
	else if ( bIIRValue == IIR_RDA )			/*Znaki w kolejce odbiorczej FIFO by³y przyczyn¹ przerwania*/
  	{
//		//WriteBufferIn(U1RBR);
//		Buff[index] = U1RBR;
//		index++;
//		UART_PID();

		data[0]=U1RBR;
		put_sbuffer(&UART_BUF_IN,data[0]);		
  	}	
	else if ( bIIRValue == IIR_THRE )		/* Dane zosta³y wys³ane, pusty rejestr THR*/
  	{
//		while(!(U1LSR & LSR_TEMT));
//		bData=ByteInBufferOut();
//		bByteToSend=(bData / BUFSIZE)? BUFSIZE : bData%BUFSIZE ;
//		bData=0;
//		while(bData<bByteToSend)
//		{
//			U1THR=ReadBufferOut();
//			bData++;
//		}
		cnt=read_sbuffer(&UART_BUF_OUT,data,BUFSIZE);
		numb+=cnt;
		if(cnt<3)
			boUartInterNext=FALSE;
		for(i=0;i<cnt;i++)
			U1THR=data[i];
	}
  	VICVectAddr = 0;
}

/*Funkcja countFDR pobiera ulamek (fFract) opisujacy stosunek DIVVAL/MULVAL, bêd¹cy miar¹*/
/*rozbie¿noœci miêdzy prêdkoœci¹ transferu rzeczywist¹ i dan¹ jako docelow¹ (tzn zmienn¹ dBAUD).*/
/*A zwraca w odpowiednim formacie (gotowym do zapisu w rejestrze FDR) wartoœci MULVAL i DIVADVAL*/
/*gdzie: 1<=MULVAL<=15, a 0<=DIVADVAL<MULVAL*/
DWORD countFDR(float fFract)
{
	DWORD dValueEnd, dDiv, dMult;
	SDWORD sdValue;
	DWORD dFract=(DWORD)(fFract*10000);
	DWORD dLastDiv=0;
	DWORD dLastMult=1;

	dValueEnd=10000;
	for (dMult=1;dMult<=15;dMult++)
	{
		for (dDiv=0 ; dDiv<dMult ; dDiv++)
		{
			sdValue=dFract-(dDiv*10000)/dMult;
			if (sdValue<0) sdValue=sdValue*(-1);
			if (sdValue<=dValueEnd)
			{
				dLastDiv=dDiv;
				dLastMult=dMult;
				dValueEnd=sdValue;
			}	
		}
	}
	return ((dLastDiv)+((dLastMult)<<4) & 0xFF);
}


DWORD Uart1Init(DWORD dBAUD)
{

	DWORD dBAUD_REAL;
	UART_BUF_OUT=create_sbuffer(_UART_BUF_OUT,UART_BUF_SIZE);
	UART_BUF_IN=create_sbuffer(_UART_BUF_IN,UART_BUF_SIZE);
	PCONP	|=	(0x1<<4);							/* W³¹czenie zasilania UART1 */
	PCLKSEL0 =	(PCLKSEL0 & (0xFFFFFFFF^(0x3<<8)))|	/* UWAGA PCLK_UART1=CCLK/n,*/
				(0x1<<8);							/* 01->n=1;10->n=2;11->n=8;00->n=4*/													
													/* w razie zmiany n tzeba zmieniæ*/
													/* wartoœæ PCLK_UART1 w uart1.h!!*/
	PINSEL0  =	(PINSEL0 & (0x3FFFFFFF))|			/* TxD1 P0.15 */
				(0x1<<30);
	PINSEL1  =	(PINSEL1 & (0x00003FFF))|			/* Zerowanie pierwszych 14 bitów*/		
				(0x1<<0)|							/* RxD1 P0.16 */
				(0x1<<2)|							/* CTS1 P0.17 */
				(0x1<<4)|							/* DCD1 P0.18 */
				(0x1<<6)|							/* DSR1 P0.19 */
				(0x1<<8)|							/* DTR1 P0.20 */
				(0x1<<10)|							/*  RI1 P0.21 */
				(0x1<<12);							/* RTS1 P0.22 */

	PINMODE0 =	(PINMODE0 & (0x3FFFFFFF))|			/* zarz¹dza rezystorem na pinie*/
				(0x0<<30);							/* TxD1 P0.15 - mo¿liwe: 00, 10, 11*/
	PINMODE1 =	(PINMODE1 & (0xFFFFFFFF^0x3))|		/* zarz¹dza rezystorem na pinie*/
				(0x0<<0)|							/* RxD1 P0.16 */
				(0x0<<2)|							/* CTS1 P0.17 */
				(0x0<<4)|							/* DCD1 P0.18 */
				(0x0<<6)|							/* DSR1 P0.19 */
				(0x0<<8)|							/* DTR1 P0.20 */
				(0x0<<10)|							/*  RI1 P0.21 */
				(0x0<<12);							/* RTS1 P0.22 */
	U1LCR	 =	(0x3)|								/* D³ugoœæ znaku w bitach: */
													/* 00->5b; 01->6b; 10->7b; 11->8b*/
				(0x0 <<2)|							/* Ile bitów na stop: 0->1b, 1->2b*/
				(0x0 <<3)|							/* Sprawdz. parzystoœci: 0-wy³, 1-w³*/
				(0x0 <<4)|							/* Rodzaj parzystoœæi czytaj USM.*/
				(0x0 <<6)|							/* Zerwij polaczenie 0->Nie, 1->Tak*/
				(0x1 <<7);							/* DLAB zezwól na zmianê dzielnika:1*/
													/* Pozwala modyfikowaæ rejestry DLL,*/
													/* DLM, FDR przy wartoœci; wartoœæ 0*/
													/* pozwala korzystaæ z rejestrów RBR*/
													/* i THR*/

	U1DLL	 =	((BYTE) (( PCLK_UART1/16/dBAUD)%256));	/*Dzielnik ustalaj¹cy prêdkoœæ rze-*/
														/* wistej transmisji danych*/
	U1DLM	 =	((BYTE) (( PCLK_UART1/16/dBAUD)/256));	/*Dzielnik ustalaj¹cy prêdkoœæ rze-*/
														/* wistej transmisji danych*/

	/*Obliczanie rzeczywistej prêdkoœci transferu w oparciu o U1DLL i U1DLM:*/
	/*dBAUD_REAL1=Fpclk/( 16x( 256xU1DLM+U1DLL ))*/

	dBAUD_REAL=PCLK_UART1/( 16*( 256*((( PCLK_UART1/16/dBAUD)/256)) + (( PCLK_UART1/16/dBAUD)%256) ));

	/*Jeœli rozbie¿noœæ miêdzy rzeczywist¹ i zadan¹ prêdkoœci¹ transferu przekracza 0.5%*/
	/*modyfikujemy rejestr U1FDR, który posiada w sobie DIVADVAL (0-3bit) i MULVAL (4-7bit)*/
	/*wtedy prêdkoœæ transmisji opisuje wzór:*/ 
	/*dBAUD_REAL=Fpclk/( 16x( 256xU1DLM+U1DLL )x(1+DIVVAL/MULVAL) )*/
	/*ogólnie mo¿na zrobiæ poni¿szy kod bez u¿ywania typu float mno¿¹c wszystko przez 10^4*/
	/*ale taki kod z rzutowaniem na float jest bardziej czytelny i mniej awaryjny :( */

	if ( (((float)((dBAUD_REAL)-(dBAUD))) / ((float)dBAUD))*100 > 0.5 )	
	{
		/*Funkcja countFDR pobiera ulamek opisujacy stosunek rozbie¿noœci miêdzy prêdkoœci¹*/
		/*transferu rzeczywist¹ i dan¹ jako docelow¹ (tzn zmienn¹ dBAUD). A zwraca w odpo-*/
		/*wiednim formacie (gotowym do zapisu w rejestrze FDR) wartoœci MULVAL i DIVADVAL*/
		/*gdzie: 1<=MULVAL<=15, a 0<=DIVADVAL<MULVAL*/

		U1FDR=countFDR( ((float)((dBAUD_REAL)-(dBAUD))) / ((float)dBAUD) );

		/*Obliczamy ile wynosi rzeczywisty dBAUD_REAL:*/
		dBAUD_REAL=(dBAUD_REAL)/(1.+ ( (float)(U1FDR&0xF)) / ((float)((U1FDR&0xF0)>>4)));
	}

	U1LCR	 =	0x03;									/*DLAB zabroñ zmiany dzielnika: 0*/
	U1FCR	 =	(0x1 <<0)|								/*W³¹cza bufor UARTa*/
				(0x1 <<1)|								/*Czyœci bufor (samoczyszcz) odczytu*/
				(0x1 <<2)|								/*Czyœci bufor (samoczyszcz) zapisu*/
				(0x0 <<6);								/*Co ile znaków generuje przerwanie:*/
														/*00->1, 01->4, 10->8, 11->14*/

	U1MCR	 =	(0x1 <<0)|								/*W³¹cza kontrolê DTR*/
				(0x1 <<1)|								/*W³¹cza kontrolê RTS*/
				(0x0 <<4)|								/*Pêtla zwrotna do testowania- zwarcie RxD i TxD*/
				(0x1 <<6)|								/*Automatyczna kontrola RTS */
				(0x1 <<7);								/*Automatyczna kontrola CTS */
	
	if ( install_irq( UART1_INT, (void *)Inter_Uart, 0x6 ) == FALSE )
    {
	  return (FALSE);
    }

	U1IER	 =	(0x1 <<0)|					/*On(1)/Off(0) przerwania od RDR - odebrany znak RBR*/
				(0x1 <<1)|					/* -||- THRE - tzn rejestr wysy³aj¹cy THR jest pusty*/
				(0x1 <<2)|					/*-||- RX status - b³êdy:  OE, PE, FE, BI, RXFE */
				(0x0 <<3)|					/*-||- modem status*/
				(0x0 <<7)|					/*-||- CTS - mo¿liwe wys³anie bajtu do modemu*/
				(0x0 <<8)|					/*-||- end of auto-baud*/
				(0x0 <<9);					/*-||- auto-baud time-out*/
	
	return dBAUD_REAL;
}

void SendByte(BYTE bNumber)
{
	int k;
	for(k=100; k>=1; k/=10)
	{
		SendChar( (bNumber/k)+'0' );
		bNumber-=(bNumber/k)*k;
	}	
}

void SendSByte(SBYTE sbNumber)
{										 
	if(sbNumber<0)
	{
		SendChar('-');
		sbNumber=sbNumber*(-1);
	}
	else
	{
		SendChar('+'); 
	}
	SendByte( sbNumber ); 	
}

void SendWord(WORD wNumber)
{
	DWORD k;
	for(k=10000; k>=1; k/=10)
	{
		SendChar( (wNumber/k)+'0' );
		wNumber-=(wNumber/k)*k;
	} 	
}

void SendSWord(SWORD swNumber)
{										 
	if(swNumber<0)
	{
		SendChar('-');
		swNumber=swNumber*(-1);
	}
	else
	{
		SendChar('+'); 
	}
	SendWord( swNumber ); 	
}

void SendDWord(DWORD dNumber)
{
	QWORD k;
	for(k=1000000000; k>=1; k/=10)
	{
		SendChar( (dNumber/k)+'0' );
		dNumber-=(dNumber/k)*k;
	} 	
}

void SendSDWord(SDWORD sdNumber)
{										 
	if(sdNumber<0)
	{
		SendChar('-');
		sdNumber=sdNumber*(-1);
	}
	else
	{
		SendChar('+'); 
	}
	SendDWord( sdNumber ); 	
}

void SendData(BYTE* tab, int size)
{
	int written=0;	BYTE data;
	int i=0;
	while(size){
		written=write_sbuffer(&UART_BUF_OUT,tab,size);
		tab+=written; size-=written;
		if(!boUartInterNext)
	 	{
			if(!get_sbuffer(&UART_BUF_OUT,&data))
				U1THR=data;
			if(!get_sbuffer(&UART_BUF_OUT,&data))
				U1THR=data;
			if(!get_sbuffer(&UART_BUF_OUT,&data))
			{
				boUartInterNext=TRUE;
				U1THR=data;
			}
		}
	}
}
BYTE *sendDataTab=NULL;
int sendDataSize=0;
void InitSendDataFree(BYTE* tab, int size)
{
	sendDataTab=tab; sendDataSize=size;
}

int SendDataFree()
{
	int written=0,read=0;	BYTE data[3];
	int i=0;
	if(sendDataSize){
		written=write_sbuffer(&UART_BUF_OUT,sendDataTab,sendDataSize);
		sendDataTab+=written; sendDataSize-=written;
		if(!boUartInterNext)
	 	{
			if(sbuffer_len(&UART_BUF_OUT)>2)
			{
				boUartInterNext=TRUE;
				read_sbuffer(&UART_BUF_OUT,data,3);
				numb+=3;
				U1THR=data[0];U1THR=data[1];U1THR=data[2];
				
			}else
			{
				read=read_sbuffer(&UART_BUF_OUT,data,2);
				numb+=read;
				for(i=0;i<read;i++) 
					U1THR=data[i];
				
			}

		}
		return 0;
	}
	else 
		return 1;
}


void ReadData(BYTE* tab,int size)
{
	BYTE read=0;
	while(size)
	{
		read=read_sbuffer(&UART_BUF_IN,tab,size);
		tab+=read;size-=read;
	}
}

BYTE *readDataTab=NULL;
int readDataSize=0;

void InitReadDataFree(BYTE* tab, int size)
{	readDataTab=tab; readDataSize=size;	}

int ReadDataFree()
{
	BYTE read=0;
	if(readDataSize)
	{
		read=read_sbuffer(&UART_BUF_IN,readDataTab,readDataSize);
		readDataTab+=read;readDataSize-=read;
		return 0;
	}else
		return 1;
}

