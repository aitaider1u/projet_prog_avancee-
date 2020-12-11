#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"
#include"gestion_terrain.h"
#include"world.h"
#include"constante.h"
#include"gestion_farmes.h"



void init_sprite(sprite_t * sprite,int h_terrain,int w_terrain,int x,int y,int large_img,int haut_img,int nbr_img_horis,int nbr_img_vetic)
{
	sprite->DestR_sprite.x = x;
	sprite->DestR_sprite.y = y;
	sprite->DestR_sprite.h = h_terrain;	
	sprite->DestR_sprite.w = w_terrain;
	sprite->SrcR_sprite.x = 0;
	sprite->SrcR_sprite.y = 0;
	sprite->SrcR_sprite.w = large_img/ nbr_img_horis;	
	sprite->SrcR_sprite.h = haut_img / nbr_img_vetic;
	init_farme(&(sprite->farme));
	sprite->est_visible = 1;                                 
}

void init_pieces_money(world_t *world)
{
	File file = file_vide();
	world->monnaie.nbr_pieces = 0;
	for(int i = 0 ; i<world->ligne ; i++)
		for (int j = 0; j < world->colonne ; j++)
			if(world->tab[i][j]== 'p')
			{
				world->monnaie.nbr_pieces++;
				enfiler(file, world->colonne *i + j);
			}
	if (world->monnaie.nbr_pieces > 0)
		world->monnaie.pieces = malloc(world->monnaie.nbr_pieces*sizeof(sprite_t));
	for(int i= 0 ; i < world->monnaie.nbr_pieces; i++)
	{
		init_sprite(&(world->monnaie.pieces[i]),world->terrain.DestR_terrain[0][0].h,world->terrain.DestR_terrain[0][0].w,world->terrain.DestR_terrain[0][0].w*(tete_file(file)%world->colonne),world->terrain.DestR_terrain[0][0].h*(tete_file(file)/world->colonne),LARGEUR_IMAGE_PIECE,HAUTEUR_IMAGE_PIECE , 10 ,NBR_VERTIC_IMAGE_PIECE);
		defiler(file);
	}
	effacer_file(file);
}

void init_ennemies(world_t *world)
{
	world->ennemies.nbr_ennemies = (world->terrain.chemin.nbr_sommet-2)/6;
	if (world->ennemies.nbr_ennemies == 1 || world->ennemies.nbr_ennemies == 0){
		world->ennemies.sprite = malloc(world->ennemies.nbr_ennemies*sizeof(sprite_t));
		world->ennemies.aller_retour = malloc(world->ennemies.nbr_ennemies*sizeof(int));
		world->ennemies.indice_chemin_actuel = malloc(world->ennemies.nbr_ennemies*sizeof(int));
		world->ennemies.indice_chemin_actuel[0] = world->terrain.chemin.nbr_sommet/2 ;// pour l'ennemmy  ;
		world->ennemies.aller_retour[0] = 0;
		int y = world->terrain.DestR_terrain[0][0].h*(world->terrain.chemin.tab[world->ennemies.indice_chemin_actuel[0]]/world->colonne);//world->terrain.DestR_terrain[0][0].w * (world->terrain.chemin.tab[world->terrain.chemin.nbr_sommet/2]/world->colonne);
		int x = world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->ennemies.indice_chemin_actuel[0]]%world->colonne);//world->terrain.DestR_terrain[0][0].h * (world->terrain.chemin.tab[world->terrain.chemin.nbr_sommet/2]%world->colonne);
		init_sprite(&(world->ennemies.sprite[0]),world->terrain.DestR_terrain[0][0].h,world->terrain.DestR_terrain[0][0].w,x,y,LARGEUR_IMAGE_ENNEMY, HAUTEUR_IMAGE_ENNEMY,NBR_HORIS_IMAGE_ENNEMY, NBR_VERTIC_IMAGE_ENNEMY);
	}
	else if(world->ennemies.nbr_ennemies >= 2) 
	{
		world->ennemies.sprite = malloc(world->ennemies.nbr_ennemies*sizeof(sprite_t));
		world->ennemies.aller_retour = malloc(world->ennemies.nbr_ennemies*sizeof(int));
		world->ennemies.indice_chemin_actuel = malloc(world->ennemies.nbr_ennemies*sizeof(int));
		
		for (int i = 0 ; i<world->ennemies.nbr_ennemies;i++){
			world->ennemies.indice_chemin_actuel[i] = 6*(i+1); // pour l'ennemmy  ;
			world->ennemies.aller_retour[i] = 0;
			int y = world->terrain.DestR_terrain[0][0].h*(world->terrain.chemin.tab[world->ennemies.indice_chemin_actuel[i]]/world->colonne);//world->terrain.DestR_terrain[0][0].w * (world->terrain.chemin.tab[world->terrain.chemin.nbr_sommet/2]/world->colonne);
			int x = world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->ennemies.indice_chemin_actuel[i]]%world->colonne);//world->terrain.DestR_terrain[0][0].h * (world->terrain.chemin.tab[world->terrain.chemin.nbr_sommet/2]%world->colonne);
			init_sprite(&(world->ennemies.sprite[i]),world->terrain.DestR_terrain[0][0].h,world->terrain.DestR_terrain[0][0].w,x,y,LARGEUR_IMAGE_ENNEMY,HAUTEUR_IMAGE_ENNEMY,NBR_HORIS_IMAGE_ENNEMY, NBR_VERTIC_IMAGE_ENNEMY);
		}
	}
} 

