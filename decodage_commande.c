#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <intrins.h>
#include "serial_io.h"
#include <c8051f020.h>

#include "decodage_commande.h"

xdata char jetons[NB_PARAM_MAX+1][10];
xdata Commande c;
void diviser_chaine(char *commande){

	char *tok = 1;
	int i = 0;
	tok = strtok(commande, " \r");
	
	while(tok != NULL){
		strcpy(jetons[i],tok);
		tok = strtok(NULL, " \r");
		i++;
		if(i >= 9)
			break;//erreur: trop de parametres (max: 30)
	}
}

char valider_commande(char **jetons, int nb_jetons){

	int taille_dernier_jeton = strlen(jetons[nb_jetons-1]);
	char test = jetons[nb_jetons-1][taille_dernier_jeton-1];
	EA = 1;
	if(jetons[nb_jetons-1][taille_dernier_jeton-1] != '\r')
		return false;
	
	return true;
	
	
}




void decoder_commande(char *commande){
	int nb_jetons = 0;
	int i = 0;
	char ret;
	
	for(i = 0; i < NB_PARAM_MAX + 1; i++){
		jetons[i][0] = '\0';
	}
	
	diviser_chaine(commande);
	
	while(jetons[nb_jetons][0] != '\0' && jetons[nb_jetons][0] != '\r') //comptage du nombre de jetons
		nb_jetons++;
	
	ret = valider_commande(jetons, nb_jetons);
	
	
	c.nom_commande = jetons[0];
	
	//DEBUG
	/*serOutstring("nom_commande:\n");
	serOutstring(c.nom_commande);
	serOutstring("\n");
	serOutstring("nom_param:\n");*/
	
	c.nb_parametres = nb_jetons - 1;
	
	
	
	
	
	for(i = 1; i < nb_jetons; i++){
		
		//DEBUG
		/*serOutstring(jetons[i]);
		serOutstring("\n");*/
		
		c.parametres[i-1].valeur = jetons[i];
		c.parametres[i-1].nb = i-1;
	}
	
	traitement_nom_commande(&c);
	
}

void traitement_nom_commande(Commande *c2)
{
	
	xdata char *nom = c.nom_commande;
	Commande_generale general;
	Commande_mouvement mouv;// {ARRET, AVANCER, RECULER, ARRET_URGENCE, STOPPER, ROT_90_G, ROT_90_D, ROT_180_G, ROT_180_D, ROT_ANGLE  } Commande_mouvement;
	Commande_information info;
	xdata unsigned int i = 0;

	
	if(strcmp(nom, "D") == 0){ //debut de l'epreuve
		char* test = c.parametres[1].valeur;
		
	}else if(strcmp(nom, "E") == 0){ //fin de l'epreuve
		
	}else if(strcmp(nom, "Q") == 0){ //arret d'urgence
		
	}else if(strcmp(nom, "TV") == 0){ //vitesse
		
	}else if(strcmp(nom, "A") == 0){ //avancer
		Send_String("mogo test test test\r\n");
	}else if(strcmp(nom, "B") == 0){ //reculer
		
	}else if(strcmp(nom, "S") == 0){ //stop
		
	}else if(strcmp(nom, "RD") == 0){ //rota droite 90
		Send_String("mogo 1:45\r\n");
	}else if(strcmp(nom, "RG") == 0){ //rota gauche 90
		
	}else if(strcmp(nom, "RC") == 0){ //rota 180
		
	}else if(strcmp(nom, "RA") == 0){ //rota angle
		i = 1;
	}else if(strcmp(nom, "G") == 0){ //deplacement de la base roulante par coordonnees
		
	}else if(strcmp(nom, "ASS") == 0){ //Acquisition signaux sonores
		
	}else if(strcmp(nom, "MI") == 0){ //mesure courant
		
	}else if(strcmp(nom, "ME") == 0){ //mesure energie
		
	}else if(strcmp(nom, "IPO") == 0){ //initialisation de la position de la base roulante
		
	}else if(strcmp(nom, "POS") == 0){ //position de la base roulante
		
	}else if(strcmp(nom, "MOU") == 0){ //detection d'obstacle unique
		
	}else if(strcmp(nom, "MOB") == 0){ //detection d'obstacle par balayage
		
	}else if(strcmp(nom, "SD") == 0){ //generation de signaux sonore
		
	}else if(strcmp(nom, "L") == 0){ //allumage du pointeur lumineux
	
	} else if(strcmp(nom, "LS") == 0){ //fin de l'allumage du pointeur lumineux
		
	}else if(strcmp(nom, "CS") == 0){ //pilotage de servomoteur
		
	}else if(strcmp(nom, "PPH") == 0){ //prise de photo
		
	}else if(strcmp(nom, "SPH") == 0){ //fin prise de photo en continu
		
	}else if(strcmp(nom, "AUX") == 0){
		
	}else{ //commande non supportée
		i = 1;
		serOutchar('#');
	}
	
	
	if(i == 0)serOutchar('\r');
	if(i == 0)serOutchar('>');
}