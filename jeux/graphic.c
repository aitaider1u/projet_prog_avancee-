#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include"world.h"
#include"constante.h"
#include<SDL2/SDL.h>
#include "message.h"
#include"jeu.h"

void init_textures(jeu_t *jeu,world_t *world,SDL_Renderer * renderer)
{
	Uint8 r = 0, g = 255, b = 255;
	world->terrain.image = charger_image_transparente("./ressource/image/pavage.bmp", renderer,r,g,b);
	world->heros.image = charger_image_transparente("./ressource/image/sprite.bmp", renderer,r,g,b);
	r = 255, g = 255, b = 255;
	world->tresor.image = charger_image_transparente("./ressource/image/tresor.bmp", renderer,r,g,b);
	for(int i = 0; i< world->ennemies.nbr_ennemies; i++)
	{
		world->ennemies.sprite[i].image = charger_image_transparente("./ressource/image/ennemy.bmp", renderer,r,g,b);
	}
	for(int i = 0; i< world->monnaie.nbr_pieces; i++)
	{
		world->monnaie.pieces[i].image = charger_image_transparente("./ressource/image/piece.bmp", renderer,r,g,b);
	}
	jeu->background.image = charger_image_transparente("./ressource/image/background.bmp", renderer,r,g,b);
 	jeu->background2.image = charger_image ("./ressource/image/background2.bmp",renderer);
	jeu->image_start.image = charger_image ("./ressource/image/start.bmp",renderer);
	jeu->image_score.image = charger_image ("./ressource/image/score.bmp",renderer);
	jeu->image_quit.image = charger_image ("./ressource/image/quit.bmp",renderer);
	jeu->home.image = charger_image ("./ressource/image/home.bmp",renderer);
	jeu->replay.image = charger_image ("./ressource/image/replay.bmp",renderer);
}

void clear_textures(jeu_t *jeu,world_t *world)
{
	SDL_DestroyTexture(world->terrain.image);
	SDL_DestroyTexture(world->heros.image);
	for(int i = 0; i< world->ennemies.nbr_ennemies; i++)
	{
		SDL_DestroyTexture(world->ennemies.sprite[i].image);
	}
	for(int i = 0; i< world->monnaie.nbr_pieces; i++)
	{
		SDL_DestroyTexture(world->monnaie.pieces[i].image);
	}
	SDL_DestroyTexture(world->tresor.image);
	SDL_DestroyTexture(jeu->background.image);
	SDL_DestroyTexture(jeu->background2.image);
	SDL_DestroyTexture(jeu->image_start.image);
	SDL_DestroyTexture(jeu->image_score.image);
	SDL_DestroyTexture(jeu->image_quit.image);
	SDL_DestroyTexture(jeu->home.image);
	SDL_DestroyTexture(jeu->replay.image);

}

