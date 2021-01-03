/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque fonctios_SDL. 
*/
#include<SDL2/SDL.h>
#include"chemin.h"
#ifndef FONCTIONS_TERRAIN_H
#define  FONCTIONS_TERRAIN_H

struct terrain_s 
{	
	chemin_t chemin;
	SDL_Texture* image;
	SDL_Rect** SrcR_terrain;
	SDL_Rect** DestR_terrain;
};
typedef struct terrain_s terrain_t;
void creer_SDL_Renderer_terrain(terrain_t *t,int ligne, int colonne);
void desallouer_SDL_Renderer_terrain(terrain_t *t,int ligne);
void init_terrain(terrain_t* t,int ligne,int colonne,char ** tab);
void init_terrain_avec_chemin(terrain_t* t,int ligne,int colonne,char ** tab ,int i , int j);
#endif 