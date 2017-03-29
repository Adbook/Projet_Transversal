//-------------------------------------------------------------------------------------
// Configuration et routine d'interruption du PCA0
//-------------------------------------------------------------------------------------
//
// Target: C8051F02x
//
// Objectifs : - Configuration du PCA 0
//						 - Routine d'interruption du PCA 0
//						 - Envoi d'une impulsion de largeur variable sur une sortie
// 
// Broches utilisées : P1.0, P1.1

//-----------------------------------------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------------------------------------
#include "c8051F020.h"
#include "Declarations_GPIO_BSE.h"
#include "CFG_PCA0.h"
#include <stdio.h>
#include <math.h>


//-----------------------------------------------------------------------------------------------------------
// Variables globales
//-----------------------------------------------------------------------------------------------------------
char Angle_actuel_H;
char Angle_actuel_V;

void Config_PCA0(void)
{
		long int Temps_angle;
		// Choix de l'horloge - SYSCLK pour un cycle de 11,852 ms
		PCA0MD |= 0x02;
		PCA0MD &= ~0x0C;
		
	
		// Mode PWM 16-bit
		PCA0CPM0=0xC2;
		PCA0CPM1=0xC2;
	
	
		// Définition du rapport cyclique
		Temps_angle=1500;
		PCA0CPH0 = ((100-(Temps_angle*100))/11851)*65536/100>>8; // Sortie sur port 1.0
		PCA0CPH1 = ((100-(Temps_angle*100))/11851)*65536/100>>8; // Sortie sur port 1.1

		// Lance le comptage du PCA0
		PCA0CN |= 0x40;
}

unsigned char CDE_Servo_V (char Angle) //pour l’axe vertical 
{
	long int Temps_angle;
	long int Temps_estime;
	
	if(Angle >= 90){
		Angle = 90;
	}
	if(Angle <= -90){
		Angle = -90;
	}
	
	Temps_angle=600+(Angle+90)*10;  // Temps en µs - Temps min : 600 µs - Temps max : 2400 µs
	
	// Calcul de la valeur de rechargement pour le PWM
	// Duty_cycle=Temps_angle/11851 avec 11851 le temps en ms d'une période
	// On multiplie par 100 pour le domaine du rapport cyclique
	// On multiplie par 65536 pour passer dans la base 16-bits
	// On divise par 100 pour avoir une valeur fidèle
	
	PCA0CPH0 = ((100-(Temps_angle*100))/11851)*65536/100>>8;
	
	// Calcul du temps estimé pour faire la rotation	
	Temps_estime=abs(Angle_actuel_V-Angle)*22/60;
	
	// Redéfinition de l'angle actuel
	Angle_actuel_V=Angle;
	
	return Temps_estime;
}

unsigned char CDE_Servo_H (char Angle) //pour l’axe horizontal 
{
	long int Temps_angle;
	long int Temps_estime;
	
	if(Angle >= 90){
		Angle = 90;
	}
	if(Angle <= -90){
		Angle = -90;
	}
	
	Temps_angle=600+(Angle+90)*10; // Temps en µs - Temps min : 600 µs - Temps max : 2400 µs
	
	// Calcul de la valeur de rechargement pour le PWM
	// Duty_cycle=Temps_angle/11851 avec 11851 le temps en ms d'une période
	// On multiplie par 100 pour le domaine du rapport cyclique
	// On multiplie par 65536 pour passer dans la base 16-bits
	// On divise par 100 pour avoir une valeur fidèle
	
	PCA0CPH1 = ((100-(Temps_angle*100))/11851)*65536/100>>8; 
	
	// Calcul du temps estimé pour faire la rotation
	Temps_estime=abs(Angle_actuel_H-Angle)*22/60; 
	
	// Redéfinition de l'angle actuel
	Angle_actuel_H=Angle;
	
	return Temps_estime;
}
