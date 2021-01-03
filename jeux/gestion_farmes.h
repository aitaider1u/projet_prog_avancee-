/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine 
* \Brief bibliotheque fonctios_SDL. 
*/

#include<SDL2/SDL.h>
#include <stdbool.h>
#ifndef  GESTION_FARMES_H
#define  GESTION_FARMES_H

struct  farme_s 
{
	bool stop; // pour arreter la boucle
	int cpt; //le numero de l'image actuel qu'on afffiche sur la ligne
	int dist; // est la distination 0 DOWN / 1 UP / 2 LEFT / 3 RIGHT.
	int temp;
};
typedef struct farme_s farme_t;



void init_farme(farme_t *frame);

void update_farmes(farme_t *farme,int nbr_image_horisental,int i, int temps) ;// elle va etre appliquer si on a changer destination  


#endif 