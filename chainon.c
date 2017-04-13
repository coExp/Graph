#include "graph.h"

#define SI_PAS_DE_PREMS	if ( ! L->prems ){ \
		L->prems = NULL ;	\
		L->der = NULL ;		\
		return ; }	

// Ajoute un chainon au debut de la liste ----------------------------------------
/*struct Chainon * AjouteDebut ( int Som, struct Chainon * L ) 
{
	struct Chainon * C = ( struct Chainon * ) malloc ( sizeof ( struct Chainon ) );
	( *C ).suiv = L;
	( *C ).Sommet = Som;
	return C ;
}*/

// Supprime le premier elemement de la liste -------------------------------------
/*struct Chainon * Supprime ( struct Chainon * L ) 
{
	struct Chainon * C = ( *L ).suiv ;	
	free ( L ) ;
	return C ;
}*/

/*struct Chainon * AjouteDebut ( int Som, struct Liste * L ) 
{
	
}*/
void AjouteFin (int Som, struct Liste * L)
{
	struct Chainon * C = (struct Chainon *) malloc (sizeof(struct Chainon));
	
	C->Sommet = Som;
	C->suiv = NULL;
	
	if (L->der)
		L->der->suiv = C;
	else
		L->prems = C;
		
	L->der = C;
	
	return;
}

void SupprimePrems (struct Liste * L)
{
	SI_PAS_DE_PREMS

	struct Chainon * C = L->prems;
	L->prems = C->suiv;
	free(C);

	SI_PAS_DE_PREMS
}

void SupprimeDer (struct Liste * L)
{
	if (!L->prems) {
		L->prems = NULL;
		L->der = NULL;
		return;
	}

	struct Chainon * AvantC = NULL;
	struct Chainon * LeC    = L->prems;
	
	while (LeC->suiv) {
        AvantC = LeC;
        LeC = LeC->suiv;
	}

	if (!AvantC) {
		L->prems = NULL;
		L->der = NULL;
		return;
	}

	free(LeC);
	L->der = AvantC;
	L->der->suiv = NULL;
	return;
}
