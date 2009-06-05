
#define DEBUG_1 if (   ( (i==4) && (LeSommet==5) )  ||  ( (i==5) && (LeSommet==4) )    ) { RED printf ("\n/!\\"); } \
                        printf ( "\n%s(N°%d/%d)(Mk%d/%d) %s Max: %.2f  Conso: %.2f  ConsoMoins: %.2f", NomSommet[LeSommet], LeSommet, i,Sommet[LeSommet],Sommet[i], NomSommet[i], Matrice_Max[LeSommet][i], Matrice_Conso[LeSommet][i], Matrice_Conso[i][LeSommet] ) ;\
                        DEFAULT_COLOR