void handle_events(jeu_t *jeu,world_t *world ,SDL_Event *evenements, SDL_Renderer * renderer,TTF_Font *font,message_t *msg)
{
	while( SDL_PollEvent( evenements ) )
			switch(evenements->type)
			{
				case SDL_QUIT:
					world->terminer = true; break;
				case SDL_KEYDOWN:                                                      
					switch(evenements->key.keysym.sym)
					{
						case SDLK_ESCAPE:
						case SDLK_q:
							world->terminer = true;  break;
						case SDLK_UP:
							if (world->heros.est_visible == 1 && !collision(&(world->heros),&(world->tresor))){
								world->heros.DestR_sprite.y = world->heros.DestR_sprite.y - 4 ;
								if (collision_murs(world->heros,world->terrain,world->ligne,world->colonne))
									world->heros.DestR_sprite.y = ((world->heros.DestR_sprite.y/world->heros.DestR_sprite.h)+1)*world->heros.DestR_sprite.h;
								update_farmes(&(world->heros.farme),NBR_HORIS_IMAGE_HEROS,1,2);// 
								world->heros.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->heros.farme.cpt;
								world->heros.SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-world->heros.SrcR_sprite.w ;
							}
							break;
						case SDLK_DOWN: 
							if (world->heros.est_visible == 1 && !collision(&(world->heros),&(world->tresor))){
								world->heros.DestR_sprite.y = world->heros.DestR_sprite.y + 4 ;
								if (collision_murs(world->heros,world->terrain,world->ligne,world->colonne))
									world->heros.DestR_sprite.y = (world->heros.DestR_sprite.y/world->heros.DestR_sprite.h)*world->heros.DestR_sprite.h;
								update_farmes(&(world->heros.farme),NBR_HORIS_IMAGE_HEROS,0,2);// 
								world->heros.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->heros.farme.cpt;
								world->heros.SrcR_sprite.y = 0;
							}	
							break;
						case SDLK_LEFT:
							if (world->heros.est_visible == 1 && !collision(&(world->heros),&(world->tresor))){
								world->heros.DestR_sprite.x  = world->heros.DestR_sprite.x - 4 ;  
								if (collision_murs(world->heros,world->terrain,world->ligne,world->colonne))
									world->heros.DestR_sprite.x = ((world->heros.DestR_sprite.x/world->heros.DestR_sprite.w)+1)*world->heros.DestR_sprite.w; // pour le coller au murs si il ya une collision avec le mur le plus 1 car c'est a gauche 
								update_farmes(&(world->heros.farme),NBR_HORIS_IMAGE_HEROS,2,2);// 
								world->heros.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->heros.farme.cpt;
								world->heros.SrcR_sprite.y =HAUTEUR_IMAGE_HEROS-3*world->heros.SrcR_sprite.w ;
							}
							break;
						case SDLK_RIGHT: 
							if (world->heros.est_visible == 1 && !collision(&(world->heros),&(world->tresor))){
								world->heros.DestR_sprite.x  = world->heros.DestR_sprite.x + 4 ; 
								if (collision_murs(world->heros,world->terrain,world->ligne,world->colonne))
									world->heros.DestR_sprite.x = (world->heros.DestR_sprite.x/world->heros.DestR_sprite.w)*world->heros.DestR_sprite.w; // pour le coller au murs si il ya une collision avec le mur 
								update_farmes(&(world->heros.farme),NBR_HORIS_IMAGE_HEROS,3,2);// *
								world->heros.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->heros.farme.cpt;
								world->heros.SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-2*world->heros.SrcR_sprite.w ;
							}
						break;
					}
				case SDL_MOUSEBUTTONDOWN:
					if(evenements->button.button == SDL_BUTTON_LEFT)
               		{	
                		if(evenements->button.x> jeu->image_start.DestR_image.x && evenements->button.x<jeu->image_start.DestR_image.x+jeu->image_start.DestR_image.w )
							if(evenements->button.y> jeu->image_start.DestR_image.y && evenements->button.y < jeu->image_start.DestR_image.y+jeu->image_start.DestR_image.h)
                    		{
                    			jeu->start = true;
                			}
                    	if(evenements->button.x> jeu->image_quit.DestR_image.x && evenements->button.x<jeu->image_quit.DestR_image.x+jeu->image_quit.DestR_image.w )
							if(evenements->button.y> jeu->image_quit.DestR_image.y && evenements->button.y < jeu->image_quit.DestR_image.y+jeu->image_quit.DestR_image.h)
                    		{
								if(!jeu->start && !jeu->score)
									world->terminer = true;
                			}
						if(evenements->button.x> jeu->image_score.DestR_image.x && evenements->button.x<jeu->image_score.DestR_image.x+jeu->image_score.DestR_image.w )
							if(evenements->button.y> jeu->image_score.DestR_image.y && evenements->button.y < jeu->image_score.DestR_image.y+jeu->image_score.DestR_image.h)
                    		{
								if(!jeu->Quit && !jeu->start)
                    				jeu->score = true;
                			}
						if(evenements->button.x> jeu->home.DestR_image.x && evenements->button.x<jeu->home.DestR_image.x+jeu->home.DestR_image.w )
							if(evenements->button.y> jeu->home.DestR_image.y && evenements->button.y < jeu->home.DestR_image.y+jeu->home.DestR_image.h)
                    					{				
								update_best_score("./ressource/text/score.txt",jeu->tab_score,world->score);
								if(!jeu->Quit && !jeu->start )
								{
									jeu->start = false;
									jeu->score = false;
								}
								if (!jeu->Quit && !jeu->score) 
								{
									jeu->start = false;
									jeu->score = false;
									clean_world(world);
									clear_textures(jeu,world);
									clean_message(msg);
									init_world(world,1,0);	
									init_textures(jeu,world,renderer);
									init_message(msg,renderer,font,jeu->tab_score,1);
								}
                			}
						if(evenements->button.x> jeu->replay.DestR_image.x && evenements->button.x<jeu->replay.DestR_image.x+jeu->replay.DestR_image.w )
							if(evenements->button.y> jeu->replay.DestR_image.y && evenements->button.y < jeu->replay.DestR_image.y+jeu->replay.DestR_image.h)
                    		{
								if(!jeu->Quit && !jeu->score)
								{
									clean_world(world);
									clear_textures(jeu,world);
									clean_message(msg);
									init_world(world,1,0);	
									init_textures(jeu,world,renderer);
									init_message(msg,renderer,font,jeu->tab_score,1);
								}

                			}
						
                    }
			}
		}



