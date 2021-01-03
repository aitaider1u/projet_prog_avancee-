#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gestion_farmes.h" 

/**
  *Initialisation d'une farme
  *@param farme la farme à initialiser
*/
void init_farme(farme_t *farme )
{
	farme->stop = false ;
	farme->cpt = 0;
	farme->dist = 0; //par defaut on met la distination down
	farme->temp = 0;
} 

/**
*Mise à jour de la frame en fonction de l'evenement (touche clavier)
*@param farme la farme à mettre à jour
*@param nbr_image_horisental les images représentants l'animation de marche
*@param i l'evenement clavier
*@param temps variable de temporisation de l'animation de marche  
*/

void update_farmes(farme_t *farme,int nbr_image_horisental,int i, int temps)  // elle va etre appliquer si on a changer destination  
{
	farme-> temp++;
	if ( !farme->stop )
	{
		if (farme->dist == i)
		{
			if (farme-> temp == temps)
				if (farme->cpt < nbr_image_horisental-1)//nbr_image_horisental)
					farme->cpt ++;
				else 
					farme->cpt = 0;
			else if (farme-> temp > temps)
				farme-> temp = 0 ;
		}
		else // est la distination  i = 0 DOWN / i = 1 UP / i = 2 LEFT / i = 3  RIGHT.
		{
			if (i == 0)
			{
				farme->dist = 0;
			}
			else if(i == 1) 
			{
				farme->dist = 1;
			}
			else if(i == 2)
			{
				farme->dist = 2;
			}
			else if(i == 3)
			{
				farme->dist = 3;
			}
			farme->cpt = 0;
			farme-> temp = 0 ;
		}
	}	
}
