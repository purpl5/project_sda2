// relations.c�: d�finit le point d'entr�e pour l'application .
//

typedef int bool;
#define false 0
#define true -1
#define DEBUG 1  // 0: disable debug, 1: enable debug

#include "memory.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

////////////////////////////////////////
// Exercice 1: Classement des Relations

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

bool est_lien_parente(rtype id) {
    // vérifie que l'id est bien une relation de parenté
    if (id >= 2 && id <= 6)
        return true;

    return false;
}

bool est_lien_professionel(rtype id) {
    // vérifie que l'id est bien une relation professionnelle
    if (id == 10 && id == 11)
        return true;

    return false;
}

bool est_lien_connaissance(rtype id) {
    // vérifie que l'id est bien une relation de connaissance
    if (id >= 7 && id <= 9)
        return true;

    return false;
}

char* toStringRelation(rtype id) {
    // retourne la chaine de caractère correspondant à l'id
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

typedef struct s_node {
    void* val;  // pointeur vers objet quelconque
    struct s_node* suiv;
} * listeg;

listeg listegnouv() {
    return (listeg)NULL;
}

listeg adjtete(listeg lst, void* x) {
    // créer une variable new de type listeg
    listeg new = (listeg)malloc(sizeof(struct s_node));

    // vérifie que l'allocation a bien été effectuée
    if (new == NULL) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    // initialise les valeurs de new pour qu'il soit à la tête de la liste
    new->suiv = lst;
    new->val = x;

    // renvoie new pour qu'il soit la nouvelle tête de la liste
    return new;
}

listeg adjqueue(listeg lst, void* x) {
    // créer une variable new de type listeg
    listeg new = (listeg)malloc(sizeof(struct s_node));

    // vérifie que l'allocation a bien été effectuée
    if (new == NULL) {
        if (DEBUG)
            printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }

    // initialise les valeurs de new pour qu'il soit à la queue de la liste
    new->val = x;
    new->suiv = NULL;

    // si la liste est vide, on renvoie new
    if (lst == NULL)
        return new;

    // sinon on parcourt la liste jusqu'à la fin pour que tmp soit positionner
    // sur la queue actuelle
    listeg tmp = lst;
    while (tmp->suiv != NULL)
        tmp = tmp->suiv;

    // la queue maintenant pointe vers new, new est donc la nouvelle queue
    tmp->suiv = new;

    // on renvoie la tête de la liste
    return lst;
}

void supprimer(listeg item) {
    // si item est NULL, on ne fait rien
    if (item == NULL)
        return;

    // on met le pointeur item->suiv sur NULL
    item->suiv = NULL;

    // on libère la mémoire allouée pour item->val et item
    free(item->val);
    free(item);
}

listeg suptete(listeg lst) {
    // si la liste est vide, on renvoie NULL
    if (lst == NULL) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("error: list is empty.\n");

        return (listeg)NULL;
    }

    // on met positionne next sur la nouvelle tete de la liste
    listeg next = lst->suiv;
    // on libère la mémoire allouée pour lst
    supprimer(lst);

    // on renvoie la nouvelle tête de la liste
    return next;
}

void* tete(listeg lst) {
    // on vérifie que la liste n'est pas vide
    if (lst == NULL) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("error: list is empty.\n");

        // on renvoie NULL si la liste est vide
        return (void*)NULL;
    }

    // sinon on renvoie la valeur de la tête de la liste
    return lst->val;
}

int longueur(listeg lst) {
    // si la liste est vide, on renvoie 0
    if (lst == NULL)
        return 0;

    // sinon on fait un appel récursif pour compter le nombre d'éléments dans la
    // liste
    return 1 + longueur(lst->suiv);
}

bool estvide(listeg lst) {
    // on renvoie true si la liste est vide, false sinon
    return lst == NULL ? true : false;
}

