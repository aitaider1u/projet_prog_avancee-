/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque graphic.h qui fait gestion de l'affichage dans le jeux  
*/
#ifndef GRAPHIC_H
#define  GRAPHIC_H

#include<SDL2/SDL.h>
#include "fonctions_SDL.h"
#include "world.h"
#include "message.h"
#include"jeu.h"


void init_textures(jeu_t *jeu,world_t *world,SDL_Renderer * renderer);
void handle_events(jeu_t *jeu,world_t *world,SDL_Event *evenements,SDL_Renderer * renderer,TTF_Font *font,message_t *msg);
void refresh_graphic(jeu_t *jeu,world_t *world,SDL_Renderer * renderer,TTF_Font *font,message_t *msg);
void clear_textures(jeu_t *jeu,world_t *world);




#endif 