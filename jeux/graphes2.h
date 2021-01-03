#ifndef GRAPHES2_H
#define GRAPHES2_H

typedef struct Noeud{

	int valeur;
	struct Noeud* suivant;

}Noeud;

typedef struct List{

	Noeud* tete;
}List;


typedef struct Graphe_s{

	int nombre_sommets;
	List* Adjacence;

}Graphe_t, *Graphe;


Graphe 	allouer_graphe(int nbr_sommets);

void desallouer_graphe(Graphe g);

void ajouter_arete(Graphe g, int src, int dest);


void afficher_graphe(Graphe g);

int nbr_voisin_listAdjacence(Graphe g,int src);




#endif 