void init_world(world_t *world)
{
	world->terminer = false ;
	world->score = 0; 
	taille_fichier("terrain.txt",&(world->ligne),&(world->colonne));
	world->tab = lire_fichier("terrain.txt");
	init_terrain(&(world->terrain),world->ligne,world->colonne,world->tab);
	init_sprite(&(world->heros),world->terrain.DestR_terrain[0][0].h,world->terrain.DestR_terrain[0][0].w,0,0,LARGEUR_IMAGE_HEROS, HAUTEUR_IMAGE_HEROS,NBR_HORIS_IMAGE_HEROS , NBR_VERTIC_IMAGE_HEROS);
	init_terrain_avec_chemin(&(world->terrain),world->ligne,world->colonne ,world->tab,world->heros.DestR_sprite.x ,world->heros.DestR_sprite.y);
	init_ennemies(world);	
	int y = (world->terrain.chemin.tab[0]/world->colonne)*world->terrain.DestR_terrain[0][0].h;
	int x = (world->terrain.chemin.tab[0]%world->colonne)*world->terrain.DestR_terrain[0][0].w;
	init_sprite(&(world->tresor),world->terrain.DestR_terrain[0][0].h,world->terrain.DestR_terrain[0][0].w,x,y,LARGEUR_IMAGE_TRESOR, HAUTEUR_IMAGE_TRESOR,4 , 1);
	init_pieces_money(world);
}

void depacemnt_bordure(sprite_t* sprite,int Hauteur_ecran,int Largeur_ecran)
{

	if(sprite->DestR_sprite.x < 0)
		sprite->DestR_sprite.x = 0;
	if( sprite->DestR_sprite.x > Largeur_ecran-sprite->DestR_sprite.w)
		sprite->DestR_sprite.x = Largeur_ecran-sprite->DestR_sprite.w ;
	if (sprite->DestR_sprite.y<0)
		sprite->DestR_sprite.y = 0;
	if  (sprite->DestR_sprite.y> Hauteur_ecran-sprite->DestR_sprite.h)
		sprite->DestR_sprite.y = Hauteur_ecran-sprite->DestR_sprite.h;
}


bool collision_murs(sprite_t sprite, terrain_t terrain, int ligne, int colonne)
{
	int x1,x2,y1,y2;
	x1 = sprite.DestR_sprite.x + sprite.DestR_sprite.w/2;//l'abcsice du centre du sprite
	y1 = sprite.DestR_sprite.y + sprite.DestR_sprite.h/2;//l'ordonnée du centre du sprite
	for (int i = 0; i < ligne; ++i)
	{
		for (int j = 0; j < colonne; ++j)
		{
			if (terrain.SrcR_terrain[i][j].x !=0 || terrain.SrcR_terrain[i][j].y != 0 ) 
			 	if (terrain.SrcR_terrain[i][j].x != 32*3 || terrain.SrcR_terrain[i][j].y != 0 ) // differente de la terre
				{
					x2 = terrain.DestR_terrain[i][j].x + terrain.DestR_terrain[i][j].w/2; // l'abscice du centre du du mur(i,j) 
					y2 = terrain.DestR_terrain[i][j].y + terrain.DestR_terrain[i][j].h/2; // l'ordonnée du centre du du mur(i,j) 
					if (abs(x1-x2) < (sprite.DestR_sprite.w + terrain.DestR_terrain[i][j].w)/2)
						if (abs(y1-y2) < (sprite.DestR_sprite.h + terrain.DestR_terrain[i][j].h)/2)
							return true;
				}
		}
	}
	return false;	
}

