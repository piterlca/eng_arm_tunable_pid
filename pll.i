#line 1 "PLL.c"





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




#line 7 "PLL.c"
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







#line 8 "PLL.c"
#line 1 "PLL.h"


















void PllInit ( void );

#line 9 "PLL.c"

void PllInit ( void )
{
	DWORD MValue, NValue;

	if ( (*(volatile unsigned long *)(0xE01FC000 + 0x088)) & (1 << 25) )  
	{
		(*(volatile unsigned long *)(0xE01FC000 + 0x080)) = (1<<0)|		 
				 (0<<1);		 
			 				 
 
		(*(volatile unsigned long *)(0xE01FC000 + 0x08C)) = 0xaa;			 
		(*(volatile unsigned long *)(0xE01FC000 + 0x08C)) = 0x55;			 
	}
	(*(volatile unsigned long *)(0xE01FC000 + 0x080)) = 0;					 
	(*(volatile unsigned long *)(0xE01FC000 + 0x08C)) = 0xaa;				 
	(*(volatile unsigned long *)(0xE01FC000 + 0x08C)) = 0x55;				 

	(*(volatile unsigned long *)(0xE01FC000 + 0x1A0)) |= (1<<5);				 
	while( !((*(volatile unsigned long *)(0xE01FC000 + 0x1A0)) & (1<<6)) );	 

	(*(volatile unsigned long *)(0xE01FC000 + 0x10C)) = 0x1;			 

   

  	(*(volatile unsigned long *)(0xE01FC000 + 0x000))	=	0;							 
  											 
    (*(volatile unsigned long *)(0xE01FC000 + 0x004))	=	0x4;						 
    (*(volatile unsigned long *)(0xE01FC000 + 0x000))	=	0x2;						 
											 
	(*(volatile unsigned long *)(0xE01FC000 + 0x084)) = 19 | (0 << 16);  
	(*(volatile unsigned long *)(0xE01FC000 + 0x08C)) = 0xaa;							 
	(*(volatile unsigned long *)(0xE01FC000 + 0x08C)) = 0x55;							 

	(*(volatile unsigned long *)(0xE01FC000 + 0x080)) = 1;								 
	(*(volatile unsigned long *)(0xE01FC000 + 0x08C)) = 0xaa;							 
	(*(volatile unsigned long *)(0xE01FC000 + 0x08C)) = 0x55;							 
	(*(volatile unsigned long *)(0xE01FC000 + 0x104)) = 5;					 
											 
	(*(volatile unsigned long *)(0xE01FC000 + 0x108)) = 9;				 

	while ( (((*(volatile unsigned long *)(0xE01FC000 + 0x088)) & (1 << 26)) == 0) );  
											 

	MValue = (*(volatile unsigned long *)(0xE01FC000 + 0x088)) & 0x00007FFF;			 
	NValue = ((*(volatile unsigned long *)(0xE01FC000 + 0x088)) & 0x00FF0000) >> 16;

 
 
	while ((MValue != 19) && ( NValue != 0) );
	(*(volatile unsigned long *)(0xE01FC000 + 0x080)) = 3;				 
	(*(volatile unsigned long *)(0xE01FC000 + 0x08C)) = 0xaa;			 
	(*(volatile unsigned long *)(0xE01FC000 + 0x08C)) = 0x55;			 

 
	while ( (((*(volatile unsigned long *)(0xE01FC000 + 0x088)) & (1 << 25)) == 0) );	 
}
