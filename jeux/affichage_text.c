/**
* \file  fonctios_SDL.c
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque d'fonctios_SDL . 
*/
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include"fonctions_SDL.h"
#include"affichage_text.h"

void init_text_SDL_Rect(text_t* text,int x,int y,int w,int h)
{
	text->DestR_text.x = x;
	text->DestR_text.y = y;
	text->DestR_text.w = w;
	text->DestR_text.h = h;
}

void init_text(text_t *txt,const char* text_afficher,SDL_Renderer* renderer,TTF_Font *font,int x,int y,int w,int h)
{
	SDL_Color color = {0,0,0,0}; 
	txt->text = charger_texte(text_afficher,renderer,font,color);
	init_text_SDL_Rect(txt,x,y,w,h);
}


