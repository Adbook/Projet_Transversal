//-------------------------------------------------------------------------------------
// CFG_PCA0.h
// Configuration et routine d'interruption du Timer0
//-------------------------------------------------------------------------------------
// AUTH: MIRABEL Clément
// DATE: 15/03/2016
// Dernière modification : 15/03/2016
//
// Target: C8051F02x
// Tool chain: KEIL eval 'c'
//
// Objectifs : - Configuration du PCA 0
//						 - Routine d'interruption du PCA 0
//						 - Envoi d'une impulsion de largeur variable sur une sortie
// 
// Broches utilisées : P1.4, P1.5
//
//
// Documents utiles : Extraits de la Datasheet du C8051F020

#ifndef CFG_PCA0
#define CFG_PCA0

void Config_PCA0(void);
unsigned char CDE_Servo_V (char Angle);
unsigned char CDE_Servo_H (char Angle);

#endif