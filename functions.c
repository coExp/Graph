/*************************/
/*     fonction.c        */
/*************************/

#include "functions.h"

///////////////////////////////////////////////////////////////////////////////
// CHANGE L'EXTENTION D'UN FICHIER
//
char * Change_Extention ( char * Nom, char * Ext )
{
	char * nom_fichier ;
	char * nom_fichier_1 ;
	char * nom_fichier_2 ;
	int len, ok ;

	// longueur du nom du fichier d'origine
	len =  strlen ( Nom ) + strlen ( Ext ) + 1 ;
	nom_fichier = (char *) malloc ( len * sizeof (char) ) ;
	memcpy ( nom_fichier, Nom, strlen( Nom ) + 1 ) ;

	// Recherche si y a un point 
	nom_fichier_1 = nom_fichier ; 
	ok = 0 ;
	do 
	{
		nom_fichier_2 = nom_fichier_1 ; 
		nom_fichier_1 = strstr ( nom_fichier_1, "." ) ;

		if ( nom_fichier_1 )
			ok = 1 ;
	} 
	while ( ( nom_fichier_1 != NULL ) && ( nom_fichier_1 != nom_fichier_2 ) ) ;

	if ( ok )	
		strcpy ( nom_fichier_2, Ext ) ;
	else 
		strcat ( nom_fichier , Ext ) ;

	return nom_fichier ;
}

/////////////////////////////////////////////////////////////////////////////////////
// CREE LA MATRICE AVEC LES RELATIONS ENTRE SOMMET
//
float ** Creer_Matrice_Carre ( int Nbr )
{
	int L, C ;

	float ** mat = ( float ** ) malloc ( Nbr * sizeof ( float * ) ) ;

	for ( L = 0 ; L < Nbr ; L++ )
	{
		mat [ L ] = ( float * ) malloc ( Nbr * sizeof ( float ) ) ;

		for ( C = 0 ; C < Nbr ; C++ )
			mat [ L ][ C ] = 0.0 ;			
	}
	return mat ;
}

/////////////////////////////////////////////////////////////////////////////////////
// AJOUTE UN NOM Dans une liste
//
int AjouteNom ( char * Nom, char *** Liste, int * Nbr )
{
	char ** Nom_tmp = malloc ( ( ( *Nbr ) + 1 ) * sizeof ( char * )  ) ;
	char * Nom_cp  = malloc ( ( strlen ( Nom ) + 1  ) * sizeof( char ) ) ;
	memcpy ( Nom_cp, Nom, strlen( Nom ) + 1 ) ;

	if ( *Liste != NULL )
	{
		memcpy ( Nom_tmp, *Liste , (*Nbr) * sizeof ( char * ) ) ;
		free ( *Liste ) ;
	}
	Nom_tmp [ (*Nbr) ] = Nom_cp ;
	*Liste = Nom_tmp ;

	return ( (*Nbr) ++ ) ;
}

//////////////////////////////////////////////////////////////////////////////////////
// AFFICHE LE FICHIER 
//
void Affiche_Fichier ( FILE * tmp )
{
	int ic ;

	fseek ( tmp, 0L , SEEK_SET ) ;

	while ( EOF != ( ic = fgetc( tmp ) ) )
		printf ( "%c", (unsigned char) ic ) ;
}

/////////////////////////////////////////////////////////////////////////////////////
// CHERHCE UN NOM DANS LA LISTE, RETOURNE SA PLACE
//
int Cherche ( char * Nom, char ** Liste, int Nbr ) 
{
	int i ;
	for ( i = 0 ; i < Nbr ; i++ )
		if ( strcasecmp ( Nom, Liste[ i ] ) == 0 )
			return i ;
	return -1 ;
}

/////////////////////////////////////////////////////////////////////////////////////
//
//
int Copy_File ( FILE * Cible, FILE * Source )
{
	char Tmp [ 50 ] ;
	size_t nbr, som ; 

	som = 0 ;
	rewind ( Source ) ;
	rewind ( Cible ) ;

	do
	{
		nbr = fread( Tmp, 1, 50, Source ) ;
		fwrite ( Tmp, 1, nbr, Cible ) ;
		som += nbr ;
	} 
	while ( nbr == 50 ) ;

	return som ;
}

/////////////////////////////////////////////////////////////////////////////////////
// ECRIT LE FICHIER CIBLE AVEC LA MATRICE RELATION
//
int Write_matrix_to_file( FILE * cible, int nbr, char ** liste_nom, float ** mat_max, float ** mat_conso, int write_nom, int write_cons )
{
        int L, C ;

        // Number of vertices
        fprintf ( cible, "%d\n", nbr ) ;

        // Name of vertices
        if ( write_nom ) //OPTIONS & O_NOM )
        {
                for ( L = 0 ; L < nbr ; L++ )
                        fprintf ( cible, "%s ", liste_nom [ L ] ) ;
                fprintf ( cible, "\n" ) ;
        }

        // Matrix of max flow
        for ( L = 0 ; L < nbr ; L++ )
        {
                for ( C = 0 ; C < nbr ; C++ )
                        fprintf ( cible, "%f ", mat_max [ L ][ C ] ) ;
                fprintf ( cible, "\n" ) ;
        }
        // ----------------
        fprintf ( cible, "---------\n" ) ;

        if ( write_cons ) //OPTIONS & O_CONSO )
        {
                for ( L = 0 ; L < nbr ; L++ )
                {
                        for ( C = 0 ; C < nbr ; C++ )
                                fprintf ( cible, "%f ", mat_conso [ L ][ C ] ) ;
                        fprintf ( cible, "\n" ) ;
                }
        }
        return 0 ;
} 

