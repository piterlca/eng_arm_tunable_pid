#line 1 "UART1.c"





#line 1 "LPC24xx.h"












 




 
#line 30 "LPC24xx.h"

#line 63 "LPC24xx.h"


 
#line 98 "LPC24xx.h"

 
#line 132 "LPC24xx.h"




 
#line 150 "LPC24xx.h"

#line 161 "LPC24xx.h"

 
#line 172 "LPC24xx.h"

 

















 
#line 198 "LPC24xx.h"

























 























































































































































































 


 




 





 



 

#line 433 "LPC24xx.h"
	
 





 


 


 



 


 










 





 
#line 485 "LPC24xx.h"

#line 494 "LPC24xx.h"

 
#line 503 "LPC24xx.h"

#line 511 "LPC24xx.h"

#line 519 "LPC24xx.h"

#line 527 "LPC24xx.h"



	
 
#line 548 "LPC24xx.h"

 
#line 566 "LPC24xx.h"

 
#line 584 "LPC24xx.h"

 
#line 602 "LPC24xx.h"


 
#line 625 "LPC24xx.h"

#line 646 "LPC24xx.h"


 
#line 664 "LPC24xx.h"

 
#line 682 "LPC24xx.h"

 
#line 699 "LPC24xx.h"

 
#line 716 "LPC24xx.h"

 
#line 726 "LPC24xx.h"

 
#line 736 "LPC24xx.h"

 
#line 746 "LPC24xx.h"

 
#line 754 "LPC24xx.h"

 
#line 767 "LPC24xx.h"

 
#line 780 "LPC24xx.h"


 
#line 811 "LPC24xx.h"


 
#line 827 "LPC24xx.h"


 




 
#line 841 "LPC24xx.h"

 
#line 852 "LPC24xx.h"






#line 871 "LPC24xx.h"
  	
#line 884 "LPC24xx.h"

#line 898 "LPC24xx.h"
  	
#line 911 "LPC24xx.h"


 
#line 934 "LPC24xx.h"


 
#line 948 "LPC24xx.h"


 
#line 966 "LPC24xx.h"

 






 







 





 






 






 




 



 






 
#line 1037 "LPC24xx.h"

 
#line 1063 "LPC24xx.h"

 
#line 1072 "LPC24xx.h"

#line 1080 "LPC24xx.h"





 
#line 1101 "LPC24xx.h"





#line 1118 "LPC24xx.h"























 
#line 1169 "LPC24xx.h"




#line 7 "UART1.c"
#line 1 "Type.h"




















typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef unsigned long long  QWORD;
typedef unsigned int   BOOL;

typedef signed char SBYTE;
typedef signed short SWORD;
typedef signed long  SDWORD;
typedef signed long long  SQWORD;
typedef signed int   SBOOL;







#line 8 "UART1.c"
#line 1 "IRQ.h"










 










 





#line 61 "IRQ.h"








 
 



 
static DWORD sysreg;		 



extern void FIQ_Handler( void ) __irq;
void init_VIC( void );
DWORD install_irq( DWORD IntNumber, void *HandlerAddr, DWORD Priority );





 
#line 9 "UART1.c"
#line 1 "PID.h"
#line 2 "PID.h"
typedef struct 
{
	WORD kp,ki,kd;
	BYTE dkp,dki,dkd;
	SBYTE sign;
	BYTE syn;
} PIDSTRUCT;
void PID_Init(void);
WORD PID(SWORD ADCbuf,PIDSTRUCT* factors,SDWORD off);


#line 10 "UART1.c"
#line 1 "PLL.h"


















void PllInit ( void );

#line 11 "UART1.c"
#line 1 "UART1.h"








#line 10 "UART1.h"
#line 11 "UART1.h"


						 		 	 










#line 32 "UART1.h"



extern volatile BYTE bByteToSend;


 
__inline void SendRawChar(BYTE bChar)
{
	(*(volatile unsigned long *)(0xE0010000 + 0x00))=bChar;	
}

 
 
__inline BYTE CheckUartReady( void )
{
	return (((*(volatile unsigned long *)(0xE0010000 + 0x14)) & 0x40) && !bByteToSend);	
}

 
 
void SendChar(BYTE bChar);

 
 
 
 
void SendStrByte(BYTE *str);

 
 
DWORD Uart1Init(DWORD dBAUD);

 
 
void Inter_Uart(void) __irq;

 
 
 
 
DWORD countFDR(float fFract);

 
 
 
void SendByte(BYTE bNumber);
void SendSByte(SBYTE sbNumber);
void SendWord(WORD wNumber);
void SendSWord(SWORD sNumber);
void SendDWord(DWORD dNumber);
void SendSDWord(SDWORD sdNumber);


void SendData(BYTE* tab, int size);
void ReadData(BYTE* tab, int size);


