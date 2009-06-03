/******************************************************************/
/**								 **/
/**   AFFICHE.C                                                  **/
/**								 **/
/******************************************************************/

#include "graph.h"

// Affiche un message d'aide ------------------------------------------------
void AfficheAide ( void )
{
	printf( "[Graph] Résolution des graphs -----------------------" ) ;
	printf( "\nUsage: graph [OPTIONS] -f file.txt" );
	printf( "\n\t-f foo.txt : charge le graph du fichier foo.txt" ) ;
	printf( "\n\t-x : export result in \'foo.res\' file" ) ;
	printf( "\n\t-v : mode verbose, bavard" ) ;
	printf( "\n\t-V : mode verbose encore plus, bavard encore plus" ) ;
	printf( "\n\t-c : charge aussi les consos courantes" ) ;
	printf( "\n\t-l : parcour le graph en largeur" ) ;
	printf( "\n\t-p : OU parcour le graph en proffondeur" ) ;
	printf( "\n\t-h : ce message d'aide" ) ;
	printf( "\n" ) ;
}

// Affiche le resultat du flot total max --------------------------------------
void AfficheTotal ( void )
{
    int i ;
    float Total = 0 ;

    for ( i = 0 ; i < NBR_SOMMET ; i++ )
		Total += Matrice_Conso [ 0 ][ i ] ;

	CYAN
	printf ( "\nFlot total : %.2f\n\n", Total ) ;
	DEFAULT_COLOR
}
// ----------------------------------------------------------------------------
// Affiche la matrice des flots / capacités -----------------------------------
// ----------------------------------------------------------------------------
void AfficheConso ( void )
{
	int i, j ;

	GREEN
	printf ( "\n" ) ;
	for ( i = 0 ; i < NBR_SOMMET ; i++ )
		printf ( "  %3s  ", NomSommet[ i ] ) ;
	DEFAULT_COLOR

	printf( "\n" );

	for ( i = 0 ; i < NBR_SOMMET ; i++ )	
	{
		// Affiche la ligne
		for ( j = 0 ; j < NBR_SOMMET ; j++ )
		{
			printf ( "\033[0;33m" );

			if ( Matrice_Max[ i ][ j ] )
			{
				if (  Matrice_Conso[ i ][ j ] == Matrice_Max[ i ][ j ]  )
					printf ( "\033[1;33m" );
					
				printf ( " %2.0f/%2.0f ", Matrice_Conso[ i ][ j ], Matrice_Max[ i ][ j ] );
			} else 
				printf ( " ----- " );
		}
		GREEN printf ( " %3s\n", (NomSommet [ i ]) ); DEFAULT_COLOR
	}
}

// Affiche les elements de la liste ----------------------------------------------
void AfficheListe ( struct Chainon *L )
{
         printf("\n\t-> Liste des sommets à faire : \033[0;32m");
         while ( L )
         {
	         printf ( " %s ", NomSommet [ L->Sommet ] ) ;
                 L = L->suiv ;
         }
	 DEFAULT_COLOR
}

// Retrouve le parcour ------------------------------------------------------------
void AfficheParcour( int OPTIONS )
{
	int i = NBR_SOMMET - 1 ;
	
	if ( Sommet [ i ] == -1 ) 
	      printf ( "\n\tChaine trouvée : aucune" ) ;
	else 
	      printf ( "\n\tChaine trouvée : " ) ;

	while ( ( Sommet[i] != -1  ) && ( i != 0 ) )
	{
		if ( Matrice_Max[ Sommet[i] ][ i ] )
		{
		    printf("\t %d:%s(%2.0f)", i, NomSommet[i],   Matrice_Max[ Sommet[i] ][ i ] - Matrice_Conso[ Sommet[i] ][ i ] );
		}
		else
		{
		    printf ( "\t %d:%s", i, NomSommet [ i ] );
		    RED 
		    printf ( "(%2.0f)", Matrice_Conso[ i ][ Sommet[i] ] );
		    DEFAULT_COLOR
		}
		i = Sommet [ i ] ;
	}

	if ( ! ( OPTIONS & G_VERB ) )
	    return ;

	printf ( "\n\tSommets marqués : " ) ;
	for ( i = 0 ; i < NBR_SOMMET ; i++ )
	{
		if ( Sommet[i] != -1 )
			printf("\t %s:%s" , NomSommet [ i ] , NomSommet [ Sommet [ i ] ] ) ;
		else
			printf("\t %s:--" , NomSommet [ i ] ) ;
	}
}

