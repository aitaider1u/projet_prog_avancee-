#include<stdio.h>
#include<stdlib.h>
#include "files.h"

File file_vide()
{	
	File f=malloc(sizeof(f));
	f->premier=NULL;
	f->dernier=NULL;

	return f;
}
/*<************************************************************************>*/



int est_vide_file(File f)
{
	return (f->premier==NULL /*&& f->dernier==NULL*/);
}
/*<************************************************************************>*/


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


int tete_file(File f)
{
	return f->premier->element;
}



int queue_file(File f)
{
	return f->dernier->element;
}


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