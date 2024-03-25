
#include "arbre.h" 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 

#define ABS(a) (((a)>0)?(a):(-(a)))

/* ------------------------------ */
/* Declaration Fonctions internes */
/* ------------------------------ */

static void initialiserNoeud(Noeud *pN, int e); 
/* Precondition : *pN non prealablement initialise, e prealablement initialise 
   Postcondition : le noeud initialise est un noeud feuille contenant dans son 
   champ info une copie de e */


static void detruireAPartirDe(Noeud *pN, Arbre *pA);
/* Precondition : *pA initialise, pN est l'adresse d'un noeud valide de l'arbre *pA, 
   ou NULL. 
   Postcondition : Libere la mémoire pour tous les noeuds du sous-arbre issu de *pN,
   pN inclus. Attention, le pointeur donné en paramètre ne doit plus être
   utilise après appel à cette procédure (pour faire plus propre, on aurait pu utiliser
   un pointeur de pointeur **ppN, afin de pouvoir mettre *ppN à NULL,
   et eviter une erreur de l'utilisateur). */

static void affichageInfixeDepuisNoeud(const Noeud *pN, Arbre A);
/* Precondition : A initialisé, pN est l'adresse d'un noeud valide de l'arbre A, ou NULL
   Postcondtion : affichage dans l'ordre infixe des elements du sous-arbre de A 
   enracine en *pN */


static void insererElementDansSSArbre(int e, Noeud ** ppN, Arbre *pA);
/* Preconditions : 
   1) *pA est un arbre binaire de recherche initialisé et non vide;
   2) ppN est l'adresse d'une case memoire contenant une adresse de noeud 
      de l'arbre *pA (adresse du champ adRacine de l'arbre, ou adresse du 
      champ fg ou fd d'un noeud de l'arbre *pA);    
   3) l'insertion du mot dans le sous-arbre enracine en **ppN ne viole pas la 
      propriete d'arbre binaire de recherche de *pA
   Postcondition : si e n'existait pas deja dans l'arbre *pA, alors
   un nouveau noeud contenant e est insere aux feuilles de *pA. Si au contraire 
   e existait deja dans l'arbre, alors l'arbre reste inchange. */


static void affichageArborescent_par_niveau (Noeud *pN, int niv);
/* Procédure récursive interne permettant d'afficher l'arbre 
	 sous sa forme arborescente a partir du noeud pN 
	 niv est la profondeur du noeud pN */
	 
static int calculHauteurDepuisSSArbre(const Noeud * n);
/* Fonction interne utilisee par hauteur */





/* ----------- */
/* Definitions */
/* ----------- */


/* ------------------------ */
/*  Vie et mort des arbres  */
/* ------------------------ */

static void initialiserNoeud(Noeud *pN, int e)
{
  pN->info = e;
  pN->fg = NULL;
  pN->fd = NULL;
}


void initialiserArbre(Arbre *pA)
{
	pA->adRacine = NULL; 
    pA->nbElemDansArbre = 0; 
}


/*void testamentArbre(Arbre *pA)
{
    libererNoeud(pA->adRacine); 
    pA->adRacine = NULL; 
    pA->nbElemDansArbre = 0; 
}*/

static void libererNoeud(Noeud *pN) {
    if (pN == NULL) {
        return;
    }

    libererNoeud(pN->fg); 
    libererNoeud(pN->fd); 

    free(pN); 
}


static void detruireAPartirDe(Noeud *pN, Arbre *pA)
{
    if (pN == NULL) {
        return; 
    }

    
    detruireAPartirDe(pN->fg, pA);
    detruireAPartirDe(pN->fd, pA);

    
    free(pN);

    
    pA->nbElemDansArbre--;
}



int testArbreVide(Arbre A)
{
  if (A.adRacine==NULL) return 1;
  else return 0;
}

