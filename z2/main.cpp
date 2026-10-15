#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[30];
    char prezime[30];
    int god;
    struct Osoba* next;
} Osoba;

typedef struct Osoba* Pozicija;

void dodajNaPocetak(Pozicija head) {
    Pozicija nova = (Pozicija)malloc(sizeof(Osoba));

    printf("Ime: ");
    scanf("%s", nova->ime);

    printf("Prezime: ");
    scanf("%s", nova->prezime);

    printf("Godina rodjenja: ");
    scanf("%d", &nova->god);

    nova->next = head->next;
    head->next = nova;
}

void ispisiListu(Pozicija head) {
    Pozicija trenutni = head->next;

    if (trenutni == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    while (trenutni != NULL) {
        printf("%s %s, %d\n", trenutni->ime, trenutni->prezime, trenutni->god);
        trenutni = trenutni->next;
    }
}

void dodajNaKraj(Pozicija head) {
    Pozicija nova = (Pozicija)malloc(sizeof(Osoba));

    printf("Ime: ");
    scanf("%s", nova->ime);

    printf("Prezime: ");
    scanf("%s", nova->prezime);

    printf("Godina rodjenja: ");
    scanf("%d", &nova->god);

    nova->next = NULL;

    Pozicija trenutni = head;

    while (trenutni->next != NULL) {
        trenutni = trenutni->next;
    }

    trenutni->next = nova;
}

Pozicija pronadi(Pozicija head, char* prezime) {
    Pozicija trenutni = head->next;

    while (trenutni != NULL) {
        if (strcmp(trenutni->prezime, prezime) == 0) {
            return trenutni;
        }

        trenutni = trenutni->next;
    }

    return NULL;
}

void obrisi(Pozicija head, char* prezime) {
    Pozicija prethodni = head;
    Pozicija trenutni = head->next;

    while (trenutni != NULL) {
        if (strcmp(trenutni->prezime, prezime) == 0) {
            prethodni->next = trenutni->next;
            free(trenutni);
            printf("Osoba je obrisana.\n");
            return;
        }

        prethodni = trenutni;
        trenutni = trenutni->next;
    }

    printf("Osoba nije pronadjena.\n");
}

int main() {
    Osoba head;
    head.next = NULL;

    int izbor;
    char prezime[30];

    do {
        printf("\n1 - Dodaj na pocetak\n");
        printf("2 - Ispisi listu\n");
        printf("3 - Dodaj na kraj\n");
        printf("4 - pronadi osobu\n");
        printf("5 - Obrisi osobu\n");
        printf("0 - Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            dodajNaPocetak(&head);
            break;

        case 2:
            ispisiListu(&head);
            break;

        case 3:
            dodajNaKraj(&head);
            break;

        case 4: {
            printf("Unesite prezime: ");
            scanf("%29s", prezime);

            Pozicija pronadjena = pronadi(&head, prezime);

            if (pronadjena != NULL) {
                printf("Pronadjena osoba: %s %s, %d\n",
                    pronadjena->ime,
                    pronadjena->prezime,
                    pronadjena->god);
            }
            else {
                printf("Osoba nije pronadjena.\n");
            }
            break;
        }

        case 5:
            printf("Unesite prezime osobe koju zelite obrisati: ");
            scanf("%29s", prezime);

            obrisi(&head, prezime);
            break;

        case 0:
            break;

        default:
            printf("Neispravan odabir.\n");
        }

    } while (izbor != 0);

    return 0;
}
