#ifndef STRUCT_H
#define STRUCT_H
#define NB_PARAM_MAX 15
#define true 1
#define false 0

typedef enum Commande_generale {  DFWGSDFGFDGDSFGDSG  } Commande_generale;
typedef enum Commande_mouvement {ARRET, AVANCER, RECULER, ARRET_URGENCE, STOPPER, ROT_90_G, ROT_90_D, ROT_180_G, ROT_180_D, ROT_ANGLE  } Commande_mouvement;
typedef enum Commande_information {  SDFGHFSDGFDSGDSFG } Commande_information;



typedef struct Etat_commandes_recues{
	Commande_generale Etat_gen;
	Commande_mouvement Etat_mouv;
	Commande_information Etat_info;
	
	unsigned char vitesse;
	unsigned char pos_x, pox_y;
	int angle;
	
	
} Etat_commandes_recues;


typedef struct Param_commande{
	int nb;
	char *valeur;
} Param_commande;

typedef struct Commande{
	char * nom_commande;
	Param_commande  parametres[NB_PARAM_MAX];
	int nb_parametres;
} Commande;


#endif