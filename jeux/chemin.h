/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque chemin.  
*/
#include<SDL2/SDL.h>
#ifndef CHEMIN_H
#define  CHEMIN_H

#include "graphes2.h"
#include "files.h"

struct chemin_s 
{
	int nbr_sommet;
	int* tab;
};
typedef struct chemin_s chemin_t;


void init_graphe(Graphe g,char** tab,int ligne, int colonne);
int calcul_nbr_cases_chemain(char **tab,int ligne , int colonne);
int** parcours_en_largeur(Graphe g, int cpt, int depart);

//int** chemin_le_plus_grand_train(int depart,int cpt,char** terrain,int ligne, int colonn, int depart )//la fonction renvoie le chemin et la taile du tableur du chemin 
int nbr_sommet_du_chemin( Graphe g,int depart,int cpt);
int* chemin_le_plus_grand_train( Graphe g,int depart,int cpt);


#endif 