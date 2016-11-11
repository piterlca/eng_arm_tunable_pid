/*--------------------------------------------------------------------------
INTTYPES.H

Standard ISO C typedefs for fixed size integral types 
Copyright (c) 2004 Keil Elektronik GmbH, and Keil Software, Inc.
All rights reserved.

MISRA-C also requires the use of typedefs for integer types.
MISRA-C1 Rules 13 and 14
MISRA-C2 Rules 6.1, 6.2, 6.3
--------------------------------------------------------------------------*/

#ifndef __TYPE_H__
#define __TYPE_H__

#ifndef NULL	  
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef unsigned int   BOOL;

#endif  /* __TYPE_H__ */
