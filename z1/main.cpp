#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Student {
    char ime[30];
    char prezime[30];
    int bodovi;
};


int main() {
    FILE* dat;
    int n = 0;
    int max_br_bodova = 30;
    struct Student* studenti;

    dat = fopen("studenti.txt", "r");

    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    char ime[30], prezime[30];
    int bodovi;

    while (fscanf(dat, "%s %s %d", ime, prezime, &bodovi) == 3) {
        n++;
    }

    rewind(dat);

    studenti = (struct Student*)malloc(n * sizeof(struct Student));


    for (int i = 0; i < n; i++) {
        fscanf(dat, "%s %s %d",
            studenti[i].ime,
            studenti[i].prezime,
            &studenti[i].bodovi);
    }

    fclose(dat);

    printf("Ime\tPrezime\tBodovi\tRelativni bodovi\n");

    for (int i = 0; i < n; i++) {
        double relativni = (double)studenti[i].bodovi / max_br_bodova * 100;

        printf("%s\t%s\t%d\t%.2f%%\n",
            studenti[i].ime,
            studenti[i].prezime,
            studenti[i].bodovi,
            relativni);
    }

    free(studenti);

    return 0;
}