#include "../header/base.h"
#include "../header/relation.h"
#include "../header/verifEntiteExiste.h"

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
        if (DEBUG) printf("fatal error: no memory allocation possible.\n");
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
        if (DEBUG) ("fatal error: no memory allocation possible.\n");
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
        if (comp(lst->val, x) == true)
            adjtete(result, lst->val);
        lst = lst->suiv;
    }

    return result;
}

////////////////////////////////////////
// Exercice 3: Construction du graphe

// 3.1 localiser dans le fichier relation.h

// 3.2 les constructeurs
Entite creerEntite(char* s, etype e) {
    Entite new = (Entite)malloc(sizeof(struct s_entite));
    if (new == NULL) {
        if (DEBUG) printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    if (strlen(s) > LONG_NOM_MAX) {
        if (DEBUG) printf("fatal error: name too long.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(new->nom, s);
    new->ident = e;

    return new;
}
Sommet nouvSommet(Entite e) {
    Sommet new = (Sommet)malloc(sizeof(struct s_sommet));
    if (new == NULL) {
        if (DEBUG) printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    new->larcs = listegnouv();
    new->x = e;

    return new;
}

Arc nouvArc(Entite e, rtype type) {
    Arc new = (Arc)malloc(sizeof(struct s_arc));

    if (new == NULL) {
        if (DEBUG) printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    new->relationType = type;
    new->x = e;

    return new;
}

void relationInit(Relations* g) {
    (*g) = (Relations)malloc(sizeof(struct s_relations));

    if (g == NULL) {
        if (DEBUG) printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    if ((*g) == NULL) {
        if (DEBUG) printf("fatal error: no memory allocation possible.\n");
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
    Sommet s = nouvSommet(e);

    if (g->entites == NULL) {
        g->entites = adjtete(g->entites, s);
        return;
    }

    if (verifEntiteExiste(g->entites, e) == true) {
        if (DEBUG) printf("fatal error: entity already exists.\n");
        return;
    } else {
        g->entites = adjqueue(g->entites, s);
    }

    return;
}

// PRE CONDITION: id doit �tre coh�rent avec les types des sommets
// correspondants � x et y
//                p.ex si x est de type OBJET, id ne peut pas etre une relation
//                de parente
// PRE CONDITION: strcmp(nom1,nom2)!=0

void adjRelation(Relations g, char* nom1, char* nom2, rtype id) {
    listeg tmp = g->entites;

    while (compEntite(((Sommet)tmp->val)->x, nom1) == false) {
        if (tmp == NULL) {
            if (DEBUG) printf("fatal error: entity not found.\n");
            exit(EXIT_FAILURE);
        }

        tmp = tmp->suiv;
    }

    if (((Sommet)tmp->val)->x->ident == OBJET && est_lien_parente(id) == true) {
        if (DEBUG) printf("error: object cannot have a parent relation.\n");
        return;
    }

    Entite e = creerEntite(nom2, PERSONNE);
    Arc a = nouvArc(e, id);

    ((Sommet)tmp->val)->larcs = adjqueue(((Sommet)tmp->val)->larcs, a);
}

////////////////////////////////////////
// Exercice 4: Explorer les relations entre personnes

// 4.1 listes de relations
listeg en_relation(Relations g, char* x) {
    listeg e = g->entites;

    while (compEntite(((Sommet)e->val)->x, x) == false) {
        if (e->suiv == NULL) {
            if (DEBUG) printf("error: entity not found.\n");
            return NULL;
        }

        e = e->suiv;
    }

    return ((Sommet)e->val)->larcs;
}

listeg chemin2(Relations g, char* x, char* y) {
    listeg result = listegnouv();
    listeg zList = en_relation(g, x);

    while (zList != NULL) {
        listeg relationZ = en_relation(g, ((Arc)zList->val)->x->nom);
        while (relationZ != NULL) {
            if (compEntite(((Arc)relationZ->val)->x, y) == true) {
                result = adjqueue(result, ((Arc)zList->val)->x);
            }

            relationZ = relationZ->suiv;
        }

        zList = zList->suiv;
    }

    return result;
}

// 4.2 verifier un lien de parente
// PRE CONDITION: strcmp(x,y)!=0
bool ont_lien_parente(Relations g, char* x, char* y) {
    return false;
}

/*
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
*/
////////////////////////////////////////
// Exercice 5: Affichages

void affichelg(listeg l, void (*aff)(void*)) {
    while (l != NULL) {
        aff(l->val);
        l = l->suiv;
    }
}

void afficheEntite(void* x) {
    printf("l'entite : %s\n", ((Entite)x)->nom);
}

void afficheArc(void* x) {
    printf("a une relation %s avec %s\n",
           toStringRelation(((Arc)x)->relationType), ((Arc)x)->x->nom);
}

////////////////////////////////////////
// Exercice 6: Parcours
/*
void affiche_degre_relations(Relations r, char* x) {}
*/