void insererElement(int e, Arbre *pA) {
   Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    if (nouveauNoeud == NULL) {
        return;
    }

    nouveauNoeud->info = e;
    nouveauNoeud->fg = NULL;
    nouveauNoeud->fd = NULL;

    if (pA->adRacine == NULL) {
        pA->adRacine = nouveauNoeud; 
        pA->nbElemDansArbre++;
        return;
    }

    Noeud* temp = pA->adRacine;
    Noeud* parent = NULL;

    while (temp != NULL) {
        parent = temp;

        if (e < temp->info) {
            temp = temp->fg; 
        } else if (e > temp->info) {
            temp = temp->fd; 
        } else {
            free(nouveauNoeud);
            return;
        }
    }

    
    if (e < parent->info) {
        parent->fg = nouveauNoeud;
    } else {
        parent->fd = nouveauNoeud;
    }

    pA->nbElemDansArbre++;
}

Noeud* creerNoeud(int e) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    if (nouveauNoeud != NULL) {
        nouveauNoeud->info = e;
        nouveauNoeud->fg = NULL;
        nouveauNoeud->fd = NULL;
    }
    return nouveauNoeud;
}


static void insererElementDansSSArbre(int e, Noeud **ppN, Arbre *pA) {
    if (*ppN == NULL) {
        *ppN = creerNoeud(e);
    } else if (e < (*ppN)->info) {
        insererElementDansSSArbre(e, &((*ppN)->fg), pA);
    } else if (e > (*ppN)->info) {
        insererElementDansSSArbre(e, &((*ppN)->fd), pA);
    }
    
}


/* ----------- */
/*  Affichage  */
/* ----------- */


static void affichageInfixeDepuisNoeud(const Noeud *pN, Arbre A)
{
  if (pN != NULL)
    {
      affichageInfixeDepuisNoeud(pN->fg, A);
      printf("%d",pN->info);  
      putchar('\n');
      affichageInfixeDepuisNoeud(pN->fd, A);
    }
}


void affichageInfixeArbre(Arbre A)
{ 
  printf("Nombre d'elements : %d \n",A.nbElemDansArbre);
  affichageInfixeDepuisNoeud(A.adRacine, A);
  putchar('\n');
}

void affichageArborescent(Arbre A) {
	affichageArborescent_par_niveau(A.adRacine, 0);
}

static void affichageArborescent_par_niveau (Noeud *pN, int niv) {
	int i;
	if (pN==NULL) {
		for (i=0; i<4*niv; i++) {
			putchar (' ');
		}
		printf("NULL\n");
	}
	else {
		affichageArborescent_par_niveau(pN->fd, niv+1);
		for (i=0; i<4*niv; i++) {
			putchar (' ');
		}
               printf("%d",pN->info);  
		printf("\n");
		affichageArborescent_par_niveau(pN->fg, niv+1);
		
	}
}


/* ------------------- */
/*  Utilitaires divers */
/* ------------------- */
 
void rechercheElement(int e, Arbre A, int * trouve, int * nb_visites) 
{
	*trouve = 0; 

    Noeud *pN = A.adRacine; 

    while (pN != NULL) {
        if (e == pN->info) {
            *trouve = 1; 
            return;
        } else if (e < pN->info) {
            pN = pN->fg; 
        } else {
            pN = pN->fd; 
        }
    }
}

static int hauteurNoeud(Noeud *n) {
    if (n == NULL) {
        return -1; // Height of an empty subtree is -1
    } else {
        int hauteurGauche = hauteurNoeud(n->fg);
        int hauteurDroite = hauteurNoeud(n->fd);

        return 1 + (hauteurGauche > hauteurDroite ? hauteurGauche : hauteurDroite);
    }
}

// Function to calculate the height of the tree
int hauteur(Arbre a) {
    return hauteurNoeud(a.adRacine);
}

static int calculHauteurDepuisSSArbre(const Noeud * pN)
{
	 if (pN == NULL) {
        return -1; 
    }

    int hauteurGauche = calculHauteurDepuisSSArbre(pN->fg);
    int hauteurDroite = calculHauteurDepuisSSArbre(pN->fd);

    return 1 + (hauteurGauche > hauteurDroite ? hauteurGauche : hauteurDroite);
  
}



