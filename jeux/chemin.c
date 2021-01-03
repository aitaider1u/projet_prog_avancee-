#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<SDL2/SDL.h>

#include "headers/graphes2.h"
#include "headers/files.h"

/**
* Initialisation d'un graphe depuis une matrice de caractères
*@param g le graphe 
*@param tab la matrice de caractère 
*@param ligne le nombre de lignes de la matrice
*@param colonne le nombre de colonnes de la matrice 
*/
void init_graphe(Graphe g,char** tab,int ligne, int colonne) // depuis une matrice 
{
	int cpt = 0;
	for(int i = 0; i <ligne ; i++)
	{
		for (int j = 0; j <colonne ; j++)
		{
			if (tab[i][j] == '0' || tab[i][j] == 'p'|| tab[i][j] == 'd')
			{
				if(j-1>=0 && (tab[i][j-1]=='0' || tab[i][j-1]== 'p'|| tab[i][j] == 'd'))
				{
					ajouter_arete(g ,cpt,cpt-1);//   
												// pour faire un graphe orienté dans les deux sens
					ajouter_arete(g ,cpt-1,cpt);//
				}
				if(j+1<=colonne-1 && (tab[i][j+1]=='0' || tab[i][j+1]=='p'|| tab[i][j] == 'd'))
				{
					ajouter_arete(g ,cpt,cpt+1);
					ajouter_arete(g ,cpt+1,cpt);
				}
				if(i-1>=0 && (tab[i-1][j]=='0' || tab[i-1][j]=='p'|| tab[i][j] == 'd'))
				{
					ajouter_arete(g,cpt,cpt-colonne);
					ajouter_arete(g,cpt-colonne,cpt);
				}
				if(i+1<=ligne-1 && (tab[i+1][j]=='0' || tab[i+1][j]=='p'|| tab[i][j] == 'd'))
				{
					ajouter_arete(g,cpt,cpt+colonne);
					ajouter_arete(g,cpt+colonne,cpt);
				}
				//tab[i][j] = 'v';
			}
			cpt++;
		}
	}
}



/**
*Calcul du nombre de cases franchissables sur un terrain (éléments de chemin qui ne sont pas des murs)
*@param tab la matrice de caractères qui représente le terrain du jeu 
*@param ligne le lonbre de lignes de la matrice 
*@param colonne le nombre de colonnes de la matrice 
*@return le nombre de cases franchissables 
*/
int calcul_nbr_cases_chemain(char **tab,int ligne , int colonne)
{
	int cpt = 0;
	for(int i = 0; i <ligne ; i++)
	{
		for (int j = 0; j <colonne ; j++)
		{
			if(tab[i][j]=='0')
				cpt++;
		}
	}
	return cpt;
}


//pere = le tableau des pere 
//dist = le tableau de distance entre les sommet
//coul = la couleur 0 i il n'est pas visiter 1 si il est dans la file et 2 si il est visité
//sont tous des tableau deux dimension   

/**
*Parcours en largeur du graphe 
*@param g le graphe à parcourir 
*@param cpt le nombre de sommets 
*@param depart le sommet de départ 
*@return le tableau des pes pères et des distances du sommet de depart 
*/
int** parcours_en_largeur(Graphe g, int cpt, int depart)
{	
	File f=file_vide();
	if (nbr_voisin_listAdjacence(g,depart)>0)
		enfiler(f,depart);
	else
		{
			printf("le point de depart n'a pas de voisin donc il n'aura pas de chemin\n");
			return NULL;
		} 
	
	int* pere = malloc(cpt*sizeof(int));
	int* dist = malloc(cpt*sizeof(int));
	int* coul = malloc(cpt*sizeof(int));
	
	for(int i = 0; i < cpt ; i++)
	{
		if(nbr_voisin_listAdjacence(g,i)==0)
			coul[i]=2; // si un point na pas de voision il est considé comme visité deja  
		else
			coul[i]=0; // un sommet qui n'a pas encore été visiter 
		pere[i] = -1; // on sait pas encore le tableau des pere on l'initialise -1
		dist[i]=-1; // la distance pas defaut c'est plus l'infinit au depart 

	}
	dist[depart] =  0; // la distance entre le point de depart et le point de depart est 0	
	while(!est_vide_file(f))
	{
		int sommet1 = tete_file(f);
		Noeud* liste_voisin = g->Adjacence[sommet1].tete;
		while(liste_voisin != NULL)
		{
			int sommet2 = liste_voisin->valeur;
			if (coul[sommet2]== 0)
			{
				coul[sommet2]= 1;
				pere[sommet2] = sommet1;
				dist[sommet2]= 1 + dist[sommet1];
				enfiler(f,sommet2);
			}
			liste_voisin = liste_voisin->suivant;
		}
		defiler(f);
		coul[sommet1]= 2; 
	}
	int** tab = malloc(2*sizeof(int*));//pour retourner un le tableau dist et aussi pere pour pouvoir trouver le chemin dan la prochaine fonction
	tab[0] = pere;
	tab[1] = dist;
	free(coul);
	effacer_file(f);
	return tab;
}

/**
*Calcul de la distance entre le point de départ du graphe et le sommet le plus éloignée de ce point   
*@param g le graphe
*@param depart indice du point de depart 
*@param cpt le nombre de sommets 
*@return la distance entre le sommet de départ et le sommet le plus éloignée de celui ci
*/

int nbr_sommet_du_chemin( Graphe g,int depart,int cpt)
{
	int max = 0;
	int** tab = parcours_en_largeur(g,cpt,depart);		
	if(tab == NULL){
		printf("la distance maximal est 0 dans il n'a pas de chemin\n");
		return 0;
	}
	for(int i=0 ; i<cpt ; i++)
	{
		if (max<tab[1][i])
		{
			max = tab[1][i];
		}
	}
	for(int i = 0 ; i<2;i++)
	{
		free(tab[i]);
	}
	free(tab);
	return max;
}

/**
* Détermination du chemin optimal entre le sommet de départ et le sommet le plus éloignée de celui-ci
*@param g le graphe 
*@param depart le point depart 
*@param cpt le nombre de sommets
*@return le chemin optimal entre le départ et le sommet le plus éloignée
*/
int* chemin_le_plus_grand_train( Graphe g,int depart,int cpt)
{
	int max = 0;
	int sommet_max = depart;
	int** tab = parcours_en_largeur(g,cpt,depart);
	if(tab == NULL){
		printf("la distance maximal est 0 dans il n'a pas de chemin\n");
		return NULL;
	}
	for(int i=0 ; i<cpt ; i++)
	{
		if (max<tab[1][i])
		{
			max = tab[1][i];
			sommet_max = i;
		}
	}	
	int* chemin = malloc((max)*sizeof(int));
	int i = 0;	
	while(sommet_max != depart)
	{
		chemin[i] = sommet_max;
		sommet_max = tab[0][sommet_max];
		i++;
	}
	chemin[i] = depart;	
	for(int i = 0 ; i<2;i++)
	{
		free(tab[i]);
	}
	free(tab);
	return chemin;
}
