#line 1 "irq.c"









 
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




#line 12 "irq.c"
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







#line 13 "irq.c"
#line 1 "IRQ.h"










 










 





#line 61 "IRQ.h"








 
 



 
static DWORD sysreg;		 



extern void FIQ_Handler( void ) __irq;
void init_VIC( void );
DWORD install_irq( DWORD IntNumber, void *HandlerAddr, DWORD Priority );





 
#line 14 "irq.c"









 
void FIQ_Handler( void ) __irq
{
#line 37 "irq.c"
}

 







 
void init_VIC(void) 
{
    DWORD i = 0;
    DWORD *vect_addr, *vect_prio;
   	
     
    (*(volatile unsigned long *)(0xFFFFF000 + 0x014)) = 0xffffffff;
    (*(volatile unsigned long *)(0xFFFFF000 + 0xF00)) = 0;
    (*(volatile unsigned long *)(0xFFFFF000 + 0x00C)) = 0;

     
    for ( i = 0; i < 32; i++ )
    {
		vect_addr = (DWORD *)(0xFFFFF000 + 0x100 + i*4);
		vect_prio = (DWORD *)(0xFFFFF000 + 0x200 + i*4);
		*vect_addr = 0x0;	
		*vect_prio = 0xF;
    }
    return;
}









 
DWORD install_irq( DWORD IntNumber, void *HandlerAddr, DWORD Priority )
{
    DWORD *vect_addr;
    DWORD *vect_prio;
      
    (*(volatile unsigned long *)(0xFFFFF000 + 0x014)) = 1 << IntNumber;	 
    if ( IntNumber >= 32 )
    {
		return ( (0) );
    }
    else
    {
		 
		vect_addr = (DWORD *)(0xFFFFF000 + 0x100 + IntNumber*4);
		vect_prio = (DWORD *)(0xFFFFF000 + 0x200 + IntNumber*4);
		*vect_addr = (DWORD)HandlerAddr;	 
		*vect_prio = Priority;
		(*(volatile unsigned long *)(0xFFFFF000 + 0x010)) = 1 << IntNumber;	 
		return( (1) );
    }
}
