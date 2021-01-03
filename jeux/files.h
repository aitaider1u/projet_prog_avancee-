#ifndef FILES_H
#define FILES_H

typedef struct file_Element_s{
	int element;
	struct file_Element_s* suivant;

}file_Element_t;

typedef struct param_file_s
{
	file_Element_t* premier;
	file_Element_t* dernier;

}param_file_t, *File;





File file_vide();//
int est_vide_file(File f);//
int tete_file(File f);
int queue_file(File f);

void enfiler(File f, int x);
void afficher_file(File f);
void defiler(File f);

int longueur_file(File f);
void effacer_file(File f);


#endif 