void InitSendDataFree(BYTE* tab, int size);
void InitReadDataFree(BYTE* tab, int size);
int SendDataFree();
int ReadDataFree();
#line 12 "UART1.c"
#line 1 "Buffer.h"








#line 10 "Buffer.h"

 

 
 
BYTE ReadBufferOut(void);


 
 
 
 
 
 
 
void WriteBufferOut(BYTE bData);

 
 
void WriteBufferNOut(BYTE* bData, BYTE bLength);

 
 
 
BYTE ByteInBufferOut(void);



 

 
BYTE ReadBufferIn(void);

 
 
void WriteBufferIn(BYTE bData);

 
 
BYTE ByteInBufferIn(void);

#line 13 "UART1.c"
#line 1 "sbuffer.h"

#line 5 "sbuffer.h"
typedef struct
{
	BYTE* buf;
	int capacity;
	int w,r;
} SBUFFER;

SBUFFER create_sbuffer(BYTE* buf, int cap);
BOOL put_sbuffer(SBUFFER *b,BYTE data);
int write_sbuffer(SBUFFER *b,BYTE *tab, int num);
int read_sbuffer(SBUFFER *b,BYTE *tab, int num);
BOOL get_sbuffer(SBUFFER *b, BYTE* data); 
int sbuffer_len(SBUFFER *b);

#line 14 "UART1.c"
volatile SBUFFER UART_BUF_IN;
volatile SBUFFER UART_BUF_OUT;

volatile BYTE _UART_BUF_IN[512];
volatile BYTE _UART_BUF_OUT[512];
volatile BOOL boUartInterNext=0;
volatile BYTE bErrorAbort;
volatile BYTE bByteToSend=0;
volatile BYTE Buff[9]={0,0,0,0,0,0,0,0,0}; 
volatile int x=0;
volatile unsigned char index=0;
WORD kp1,ki1,kd1=0;
extern WORD kp,kd,ki;
volatile int numb=0;



 
 











 
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
	while(!((*(volatile unsigned long *)(0xE0010000 + 0x14)) & 0x40));
		(*(volatile unsigned long *)(0xE0010000 + 0x00))=bChar; 
}

void SendStrByte(BYTE *str)
{
	WORD uiCount=0x0;
	while(!((*(volatile unsigned long *)(0xE0010000 + 0x14)) & 0x40));
	while(*str)
	{
		if ( (uiCount>=0xF) )
		{
			while(!((*(volatile unsigned long *)(0xE0010000 + 0x14)) & 0x40));
			uiCount=0x0;
		}
		uiCount++;
		(*(volatile unsigned long *)(0xE0010000 + 0x00))=(*str++);	
	}	
}

