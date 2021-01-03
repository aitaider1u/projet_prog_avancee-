/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque graphic.h qui fait gestion de l'affichage dans le jeux  
*/
#ifndef JEU_H
#define  JEU_H

#include<SDL2/SDL.h>
#include"fonctions_SDL.h"
#include<stdbool.h>
#include"world.h"
#include"message.h"

struct image_s
{
	SDL_Texture* image;
	SDL_Rect SrcR_image;
	SDL_Rect DestR_image;

};
typedef struct image_s image_t;

struct jeu_s
{
	bool start;
	bool score;
	bool Quit;
	image_t background;
	image_t background2;
	image_t image_start;
	image_t image_score;
	image_t image_quit;	
	int *tab_score;
	image_t home;
	image_t replay;
};
typedef struct jeu_s jeu_t;

void init_XYWH(SDL_Rect *rect,int x,int y,int w,int h);
void init_jeux(jeu_t *jeu);
void update_best_score(const char* nomFichier,int *tab ,int score);
void clean_jeu(jeu_t *jeu);

#endif 