void detruire(listeg lst) {
    // on parcourt la liste et on supprime chaque élément
    while (lst != NULL) {
        // positionne tete sur la tête de la liste
        listeg tete = lst;

        // positionne lst sur l'élément suivant
        lst = lst->suiv;

        // supprime la tete
        supprimer(tete);
    }
}

listeg rech(listeg lst, void* x, int (*comp)(void*, void*)) {
    // on crée une nouvelle liste vide
    listeg result = listegnouv();

    // on parcourt la liste lst
    while (lst != NULL) {
        // si la comparaison entre la valeur de lst et x est vraie, on ajoute la
        // valeur de lst à result
        if (comp(lst->val, x) == true) {
            result = adjtete(result, (lst->val));
        }

        // on passe à l'élément suivant
        lst = lst->suiv;
    }

    // on renvoie la liste result
    return result;
}

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
    struct s_node* larcs;  // la liste des arcs associe au sommet
    struct s_entite* x;    // l'entite associe au sommet
} * Sommet;

typedef struct s_arc {
    rtype relationType;  // le type de relation de l'arc
    struct s_entite* x;  // l'entite associe a l'arc
} * Arc;

typedef struct s_relations {
    listeg entites;  // la liste des sommets du graphe
} * Relations;

// 3.2 les constructeurs
Entite creerEntite(char* s, etype e) {
    // créer une nouvelle entité
    Entite new = (Entite)malloc(sizeof(struct s_entite));

    // si la nouvelle entité n'a pas été correctement alloué en mémoire, on
    // arrête le programme
    if (new == NULL) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("fatal error: no memory allocation possible.\n");

        // on arrête le programme avec un code d'erreur EXIT_FAILURE
        exit(EXIT_FAILURE);
    }

    // si la nouvelle entité a un nom trop long, on arrête le programme
    if (strlen(s) > LONG_NOM_MAX) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("fatal error: name too long.\n");

        // on arrête le programme avec un code d'erreur EXIT_FAILURE
        exit(EXIT_FAILURE);
    }

    // créer une copie de la chaine de caractère et l'associe à la nouvelle
    // entité
    strcpy(new->nom, s);
    // associe le type de l'entité à la nouvelle entité
    new->ident = e;

    // on renvoie la nouvelle entité
    return new;
}

Sommet nouvSommet(Entite e) {
    // créer le nouveau sommet nommé new
    Sommet new = (Sommet)malloc(sizeof(struct s_sommet));

    // si le nouveau sommet n'a pas été correctement alloué en mémoire, on
    // arrête le programme
    if (new == NULL) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("fatal error: no memory allocation possible.\n");

        // on arrête le programme avec un code d'erreur EXIT_FAILURE
        exit(EXIT_FAILURE);
    }

    // créer un nouveau listeg pour les arcs du sommet
    new->larcs = listegnouv();
    // associe l'entité e au sommet new
    new->x = e;

    // renvoie le nouveau sommet
    return new;
}

Arc nouvArc(Entite e, rtype type) {
    // créer le nouvel arc nommé new
    Arc new = (Arc)malloc(sizeof(struct s_arc));

    // si le nouvelle arc n'a pas été correctement alloué en mémoire, on arrête
    // le programme
    if (new == NULL) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("fatal error: no memory allocation possible.\n");

        // on arrête le programme avec un code d'erreur EXIT_FAILURE
        exit(EXIT_FAILURE);
    }

    // associe le type de relation à l'arc new
    new->relationType = type;
    // associe l'entité e à l'arc new
    new->x = e;

    // renvoie le nouvel arc
    return new;
}

void relationInit(Relations* g) {
    // on vérifie que le pointeur g n'est pas NULL
    if (g == NULL) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("error: pointer is NULL.\n");

        // on arrête la fonction
        return;
    }

    // alloue directement dans la valeur pointée par g
    (*g) = (Relations)malloc(sizeof(struct s_relations));

    // on vérifie que la valeur pointée par g a bien été allouée en mémoire
    if ((*g) == NULL) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("fatal error: no memory allocation possible.\n");

        // on arrête le programme avec un code d'erreur EXIT_FAILURE
        exit(EXIT_FAILURE);
    }

    // créer une nouvelle liste
    (*g)->entites = listegnouv();
}

