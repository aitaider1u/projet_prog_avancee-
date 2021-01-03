#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<SDL2/SDL.h>
#include"fonctions_fichiers.h"
#include"gestion_terrain.h"
#include"graphes2.h"
#include"chemin.h"
#include"constante.h"



/**
 *\Allocation de deux tableaux à 2 dimensions pour les deux champs de t    (DestR_terrain et SrcR_terrain) de taille ligne *colonne
 *\param t une variable de type terrain_t
 *\param ligne nombre de ligne du fichier qui a partir du quel on constuit le terrain
 *\param colonne nombre de colonnr du fichier qui a partir du quel on constuit le terrain
*/

void creer_SDL_Renderer_terrain(terrain_t *t,int ligne, int colonne)
{
	t->DestR_terrain = malloc(ligne*sizeof(SDL_Rect*));
	for (int i = 0; i < ligne; ++i)
	{
		t->DestR_terrain[i] = malloc(colonne*sizeof(SDL_Rect));
	}

	t->SrcR_terrain = malloc(ligne*sizeof(SDL_Rect*));
	for (int i = 0; i < ligne; ++i)
	{
		t->SrcR_terrain[i] = malloc(colonne*sizeof(SDL_Rect));
	}

}
/**
 *\Desallocation de deux tableaux 2 dimensions de deux champs de t (DestR_terrain et t.SrcR_terrain) de taille ligne *colonne
 *\param t une variable de type terrain_t
 *\param ligne nombre de ligne du fichier qui a partir du quel on constuit le terrain
*/

void desallouer_SDL_Renderer_terrain(terrain_t *t,int ligne)
{
	for (int i = 0; i < ligne; ++i)
	{
		free(t->DestR_terrain[i]);
	}
	free(t->DestR_terrain);
	for (int i = 0; i < ligne; ++i)
	{
		free(t->SrcR_terrain[i]);
	}
	free(t->SrcR_terrain);
	free(t->chemin.tab);

}
/**
 *\Initialisation de deux tableaux à 2 dimensions pour les deux champs de t    (DestR_terrain et SrcR_terrain) de taille ligne *colonne a partir de tab
 *\param t une variable de type terrain_t
 *\param ligne nombre de ligne du fichier qui a partir du quel on constuit le terrain
 *\param colonne nombre de colonne du fichier qui a partir du quel on constuit le terrain
 *\param tab  tableau a 2 dimensions qui qu'ona initialisé a partir de la leture depuis le fichier
*/

void init_terrain(terrain_t* t,int ligne,int colonne,char ** tab )
{
	creer_SDL_Renderer_terrain(t,ligne,colonne);
	for (int i = 0; i < ligne; i++)
	{
		for(int j=0; j<colonne; j++)
		{
			t->DestR_terrain[i][j].w = LARGEUR_TERRAIN_AFFICHAGE; // Largeur du sprite
			t->DestR_terrain[i][j].h = HAUTEUR_TERRAIN_AFFICHAGE; // Hauteur du sprite
			t->DestR_terrain[i][j].x = t->DestR_terrain[i][j].w*j;
			t->DestR_terrain[i][j].y = t->DestR_terrain[i][j].h *i; 
			
		}
	}

	for (int i = 0; i<ligne; i++)
	{
		for(int j=0; j<colonne; j++)
		{
			if (tab[i][j]== '0'  || tab[i][j] == 'p' || tab[i][j] == ' ' || tab[i][j] == 'd')
				t->SrcR_terrain[i][j].x = LARGEUR_TERRAIN_IMAGE*0;
			else if (tab[i][j]== '1')
				t->SrcR_terrain[i][j].x = LARGEUR_TERRAIN_IMAGE*1;
			else if (tab[i][j]== '2')
				t->SrcR_terrain[i][j].x = LARGEUR_TERRAIN_IMAGE*2;
			else if (tab[i][j]== '3')
				t->SrcR_terrain[i][j].x = LARGEUR_TERRAIN_IMAGE*3;
			else if (tab[i][j]== '4')
				t->SrcR_terrain[i][j].x = LARGEUR_TERRAIN_IMAGE*4;
			t->SrcR_terrain[i][j].y = 0;
			t->SrcR_terrain[i][j].w = LARGEUR_TERRAIN_IMAGE;
			t->SrcR_terrain[i][j].h = HAUTEUR_TERRAIN_IMAGE;
		}
	}
	
}

/**
 *\Initialisation de terrain avec chemin 
 *\param t une variable de type terrain_t
 *\param ligne nombre de ligne du fichier qui a partir du quel on constuit le terrain
 *\param colonne nombre de colonne du fichier qui a partir du quel on constuit le terrain
 *\param tab  tableau a 2 dimensions qui qu'ona initialisé a partir de la leture depuis le fichier
 *\param i c'est l'abscisse du heros
 *\param j c'est l'ordonnée du heros
*/


void init_terrain_avec_chemin(terrain_t* t,int ligne,int colonne,char ** tab ,int i , int j)
{
	
	Graphe g = allouer_graphe(ligne*colonne);
	init_graphe(g,tab,ligne,colonne);
	t->chemin.nbr_sommet = nbr_sommet_du_chemin(g,i*colonne+j,ligne*colonne);
	t->chemin.tab= chemin_le_plus_grand_train(g,i*colonne+j ,ligne*colonne);
	desallouer_graphe(g);
	for(int i = 1 ; i<t->chemin.nbr_sommet-1 ; i++)
	{
		int x = t->chemin.tab[i]/colonne;
		int y = t->chemin.tab[i]%colonne;
		t->SrcR_terrain[x][y].x = LARGEUR_TERRAIN_IMAGE*3;
		t->SrcR_terrain[x][y].y = 0;

	}
}
