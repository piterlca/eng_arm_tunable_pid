// Header: CYFROWY REGULATOR PID NAG£ÓWKOWY SSP0
// File Name: SSP0_SPI.h
// Author: PAWE£ BICZYSKO
// Date: 10.11.2013

/* SSP select pin */
#define SSP0_SEL		(1 <<21)
/* SSP Convert pin*/
#define SSP0_CNV		(1 <<25)
	
/* SSP Status register */
#define SSPSR_TFE		(1 << 0)
#define SSPSR_TNF		(1 << 1) 
#define SSPSR_RNE		(1 << 2)
#define SSPSR_RFF		(1 << 3) 
#define SSPSR_BSY		(1 << 4)

/* SSP0 CR0 register */
#define SSPCR0_DSS		(1 << 0)
#define SSPCR0_FRF		(1 << 4)
#define SSPCR0_SPO		(1 << 6)
#define SSPCR0_SPH		(1 << 7)
#define SSPCR0_SCR		(1 << 8)

/* SSP0 CR1 register */
#define SSPCR1_LBM		(1 << 0)
#define SSPCR1_SSE		(1 << 1)
#define SSPCR1_MS		(1 << 2)
#define SSPCR1_SOD		(1 << 3)

/* SPI read and write buffer size */
#define SSP_BUFSIZE		256
#define FIFOSIZE		16


void SSP0Init( void );
void SSP0Send( WORD Buf);
void SSP0Receive( SWORD* buf);
