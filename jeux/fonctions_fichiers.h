/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine 
* \Brief bibliotheque fonctios_SDL. 
*/

#ifndef FONCTIONS_FICHIERS_H
#define  FONCTIONS_FICHIERS_H

char** allouer_tab_2D(int n, int m);
void desallouer_tab_2D(char** tab, int n);
void afficher_tab_2D(char** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);
void lire_best_score(const char* nomFichier,int *tab);
void ecrire_best_score(const char* nomFichier,int *tab);
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m);
#endif 