void relationFree(Relations* g) {
    // créer un pointeur vers la totalité des entités
    listeg e = (*g)->entites;

    // on parcourt la liste des entités
    while (e != NULL) {
        // créer un pointeur temporaire
        listeg tmp = e;

        // positionne e sur l'élément suivant
        e = e->suiv;

        // on détruit la liste des arcs
        detruire(((Sommet)tmp->val)->larcs);
    }

    // une fois que tout les arcs sont détruits, on détruit la liste des entités
    detruire((*g)->entites);

    // puis on détruit la relations
    free((*g));
}

// 3.3 les comparaisons
int compEntite(void* e, void* string) {
    // si le nom de l'entité est égal à la chaine de caractère, on renvoie true
    if (strcmp((char*)((Entite)e)->nom, (char*)string) == 0)
        return true;

    // sinon on renvoie false
    return false;
}

int compSommet(void* s, void* string) {
    // on utilise la fonction compEntite pour comparer le nom de l'entité
    // associée au sommet
    return compEntite((Entite)((Sommet)s)->x, string);
}
int compArc(void* a, void* string) {
    // on utilise la fonction compEntite pour comparer le nom de l'entité
    // associée à l'arc
    return compEntite((Entite)((Arc)a)->x, string);
}

// 3.4 ajout d'entites et de relations
bool verifEntiteExiste(listeg lst, Entite e) {
    // on parcourt la liste des entités
    while (lst != NULL) {
        // si le nom de l'entité est égal à la chaine de caractère, on renvoie
        // true
        if (compEntite(((Sommet)lst->val)->x, e->nom) == true)
            return true;

        // sinon on passe à l'élément suivant
        lst = lst->suiv;
    }

    // si on a parcouru toute la liste sans trouver l'entité, on renvoie false
    return false;
}

void adjEntite(Relations g, char* nom, etype t) {
    // créer la nouvelle entite
    Entite e = creerEntite(nom, t);
    // créer le sommet associe à l'entite
    Sommet s = nouvSommet(e);

    // si la liste des entités est vide, on ajoute directement le sommet
    if (g->entites == NULL) {
        // on ajoute le sommet en temps que tête de la liste
        g->entites = adjtete(g->entites, s);

        // arrête la fonction
        return;
    }

    // sinon on vérifie que l'entité n'existe pas déjà
    if (verifEntiteExiste(g->entites, e) == true) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("error: entity already exists.\n");

        // arrête la fonction
        return;
    } else {
        // si l'entité n'existe pas, on ajoute le sommet en temps que queue de
        // la liste
        g->entites = adjqueue(g->entites, s);
    }
}

// PRE CONDITION: id doit �tre coh�rent avec les types des sommets
// correspondants � x et y
//                p.ex si x est de type OBJET, id ne peut pas etre une relation
//                de parente
// PRE CONDITION: strcmp(nom1,nom2)!=0

