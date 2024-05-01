#include "../header/base.h"
#include "../header/relation.h"
#include "../header/verifEntiteExiste.h"

bool verifEntiteExiste(listeg lst, Entite e) {
    while (lst != NULL) {
        if (compEntite(((Sommet) lst->val)->x, e->nom) == true)
            return true;
        

        lst = lst->suiv;
    }

    return false;
}   