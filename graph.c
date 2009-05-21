/******************************************************************/
/**                                                              **/
/**   --- GRAPH.C ---                                            **/
/**                                                              **/
/******************************************************************/

#include "graph.h"

// Initialise le tableau des consomations à 0 ---------------------------------
void InitMatrice ( void )
{
	int i, j ;
	for ( i = 0 ; i < NBR_SOMMET ; i++ )
		for ( j = 0 ; j < NBR_SOMMET ; j++ )
			Matrice_Conso[i][j] = 0 ;
}

// Charge le fichier et flot en memoire ---------------------------------------
int ChargeFichier ( char * fichier )
{
	FILE *ptr;		// Pointeur sur le fichier
	size_t s;		// Taille du nom lu
	int i, j ;		// deux lettres de l'alphabete
	char *tmp = (char *) calloc ( 1, 50 ) ;	// Nom temporaire du sommet : max 50 char
	char * tmpNom ;	// Pointeur vers la vraie future zone memoire du nom

	if ( ( ptr = fopen ( fichier, "r+" ) ) == NULL )
	{	
		fprintf ( stderr, "Erreur: Lors de l'ouverture du fichier\n" ) ;
		return 2 ;	// Erreur sur fichier
	}

	// Lit le nombre de Sommets
	fscanf( ptr, "%d", &NBR_SOMMET );
	if ( NBR_SOMMET <= 0 )
	    return 3;

	// Alloue la memoire pour la matrice Max
	Matrice_Max = (float **) malloc ( sizeof ( float * ) * NBR_SOMMET );
	for( i = 0 ; i < NBR_SOMMET ; i++ )
		Matrice_Max [ i ] = malloc ( sizeof ( float ) * NBR_SOMMET);

	// Alloue la memoire pour la matrice Conso
	Matrice_Conso = (float **) malloc ( sizeof ( float * ) * NBR_SOMMET );
	for( i = 0 ; i < NBR_SOMMET ; i++ )
		Matrice_Conso [ i ] = malloc ( sizeof (float ) * NBR_SOMMET);

	// Alloue memoire pour les noms des sommets
	NomSommet = (char **) malloc ( sizeof ( char * ) * NBR_SOMMET );

	// Alloue memoire pour les marquage entre sommets (Qui marque qui)
	Sommet   =   (int *) malloc ( sizeof ( int ) * NBR_SOMMET ) ;
	SommetPlus = (int *) malloc ( sizeof ( int ) * NBR_SOMMET ) ;

	// Lit le nom des Sommets :
	for ( i = 0 ; i < NBR_SOMMET ; i++ )
	{
		fscanf ( ptr, "%49s",  tmp ) ;	
		s = strlen ( tmp ) ;
	      	tmpNom = (char *) calloc ( 1, s + 3 ) ;
		memcpy ( tmpNom, tmp, s ) ;//strncpy ( tmpNom , tmp, s )  ;
		tmpNom [ (int) s ] = '\0' ;
	      	NomSommet [ i ] = tmpNom ;
	}

	// Lit les consommation max entre chaque sommet :
	for( i = 0 ; i < NBR_SOMMET ; i++ )
	{
		for ( j = 0 ; j < NBR_SOMMET ; j++ ) 		
			fscanf( ptr, "%f", &Matrice_Max[ i ][ j ] );		
	}

	// Charge les consos si il y en a :
	if ( OPTIONS & CONSO )
	{	
	      fscanf ( ptr, "%49s\n", tmp ) ;	// lit une ligne de séparation 49 char max
	      for( i = 0 ; i < NBR_SOMMET ; i++ )
		      for ( j = 0 ; j < NBR_SOMMET ; j++ ) 		
			      fscanf( ptr, "%f", &Matrice_Conso[ i ][ j ] );		
	}
	else 
	      InitMatrice () ;

	return 0 ;	// Ok, tout c'est bien passé 
}	

// Marque le sommet et l'affiche ----------------------------------------------
void MarqueSommet ( int i, int vientDe, int Plus ) 
{
	if ( OPTIONS & VERB )
		printf ( "\n\tMarque \033[0;32m%2s\033[0;m venant de \033[1;32m%2s\033[0;m" , NomSommet [ i ], NomSommet [ vientDe ] ) ; 
	Sommet [ i ] = vientDe ;	// Associe les deux sommets
	SommetPlus [ i ] = Plus ;	// Plus = 1  OU  Moins = 0
}

