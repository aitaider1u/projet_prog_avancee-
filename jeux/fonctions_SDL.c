/**
* \file  fonctios_SDL.c
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque d'fonctios_SDL . 
*/
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include"headers/fonctions_SDL.h"

/**
*Fonction d'initialisation de la SDL
*/
void init_SDL()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
	{
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return;
	}
}


/**
*Fonction de création d'une être 
*@param hauteur la hauteur de la fenêtre
*@param largeur la largeur de la fenêtre 
*@return la fenêtre 
*/
SDL_Window* creer_window(int hauteur,int largeur){

	SDL_Window *fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,hauteur,largeur,SDL_WINDOW_RESIZABLE);
	if(fenetre == NULL) // En cas d’erreur
	{
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
		return NULL;
	}
	return fenetre;
}


/**
     * Chargement d'une image sur un rendu
     * @param nomFichier le nom de l'image au format Bitmap à charger 
     * @param renderer le rendu 
     * @return une texture contenant l'image chargée
     */

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer)
{

	SDL_Surface *image =  SDL_LoadBMP(nomfichier);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer ,image);
	SDL_FreeSurface(image);
	if (texture != NULL) //si l'image est bien charger  elle renvoie la texture associé a l'image 
		return texture ;
	printf("l'image n'a pas été chargée ");
	return NULL ;
}
/**
	*Chargement d'une image transparente 
	*@param nomfichier le nom de l'image au format Bitmap à charger 
	*@param renderer le rendu
	*@param r le taux de rouge de la couleur à masquer
	*@param g le taux de vert de la couleur à masquer
	*@param b le taux de bleue de la couleur à masquer
	*@return l'image privée de la couleur souhaitée
	*/

SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;
	image = SDL_LoadBMP(nomfichier);
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format,r,g,b));
	texture = SDL_CreateTextureFromSurface(renderer ,image); 
	SDL_FreeSurface(image);
	return texture ;
}
/**
	*Affichage de texte sur le rendu 
	*@param message le message à afficher
	*@param renderer le rendu
	*@param font la police de charactère 
	*@param color couleur de la police
	*@return l'image privée de la couleur souhaitée
	*/
	
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color) 
{
	SDL_Texture *texture = NULL;
	SDL_Surface *texte;
	texte = TTF_RenderText_Solid(font,message,color);
	texture = SDL_CreateTextureFromSurface(renderer ,texte);
	SDL_FreeSurface(texte);
	return texture;
}


/**
 * \brief La fonction met le programme en pause pendant un laps de temps
 * \param time ce laps de temps en milliseconde
*/

void pause(int time){
    SDL_Delay(time);
}
