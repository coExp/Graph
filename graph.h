/******************************************************************/
/**                                                              **/
/**   GRAPH.H                                                    **/
/**                                                              **/
/******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

#include "couleurs.h"
#include "chainon.h"
#include "affiche.h"
#include "functions.h"

#ifndef PROF
	#define PROF 1           // Flag pour proffondeur
	#define LARG 2           // Flag pour largeur
	#define FICH 4           // Flag pour fichier
	#define VERB 8           // Flag pour verbose
	#define G_VERB 16        // Flag pour verbose encore plus
	#define CONSO  32        // Flag pour les consos	
	#define EXPORT 64        // Flag pour les exportations

	int NBR_SOMMET ;        // Nombre de sommet dans le Graph
	float ** Matrice_Max ;  // Matrice representant le Graph avec conso max
	float ** Matrice_Conso ;// Matrice des consomations en cour
	char ** NomSommet ;     // Matrice avec les noms de chaques Sommets
	int   * Sommet ;        // Qui pointe Qui ET Qui est marqué
	int   * SommetPlus ;    // Plus = 1  OU  Moins = 0
#else
	extern int NBR_SOMMET ;        // Nombre de sommet dans le Graph
	extern float ** Matrice_Max ;  // Matrice representant le Graph avec conso max
	extern float ** Matrice_Conso ;// Matrice des consomations en cour
	extern char ** NomSommet ;     // Matrice avec les noms de chaques Sommets
	extern int   * Sommet ;        // Qui pointe Qui ET Qui est marqué
#endif

char *  LitOptions  ( int argc, char ** argv, int * OPTIONS ) ;   

