/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque world.h qui fait la gestion des données de jeux
*/

#ifndef WORLD_H
#define  WORLD_H
#include"gestion_terrain.h"
#include"gestion_farmes.h"

struct sprite_s 
{
	farme_t farme;
	SDL_Texture* image;
	SDL_Rect SrcR_sprite;
	SDL_Rect DestR_sprite;
	int est_visible; // 1 si il est visble, 0 si il n'est pas visible
};
typedef struct sprite_s sprite_t;

struct  money_s
{
	sprite_t * pieces ; // tableau de sptrit
	int nbr_pieces; 
	int valeur;
};
typedef struct  money_s money_t;

struct ennemy_s 
{
	sprite_t *sprite; //tableau de sprite 
	int nbr_ennemies; //il est calculer en fonction dela distance du chemins
	int* aller_retour;//pour l'ennemy 0 pour le retour et 1 pour l'aller
	int* indice_chemin_actuel;// pour l'ennemmy  ;
 
};
typedef struct ennemy_s ennemy_t;

struct world_s 	
{	
	//int ligne,colonne;//nombre de ligne et de colonne de la matrice q'on va lire depuis de fichier .txt du terrain

	ennemy_t ennemies;
	money_t monnaie;
	sprite_t tresor; 
	bool terminer;
	terrain_t terrain;
	char ** tab; //la matrice de du jeux 
	sprite_t heros;	
	int score; //le score de la partie	
	int niveau;
	int colonne;
	int ligne;//nombre de ligne et de colonne de la matrice q'on va lire depuis de fichier .txt du terrain		

	///int niveau;		
};

typedef struct world_s world_t;

void init_sprite(sprite_t * sprite  , int h_terrain ,int w_terrain,int x,int y,int large_img,int haut_img,int nbr_img_horis,int nbr_img_vetic);
void init_ennemies(world_t *world);
void init_world(world_t *world, int niveau,int score);
void depacemnt_bordure(sprite_t* sprite,int Hauteur_ecran,int Largeur_ecran);
bool collision_murs(sprite_t sprite, terrain_t terrain, int ligne, int colonne);
bool collision(sprite_t* sprite_1,sprite_t* sprite_2); // pour la collision entre deux sprites 
void visible (sprite_t * sprite);// pour rendre le sprite visible 
void invisible (sprite_t * sprite); // pour rendre le sprite invisible 
void update_world(world_t *world);
void clean_world(world_t *world);

#endif 
