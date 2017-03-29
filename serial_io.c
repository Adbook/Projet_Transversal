#include "serial_io.h"
#include <c8051f020.h> 
#include <intrins.h>
#include "UART0_RingBuffer_lib.h"
char Putchar(char c)
{
  SBUF1 =c;   //UART prêt
	while (SCON1 == 0x50);	
	SCON1 &= 0xfd;	// TI1 a 0
		
  return 0;
}


char Send_String(char * char_ptr)
{
    
	char c;
	xdata unsigned int j = 0;
	EA = 0;
    while(char_ptr[j] != '\0')
	{ 
		c = Putchar(char_ptr[j]);
		j ++;
		//compteur++;

	}
	EA = 1;
	return 0;
    
}

char Getchar()
{
	char c;
	
	if(RI0 == 0)
		return 0;

	c = SBUF0;
	RI0 = 0;
	
	return c;
}