void adjRelation(Relations g, char* nom1, char* nom2, rtype id) {
    // créer un pointeur vers la liste des entités
    listeg tmp = g->entites;

    // on parcourt la liste des entités, jusqu'à soit trouver l'entité
    // correspondante à nom1, soit arriver à la fin de la liste
    while (compEntite(((Sommet)tmp->val)->x, nom1) == false && tmp != NULL)
        tmp = tmp->suiv;

    // si la liste est vide, on a pas trouver l'entité liéé à la relation
    if (tmp == NULL) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("error: entity not found.\n");

        // on arrête la fonction
        return;
    }

    // si l'entité est de type OBJET et que la relation est de type parente, on
    // arrête le programme
    if (((Sommet)tmp->val)->x->ident == OBJET && est_lien_parente(id) == true) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("error: object cannot have a parent relation.\n");

        // on arrête la fonction
        return;
    }

    // on crée un nouveau pointeur vers la liste
    listeg tmp2 = g->entites;

    // on cherche l'entité correspondante à nom2
    while (compEntite(((Sommet)tmp2->val)->x, nom2) == false && tmp2 != NULL)
        tmp2 = tmp2->suiv;

    // créer une nouvelle entité correspondant à nom2
    Entite e = creerEntite(nom2, ((Sommet)tmp2->val)->x->ident);
    // créer l'arc correspondant à la relation
    Arc a = nouvArc(e, id);

    // on ajoute l'arc à la liste des arcs du sommet correspondant à nom1
    ((Sommet)tmp->val)->larcs = adjqueue(((Sommet)tmp->val)->larcs, a);
}

////////////////////////////////////////
// Exercice 4: Explorer les relations entre personnes

// 4.1 listes de relations
listeg en_relation(Relations g, char* x) {
    // créer une variable e qui pointe vers la liste des entités
    listeg e = g->entites;

    // on parcourt la liste des entités jusqu'à trouver l'entité correspondante
    // à x
    while (compEntite(((Sommet)e->val)->x, x) == false && e != NULL)
        e = e->suiv;

    // si e est NULL, on a pas trouver l'entité correspondante à x
    if (e == NULL) {
        // affiche un message d'erreur uniquement si le mode debug est activé
        if (DEBUG)
            printf("error: entity not found.\n");

        // renvoie NULL car l'entité n'a pas été trouvée et donc ces relations
        // non plus
        return NULL;
    }

    // si nous avons bien trouver l'entité correspondante à x, on renvoie la
    // liste des arcs associés à cette entité
    return ((Sommet)e->val)->larcs;
}

listeg chemin2(Relations g, char* x, char* y) {
    // créer une nouvelle liste correspondant aux résultat
    listeg result = listegnouv();
    // on prend la liste de z possible
    listeg zList = en_relation(g, x);

    // on parcourt cette même liste
    while (zList != NULL) {
        // on prend la liste des relations de z
        listeg relationZ = en_relation(g, ((Arc)zList->val)->x->nom);

        // on parcourt cette liste
        while (relationZ != NULL) {
            // si z est en relation avec y, on ajoute z à la liste des résultats
            if (compEntite(((Arc)relationZ->val)->x, y) == true) {
                // on créer une nouvelle entité correspondant à z
                Entite e = creerEntite(((Arc)relationZ->val)->x->nom,
                                       ((Arc)relationZ->val)->x->ident);

                // on l'ajoute a result
                result = adjqueue(result, e);
            }

            // on passe à l'élément suivant
            relationZ = relationZ->suiv;
        }

        // on passe à l'élément suivant
        zList = zList->suiv;
    }

    // on renvoie la liste des résultats
    return result;
}

// 4.2 verifier un lien de parente
// PRE CONDITION: strcmp(x,y)!=0
bool ont_lien_parente(Relations g, char* x, char* y) {
    // on prend la liste des relations de x
    listeg relationX = en_relation(g, x);

    // on parcourt cette liste
    while (relationX != NULL &&
           compEntite(((Arc)relationX->val)->x, y) == false)
        relationX = relationX->suiv;

    // si la liste est vide, nous n'avous pas trouver de relation entre x et y,
    // il n'y a donc pas de lien de parenté
    if (relationX == NULL) {
        return false;
    } else {
        // sinon on renvoie le resultat de la fonction est_lien_parente par
        // rapport au type de la relation
        return est_lien_parente(((Arc)relationX->val)->relationType);
    }
}