void visible (sprite_t * sprite)
{
	sprite->est_visible = 1;
}

void invisible (sprite_t * sprite)
{
	sprite->est_visible = 0;
}

bool collision(sprite_t *sprite_1,sprite_t *sprite_2 )
{
	int x1,x2,y1,y2;
	x1 = sprite_1->DestR_sprite.x;
	x2 = sprite_2->DestR_sprite.x;
	y1 = sprite_1->DestR_sprite.y;
	y2 = sprite_2->DestR_sprite.y;
	if (abs(x1-x2) < (sprite_1->DestR_sprite.w +sprite_2->DestR_sprite.w)/4)
		if (abs(y1-y2) < (sprite_1->DestR_sprite.h + sprite_2->DestR_sprite.h)/4)
			return true;
	return false;
}



void demarche_ennemies(world_t *world)
{
	int x_prochain; // c'est pour trouver les cordoner du prchainn 
	int y_prochain; //
	for(int i = 0; i <world->ennemies.nbr_ennemies;i++){
		if(world->ennemies.sprite[i].est_visible == 1){ 
			if (world->ennemies.aller_retour[i] == 0)
			{
				y_prochain = world->terrain.DestR_terrain[0][0].h*(world->terrain.chemin.tab[world->ennemies.indice_chemin_actuel[i]-1]/world->colonne);
				x_prochain = world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->ennemies.indice_chemin_actuel[i]-1]%world->colonne);

				if (y_prochain != world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[0]/ world->colonne) ||  x_prochain != world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[0] % world->colonne))
				  {
					if(y_prochain != world->ennemies.sprite[i].DestR_sprite.y)
					{
							if(y_prochain>world->ennemies.sprite[i].DestR_sprite.y)
							{
								world->ennemies.sprite[i].DestR_sprite.y++;
								update_farmes(&(world->ennemies.sprite[i].farme),NBR_HORIS_IMAGE_HEROS,1,5);// 
								world->ennemies.sprite[i].SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemies.sprite[i].farme.cpt;
								world->ennemies.sprite[i].SrcR_sprite.y = 0;

							}
							else if (y_prochain<world->ennemies.sprite[i].DestR_sprite.y)
							{
								world->ennemies.sprite[i].DestR_sprite.y--;
								update_farmes(&(world->ennemies.sprite[i].farme),NBR_HORIS_IMAGE_HEROS,0,5);// 
								world->ennemies.sprite[i].SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemies.sprite[i].farme.cpt;
								world->ennemies.sprite[i].SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-world->heros.SrcR_sprite.w;
							}
					}
					else if (x_prochain != world->ennemies.sprite[i].DestR_sprite.x)
					{
							if(x_prochain>world->ennemies.sprite[i].DestR_sprite.x)
							{
								world->ennemies.sprite[i].DestR_sprite.x++;
								update_farmes(&(world->ennemies.sprite[i].farme),NBR_HORIS_IMAGE_HEROS,3,5);// 
								world->ennemies.sprite[i].SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemies.sprite[i].farme.cpt;
								world->ennemies.sprite[i].SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-2*world->heros.SrcR_sprite.w ;
							}
							else if (x_prochain<world->ennemies.sprite[i].DestR_sprite.x)
							{
								world->ennemies.sprite[i].DestR_sprite.x--;
								update_farmes(&(world->ennemies.sprite[i].farme),NBR_HORIS_IMAGE_HEROS,2,5);// 
								world->ennemies.sprite[i].SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemies.sprite[i].farme.cpt;
								world->ennemies.sprite[i].SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-3*world->heros.SrcR_sprite.w ;
							}
					}
					if(y_prochain == world->ennemies.sprite[i].DestR_sprite.y && x_prochain == world->ennemies.sprite[i].DestR_sprite.x )
						world->ennemies.indice_chemin_actuel[i] = world->ennemies.indice_chemin_actuel[i]-1;
				}
				else 
				{
					world->ennemies.indice_chemin_actuel[i] = 1;
					world->ennemies.aller_retour[i] = 1;
				}
			}else if (world->ennemies.aller_retour[i] == 1)	
			{
				y_prochain = world->terrain.DestR_terrain[0][0].h*(world->terrain.chemin.tab[world->ennemies.indice_chemin_actuel[i]+1]/world->colonne);
				x_prochain = world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->ennemies.indice_chemin_actuel[i]+1]%world->colonne);

				if (y_prochain != world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->terrain.chemin.nbr_sommet-1]/ world->colonne) ||  x_prochain != world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->terrain.chemin.nbr_sommet-1] % world->colonne))
				{
					if(y_prochain != world->ennemies.sprite[i].DestR_sprite.y)
					{
							if(y_prochain>world->ennemies.sprite[i].DestR_sprite.y)
							{
								world->ennemies.sprite[i].DestR_sprite.y++;
								update_farmes(&(world->ennemies.sprite[i].farme),NBR_HORIS_IMAGE_HEROS,1,5);// 
								world->ennemies.sprite[i].SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemies.sprite[i].farme.cpt;
								world->ennemies.sprite[i].SrcR_sprite.y = 0;
							}
							else if (y_prochain<world->ennemies.sprite[i].DestR_sprite.y)
							{
								world->ennemies.sprite[i].DestR_sprite.y--;
								update_farmes(&(world->ennemies.sprite[i].farme),NBR_HORIS_IMAGE_HEROS,0,5);// 
								world->ennemies.sprite[i].SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemies.sprite[i].farme.cpt;
								world->ennemies.sprite[i].SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-world->heros.SrcR_sprite.w;
							}
					}
					else if (x_prochain != world->ennemies.sprite[i].DestR_sprite.x)
					{
						if(x_prochain>world->ennemies.sprite[i].DestR_sprite.x)
						{
							world->ennemies.sprite[i].DestR_sprite.x++;
							update_farmes(&(world->ennemies.sprite[i].farme),NBR_HORIS_IMAGE_HEROS,3,5);// 
							world->ennemies.sprite[i].SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemies.sprite[i].farme.cpt;
							world->ennemies.sprite[i].SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-2*world->heros.SrcR_sprite.w ;
						}
						else if (x_prochain<world->ennemies.sprite[i].DestR_sprite.x){
							world->ennemies.sprite[i].DestR_sprite.x--;
							update_farmes(&(world->ennemies.sprite[i].farme),NBR_HORIS_IMAGE_HEROS,2,5);// 
							world->ennemies.sprite[i].SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemies.sprite[i].farme.cpt;
							world->ennemies.sprite[i].SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-3*world->heros.SrcR_sprite.w ;
						}
					}
					if(y_prochain == world->ennemies.sprite[i].DestR_sprite.y && x_prochain == world->ennemies.sprite[i].DestR_sprite.x )
						world->ennemies.indice_chemin_actuel[i] = world->ennemies.indice_chemin_actuel[i]+1;
				}
				else 
				{
					world->ennemies.indice_chemin_actuel[i] = world->terrain.chemin.nbr_sommet-1;
					world->ennemies.aller_retour[i] = 0;
				}
			}
		}
	}
}

