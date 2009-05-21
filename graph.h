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

#define DEBUG_1	if (   ( (i==4) && (LeSommet==5) )  ||  ( (i==5) && (LeSommet==4) )    ) { RED printf ("\n/!\\"); } \
			printf ( "\n%s(N°%d/%d)(Mk%d/%d) %s Max: %.2f  Conso: %.2f  ConsoMoins: %.2f", NomSommet[LeSommet], LeSommet, i,Sommet[LeSommet],Sommet[i], NomSommet[i], Matrice_Max[LeSommet][i], Matrice_Conso[LeSommet][i], Matrice_Conso[i][LeSommet] ) ;\
			DEFAULT_COLOR

#ifndef PROF
	#define PROF 1           // Flag pour proffondeur
	#define LARG 2           // Flag pour largeur
	#define FICH 4           // Flag pour fichier
	#define VERB 8           // Flag pour verbose
	#define G_VERB 16        // Flag pour verbose encore plus
	#define CONSO  32        // Flag pour les consos	

	int OPTIONS ;           // Flag pour les options
	int NBR_SOMMET ;        // Nombre de sommet dans le Graph
	float ** Matrice_Max ;  // Matrice representant le Graph avec conso max
	float ** Matrice_Conso ;// Matrice des consomations en cour
	char ** NomSommet ;     // Matrice avec les noms de chaques Sommets
	int   * Sommet ;        // Qui pointe Qui ET Qui est marqué
	int   * SommetPlus ;    // Plus = 1  OU  Moins = 0
#else
	extern int OPTIONS ;           // Flag pour les options
	extern int NBR_SOMMET ;        // Nombre de sommet dans le Graph
	extern float ** Matrice_Max ;  // Matrice representant le Graph avec conso max
	extern float ** Matrice_Conso ;// Matrice des consomations en cour
	extern char ** NomSommet ;     // Matrice avec les noms de chaques Sommets
	extern int   * Sommet ;        // Qui pointe Qui ET Qui est marqué
#endif

// Liste des Sommets à parcourir ------------------------------------------------
struct Liste
{
	struct Chainon * prems  ;	// Premier element de la liste
	struct Chainon * der	;	// Dernier element de la liste
};
struct Chainon
{
         int Sommet ;              // Numero du sommet
         struct Chainon * suiv ;   // Sommet a parcourir apres
};
//struct Liste * AjouteDebut ( int Som, struct Liste * L ) ;
void AjouteFin ( int Som, struct Liste * L ) ;
void SupprimeDer ( struct Liste * L ) ;

// Fonctions d'affichage -----------------------
void AfficheTotal ( void ) ;
void AfficheConso ( void ) ;	
void AfficheParcour( void );
void AfficheListe ( struct Chainon *L ) ;
