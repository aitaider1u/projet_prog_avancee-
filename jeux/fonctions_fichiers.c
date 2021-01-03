#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include"headers/fonctions_fichiers.h"

/**
*Allocation d'un tableau à 2 dimensions ch caractères
*@param n nombre de lignes 
*@param m nombre de colonnes
*@return tableau de Pointeurs (tableau à 2 dimensions)
*/
char** allouer_tab_2D(int n, int m)
{
	char** tab = malloc(n*sizeof(char*));
	for(int i = 0 ; i<n ; i++)
	{
		tab[i] = malloc(m*sizeof(char));
	}
	return tab ;
}



/**
*Libération de la mémoire alouée à la création du tableau de pointeurs
*@param tab le tableau à désallouer
*@param n nombre de lignes du tableau 
*/
void desallouer_tab_2D(char** tab, int n)
{
	for (int i=0 ; i<n ; i++)
	{
		free(tab[i]);
	}
	free(tab); 

}



/**
*Affichage d'un tableau à 2 dimensions de caractères
*@param tab le tableau à afficher
*@param n le nombre de lignes du tableau
*@param m le nombre de colonnes du tableau
*/
void afficher_tab_2D(char** tab, int n, int m)
{
	for (int i = 0; i<n; i++)      
	{
		for (int j = 0; j<m ;j++)
			{
			printf("%c ",tab[i][j]);
		}
		printf("\n");
	}
}


/**
*Calcul de la taille(nombre de lignes et de colonnes) maximale d'un fichier 
*@param nomFichier le fichier 
*@param nbLig	adresse dans laquelle stocker le nombre max de lignes du fichier 
*@param nbCol   adresse dans laquelle stocker le nombre max de colonnes du fichier
*/
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol)
{
	FILE* fichier = fopen(nomFichier,"r");
	int cpt_colonne=0;
	int cpt_ligne = 0; 
	char char_actuel,char_precedant;

	if (fichier != NULL)
    {
        do
        {
            char_actuel= fgetc(fichier);
            if (char_actuel == EOF)
            {
				if (*nbCol<cpt_colonne)
            		*nbCol = cpt_colonne;
				cpt_colonne = 0;
				if (char_precedant == '\n')
					cpt_ligne = cpt_ligne -1;
            	cpt_ligne++;
            }

            else if(char_actuel == '\n'){  
            	if (*nbCol<cpt_colonne)
            		*nbCol = cpt_colonne;
				cpt_colonne = 0;
				cpt_ligne++;           	}
           	else
           	{
           		cpt_colonne++;
           	}
           	char_precedant = char_actuel;
        }while (char_actuel != EOF);
        *nbLig= cpt_ligne;
        fclose(fichier);

    }
}



/**
*Lecture d'un fichier et sa copie dans un tableau à 2 dimension 
*@param nomFichier le tableau à lire
*@return le tableau contenant tous les carabtères du fichier
*/

char** lire_fichier(const char* nomFichier)
{
	FILE* fichier =  fopen(nomFichier,"r");
	int nbr_ligne ;
	int nbr_colonne ;
	char  c ;

	taille_fichier(nomFichier,&nbr_ligne,&nbr_colonne);
	char** tab = allouer_tab_2D(nbr_ligne,nbr_colonne);
    for(int i = 0 ; i<nbr_ligne;i++)
    {
    	for (int j = 0; j < nbr_colonne; j++)
    	{
    			tab[i][j] = ' '; 
    	}
    }
    int i=0,j=0;

    if (fichier != 0){
    	while(c!=EOF){       		
        	c = fgetc(fichier);
	  	if (c == '\n' || c==EOF){
        		j=0;
        		i++;
        	}
        	else{
        		tab[i][j] = c;
        		j++;

        	}
       	}
 	}
	fclose(fichier);
	return tab;
}

/**
*
*@param 
*@param
*@param 
*@return 
*/
void lire_best_score(const char* nomFichier,int *tab)
{
	FILE* fichier =  fopen(nomFichier,"a+");
	char c = fgetc(fichier);
	fclose(fichier);

	if (c!= EOF)
	{
		fichier =  fopen(nomFichier,"r");
		fscanf(fichier, "les meilleurs scores sont %i %i %i\n",&tab[0],&tab[1],&tab[2]);
		fclose(fichier);
	}
	else
	{ 
		fichier =  fopen(nomFichier,"w+");
		tab[0]= 0; 
		tab[1]= 0;
		tab[2]= 0;
		fprintf(fichier,"les meilleurs scores sont %i %i %i\n",tab[0],tab[1],tab[2]);
		fclose(fichier);
	}

	
}

/**
*Fonction d'écriture du score dans un fichier à partir d'un tableau de scores
*@param nomFichier le nom du fichier 
*@param tab le tableau de scores
*/

void ecrire_best_score(const char* nomFichier,int *tab)
{
	FILE* fichier =  fopen(nomFichier,"w+");
	if (fichier != 0)
	{
		fprintf(fichier, "les meilleurs scores sont %i %i %i\n",tab[0],tab[1],tab[2]);
   	}
	fclose(fichier);
}

/**
*Modifier un caractère présent dans un tableau par un autre 
*@param tab le tableau de caractère à modifier 
*@param	n nombre de lignes du tableau
*@param m nombre de colonnes du tableau 
*@param ancien le caractère à remplacer
*@param nouveau le nouveau caractère
*@return un nouveau tableau sur lequel on a replacé les caractères souhaités 
*/

char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau)
{
	char ** nv = allouer_tab_2D(n,m);
	for(int i=0;i<n;i++)
	{
		for (int j = 0; j< m;j++)
		{
			if(tab[i][j] == ancien)
				nv[i][j] = nouveau;
			else 
				nv[i][j] = tab[i][j];
		}
	}
	return nv;
}

/**
*Ecriture sur un fichier à partir d'un tableau de caractères
*@param nomFichier le fichier
*@param	tab le tableau
*@param	n nombre de lignes du tableau
*@param m nombre de colonnes du tableau
*/
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m)
{
	FILE* fichier =  fopen(nomFichier,"w");
	for(int i=0;i<n;i++)
	{
		for (int j = 0; j< m;j++)
		{
			fputc(tab[i][j],fichier);
		
		}
		fputc('\n',fichier);
	}

	fclose(fichier);
}
