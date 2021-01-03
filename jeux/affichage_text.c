/**
* \file  fonctios_SDL.c
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque d'fonctios_SDL . 
*/
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include"headers/fonctions_SDL.h"
#include"headers/affichage_text.h"

/**
*Initialisation du rectangle qui accueillira le texte 
*@param text le texte a afficher
*@param x abcisse du point de création du rectangle 
*@param y ordonnée du point de création du rectangle 
*@param w largeur du rectangle 
*@param h hauteur du rectangle
*/
void init_text_SDL_Rect(text_t* text,int x,int y,int w,int h)
{
	text->DestR_text.x = x;
	text->DestR_text.y = y;
	text->DestR_text.w = w;
	text->DestR_text.h = h;
}


/**
* Initialisation du texte à afficher  
*@param txt la structure du texte
*@param text_afficher le texte  àafficher 
*@param renderer le rendu 
*@param font la police d'affichage
*@param x l'abcisse du rectangle de destination de l'affichage  
*@param y l'ordonnée du rectangle de destination de l'affichage 
*@param w la largeur du rectangle de destination de l'affichage  
*@param h la hauteur du rectangle de destination de l'affichage 

*/
void init_text(text_t *txt,const char* text_afficher,SDL_Renderer* renderer,TTF_Font *font,int x,int y,int w,int h)
{
	SDL_Color color = {0,0,0,0}; 
	txt->text = charger_texte(text_afficher,renderer,font,color);
	init_text_SDL_Rect(txt,x,y,w,h);
}


