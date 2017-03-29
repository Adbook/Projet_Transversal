#include "struct.h"
#include "decodage_commande.h"
#include "init_device.h"
#include <c8051f020.h> 
#include <intrins.h>
#include <stdlib.h>
#include <string.h>
#include "serial_io.h"
#include "CFG_Globale.h"
#include "UART0_RingBuffer_lib.h"
#define boolean char
#define true 1
#define false 0

sbit BP = P3^7; 
xdata char current_string[64];

boolean updateString (char * s){ //renvoie 1 si la chaine est terminée (\r reçu)
	static int i = 0;
	char c;
	if((c=serInchar())!=0){
		serOutchar(c);
		s[i] = c;
		i++;
		
		if(c == '\r')
		{
            s[i] = '\0';
			i = 0;
			serOutchar('\n');
			return true;
		}
	}
	return false;
}
int main(){
	char c;
	char test;
	char commande[] = "A\r";
	//char *mem = malloc(sizeof(char)*strlen(commande));
    
	init_Serial_Buffer();	
	init_device();
	//cfg_Clock_UART();
  ///cfg_UART0_mode1();


	EA = 1;                              /* allow interrupts to happen */
    serOutstring("\nBonjour\n\r>");

	while(1){
			if(updateString(current_string) == true){
				decoder_commande(current_string);
                current_string[0] = '\0';
                
			}

	}
		
}






