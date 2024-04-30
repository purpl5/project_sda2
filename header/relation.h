#ifndef RELATION_H
#define RELATION_H

typedef int bool;
#define false 0
#define true -1

typedef enum {
    FRERE = 2,
    COUSIN,
    PARENT,
    ONCLE,
    EPOUX,
    AMI,
    VIT,
    CONNAIT,
    CHEF,
    COLLEGUE,
    LOCATAIRE,
    TRAVAILLE,
    PROPRIETAIRE,
    SITUE,
    DECOUVERT
} rtype;

typedef struct s_node {
    void* val;  // pointeur vers objet quelconque
    struct s_node* suiv;
} * listeg;

bool est_lien_parente(rtype id);
bool est_lien_professionel(rtype id);
bool est_lien_connaissance(rtype id);
char* toStringRelation(rtype id);

listeg listegnouv();
listeg adjtete(listeg lst, void* x);
listeg adjqueue(listeg lst, void* x) ;
void supprimer(listeg item);
void* tete(listeg lst);
int longueur(listeg lst);
bool estvide(listeg lst);
void detruire(listeg lst);
listeg rech(listeg lst, void* x, int (*comp)(void*, void*));

#endif