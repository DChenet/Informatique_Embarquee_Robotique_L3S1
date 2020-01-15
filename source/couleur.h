#include <stdbool.h>

#define DETECT_SEUIL 120
#define DETECT_ECART 60

typedef struct {
    int r;
    int g;
    int b;
}Couleur;

Couleur allocCouleur();
Couleur createCouleur(int r, int g, int b);

bool estRouge(Couleur couleur);
bool estVert(Couleur couleur);
bool estBleu(Couleur couleur);