#include <stdio.h>
#include "arbre.h"
#include "arbre.c"

int main() {
    Arbre arbre;
    initialiserArbre(&arbre);
    insererElement(5, &arbre);
    insererElement(3, &arbre);
    insererElement(7, &arbre);
    insererElement(5, &arbre);
    insererElement(3, &arbre);
    insererElement(7, &arbre);
    insererElement(2, &arbre);
    insererElement(4, &arbre);
    insererElement(6, &arbre);
    insererElement(8, &arbre);
    affichageInfixeArbre(arbre);
    affichageArborescent(arbre);
    int trouve = 0;
    int nb_visites = 0;
    int element_to_search = 3;
    rechercheElement(element_to_search, arbre, &trouve, &nb_visites);

    if (trouve) {
        printf("Element %d found in the tree.\n", element_to_search);
    } else {
        printf("Element %d not found in the tree.\n", element_to_search);
    }

    printf("Number of nodes visited during search: %d\n", nb_visites);
    
    
    int tree_height = hauteur(arbre);
    printf("Height of the tree: %d\n", tree_height);

    

    return 0;
}
