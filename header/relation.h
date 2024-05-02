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
listeg adjqueue(listeg lst, void* x);
void supprimer(listeg item);
void* tete(listeg lst);
int longueur(listeg lst);
bool estvide(listeg lst);
void detruire(listeg lst);
listeg rech(listeg lst, void* x, int (*comp)(void*, void*));

#define LONG_NOM_MAX 64
typedef enum { PERSONNE = 1, OBJET, ADRESSE, VILLE } etype;
typedef struct s_entite {
    char nom[LONG_NOM_MAX];  // le nom de l�entit� p.ex � Peugeot 106 �
    etype ident;             // l�identifiant associ�, p.ex OBJET
} * Entite;

// 3.1 les structures de donn�es

typedef struct s_sommet {
    struct s_node* larcs;
    struct s_entite* x;
} * Sommet;

typedef struct s_arc {
    rtype relationType;
    struct s_entite* x;
} * Arc;

typedef struct s_relations {
    listeg entites;
} * Relations;

Entite creerEntite(char* s, etype e);
Sommet nouvSommet(Entite e);
Arc nouvArc(Entite e, rtype type);

void relationInit(Relations* g);

int compEntite(void* e, void* string);
int compSommet(void* s, void* string);
int compArc(void* a, void* string);

void adjEntite(Relations g, char* nom, etype t);
void adjRelation(Relations g, char* nom1, char* nom2, rtype id);

listeg en_relation(Relations g, char* x);

void affichelg(listeg l, void (*aff)(void*));
void afficheEntite(void* x);
void afficheArc(void* x);

listeg chemin2(Relations g, char* x, char* y);

bool ont_lien_parente(Relations g, char* x, char* y);

#endif