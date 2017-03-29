#ifndef DECODAGE_COMMANDE_H
#define DECODAGE_COMMANDE_H
#include "UART0_RingBuffer_lib.h"

char valider_commande(char **jetons, int nb_jetons);
	
void decoder_commande(char *commande);

void traitement_nom_commande(Commande *c);
#endif