void refresh_graphic(jeu_t *jeu,world_t *world,SDL_Renderer * renderer,TTF_Font *font,message_t *msg)
{
	SDL_RenderClear(renderer);
	if(!jeu->start )
	{
		SDL_RenderCopy(renderer,jeu->background.image,&(jeu->background.SrcR_image),&(jeu->background.DestR_image));
		SDL_RenderCopy(renderer,jeu->image_start.image,&(jeu->image_start.SrcR_image),&(jeu->image_start.DestR_image));
		SDL_RenderCopy(renderer,jeu->image_score.image,&(jeu->image_score.SrcR_image),&(jeu->image_score.DestR_image));
		SDL_RenderCopy(renderer,jeu->image_quit.image,&(jeu->image_quit.SrcR_image),&(jeu->image_quit.DestR_image));
	}
	if(jeu->score )
	{	
		SDL_RenderCopy(renderer,jeu->background2.image,&(jeu->background2.SrcR_image),&(jeu->background2.DestR_image));
		init_XYWH(&(jeu->home.DestR_image),(LARGEUR_ECRAN)/16,(HAUTEUR_ECRAN)/16,LARGEUR_ECRAN/16,HAUTEUR_ECRAN/16);
		SDL_RenderCopy(renderer,jeu->home.image,&(jeu->home.SrcR_image),&(jeu->home.DestR_image));
		for(int i=0 ; i <7 ; i++){
		SDL_RenderCopy(renderer,msg->best_score[i].text,NULL,&(msg->best_score[i].DestR_text));
		}

	}		

	if(jeu->start ){
		for (int i = 0; i < world->ligne; i++)
		{
			for (int j=0 ; j<world->colonne ; j++)
			{
				SDL_RenderCopy(renderer,world->terrain.image,&(world->terrain.SrcR_terrain[i][j]),&(world->terrain.DestR_terrain[i][j]));
			}
		}
		for(int i = 0 ; i<world->ennemies.nbr_ennemies;i++)
		{
			if(world->ennemies.sprite[i].est_visible == 1)
			{
				SDL_RenderCopy(renderer,world->ennemies.sprite[i].image,&(world->ennemies.sprite[i].SrcR_sprite),&(world->ennemies.sprite[i].DestR_sprite) );
			}
		}

		for(int i = 0 ; i<world->monnaie.nbr_pieces;i++)
		{
			if(world->monnaie.pieces[i].est_visible == 1)
			{
				SDL_RenderCopy(renderer,world->monnaie.pieces[i].image, &(world->monnaie.pieces[i].SrcR_sprite), &(world->monnaie.pieces[i].DestR_sprite));
				update_farmes(&(world->monnaie.pieces[i].farme),NBR_HORIS_IMAGE_PIECE,0,10);
				world->monnaie.pieces[i].SrcR_sprite.x = (LARGEUR_IMAGE_PIECE/NBR_HORIS_IMAGE_PIECE)*world->monnaie.pieces[i].farme.cpt;
				world->monnaie.pieces[i].SrcR_sprite.y = 0;
			}
		}
		init_XYWH(&(jeu->home.DestR_image),(LARGEUR_ECRAN*16)/17-LARGEUR_ECRAN/64,(HAUTEUR_ECRAN)/32,LARGEUR_ECRAN/16,HAUTEUR_ECRAN/16);
		SDL_RenderCopy(renderer,jeu->home.image,&(jeu->home.SrcR_image),&(jeu->home.DestR_image));
		SDL_RenderCopy(renderer,jeu->replay.image,&(jeu->replay.SrcR_image),&(jeu->replay.DestR_image));

		if(world->heros.est_visible == 1) 
			SDL_RenderCopy(renderer,world->heros.image, &(world->heros.SrcR_sprite), &(world->heros.DestR_sprite) );
		SDL_RenderCopy(renderer,world->tresor.image, &(world->tresor.SrcR_sprite), &(world->tresor.DestR_sprite) );
		if(world->heros.est_visible == 0)
		{
			SDL_RenderCopy(renderer,msg->game_over.text,NULL,&(msg->game_over.DestR_text));
		}		
		else if(collision(&(world->heros),&(world->tresor)))
		{
			if (world->tresor.farme.cpt<3)
			{
				if(world->tresor.farme.cpt  <2 )
				{
					world->score = world->score + VALEUR_PIECE_MONEY ;			
				}
				if(world->tresor.farme.cpt == 2)
				{
					world->tresor.farme.stop = true;
				}
				update_farmes(&(world->tresor.farme),NBR_HORIS_IMAGE_TRESOR,0,15);// *
				world->tresor.SrcR_sprite.x = (LARGEUR_IMAGE_TRESOR/NBR_HORIS_IMAGE_TRESOR)*world->tresor.farme.cpt;
				world->tresor.SrcR_sprite.y = 0 ;
				SDL_RenderCopy(renderer,world->tresor.image, &(world->tresor.SrcR_sprite), &(world->tresor.DestR_sprite));
			}		
		}
		if(world->tresor.farme.stop)
		{	
			if(world->niveau==NBR_NIVEAU)		
				SDL_RenderCopy(renderer,msg->game_finished.text,NULL,&(msg->game_finished.DestR_text));
			else
				SDL_RenderCopy(renderer,msg->you_win.text,NULL,&(msg->you_win.DestR_text));
		}
		SDL_RenderCopy(renderer,msg->score.text,NULL,&(msg->score.DestR_text));
		update_message(&(msg->score_chiffre),renderer,font,world->score,LARGEUR_ECRAN*5/8+LARGEUR_ECRAN/6,0,HAUTEUR_ECRAN/16);
		SDL_RenderCopy(renderer,msg->score_chiffre.text,NULL,&(msg->score_chiffre.DestR_text));	
		if(!msg->est_affiche_niveau)
		{
			SDL_RenderCopy(renderer,msg->niveau[0].text,NULL,&(msg->niveau[0].DestR_text));
			SDL_RenderCopy(renderer,msg->niveau[1].text,NULL,&(msg->niveau[1].DestR_text));
		}
	}
	SDL_RenderPresent(renderer);
	
	if(!msg->est_affiche_niveau && jeu->start ) 
	{		
		SDL_Delay(1000);
		msg->est_affiche_niveau = true;
	}
	if(world->tresor.farme.stop)
	{	         	
		SDL_Delay(1000);
		if(world->niveau<NBR_NIVEAU)
		{	
			world->niveau++;
			clean_world(world);
			clear_textures(jeu,world);
			clean_message(msg);
			init_world(world,world->niveau,world->score);	
			init_textures(jeu,world,renderer);
			init_message(msg,renderer,font,jeu->tab_score,world->niveau);
		}
	}

}






