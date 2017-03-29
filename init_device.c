#define SYSCLK 22118400
#define BAUDRATE 19200

#include "init_device.h"
#include <c8051f020.h> 

void init_device(){	
	P0MDOUT = 0xC1;
	XBR0 = 0x06;
	XBR1 = 0xF8;
	XBR2 = 0x44;
	
	Config_Watchdog();
	Oscillator_Init();
	//CFG_Clock_UART0();
	CFG_UART0();
	CFG_UART1();

}
/*void UART0_ISR() interrupt 4{
	EA = 0;
	/*if(TI0 == 1)
	{
		
		TI0 = 0;
	}else if(RI0 == 0){
		
		
	}
	*/
	
	/*EA = 1;
}*/

void Oscillator_Init(){
	int i = 0;
	OSCXCN = 0x65;
	for(i = 0; i < 3000; i++);
	while((OSCXCN & 0x80) == 0);
	OSCICN = 0x0C;
}


void Config_Watchdog(){
	WDTCN = 0xDE;
	WDTCN = 0xAD;
}

void CFG_Clock_UART0(){
	CKCON |= 0x10;
	TMOD |= 0x20;
	TMOD &= 0x2F;
	TF1 = 0;
	TH1 = - (SYSCLK / (BAUDRATE *  16)); //th1 reload value
	
	TR1 = 1; //Timer 1 démarré
	EA = 1;
	
}
void CFG_UART0(){
	/*RCLK0 = 0; //set source clock: timer 1
	TCLK0 = 0;
	PCON |= 0x80; //Baud rate doubler disabled
	PCON &= 0xBF; //SSTAT0 = 0 (Frame error detection off)
	SCON0 = 0x70; // Mode 1: 8-Bit UART, Variable Baud Rate --- user software writes data to the SBUF0 register while a transmit is in progress --- réception activée
	TI0 = 1; // clear du flag de transmission
	ES0 = 1; //activation interruption UART0;*/
	
	/* A REPRENDRE */
	TF1 =0; //flag désactivé
	SCON0 = 0x50; // UART mode 1, 8-bit UART, enable RX
	TMOD = 0x20; // TMOD: timer 1, mode 2, 8-bit reload
	TH1 = -(SYSCLK/BAUDRATE/16); // set Timer1 reload value for baudrate
	TL1 = TH1; // set Timer1 initial value
	CKCON |= 0x10; // Timer1 uses SYSCLK as time base
	TR1 = 1; // start Timer1
	ES0 = 1; // enable UART0 interrupts
	
	//CFG_Clock_UART0
	RCLK0 =0;   //T2CON source CLK timer1
    TCLK0 =0;   //T2CON
    PCON |=0x80;    //SMOD0
    PCON &=0xBF;    //SSTAT0=0
    SCON0 =0x72;    //mode 1 : check stop bit - reception validée
}
void CFG_UART1(){
/*	
	T4CON &= 0xCF; // Timer 1 overflows used for transmit/receive clock.
	PCON |= 0x10; //SMOD1: UART1 Baud Rate Doubler Enable. (désactivé)
	PCON &= 0xF7; //SSTAT1: Reads/writes of SM21-SM01 access the SM21-SM01 UART1 mode setting.
	SCON1 = 0x70; //Mode 1: 8-Bit UART, Variable Baud Rate ---
    
*/
	SCON1 = 0x50; // SCON1: mode 1, 8-bit UART, enable RX
	TMOD = 0x20; // TMOD: timer 1, mode 2, 8-bit reload
	TH1 = -(SYSCLK/BAUDRATE/16); // set Timer1 reload value for baudrate
	CKCON |= 0x10; // Timer1 uses SYSCLK as time base
	PCON |= 0x10; // SMOD1 = 1
	TR1 = 1; // start Timer1
	EIE2 |= 0x40; // enable UART1 interrupts

}