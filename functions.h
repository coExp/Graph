#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * 	Change_Extention ( char * Nom, char * Ext ) ;
float** Creer_Matrice_Carre ( int Nbr ) ;
int 	AjouteNom ( char * Nom, char *** Liste, int * Nbr ) ;
void 	Affiche_Fichier ( FILE * tmp ) ;
int 	Cherche ( char * Nom, char ** Liste, int Nbr ) ;
int Copy_File ( FILE * Cible, FILE * Source ) ;
int Write_matrix_to_file( FILE * cible, int nbr, char ** liste_nom, float ** mat_max, float ** mat_conso, int write_nom, int write_cons );

