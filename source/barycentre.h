typedef struct {
    int x;
    int y;
}B_Point;

typedef struct {
    int max_size;
    int size;
    B_Point *tab;
}ListePoints;

#define ZONE_MORTE 15
#define ZONE_LENTE 60
#define DOUBLE_VITESSE 1

B_Point initPoint(int x, int y);
void affPoint(B_Point p);
ListePoints initListePoint(int size);
void affListe(ListePoints lp);
void inserPoint(ListePoints * lp, B_Point p);
void viderListe(ListePoints * lp);
B_Point calculateBarycentre(ListePoints lp);
B_Point convertToCenter(B_Point p, int h, int w);
const char * getCommandeX(B_Point pos);
const char * getCommandeY(B_Point pos);


