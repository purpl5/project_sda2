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
    return (listeg)NULL;
}

listeg adjtete(listeg lst, void* x) {
    listeg new = (listeg)malloc(sizeof(struct s_node));
    if (new == NULL) {
        printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    new->suiv = lst;
    new->val = x;

    return new;
}

listeg adjqueue(listeg lst, void* x) {
    listeg new = (listeg)malloc(sizeof(struct s_node));
    new->val = x;
    new->suiv = NULL;

    if (new == NULL) {
        printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    if (lst == NULL)
        return new;

    listeg tmp = lst;
    while (tmp->suiv != NULL)
        tmp = tmp->suiv;

    tmp->suiv = new;

    return lst;
}

void supprimer(listeg item) {
    if (item == NULL)
        return;
    item->suiv = NULL;

    free(item->val);
    free(item);
}

listeg suptete(listeg lst) {
    if (lst == NULL)
        exit(1);

    listeg next = lst->suiv;
    supprimer(lst);

    return next;
}

void* tete(listeg lst) {
    if (lst == NULL)
        exit(EXIT_FAILURE);
    return lst->val;
}

int longueur(listeg lst) {
    if (lst == NULL)
        return 0;
    return 1 + longueur(lst->suiv);
}

bool estvide(listeg lst) {
    return lst == NULL ? true : false;
}

void detruire(listeg lst) {
    while (lst != NULL) {
        listeg next = lst->suiv;
        supprimer(lst);
        lst = next;
    }
}

listeg rech(listeg lst, void* x, int (*comp)(void*, void*)) {
    listeg result = (listeg)malloc(sizeof(struct s_node));

    while (lst != NULL) {
        if (comp(lst->val, x) == 0)
            adjtete(result, lst->val);
        lst = lst->suiv;
    }

    return result;
}

////////////////////////////////////////
// Exercice 3: Construction du graphe

// 3.1 les structures de donn�es
typedef struct s_sommet {
    struct s_node* larcs;
    struct s_entite* x;
} * Sommet;

typedef struct s_arc {
    rtype type;
    struct s_entite* x;
} * Arc;

typedef struct s_relations {
    listeg entites;
} * Relations;

// 3.2 les constructeurs
Entite creerEntite(char* s, etype e) {
    Entite new = (Entite)malloc(sizeof(struct s_entite));
    if (new == NULL) {
        printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    if (strlen(s) > LONG_NOM_MAX) {
        printf("fatal error: name too long.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(new->nom, s);
    new->ident = e;

    return new;
}
Sommet nouvSommet(Entite e) {
    Sommet new = (Sommet)malloc(sizeof(struct s_sommet));
    if (new == NULL) {
        printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    new->larcs = listegnouv();
    new->x = e;

    return NULL;
}

Arc nouvArc(Entite e, rtype type) {
    Arc new = (Arc)malloc(sizeof(struct s_arc));

    if (new == NULL) {
        printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    new->type = type;
    new->x = e;

    return NULL;
}

void relationInit(Relations* g) {
    g = (Relations*)malloc(sizeof(Relations));

    if (g == NULL) {
        printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    (*g)->entites = listegnouv();
}

void relationFree(Relations* g) {
    detruire((*g)->entites);
    free(g);
}

// 3.3 les comparaisons
int compEntite(void* e, void* string) {
    if (strcmp((char*)((Entite)e)->nom, (char*)string) == 0)
        return true;

    return false;
}

int compSommet(void* s, void* string) {
    return compEntite((Entite)((Sommet)s)->x, string);
}
int compArc(void* a, void* string) {
    return compEntite((Entite)((Arc)a)->x, string);
}

// 3.4 ajout d'entites et de relations
void adjEntite(Relations g, char* nom, etype t) {
    Entite e = creerEntite(nom, t);
}

// PRE CONDITION: id doit �tre coh�rent avec les types des sommets
// correspondants � x et y
//                p.ex si x est de type OBJET, id ne peut pas etre une relation
//                de parente
// PRE CONDITION: strcmp(nom1,nom2)!=0
void adjRelation(Relations g, char* nom1, char* nom2, rtype id) {}
/*
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