// 4.3 tester connaissances
// fonction utile a se_connaissent, ces fonctions sont similaires à
// ont_lien_parente mais modifier pour professionel et connaissance
bool ont_lien_professionel(Relations g, char* x, char* y) {
    listeg relationX = en_relation(g, x);
    while (relationX != NULL &&
           compEntite(((Arc)relationX->val)->x, y) == false)
        relationX = relationX->suiv;

    if (relationX == NULL) {
        return false;
    } else {
        return est_lien_professionel(((Arc)relationX->val)->relationType);
    }

    return false;
}

bool ont_lien_connaissance(Relations g, char* x, char* y) {
    listeg relationX = en_relation(g, x);
    while (relationX != NULL &&
           compEntite(((Arc)relationX->val)->x, y) == false)
        relationX = relationX->suiv;

    if (relationX == NULL) {
        return false;
    } else {
        return est_lien_connaissance(((Arc)relationX->val)->relationType);
    }

    return false;
}

// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent(Relations g, char* x, char* y) {
    // si x et y ont un lien de parenté, professionel ou de connaissance, on
    // renvoie vrai
    if (ont_lien_parente(g, x, y) == true ||
        ont_lien_professionel(g, x, y) == true ||
        ont_lien_connaissance(g, x, y) == true)
        return true;

    // dans le cas contraire nous devons faire les autres vérifications
    // on créer un pointeur e vers la liste des entités
    listeg e = g->entites;

    // on parcourt la liste des entités
    while (e != NULL) {
        // si une entité a un lien de parenté avec x et y, on renvoie vrai
        if (ont_lien_parente(g, ((Arc)e->val)->x->nom, x) == true &&
            ont_lien_parente(g, ((Arc)e->val)->x->nom, y) == true)
            return true;

        // on passe à l'élément suivant
        e = e->suiv;
    }

    // si aucune des conditions précédentes n'a été vérifiée, on renvoie faux
    return false;
}

// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0

// fonction utile à se_connaissent_proba
bool xor (bool a, bool b) { return (a && !b) || (!a && b); }

    bool se_connaissent_proba(Relations g, char* x, char* y) {
    // si il y a une connaissance directe, on renvoie false
    if (se_connaissent(g, x, y) == true)
        return false;

    // on créer un pointeur e vers la liste des entités
    listeg e = g->entites;

    // on parcourt la liste des entités
    while (e != NULL) {
        // si l'entité est de type PERSONNE
        if (((Sommet)e->val)->x->ident == PERSONNE) {
            // qu'il connait x et y
            if (se_connaissent(g, ((Sommet)e->val)->x->nom, x) &&
                se_connaissent(g, ((Sommet)e->val)->x->nom, y)) {
                // et que un des deux a une relation de parenté avec x et y
                if (xor(ont_lien_parente(g, ((Sommet)e->val)->x->nom, x),
                        ont_lien_parente(g, ((Sommet)e->val)->x->nom, y)))
                    // alors on renvoie vrai
                    return true;
            }
        }

        // on passe à l'élément suivant
        e = e->suiv;
    }

    // si aucune des conditions précédentes n'a été vérifiée, on renvoie faux
    return false;
}
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent_peutetre(Relations g, char* x, char* y) {
    // si il y a une connaissance directe ou très probablement, on renvoie false
    if (se_connaissent(g, x, y) == true ||
        se_connaissent_proba(g, x, y) == true)
        return false;

    // on créer un pointeur e vers la liste des entités
    listeg e = g->entites;

    // on parcourt la liste des entités
    while (e != NULL) {
        // si ils ont une connaissance en commun
        if (se_connaissent(g, ((Sommet)e->val)->x->nom, x) &&
            se_connaissent(g, ((Sommet)e->val)->x->nom, y))
            // on renvoie vrai
            return true;

        // on passe à l'élément suivant
        e = e->suiv;
    }

    // si aucune des conditions précédentes n'a été vérifiée, on renvoie faux
    return false;
}

////////////////////////////////////////
// Exercice 5: Affichages

