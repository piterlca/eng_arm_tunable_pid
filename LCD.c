#include "LCD.h"
#include <lpc23xx.h>
#include <stdlib.h>
#include <stdio.h>

volatile int prev_val=0;

void wait_ms (char time)
	{
		  int i=0;
		  for (i; i<(time*12000);i++);
	}

 void wait_us (char time)
	{
		  int i=0;
		  for (i; i<(time*12);i++);
	}
void  DATA_to_LCD(char x) 
	{
   		IOCLR0 = ( (~x) & Mask ) << Data_Bits ;
   		IOSET0 = ( (x) & Mask ) << Data_Bits ;  
	}

void write_LCD (  char y) 
{
 	E_clr;							 // Enable=0 wyœwietlacz nieaktywny                         
  	DATA_to_LCD(y);      //dane s¹ przekazywane na liniach P0_3...P0_0
  	E_set;                   // linia Enable E=1: zapis do wyœwietlacza
  	E_clr;                           // linia Enable E=0: koniec zapisu
}
void LCD_Write_data (char data)
	 {
		 wait_us (100);
		 RS_set;                  
  		 write_LCD(data >> 4);         // zapis starszej czwórki bajtu Data
  		 write_LCD(data);               // zapis m³odszej czwórki bajtu Data
	}
void LCD_Write_cmd (char cmd)
	 {
		 wait_us (100);
		 RS_clr;                 
  		 write_LCD(cmd >> 4);        // zapis starszej czwórki bajtu cmd
  		 write_LCD(cmd);               // zapis m³odszej czwórki bajtu cmd
	}

void LCD_Write_text(char * text)
	{
		while(*text)
  		LCD_Write_data(*text++);
	}

void LCD_set_cursor (char rownr, char colnr) 
	{
  		int cmd;
 		rownr= rownr%NB_ROW;      // umieszczenie numeru wiersza obszarze limitu
 	    colnr= colnr%NB_COL;      // umieszczenie numeru kolumny obszarze limitu
  		switch (rownr)
		 {
    		case 0:
           	cmd = ROW0 | 0x80;
           	break;
    		case 1:
          	cmd = ROW1  | 0x80;
          	break;
    		case 2:
          	cmd = ROW2  | 0x80;
          	break;
    		case 3:
          	cmd = ROW3  | 0x80;
          	break;
    		default:
           	cmd = ROW0 | 0x80;
           	break;
  		}
  		LCD_Write_cmd(cmd + colnr); 
	}

void  LCD_all_init (void)
 	{ 
    	IODIR0 |= 0x3F0;   //P0 4..9 
	}
void lcd_init (void) 
	{
  		char i;
  		const char init_tab[] = 
       	{0x30,0x30,0x30,0x20,0x28,0x0E,0x01,0x06};
       	LCD_all_init();
  	  	for (i = 0; i < sizeof init_tab; i++) 
	   		{
	   			wait_ms (8); 
       			LCD_Write_cmd(init_tab[i]);                 // zapis danych inicjuj¹cych
  	   		}

       	LCD_set_cursor(0, 0);

}


void LCD_clear (void) 
	{
 		LCD_Write_cmd(CLR_LCD);
		wait_us (70);
	}

void LCD_cursorOFF (void)
	{
 		LCD_Write_cmd(CUR_OFF);
	}	

void Result_on_LCD(int val)
	{
		
		 float adc;
		 const float div=(3.3/1023);
		 char result [10]={0};   
		 wait_ms (100);   
		 adc=(val*div*100)-273;//(330000*val-27300*1023)/(100*1023)				   //*100 dla lm35 // *100 -273 dla lm335
	     sprintf(result,"%.1f",adc);
		 //tobinstr(val,10,result);
		 LCD_set_cursor(0,0);
		 LCD_clear;
		 //LCD_Write_data(text);
		 LCD_Write_text(result);
		 LCD_Write_text("C");
	}

void tobinstr(int value, int bitsCount, char* output)
	{
    	int i;
    	output[bitsCount] = '\0';
    	for (i = bitsCount - 1; i >= 0; --i, value >>= 1)
    	{
        	output[i] = (value & 1) + '0';
    	}
	}
