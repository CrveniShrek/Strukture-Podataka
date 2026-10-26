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

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        return;
    }

    printf("Ime: ");
    scanf("%29s", nova->ime);

    printf("Prezime: ");
    scanf("%29s", nova->prezime);

    printf("Godina rodjenja: ");
    scanf("%d", &nova->god);

    nova->next = head->next;
    head->next = nova;

    printf("Dodavanje na pocetak uspjesno obavljeno.\n");
}

void ispisiListu(Pozicija head) {
    Pozicija trenutni = head->next;

    if (trenutni == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    while (trenutni != NULL) {
        printf("%s %s, %d\n",
            trenutni->ime,
            trenutni->prezime,
            trenutni->god);

        trenutni = trenutni->next;
    }

    printf("Ispis liste uspjesno obavljen.\n");
}

void dodajNaKraj(Pozicija head) {
    Pozicija nova = (Pozicija)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        return;
    }

    printf("Ime: ");
    scanf("%29s", nova->ime);

    printf("Prezime: ");
    scanf("%29s", nova->prezime);

    printf("Godina rodjenja: ");
    scanf("%d", &nova->god);

    nova->next = NULL;

    Pozicija trenutni = head;

    while (trenutni->next != NULL) {
        trenutni = trenutni->next;
    }

    trenutni->next = nova;

    printf("Dodavanje na kraj uspjesno obavljeno.\n");
}

Pozicija pronadji(Pozicija head, char* prezime) {
    Pozicija trenutni = head->next;

    while (trenutni != NULL) {
        if (strcmp(trenutni->prezime, prezime) == 0) {
            printf("Pronalaženje uspjesno obavljeno.\n");
            return trenutni;
        }

        trenutni = trenutni->next;
    }

    printf("Osoba nije pronadjena.\n");
    return NULL;
}

void obrisi(Pozicija head, char* prezime) {
    Pozicija prethodni = head;
    Pozicija trenutni = head->next;

    while (trenutni != NULL) {
        if (strcmp(trenutni->prezime, prezime) == 0) {
            prethodni->next = trenutni->next;
            free(trenutni);

            printf("Brisanje uspjesno obavljeno.\n");
            return;
        }

        prethodni = trenutni;
        trenutni = trenutni->next;
    }

    printf("Osoba nije pronadjena.\n");
}

void dodajIza(Pozicija head, char* prezime) {
    Pozicija trenutni = head->next;

    while (trenutni != NULL) {
        if (strcmp(trenutni->prezime, prezime) == 0) {
            Pozicija nova = (Pozicija)malloc(sizeof(Osoba));

            if (nova == NULL) {
                printf("Greska pri alokaciji memorije.\n");
                return;
            }

            printf("Ime: ");
            scanf("%29s", nova->ime);

            printf("Prezime: ");
            scanf("%29s", nova->prezime);

            printf("Godina rodjenja: ");
            scanf("%d", &nova->god);

            nova->next = trenutni->next;
            trenutni->next = nova;

            printf("Dodavanje iza osobe uspjesno obavljeno.\n");
            return;
        }

        trenutni = trenutni->next;
    }

    printf("Osoba nije pronadjena.\n");
}

void dodajIspred(Pozicija head, char* prezime) {
    Pozicija prethodni = head;
    Pozicija trenutni = head->next;

    while (trenutni != NULL) {
        if (strcmp(trenutni->prezime, prezime) == 0) {
            Pozicija nova = (Pozicija)malloc(sizeof(Osoba));

            if (nova == NULL) {
                printf("Greska pri alokaciji memorije.\n");
                return;
            }

            printf("Ime: ");
            scanf("%29s", nova->ime);

            printf("Prezime: ");
            scanf("%29s", nova->prezime);

            printf("Godina rodjenja: ");
            scanf("%d", &nova->god);

            nova->next = trenutni;
            prethodni->next = nova;

            printf("Dodavanje ispred osobe uspjesno obavljeno.\n");
            return;
        }

        prethodni = trenutni;
        trenutni = trenutni->next;
    }

    printf("Osoba nije pronadjena.\n");
}

void sortiraniUnos(Pozicija head) {
    Pozicija nova = (Pozicija)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        return;
    }

    printf("Ime: ");
    scanf("%29s", nova->ime);

    printf("Prezime: ");
    scanf("%29s", nova->prezime);

    printf("Godina rodjenja: ");
    scanf("%d", &nova->god);

    Pozicija trenutni = head;

    while (trenutni->next != NULL &&
        strcmp(nova->prezime, trenutni->next->prezime) > 0) {
        trenutni = trenutni->next;
    }

    nova->next = trenutni->next;
    trenutni->next = nova;

    printf("Sortirani unos uspjesno obavljen.\n");
}

void upisiUDatoteku(Pozicija head) {
    FILE* dat = fopen("upisi.txt", "w");

    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    Pozicija trenutni = head->next;

    while (trenutni != NULL) {
        fprintf(dat, "%s %s %d\n",
            trenutni->ime,
            trenutni->prezime,
            trenutni->god);

        trenutni = trenutni->next;
    }

    fclose(dat);

    printf("Upis u datoteku uspjesno obavljen.\n");
}

void ucitajIzDatoteke(Pozicija head) {
    if (head->next != NULL) {
        printf("Lista mora biti prazna za ucitavanje iz datoteke.\n");
        return;
    }

    FILE* dat = fopen("ucitaj.txt", "r");

    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    Pozicija trenutni = head;

    while (1) {
        Pozicija nova = (Pozicija)malloc(sizeof(Osoba));

        if (nova == NULL) {
            printf("Greska pri alokaciji memorije.\n");
            fclose(dat);
            return;
        }

        if (fscanf(dat, "%29s %29s %d",
            nova->ime,
            nova->prezime,
            &nova->god) != 3) {
            free(nova);
            break;
        }

        nova->next = NULL;
        trenutni->next = nova;
        trenutni = nova;
    }

    fclose(dat);

    printf("Citanje iz datoteke uspjesno obavljeno.\n");
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
        printf("4 - Pronadji osobu\n");
        printf("5 - Obrisi osobu\n");
        printf("6 - Dodaj iza osobe\n");
        printf("7 - Dodaj ispred osobe\n");
        printf("8 - Sortirani unos\n");
        printf("9 - Upisi listu u datoteku\n");
        printf("10 - Ucitaj listu iz datoteke\n");
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

            Pozicija pronadjena = pronadji(&head, prezime);

            if (pronadjena != NULL) {
                printf("Pronadjena osoba: %s %s, %d\n",
                    pronadjena->ime,
                    pronadjena->prezime,
                    pronadjena->god);
            }
            break;
        }

        case 5:
            printf("Unesite prezime osobe koju zelite obrisati: ");
            scanf("%29s", prezime);

            obrisi(&head, prezime);
            break;

        case 6:
            printf("Unesite prezime osobe iza koje zelite dodati: ");
            scanf("%29s", prezime);

            dodajIza(&head, prezime);
            break;

        case 7:
            printf("Unesite prezime osobe ispred koje zelite dodati: ");
            scanf("%29s", prezime);

            dodajIspred(&head, prezime);
            break;

        case 8:
            sortiraniUnos(&head);
            break;

        case 9:
            upisiUDatoteku(&head);
            break;

        case 10:
            ucitajIzDatoteke(&head);
            break;

        case 0:
            break;

        default:
            printf("Neispravan odabir.\n");
        }

    } while (izbor != 0);

    Pozicija trenutni = head.next;

    while (trenutni != NULL) {
        Pozicija pomocni = trenutni;
        trenutni = trenutni->next;
        free(pomocni);
    }

    return 0;
}