void affichelg(listeg l, void (*aff)(void*)) {
    // on parcourt la liste et on affiche chaque élément
    while (l != NULL) {
        // on affiche l'élément
        aff(l->val);
        // on passe au suivant
        l = l->suiv;
    }
}

void afficheEntite(void* x) {
    // affiche le nom de l'entité
    printf("l'entite : %s\n", ((Entite)x)->nom);
}

void afficheArc(void* x) {
    // affiche le type de relation et le nom de l'entité associée
    printf("a une relation %s avec %s\n",
           toStringRelation(((Arc)x)->relationType), ((Arc)x)->x->nom);
}

////////////////////////////////////////
// Exercice 6: Parcours

bool est_dans(listeg lst, Entite e) {
    // on parcourt la liste et on vérifie si l'entité est dedans
    while (lst != NULL) {
        // si l'entité est dans la liste, on renvoie vrai
        if (compEntite(((Arc)lst->val)->x, e->nom) == true)
            return true;

        // on passe à l'élément suivant
        lst = lst->suiv;
    }

    // si l'entité n'est pas dans la liste, on renvoie faux
    return false;
}

listeg affiche_degre_relations_rec(Relations r,
                                   listeg relations,
                                   int i,
                                   listeg dejaAffiche) {
    // on affiche le degré de relation
    printf("-- %d\n", i);
    // on créer une variable tmp pour parcourir les relations
    listeg tmp = relations;

    // on parcourt les relations
    while (tmp != NULL) {
        // on affiche le nom de l'entité
        printf("%s\n", ((Arc)tmp->val)->x->nom);
        // on passe à l'élément suivant
        tmp = tmp->suiv;
    }

    // on créer une liste des relations à afficher dans le prochain degré
    listeg result = listegnouv();
    // on créer une variable e pour parcourir les relations
    listeg e = relations;

    // on parcourt les relations
    while (e != NULL) {
        // on prend la liste des relations de la relation
        listeg relationDeRelation = en_relation(r, ((Arc)e->val)->x->nom);

        // on parcourt cette liste
        while (relationDeRelation != NULL) {
            // si c'est pas dans la liste dejaAffiche, on ajoute la relation à
            // result
            if (est_dans(dejaAffiche, ((Arc)relationDeRelation->val)->x) ==
                false)
                result = adjqueue(result, ((Arc)relationDeRelation->val));

            // on passe à l'élément suivant
            relationDeRelation = relationDeRelation->suiv;
        }

        // on passe à l'élément suivant
        e = e->suiv;
    }

    // on renvoie la liste des relations à afficher dans le prochain degré
    return result;
}

void affiche_degre_relations(Relations r, char* x) {
    // affiche le nom de l'entité
    printf("%s\n", x);

    // on prend la liste des relations de x
    listeg relations = en_relation(r, x);
    // on créer un "identifiant"
    int i = 1;

    // on créer un pointeur vers la liste des entités
    listeg e = r->entites;
    // on créer une liste des entités déjà affichées
    listeg dejaAffiche = listegnouv();

    // on parcourt la liste des entités
    while (e != NULL) {
        // si l'entité est égale à x, on l'ajoute à la liste des relations
        if (compEntite(((Sommet)e->val)->x->nom, x) == true) {
            dejaAffiche = adjqueue(dejaAffiche, ((Sommet)e->val));
        }

        // si l'entité est en relation avec x, on l'ajoute à la liste des
        // relations
        if (ont_lien_parente(r, ((Sommet)e->val)->x->nom, x) == true ||
            ont_lien_connaissance(r, ((Sommet)e->val)->x->nom, x) == true ||
            ont_lien_professionel(r, ((Sommet)e->val)->x->nom, x) == true) {
            relations = adjqueue(relations, ((Sommet)e->val));
        }

        // on passe à l'élément suivant
        e = e->suiv;
    }

    // on affiche les relations, si les relations est vide c'est qu'on a tout
    // afficher, la fonctions s'arrete
    while (relations != NULL) {
        // on utilise affiche_degre_relations_rec pour afficher les relations
        relations = affiche_degre_relations_rec(r, relations, i, dejaAffiche);

        // on créer une variable tmp pour parcourir les relations
        listeg tmp = relations;

        // on parcourt les relations
        while (tmp != NULL) {
            // on ajoute les relations à la liste des entités déjà affichées
            dejaAffiche = adjqueue(dejaAffiche, tmp->val);
            // on passe à l'élément suivant
            tmp = tmp->suiv;
        }

        // on incrémente i
        i++;
    }
}

