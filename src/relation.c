#include "../header/base.h"
#include "../header/relation.h"

////////////////////////////////////////
// Exercice 1: Classement des Relations

bool est_lien_parente(rtype id) {
    if (id >= 2 && id <= 6)
        return true;

    return false;
}

bool est_lien_professionel(rtype id) {
    if (id == 10 && id == 11)
        return true;

    return false;
}

bool est_lien_connaissance(rtype id) {
    if (id >= 7 && id <= 9)
        return true;

    return false;
}

char* toStringRelation(rtype id) {
    char* relations[15] = {"frère ou soeur de",
                           "cousin ou cousine de",
                           "parent de",
                           "oncle ou tante de",
                           "époux ou épouse de",
                           "ami(e) de",
                           "vit à",
                           "connaît",
                           "chef de",
                           "collègue de",
                           "locataire de",
                           "travaille pour",
                           "propriétaire de",
                           "est situé(e) à",
                           "a découvert"};

    return relations[id - 2];
}



////////////////////////////////////////
// Exercice 2: Liste de pointeurs

listeg listegnouv() {
    return (listeg) NULL;
}


listeg adjtete(listeg lst, void* x) {
    listeg new = (listeg) malloc(sizeof(struct s_node));
    if (new == NULL) {
        printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    new->suiv = lst;
	new->val = x;

    return new;
}

listeg adjqueue(listeg lst, void* x) {
    return lst;
}

listeg suptete(listeg lst) {
    return lst;
}

void* tete(listeg lst) {
    return NULL;
}

int longueur(listeg lst) {
    return -1;
}

bool estvide(listeg lst) {
    return false;
}

void detruire(listeg lst) {}

listeg rech(listeg lst, void* x, int (*comp)(void*, void*)) {
    return NULL;
}

/*
////////////////////////////////////////
// Exercice 3: Construction du graphe

#define LONG_NOM_MAX 64
typedef enum { PERSONNE = 1, OBJET, ADRESSE, VILLE } etype;
typedef struct s_entite {
    char nom[LONG_NOM_MAX];  // le nom de l�entit� p.ex � Peugeot 106 �
    etype ident;             // l�identifiant associ�, p.ex OBJET
} * Entite;
// 3.1 les structures de donn�es
typedef struct s_sommet {
    // A DEFINIR
} * Sommet;

typedef struct s_arc {
    // A DEFINIR
} * Arc;

typedef struct s_relations {
    // A DEFINIR
} * Relations;

// 3.2 les constructeurs
Entite creerEntite(char* s, etype e) {
    return NULL;
}
Sommet nouvSommet(Entite e) {
    return NULL;
}
Arc nouvArc(Entite e, rtype type) {
    return NULL;
}
void relationInit(Relations* g) {}
void relationFree(Relations* g) {}

// 3.3 les comparaisons
int compEntite(void* e, void* string) {
    return 0;
}
int compSommet(void* s, void* string) {
    return 0;
}
int compArc(void* a, void* string) {
    return 0;
}

// 3.4 ajout d'entites et de relations
void adjEntite(Relations g, char* nom, etype t) {}
// PRE CONDITION: id doit �tre coh�rent avec les types des sommets
// correspondants � x et y
//                p.ex si x est de type OBJET, id ne peut pas etre une relation
//                de parente
// PRE CONDITION: strcmp(nom1,nom2)!=0
void adjRelation(Relations g, char* nom1, char* nom2, rtype id) {}

////////////////////////////////////////
// Exercice 4: Explorer les relations entre personnes

// 4.1 listes de relations
listeg en_relation(Relations g, char* x) {
    return NULL;
}
listeg chemin2(Relations g, char* x, char* y) {
    return NULL;
}
// 4.2 verifier un lien de parente
// PRE CONDITION: strcmp(x,y)!=0
bool ont_lien_parente(Relations g, char* x, char* y) {
    return false;
}

// 4.3 tester connaissances
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent(Relations g, char* x, char* y) {
    return false;
}
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent_proba(Relations g, char* x, char* y) {
    return false;
}
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent_peutetre(Relations g, char* x, char* y) {
    return false;
}

////////////////////////////////////////
// Exercice 5: Affichages

void affichelg(listeg l, void (*aff)(void*)) {}

void afficheEntite(void* x) {}
void afficheArc(void* x) {}

////////////////////////////////////////
// Exercice 6: Parcours
void affiche_degre_relations(Relations r, char* x) {}
*/