// ----------------------------------------------------------------------------
// Parcour le graphe en LARGEUR  ----------------------------------------------
// ----------------------------------------------------------------------------
void Parcour_Largeur ( int Som ) 
{
	struct Liste L ;	// Liste des sommets à parcourir
	L.prems = NULL ;
	L.der = NULL ;
	int i, LeSommet ;

	AjouteFin ( Som , &L ) ;
	MarqueSommet ( Som, Som , 1 ) ;
	while ( L.prems )	
	{
		if ( OPTIONS & G_VERB )
		      AfficheListe ( L.prems );  // Affiche la liste de sommet à parcourir

		LeSommet = L.prems->Sommet; // Recupere le sommet que l'on traite
		SupprimePrems ( &L );	// Supprime le sommet en cour de la liste

		for ( i = 0 ; i < NBR_SOMMET ; i++ ) 
		{
			// Si le sommet n'est pas marqué ET si lien entre sommet ET possibilité de GAIN
			if ( ( Sommet[i] == -1 ) && (( Matrice_Max [ LeSommet ][ i ] - Matrice_Conso[ LeSommet ][i] ) > 0.0 )  )
			{
				if ( OPTIONS & G_VERB ) { DEBUG_1 }
				MarqueSommet ( i, LeSommet, 1 ) ; 
				AjouteFin ( i, &L ) ;
			}
			// Si le sommet n'est pas marqué ET si lien entre sommet ET possibilité de BAISSE
			else if ( ( Sommet[i] == -1 ) && ( Matrice_Conso[ i ][ LeSommet ] > 0.0 ) )
			{
				if ( OPTIONS & G_VERB ) { DEBUG_1 } 
				MarqueSommet ( i, LeSommet, 0 ) ;
				AjouteFin ( i, &L ) ;
			}
		}
	}
}

// -------------------------------------------------------------------------------
// Parcour le graphe en PROFFONDEUR ----------------------------------------------
// -------------------------------------------------------------------------------
void Parcour_Proffondeur ( int LeSommet )
{
       int i;

       // Pour tout i : SI Capacité > Flot ET Sommet i non marqué ALORS
	for ( i = 0 ; i < NBR_SOMMET ; i++ )
        {
        	if ( ( Matrice_Max[ LeSommet ][ i ] > Matrice_Conso[ LeSommet ][ i ] ) && ( Sommet[ i ] == -1 ) )
                {
                	MarqueSommet( i, LeSommet, 1 ); // Marque sommet i venant de LeSommet
                        Parcour_Proffondeur( i );       // Parcour sommet i
                }
        }
       // Pour tout i : SI Flot > 0  ET Sommet i non marqué ALORS
       for ( i = 0 ; i < NBR_SOMMET ; i++ )
       {
       	   if ( ( Matrice_Conso[ i ][ LeSommet ] > 0 ) && ( Sommet[ i ] == -1 ) )
           {
		MarqueSommet( i, LeSommet, 0 ); // Marque sommet i venant de LeSommet
                Parcour_Proffondeur( i );       // Parcour sommet i
           }
       }
}
       

// Recherche le pacour, le minimum, et si c'est une chaine augmentante ------------
int RechercheParcour ( void )
{
	int tmp, Min ;
	int i = NBR_SOMMET - 1 ;

	// Si P n'est pas marquée, alors il n'y a plus d'optimisation possible
	if ( Sommet[ i ] == -1 )
		return 0 ;

	if ( SommetPlus [ i ] )
		Min = Matrice_Max[ Sommet[ i ] ][ i ] - Matrice_Conso[ Sommet[i] ][ i ] ; 
	else 
		Min = Matrice_Conso[ i ][ Sommet[i] ] ; 
		
//	if ( Min == 0 )
//	    Min = Matrice_Conso[ i ][ Sommet[i] ] ;

	// Tant que l'on passe par un sommet marque ET pas par l'entrée 
	while ( ( Sommet[ i ] != -1  ) && ( i != 0 ) ) 
	{	
		// Difference de consomation
		if ( SommetPlus[ i ] )
			tmp =  Matrice_Max[ Sommet[i] ][ i ] - Matrice_Conso[ Sommet[i] ][ i ] ;
		else
			tmp =  Matrice_Conso[ i ][ Sommet[i] ] ;

//		if ( tmp == 0 )
//		    tmp = Matrice_Conso[ i ][ Sommet[i] ] ;

		if ( tmp < Min )
			Min = tmp ;
		i = Sommet [ i ] ;
	}
	return Min ;
}

