#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiant {
    int idKairos;
    char nom[50];
    float moyenne;
    struct Etudiant* suivant;
} Etudiant;


Etudiant* ajouterEnTete(Etudiant* tete) {
    Etudiant* nouv = malloc(sizeof(Etudiant));
    if (!nouv) {
        printf("Erreur d'allocation.\n");
        return tete;
    }

    printf("ID Kairos : ");
    scanf("%d", &nouv->idKairos);
    printf("Nom : ");
    scanf("%s", nouv->nom);
    printf("Moyenne : ");
    scanf("%f", &nouv->moyenne);

    nouv->suivant = tete;
    return nouv;
}


void ajouterApres(Etudiant* tete, int id) {
    Etudiant* courant = tete;

    while (courant != NULL && courant->idKairos != id)
        courant = courant->suivant;

    if (courant == NULL) {
        printf("ID non trouvé.\n");
        return;
    }

    Etudiant* nouv = malloc(sizeof(Etudiant));
    printf("ID Kairos : ");
    scanf("%d", &nouv->idKairos);
    printf("Nom : ");
    scanf("%s", nouv->nom);
    printf("Moyenne : ");
    scanf("%f", &nouv->moyenne);

    nouv->suivant = courant->suivant;
    courant->suivant = nouv;
}


Etudiant* supprimerParID(Etudiant* tete, int id) {
    if (tete == NULL) return NULL;

    if (tete->idKairos == id) {
        Etudiant* tmp = tete;
        tete = tete->suivant;
        free(tmp);
        return tete;
    }

    Etudiant* courant = tete;
    while (courant->suivant != NULL && courant->suivant->idKairos != id)
        courant = courant->suivant;

    if (courant->suivant != NULL) {
        Etudiant* tmp = courant->suivant;
        courant->suivant = tmp->suivant;
        free(tmp);
    } else {
        printf("ID non trouvé.\n");
    }

    return tete;
}


void afficherListe(Etudiant* tete) {
    if (!tete) {
        printf("Liste vide.\n");
        return;
    }
    while (tete != NULL) {
        printf("ID:%d | Nom:%s | Moyenne:%.2f\n",
               tete->idKairos, tete->nom, tete->moyenne);
        tete = tete->suivant;
    }
}


void moyenneEtudiants(Etudiant* tete) {
    if (!tete) {
        printf("Liste vide.\n");
        return;
    }
    int c = 0;
    float somme = 0;
    while (tete) {
        somme += tete->moyenne;
        c++;
        tete = tete->suivant;
    }
    printf("Moyenne générale : %.2f\n", somme / c);
}


Etudiant* supprimerDernier(Etudiant* tete) {
    if (!tete) return NULL;

    if (tete->suivant == NULL) {
        free(tete);
        return NULL;
    }

    Etudiant* courant = tete;
    while (courant->suivant->suivant != NULL)
        courant = courant->suivant;

    free(courant->suivant);
    courant->suivant = NULL;
    return tete;
}


Etudiant* viderListe(Etudiant* tete) {
    Etudiant* tmp;
    while (tete != NULL) {
        tmp = tete;
        tete = tete->suivant;
        free(tmp);
    }
    return NULL;
}


int main() {
    Etudiant* liste = NULL;
    int choix, id;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Ajouter en tete\n");
        printf("2. Ajouter apres un ID\n");
        printf("3. Supprimer par ID\n");
        printf("4. Afficher la liste\n");
        printf("5. Moyenne des etudiants\n");
        printf("6. Supprimer le dernier\n");
        printf("7. Vider la liste\n");
        printf("8. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                liste = ajouterEnTete(liste);
                break;

            case 2:
                printf("ID après lequel ajouter : ");
                scanf("%d", &id);
                ajouterApres(liste, id);
                break;

            case 3:
                printf("ID a supprimer : ");
                scanf("%d", &id);
                liste = supprimerParID(liste, id);
                break;

            case 4:
                afficherListe(liste);
                break;

            case 5:
                moyenneEtudiants(liste);
                break;

            case 6:
                liste = supprimerDernier(liste);
                break;

            case 7:
                liste = viderListe(liste);
                break;

            case 8:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 8);

    return 0;
}

    







