/**
* \file  fonctios_SDL.c
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque d'fonctios_SDL . 
*/
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include"fonctions_SDL.h"


#ifndef AFFICHAGE_TEXT_H
#define AFFICHAGE_TEXT_H


struct text_s
{
	SDL_Texture* text;
	SDL_Rect DestR_text;
};
typedef struct text_s text_t;

void init_text_SDL_Rect(text_t* text,int x,int y,int w,int h);

void init_text(text_t *txt,const char* text_afficher,SDL_Renderer* renderer,TTF_Font *font,int x,int y,int w,int h);
#endif 
