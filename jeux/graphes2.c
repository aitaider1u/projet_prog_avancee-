#include<stdio.h>
#include<stdlib.h>
#include "headers/graphes2.h"


/**
*Fonction d'allocation d'un Graphe 
*@param nbr_sommets le nombre de somemt du graphe souhaité
*@return le graphe 
*/
Graphe 	allouer_graphe(int nbr_sommets)
{
	Graphe g= malloc(sizeof(g));

	if(g==NULL)
	{
		printf("Allocation graphe echouee\n");
		exit(0);
	}

	g->nombre_sommets=nbr_sommets;

	List* Adj=malloc(sizeof(Adj)*nbr_sommets);

	if(Adj==NULL)
	{
		printf("Allocation liste adjacence echouee\n");
		exit(0);
	}

	g->Adjacence=Adj;

	for(int i=0;i<nbr_sommets;i++)
		g->Adjacence[i].tete=NULL;

	return g;
}



/**
*Fonction d'ajout d'arete à un graphe 
*@param g le graphe 
*@param src l'indice du sommet source 
*@param dest l'indice du sommet destination
*/
void ajouter_arete(Graphe g, int src, int dest)
{
	Noeud* tmp=NULL;

	if(g->Adjacence[src].tete==NULL)	// si l'element d'indice src n'a encore aucun voisin
	{
		Noeud* source=malloc(sizeof(source));

		if(source==NULL)
		{
			printf("Allocation Noeud echouee\n");
			exit(0);
		}
		source->valeur=src;
		source->suivant=NULL;
		g->Adjacence[src].tete=source;
	}

	Noeud* destination=malloc(sizeof(destination));
	if(destination==NULL)
		{
			printf("Allocation Noeud echouee\n");
			exit(0);
		}
	destination->valeur=dest;
	destination->suivant=NULL;


	tmp=g->Adjacence[src].tete;
	while(tmp->suivant!=NULL) 	//la valeur du champs suivant du Noeud !! important 
	{
		tmp=tmp->suivant;
	}
	tmp->suivant=destination;

}



/**
* Fonction de suppression d'un graphe
*@param g le graphe à supprimer
*/
void desallouer_graphe(Graphe g)
{	
	for(int i=0;i<g->nombre_sommets;i++)
	{	
		Noeud* head=g->Adjacence[i].tete;
		while(head!=NULL)
		{
			Noeud* tmp=head;
			head=head->suivant;
			free(tmp);	
		}
		//free(g->Adjacence[i].tete);
	}
	free(g->Adjacence);
	free(g);
}


/**
* Fonction d'affichage d'un graphe 
*@param g le graphe à afficher
*/
void afficher_graphe(Graphe g)
{	
	Noeud* tmp;
	for(int i=0;i<g->nombre_sommets;i++)
	{
		tmp=g->Adjacence[i].tete;
		printf(" Sommet %d : ",i);
		while(tmp!=NULL)
		{
			printf("(%d - %d) ",i,tmp->valeur);
			tmp=tmp->suivant;
		}
		printf("\n");
	}
}


/**
*Fonction qui calcule le nombre de voisins d'un sommet
*@param g le graphe 
*@param src le sommet dont on désire connaitre le nombre de voisins 
*@return le nombre de voisins du sommet
*/
int nbr_voisin_listAdjacence(Graphe g,int src)
{
	Noeud* tmp;
	tmp=g->Adjacence[src].tete;
	int cpt = 0;
	while(tmp!=NULL)
		{
			cpt++;
			tmp=tmp->suivant;
		}
	return cpt ;


}
