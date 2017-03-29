//-----------------------------------------------------------------------------------------------------------
// Main.c
//-----------------------------------------------------------------------------------------------------------
//
// Target: C8051F02x

//-----------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include "C8051F020.h"
#include "Declarations_GPIO_BSE.h"
#include "CFG_PCA0.h"
#include <stdio.h>
#include "intrins.h"

void CFG_Sysclk(void)					//Initialisation de l'horloge du systeme
{
    int i;
    OSCXCN = 0x67;						//On a des quartz de fréquence f>6.7Mhz
    for(i=0; i<3000; i++);		//Attente d'une 1ms minimum
    while((OSCXCN & 0x80)==0);//Attente de la stabilisation du quartz
    OSCICN = 0x08; 						//On réoriente l'horloge interne vers l'horloge externe.
}


void main(void)
{
	P1MDOUT   = 0x07;
	XBR0      = 0x1E;
	XBR1      = 0xAA;
	XBR2      = 0x4C;
	WDTCN     = 0xDE;						// Désactivation du Watchdog
	WDTCN     = 0xAD;
	CFG_Sysclk();
	Config_PCA0();
  CDE_Servo_V (30); 					// Sortie sur port 1.0
	CDE_Servo_H (30); 					// Sortie sur port 1.1
	while(1) {}
}