void update_world(world_t *world)
{
	depacemnt_bordure(&(world->heros),world->colonne*40,world->ligne*40);
	if(!collision(&(world->heros),&(world->tresor)) && world->heros.est_visible == 1){
		for(int i = 0 ; i<world->ennemies.nbr_ennemies;i++){
			if (collision(&(world->heros),&(world->ennemies.sprite[i])) && world->heros.est_visible == 1)
			{
				invisible(&(world->heros));
				invisible (&(world->ennemies.sprite[i]));
			}
		}
		demarche_ennemies(world);
	}
	for(int i = 0 ; i<world->monnaie.nbr_pieces ;i++){
			if (collision(&(world->heros),&(world->monnaie.pieces[i])) && world->heros.est_visible == 1  && 1 == world->monnaie.pieces[i].est_visible)
			{
				invisible (&(world->monnaie.pieces[i]));
				world->score = world->score + VALEUR_PIECE_MONEY ;			
			}
		}

}

void clean_world(world_t *world)
{
	free(world->ennemies.sprite);
	free(world->monnaie.pieces);
	free(world->ennemies.aller_retour);
	free(world->ennemies.indice_chemin_actuel);
	desallouer_tab_2D(world->tab,world->ligne);
	desallouer_SDL_Renderer_terrain(&(world->terrain),world->ligne);
}


