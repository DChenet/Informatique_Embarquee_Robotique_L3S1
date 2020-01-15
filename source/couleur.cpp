#include "couleur.h"
#include <stdbool.h>
#include <stdlib.h>

Couleur createCouleur(int r, int g, int b){
    Couleur* c = (Couleur*)malloc(sizeof(Couleur));
    c->r = r;
    c->g = g;
    c->b = b;
    return *c;
}

bool estRouge(Couleur couleur){
    int r = couleur.r;
    int g = couleur.g;
    int b = couleur.b;

    return b>g+DETECT_ECART && b>r+DETECT_ECART && r<DETECT_SEUIL && g<DETECT_SEUIL;
}

bool estBleu(Couleur couleur){
    int r = couleur.r;
    int g = couleur.g;
    int b = couleur.b;

    return b<40 && g<40 && r>b && r>g;
}

bool estVert(Couleur couleur){
    int r = couleur.r;
    int g = couleur.g;
    int b = couleur.b;

    return g>r && g>b && (r<g-38 || b<g-38);
}