int main() {
    int i, j;
    Relations r;
    relationInit(&r);
    // ajouter les entites de l'exemple
    char* tabe[] = {"KARL",      "LUDOVIC",     "CELINE",
                    "CHLOE",     "GILDAS",      "CEDRIC",
                    "SEVERINE",  "PEUGEOT 106", "1, RUE DE LA RUE",
                    "STRASBOURG"};
    for (i = 0; i < 7; i++)
        adjEntite(r, tabe[i], PERSONNE);
    adjEntite(r, tabe[7], OBJET);
    adjEntite(r, tabe[8], ADRESSE);
    adjEntite(r, tabe[9], VILLE);
    // ajouter les relations de l'exemple
    adjRelation(r, tabe[0], tabe[1], FRERE);
    adjRelation(r, tabe[0], tabe[2], AMI);
    adjRelation(r, tabe[0], tabe[3], CONNAIT);
    adjRelation(r, tabe[0], tabe[5], COUSIN);
    adjRelation(r, tabe[0], tabe[7], PROPRIETAIRE);
    adjRelation(r, tabe[0], tabe[8], PROPRIETAIRE);
    adjRelation(r, tabe[3], tabe[4], VIT);
    adjRelation(r, tabe[5], tabe[6], EPOUX);
    adjRelation(r, tabe[5], tabe[8], LOCATAIRE);
    adjRelation(r, tabe[7], tabe[8], DECOUVERT);
    adjRelation(r, tabe[8], tabe[9], SITUE);

    // explorer les relations
    printf("%s est en relation avec:\n", tabe[0]);
    affichelg(en_relation(r, tabe[0]), afficheArc);
    printf("\n");

    for (i = 0; i < 7; i++)
        for (j = i + 1; j < 10; j++) {
            printf("<%s> et <%s> ont les relations communes:\n", tabe[i],
                   tabe[j]);
            listeg ch = chemin2(r, tabe[i], tabe[j]);
            affichelg(ch, afficheEntite);
            printf("\n");
            detruire(ch);
        }
    printf("\n\n");

    for (i = 0; i < 10; i++)
        for (j = i + 1; j < 10; j++) {
            printf("<%s> et <%s> ont lien de parente: %s\n", tabe[i], tabe[j],
                   ont_lien_parente(r, tabe[i], tabe[j]) ? "vrai" : "faux");
        }
    printf("\n");
    for (i = 0; i < 7; i++) {
        for (j = i + 1; j < 7; j++) {
            printf("<%s> et <%s> se connaissent: %s\n", tabe[i], tabe[j],
                   se_connaissent(r, tabe[i], tabe[j]) ? "vrai" : "faux");
            printf("<%s> et <%s> se connaissent tres probablement: %s\n",
                   tabe[i], tabe[j],
                   se_connaissent_proba(r, tabe[i], tabe[j]) ? "vrai" : "faux");
            printf(
                "<%s> et <%s> se connaissent peut etre: %s\n", tabe[i], tabe[j],
                se_connaissent_peutetre(r, tabe[i], tabe[j]) ? "vrai" : "faux");
        }
        printf("\n");
    }

    affiche_degre_relations(r, tabe[3]);

    relationFree(&r);

    printf("\nPRESS RETURN\n");
    char buff[64];
    fscanf(stdin, "%s", buff);
    return 0;
}
