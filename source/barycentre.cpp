#include "barycentre.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

B_Point initPoint(int x, int y){
    B_Point *p = (B_Point*)malloc(sizeof(B_Point));
    p->x = x;
    p->y = y;
    return *p;
}

void affPoint(B_Point p){
    printf("Point x: %d , y: %d\n",p.x,p.y);
}

ListePoints initListePoint(int size){
    ListePoints lp;
    lp.max_size = size;
    lp.size = 0;
    lp.tab = (B_Point*)malloc(size*sizeof(B_Point));
    return lp;
}

void affListe(ListePoints lp){
    printf("Liste (s=%d) (ms=%d): \n",lp.size,lp.max_size);
    for(int i = 0 ; i < lp.size ; i++){
        B_Point p = lp.tab[i];
        affPoint(p);
    }
}

void inserPoint(ListePoints * lp, B_Point p){
    if(lp->size != lp->max_size){
        lp->tab[lp->size] = p;
        lp->size = lp->size+1;
    }

    else{
        printf("Liste pleine");
    }
}

B_Point calculateBarycentre(ListePoints lp){
    B_Point p = initPoint(0,0);
    if(lp.size != 0){
        for(int i = 0 ; i < lp.size ; i++){
            B_Point pl = lp.tab[i];
            p.x = p.x + pl.x;
            p.y = p.y + pl.y;
        }

        p.x = p.x / lp.size;
        p.y = p.y / lp.size;
        return p;
    }
    
    
    else{
        return p;
    }
}

B_Point convertToCenter(B_Point p, int h, int w){
    p.x = p.x-(h/2);
    p.y = p.y-(w/2);
    return p;
}

const char * getCommandeX(B_Point pos){
    const char * commande = (char *) malloc( 1 );
    if(pos.x > ZONE_MORTE){
        #if DOUBLE_VITESSE == 1
        if(pos.x < ZONE_LENTE){
            commande = "s";
        } 

        else{
            commande = "ss";
        }
        #else
            commande = "s";
        #endif
    }

    else{
        if(pos.x < -ZONE_MORTE){
            #if DOUBLE_VITESSE == 1
            if(pos.x > -ZONE_LENTE){
            commande = "z";
            } 

            else{
            commande = "zz";
            }
            #else
            commande = "z";
            #endif
        }

        else{
            commande ="";
        }
    }

    return commande;
}

const char * getCommandeY(B_Point pos){
    const char * commande = (char *) malloc( 1 );
    if(pos.y > ZONE_MORTE){
        #if DOUBLE_VITESSE == 1
        if(pos.y < ZONE_LENTE){
            commande = "q";
        } 

        else{
            commande = "qq";
        }
        #else
        commande = "q";
        #endif
    }

    else{
        if(pos.y < -ZONE_MORTE){
            #if DOUBLE_VITESSE == 1
            if(pos.y > -ZONE_LENTE){
                commande = "d";
            }  

            else{
                commande = "dd";
            }
            #else
            commande = "d";
            #endif
        }

        else{
            commande ="";
        }
    }

    return commande;
}