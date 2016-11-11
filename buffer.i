#line 1 "Buffer.c"





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




#line 7 "Buffer.c"
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







#line 8 "Buffer.c"
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
#line 9 "Buffer.c"
#line 1 "Buffer.h"








#line 10 "Buffer.h"

 

 
 
BYTE ReadBufferOut(void);


 
 
 
 
 
 
 
void WriteBufferOut(BYTE bData);

 
 
void WriteBufferNOut(BYTE* bData, BYTE bLength);

 
 
 
BYTE ByteInBufferOut(void);



 

 
BYTE ReadBufferIn(void);

 
 
void WriteBufferIn(BYTE bData);

 
 
BYTE ByteInBufferIn(void);

#line 10 "Buffer.c"

static volatile BYTE abBuffIn[256];
static volatile BYTE bWrIn=0;
static volatile BYTE bRdIn=0;

static volatile BYTE abBuffOut[256];
static volatile BYTE bWrOut=0;
static volatile BYTE bRdOut=0;


 

 
 
BYTE ReadBufferOut(void)
{
	return (bWrOut != bRdOut )? abBuffOut[++bRdOut] : 0; 
}

 
 
void WriteBufferOut(BYTE bData)
{
	if( (BYTE)(bWrOut+1) != bRdOut ) abBuffOut[++bWrOut]=bData;
}

 
 
 
 
 
 
 
 
void WriteBufferNOut(BYTE* bData, BYTE bLength)	 
{
	BYTE k=0x0F;											 
	if( CheckUartReady() )	   
	{
		 
		 
		while( --k && (bWrOut!=bRdOut) ) SendRawChar( abBuffOut[++bRdOut] );
		 
		 
		
		while( k-- && bLength )
		{
			SendRawChar( *bData );
			++bData; --bLength;
		}
	}
	while( bLength-- )						 
	{
		while( (BYTE)(bWrOut+1)==bRdOut );	 
		abBuffOut[++bWrOut]= *bData++;		 
	}	
}

 
 
 
BYTE ByteInBufferOut(void)
{
	return bWrOut-bRdOut;
}

 

 
BYTE ReadBufferIn(void)
{
	return (bWrIn != bRdIn )? abBuffIn[++bRdIn] : 0; 
}

 
 
 
void WriteBufferIn(BYTE bData)
{
	if((BYTE)(bWrIn+1) != bRdIn ) abBuffIn[++bWrIn]=bData;
}

 
 
BYTE ByteInBufferIn(void)
{
	return bWrIn-bRdIn;
}

