
struct Liste
{
        struct Chainon * prems  ;       // Premier element de la liste
        struct Chainon * der    ;       // Dernier element de la liste
};
struct Chainon
{
         int Sommet ;              // Numero du sommet
         struct Chainon * suiv ;   // Sommet a parcourir apres
};

void AjouteFin ( int Som, struct Liste * L ) ;
void SupprimeDer ( struct Liste * L ) ;
void SupprimePrems ( struct Liste * L );

