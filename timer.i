#line 1 "Timer.c"





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




#line 7 "Timer.c"
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







#line 8 "Timer.c"
#line 1 "IRQ.h"










 










 





#line 61 "IRQ.h"








 
 



 
static DWORD sysreg;		 



extern void FIQ_Handler( void ) __irq;
void init_VIC( void );
DWORD install_irq( DWORD IntNumber, void *HandlerAddr, DWORD Priority );





 
#line 9 "Timer.c"
#line 1 "Timer.h"









#line 11 "Timer.h"
#line 12 "Timer.h"
#line 1 "PLL.h"


















void PllInit ( void );

#line 13 "Timer.h"
	


 
 
void Timer1Init( void );
void Timer0Init( void* timer0_irq, DWORD T );
void Timer0Start(void);
void Timer0Stop(void);
void Timer0Restart(void);

 
 
void DelayCclk(DWORD dDelayInCclk);

  
 
void DelayUs(DWORD dDelayInUs);

  
 
void DelayMs(DWORD dDelayInMs);

 
 
 
 
void StoperUsStart( void );

void StoperUsStop( void );

__inline DWORD StoperUsClick()
{
	return (*(volatile unsigned long *)(0xE0008000 + 0x08));
}

#line 10 "Timer.c"
#line 1 "sys_buf.h"
#line 4 "sys_buf.h"

BOOL get_sysbuf_word(WORD* v);
BOOL get_sysbuf_sword(SWORD* v);

BOOL put_sysbuf_word(WORD v);
BOOL put_sysbuf_sword(SWORD v);


#line 11 "Timer.c"


void Timer1Init( void ) 
{
	(*(volatile unsigned long *)(0xE01FC000 + 0x0C4))	|=	(0x1<<2); 							 
	(*(volatile unsigned long *)(0xE01FC000 + 0x1A8)) =	((*(volatile unsigned long *)(0xE01FC000 + 0x1A8)) & (0xFFFFFFFF^(0x3<<4)))|	 
				(0x1<<4);							 
	(*(volatile unsigned long *)(0xE0008000 + 0x14))	=	(0<<0)|(0<<1)|(1<<2);		 
	(*(volatile unsigned long *)(0xE0008000 + 0x28))	=	0x0;				 				
	(*(volatile unsigned long *)(0xE0008000 + 0x70))	=	0x0;				 
	(*(volatile unsigned long *)(0xE0008000 + 0x0C))	=	1;					 
	(*(volatile unsigned long *)(0xE0008000 + 0x00))  	=	0xFF;
}


void Timer0Init( void* timer0_irq, DWORD T ) 
{
	(*(volatile unsigned long *)(0xE01FC000 + 0x0C4))	|=	(0x1<<2); 							 
	(*(volatile unsigned long *)(0xE01FC000 + 0x1A8)) =	((*(volatile unsigned long *)(0xE01FC000 + 0x1A8)) & (~(0x3<<2)))|	 
				(0x1<<2);							 
	(*(volatile unsigned long *)(0xE0004000 + 0x14))	=	(1<<0)|(1<<1)|(0<<2);		 
	(*(volatile unsigned long *)(0xE0004000 + 0x18)) = T;
	(*(volatile unsigned long *)(0xE0004000 + 0x28))	=	0x0;				 				
	(*(volatile unsigned long *)(0xE0004000 + 0x70))	=	0x0;				 
	(*(volatile unsigned long *)(0xE0004000 + 0x0C))	=	0;					 
	(*(volatile unsigned long *)(0xE0004000 + 0x00))  	=	0xFF;
	(*(volatile unsigned long *)(0xE0004000 + 0x04))=0x2;
	while((*(volatile unsigned long *)(0xE0004000 + 0x08))!=0);
	(*(volatile unsigned long *)(0xE0004000 + 0x04))=0x00;
	install_irq( 4, timer0_irq, 0x0F-6 );
}

void Timer0Start(void)
{
	(*(volatile unsigned long *)(0xE0004000 + 0x04))=0x1;
}

void Timer0Restart(void)
{
	(*(volatile unsigned long *)(0xE0004000 + 0x04))=0x2;
	while((*(volatile unsigned long *)(0xE0004000 + 0x08))!=0);
	(*(volatile unsigned long *)(0xE0004000 + 0x04))=0x1;
}	


void Timer0Stop(void)
{
	(*(volatile unsigned long *)(0xE0004000 + 0x04))=0x0;	
}

void DelayCclk(DWORD dDelayInCclk)
{								  
	(*(volatile unsigned long *)(0xE0008000 + 0x04)) = 0x02;						 
	(*(volatile unsigned long *)(0xE0008000 + 0x0C))  = 0;							 
	(*(volatile unsigned long *)(0xE0008000 + 0x00))  = 0xFF;						 
	(*(volatile unsigned long *)(0xE0008000 + 0x18)) = dDelayInCclk;				 
	(*(volatile unsigned long *)(0xE0008000 + 0x04)) = 0x01;						 
	while ((*(volatile unsigned long *)(0xE0008000 + 0x04)) & 0x01);
}

void DelayUs(DWORD dDelayInUs)
{
	(*(volatile unsigned long *)(0xE0008000 + 0x04)) = 0x02;						 
	(*(volatile unsigned long *)(0xE0008000 + 0x0C))  = ((80000000/1)/1000000)-1;	 
	(*(volatile unsigned long *)(0xE0008000 + 0x00))  = 0xFF;						 
	(*(volatile unsigned long *)(0xE0008000 + 0x18)) = dDelayInUs;					 
	(*(volatile unsigned long *)(0xE0008000 + 0x04)) = 0x01;						 
	while ((*(volatile unsigned long *)(0xE0008000 + 0x04)) & 0x01);
}

void DelayMs(DWORD dDelayInMs)
{
	(*(volatile unsigned long *)(0xE0008000 + 0x04)) = 0x02;						 
	(*(volatile unsigned long *)(0xE0008000 + 0x0C))  = ((80000000/1)/1000)-1;		 
	(*(volatile unsigned long *)(0xE0008000 + 0x00))  = 0xFF;						 
	(*(volatile unsigned long *)(0xE0008000 + 0x18)) = dDelayInMs;					 
	(*(volatile unsigned long *)(0xE0008000 + 0x04)) = 0x01;						 
	while ((*(volatile unsigned long *)(0xE0008000 + 0x04)) & 0x01);
}

void StoperUsStart(void)
{
	(*(volatile unsigned long *)(0xE0008000 + 0x04)) = 0x02;			  			 
	(*(volatile unsigned long *)(0xE0008000 + 0x00))  = 0xFF;						 
	(*(volatile unsigned long *)(0xE0008000 + 0x0C))  = ((80000000/1)/1000000)-1;	 
	(*(volatile unsigned long *)(0xE0008000 + 0x18)) = 0xFFFFFFFF;					 
	(*(volatile unsigned long *)(0xE0008000 + 0x04)) = 0x01;						 
}

void StoperUsStop(void)
{
	(*(volatile unsigned long *)(0xE0008000 + 0x04)) = 0x02;						 
	(*(volatile unsigned long *)(0xE0008000 + 0x00))  = 0xFF;						   
}




