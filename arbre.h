#ifndef _ARBRE
#define _ARBRE




struct sNoeud {
  int info;
  struct sNoeud * fg;
  struct sNoeud * fd;
};
typedef struct sNoeud Noeud;


struct sArbre {
  Noeud * adRacine; 
  int nbElemDansArbre;
};
typedef struct sArbre Arbre;


void initialiserArbre(Arbre * pA);
/* Precondition : *pA non prealablement initialise
   Postcondition : *pA est initialise vide */


void testamentArbre(Arbre *pA);
/* Precondition : *pA prealablement initialise
   Postcondition : *pA pret a disparaitre (ne doit plus etre utilise) */


int testArbreVide(Arbre A);
/* Precondition : A initialise
   Resultat : 1 si A est vide, 0 sinon */


void affichageInfixeArbre(Arbre A);
/* Precondition : A initialise
   Postcondition : Affichage infixe de tous les elements de A */

void affichageArborescent(Arbre A);
/* Precondition : A initialise
   Postcondition : Affichage infixe de tous les elements de A */

void insererElement(int e, Arbre *pA);
/* Precondition : *pA est un arbre binaire de recherche initialise
   Postcondition : si e n'existait pas deja dans l'arbre *pA, alors
   un nouveau noeud contenant e est insere aux feuilles de *pA. 
   Si au contraire e existait deja dans l'arbre, alors l'arbre est
   inchange. */


void rechercheElement(int e, Arbre A, int * trouve, int * nb_visites);
/* Precondition : A initialise
   Postcondition : si aucun noeud de l'arbre A ne contient la valeur e passee
   en parametre, l'entier *trouve vaut 0. Si au contraire on a trouve un
   noeud avec le e demande, alors *trouve vaut 1. Dans les deux cas, nb_visites
   contient le nombre de noeuds visites lors de cette recherche. */


int hauteur(Arbre a);
/* Precondition : a initialise
   Résultat : renvoie la hauteur de l'arbre (longueur de sa plus
   longue branche), ou -1 s'il est vide */

double profondeurMoyenne(Arbre a);
/* Precondition : a initialise
   Resultat : somme des profondeurs de tous les noeuds de l'arbre, 
   divisee par le nombre de noeuds. La profondeur de la racine est 0,
   celle des fils de la racine est 1, celle des fils des fils de la
   racine est 2, etc. */



#endif