// Applique l'augmentation au parcour ------------------------------------------
void AppliqueParcour ( int AjouteConso ) 
{	
	int i = NBR_SOMMET - 1 ;

	while ( ( Sommet[ i ] != -1  ) && ( i != 0 ) ) 
	{
/*		if ( SommetPlus [ i ] )
			Matrice_Conso[ Sommet[i] ][ i ] += AjouteConso ;
		else 
			Matrice_Conso[ Sommet[i] ][ i ] -= AjouteConso ;*/
		
		if ( Matrice_Max[ Sommet[i] ][ i ] )
		    Matrice_Conso [ Sommet[i] ][ i ] += AjouteConso;
		else
		    Matrice_Conso [ i ][ Sommet[i] ] -= AjouteConso;
		    
		i = Sommet [ i ] ;
	}
}

// Initialise le tableau des marquages des sommets ------------------------------
void Init_Marquage ( void )
{
	int i ;
	Sommet [ 0 ] = 0 ;
	for ( i = 1 ; i < NBR_SOMMET ; i++ )
		Sommet [ i ] = -1 ;
}

// ----------------------------------------------------------------------------
void AfficheAide ( void ) ;
void LitOptions  ( int argc, char ** argv ) ;
// ----------------------------------------------------------------------------
int main ( int agc, char ** argv ) 
{
	int NbrIteration = 1 ;
	int Min ;

	LitOptions ( agc, argv ) ;  	// Charge le Graph contenu ds le fichier

	do 
	{
		/* 1 */ RED printf ( "\n( %d ) PARCOUR LE FLOT ", NbrIteration ) ; DEFAULT_COLOR
			
		Init_Marquage () ;	// Reinitialise le marquage des sommets

		if ( OPTIONS & PROF )
			Parcour_Proffondeur ( 0 ); 
		else if ( OPTIONS & LARG )
			Parcour_Largeur ( 0 );

		/* 2 */ RED printf ( "\n( %d ) RECHERCHE CHAINE AUGMENTANTE ", NbrIteration ) ; DEFAULT_COLOR

		if ( OPTIONS & VERB )
			AfficheParcour () ;

		Min = RechercheParcour () ; 

		/* 3 */ RED printf( "\n( %d ) APPLIQUE CHAINE AUGMENTANTE DE \033[1;33m%d ", NbrIteration, Min ) ; DEFAULT_COLOR

		AppliqueParcour ( Min ) ;

		if ( OPTIONS & G_VERB )
			AfficheConso () ;

		NbrIteration ++ ;
		
	} while ( Min != 0 ) ;

	CYAN 
	printf( "\n\n   -----------------------------------" );
	printf(   "\n  ----       RESULTAT FINAL        ----" );
	DEFAULT_COLOR
	AfficheConso () ;
	AfficheTotal () ;
	return 0;
}


// Lit les options entrées en arguments -------------------------------------
void LitOptions  ( int argc, char ** argv )
{
	int opt ;
	char * NomFichier;
	OPTIONS = 0 ;

	while ( ( opt = getopt(argc, argv, "cVvlpf:h") ) != -1 ) 
	{
		switch ( opt ) 
		{
			case 'c' :
				OPTIONS |= CONSO ; 
				break;
			case 'v' :
				OPTIONS |= VERB ; 
				break;
			case 'V' :
				OPTIONS |= VERB | G_VERB ; 
				break;
			case 'p' :
				OPTIONS |= PROF ; 
				break;
			case 'l' :
				OPTIONS |= LARG ; 
				break;
			case 'f' :
				NomFichier = optarg ;
				OPTIONS |= FICH ;
				break;
			case 'h' :
				AfficheAide () ;
				exit ( EXIT_SUCCESS ) ;
				break;
			default: 	
				fprintf ( stderr, "\nErreur: Argument inconnu" ) ;
				AfficheAide () ;
				exit ( EXIT_FAILURE ) ;
		}
	}
	// Si aucun mode de parcoure demamnde, on en fix un
	if ( ! ( OPTIONS & 3 ) )
		OPTIONS |= LARG ;

	// FICH : Si un fichier bien entre
	if ( ! ( OPTIONS & FICH ) )
	{
		AfficheAide () ;
		exit ( EXIT_FAILURE ) ;
	}

	// Chager le fichier avec les graph des conso et max
	if ( ChargeFichier ( NomFichier ) )
		exit ( EXIT_FAILURE ) ; 
}