void Inter_Uart(void) __irq
{
	BYTE bIIRValue, bLSRValue;
	BYTE bData=0;
	int cnt=0;
	int i;
	BYTE data[0xF];
	bIIRValue = (*(volatile unsigned long *)(0xE0010000 + 0x08));
	bIIRValue >>= 1;		 
	bIIRValue &= 0x07;	 
  	if ( bIIRValue == 0x03 )			  
  	{									
		bLSRValue = (*(volatile unsigned long *)(0xE0010000 + 0x14));	  			     
		if ( bLSRValue & (0x02|0x04|0x08|0x80|0x10) ) 	   
		{
			bData=(*(volatile unsigned long *)(0xE0010000 + 0x00));	 						 
	  		bErrorAbort=bLSRValue & (0x3 | bData);	 	
		}
		if ( bLSRValue & 0x01 ) 			 
		{									 
			
		}									 
	}										 
	else if ( bIIRValue == 0x02 )			 
  	{





		data[0]=(*(volatile unsigned long *)(0xE0010000 + 0x00));
		put_sbuffer(&UART_BUF_IN,data[0]);		
  	}	
	else if ( bIIRValue == 0x01 )		 
  	{









		cnt=read_sbuffer(&UART_BUF_OUT,data,0xF);
		numb+=cnt;
		if(cnt<3)
			boUartInterNext=(0);
		for(i=0;i<cnt;i++)
			(*(volatile unsigned long *)(0xE0010000 + 0x00))=data[i];
	}
  	(*(volatile unsigned long *)(0xFFFFF000 + 0xF00)) = 0;
}

 
 
 
 
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
	UART_BUF_OUT=create_sbuffer(_UART_BUF_OUT,512);
	UART_BUF_IN=create_sbuffer(_UART_BUF_IN,512);
	(*(volatile unsigned long *)(0xE01FC000 + 0x0C4))	|=	(0x1<<4);							 
	(*(volatile unsigned long *)(0xE01FC000 + 0x1A8)) =	((*(volatile unsigned long *)(0xE01FC000 + 0x1A8)) & (0xFFFFFFFF^(0x3<<8)))|	 
				(0x1<<8);							 													
													 
													 
	(*(volatile unsigned long *)(0xE002C000 + 0x00))  =	((*(volatile unsigned long *)(0xE002C000 + 0x00)) & (0x3FFFFFFF))|			 
				(0x1<<30);
	(*(volatile unsigned long *)(0xE002C000 + 0x04))  =	((*(volatile unsigned long *)(0xE002C000 + 0x04)) & (0x00003FFF))|			 		
				(0x1<<0)|							 
				(0x1<<2)|							 
				(0x1<<4)|							 
				(0x1<<6)|							 
				(0x1<<8)|							 
				(0x1<<10)|							 
				(0x1<<12);							 

	(*(volatile unsigned long *)(0xE002C000 + 0x40)) =	((*(volatile unsigned long *)(0xE002C000 + 0x40)) & (0x3FFFFFFF))|			 
				(0x0<<30);							 
	(*(volatile unsigned long *)(0xE002C000 + 0x44)) =	((*(volatile unsigned long *)(0xE002C000 + 0x44)) & (0xFFFFFFFF^0x3))|		 
				(0x0<<0)|							 
				(0x0<<2)|							 
				(0x0<<4)|							 
				(0x0<<6)|							 
				(0x0<<8)|							 
				(0x0<<10)|							 
				(0x0<<12);							 
	(*(volatile unsigned long *)(0xE0010000 + 0x0C))	 =	(0x3)|								 
													 
				(0x0 <<2)|							 
				(0x0 <<3)|							 
				(0x0 <<4)|							 
				(0x0 <<6)|							 
				(0x1 <<7);							 
													 
													 
													 
													 

	(*(volatile unsigned long *)(0xE0010000 + 0x00))	 =	((BYTE) (( (80000000/1)/16/dBAUD)%256));	 
														 
	(*(volatile unsigned long *)(0xE0010000 + 0x04))	 =	((BYTE) (( (80000000/1)/16/dBAUD)/256));	 
														 

	 
	 

	dBAUD_REAL=(80000000/1)/( 16*( 256*((( (80000000/1)/16/dBAUD)/256)) + (( (80000000/1)/16/dBAUD)%256) ));

	 
	 
	  
	 
	 
	 

	if ( (((float)((dBAUD_REAL)-(dBAUD))) / ((float)dBAUD))*100 > 0.5 )	
	{
		 
		 
		 
		 

		(*(volatile unsigned long *)(0xE0010000 + 0x28))=countFDR( ((float)((dBAUD_REAL)-(dBAUD))) / ((float)dBAUD) );

		 
		dBAUD_REAL=(dBAUD_REAL)/(1.+ ( (float)((*(volatile unsigned long *)(0xE0010000 + 0x28))&0xF)) / ((float)(((*(volatile unsigned long *)(0xE0010000 + 0x28))&0xF0)>>4)));
	}

	(*(volatile unsigned long *)(0xE0010000 + 0x0C))	 =	0x03;									 
	(*(volatile unsigned long *)(0xE0010000 + 0x08))	 =	(0x1 <<0)|								 
				(0x1 <<1)|								 
				(0x1 <<2)|								 
				(0x0 <<6);								 
														 

	(*(volatile unsigned long *)(0xE0010000 + 0x10))	 =	(0x1 <<0)|								 
				(0x1 <<1)|								 
				(0x0 <<4)|								 
				(0x1 <<6)|								 
				(0x1 <<7);								 
	
	if ( install_irq( 7, (void *)Inter_Uart, 0x6 ) == (0) )
    {
	  return ((0));
    }

	(*(volatile unsigned long *)(0xE0010000 + 0x04))	 =	(0x1 <<0)|					 
				(0x1 <<1)|					 
				(0x1 <<2)|					 
				(0x0 <<3)|					 
				(0x0 <<7)|					 
				(0x0 <<8)|					 
				(0x0 <<9);					 
	
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
				(*(volatile unsigned long *)(0xE0010000 + 0x00))=data;
			if(!get_sbuffer(&UART_BUF_OUT,&data))
				(*(volatile unsigned long *)(0xE0010000 + 0x00))=data;
			if(!get_sbuffer(&UART_BUF_OUT,&data))
			{
				boUartInterNext=(1);
				(*(volatile unsigned long *)(0xE0010000 + 0x00))=data;
			}
		}
	}
}
BYTE *sendDataTab=((void *)0);
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
				boUartInterNext=(1);
				read_sbuffer(&UART_BUF_OUT,data,3);
				numb+=3;
				(*(volatile unsigned long *)(0xE0010000 + 0x00))=data[0];(*(volatile unsigned long *)(0xE0010000 + 0x00))=data[1];(*(volatile unsigned long *)(0xE0010000 + 0x00))=data[2];
				
			}else
			{
				read=read_sbuffer(&UART_BUF_OUT,data,2);
				numb+=read;
				for(i=0;i<read;i++) 
					(*(volatile unsigned long *)(0xE0010000 + 0x00))=data[i];
				
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

BYTE *readDataTab=((void *)0);
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

