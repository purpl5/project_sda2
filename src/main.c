#include "../header/base.h"
#include "../header/relation.h"

int main() {
    rtype test = 2;
    printf("%d %d %d\n", est_lien_parente(test), est_lien_professionel(test),
           est_lien_connaissance(test));
    printf("%s\n", toStringRelation(test));

    /*
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
    */
    return 0;
}
