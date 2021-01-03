#include<stdio.h>
#include<stdlib.h>
#include "headers/files.h"


/**
*Fonction de création d'une file vide 
*@return une file vide 
*/
File file_vide()
{	
	File f=malloc(sizeof(f));
	f->premier=NULL;
	f->dernier=NULL;

	return f;
}
/*<************************************************************************>*/


/**
*Fonction détérminant si une file est vide 
*@param f la file
*@return l'etat de la file 0 si vide 1 sinon 
*/
int est_vide_file(File f)
{
	return (f->premier==NULL /*&& f->dernier==NULL*/);
}
/*<************************************************************************>*/

/**
* Fonction permettant d'enfiler un élement
*@param f la file 
*@param x l'élément à enfiler
*/
void enfiler(File f, int x)
{
	file_Element_t* elem=malloc(sizeof(*elem));

	if(elem==NULL)
		printf("Allocation file echouee\n");

	elem->element= x;
	elem->suivant=NULL;

	//deux cas : file vide ou non vide 

	if(f->dernier!=NULL)	// on a déjà une queue quelque part 
	{
		f->dernier->suivant=elem; // on lie le nouvel element 
	}	
	f->dernier=elem; 		//elem devient la nouvelle queue de file(le dernier)


	if(f->premier==NULL) //		// cas d'une file vide
	{
		f->premier=elem;
	}
}
/*<************************************************************************>*/



/**
* Fonction qui éfface le contenue d'une file 
*@param f la file
*/
void effacer_file(File f)
{	
	file_Element_t* tmp=NULL;
	

	if(est_vide_file(f))
		printf("la file est deja vide\n");

	while(f->premier!=NULL)
	{
		tmp=f->premier;
		f->premier=f->premier->suivant;
		free(tmp);
	}
	free(f);


}

/**
*Détérmination de la tête de file
*@param f la file 
*@return la tete de file
*/
int tete_file(File f)
{
	return f->premier->element;
}


/**
*Recherche de la queue de la file
*@param f la file 
*@return l'élément en queue de file 
*/
int queue_file(File f)
{
	return f->dernier->element;
}

/**
* Afficher les éléments d'une file
*@param f la file à afficher 
*/
void afficher_file(File f)
{
	file_Element_t* temp=f->premier;
	if(temp==NULL)
		printf("la fille est vide il n'y a rien à afficher !\n");
	while(temp!=NULL)
	{
		printf("[%d]",temp->element);
		temp=temp->suivant;
	}
	printf("\n");
}

/**
*Défiler un élement de la file
*@param f la file
*/
void defiler(File f)
{	
	if(est_vide_file(f))
	{
		printf("Defilement impossible sur file vide \n");
		return;
	}
	
	file_Element_t* temp=f->premier;

	f->premier=temp->suivant;
	free(temp);
}

/**
*Calcul de la longeur d'une file
*@param f la file dont on veut déterminer la longueur
*@return la longueur de la file
*/
int longueur_file(File f)
{
	int longueur=0;
	file_Element_t* temp=f->premier;
	while(temp!=NULL)
	{
		longueur++;
		temp=temp->suivant;
	}
	return longueur;
}
