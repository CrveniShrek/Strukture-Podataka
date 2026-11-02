#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Poli {
	int koef;
	int eksp;
	struct Poli* next;
}poli;
typedef struct Poli* poz;

void ispis(poz head) {
	poz p = head->next;
	while (p != NULL) {
		printf("%dx^%d", p->koef, p->eksp);
		if (p->next != NULL)
			printf(" + ");
		p = p->next;
	}
	printf("\n");
}

void unos(FILE* file, poz head) {
	while (1) {
		poz mono = (poz)malloc(sizeof(poli));
		if (fscanf(file, "%d %d", &(mono->koef), &(mono->eksp)) != 2) {
			free(mono);
			break;
		}

		poz p=head;
		while (1) {
			if (p->next == NULL) {
					p->next = mono;
					mono->next = NULL;
					break;
			}
			if (mono->eksp > p->next->eksp) {
					mono->next = p->next;
					p->next = mono;
					break;
			}
			p = p->next;
		}

		char c = fgetc(file);
		if (c == '\n' || feof(file)) break;
	}

}

poz zbroj(poz h1, poz h2) {
	poz hz = (poz)malloc(sizeof(poli));
	hz->next = NULL;
	
	poz p1 = h1->next;
	poz pz = hz;
	while (p1 != NULL) {
		poz mono = (poz)malloc(sizeof(poli));
		mono->koef = p1->koef;
		mono->eksp = p1->eksp;

		pz->next = mono;
		mono->next = NULL;
		pz = mono;
		p1 = p1->next;
	}

	poz p2 = h2->next;
	while (p2 != NULL) {
		poz mono = (poz)malloc(sizeof(poli));
		mono->koef = p2->koef;
		mono->eksp = p2->eksp;

		poz pz = hz;
		while (1) {

			if (pz->next == NULL) {
					pz->next = mono;
					mono->next = NULL;
					break;
			}

			if (mono->eksp > pz->next->eksp) {
					mono->next = pz->next;
					pz->next = mono;
					break;
			}

			if (mono->eksp == pz->next->eksp) {
				pz->next->koef += mono->koef;
				free(mono);

				if (pz->next->koef == 0) {
					poz temp = pz->next;
					pz->next = temp->next;
					free(temp);
				}
				break;
			}

			pz = pz->next;
		}

		p2 = p2->next;
	}
	
	return hz;
}

poz umnozak(poz h1, poz h2) {
	poz hu = (poz)malloc(sizeof(poli));
	hu->next = NULL;

	poz p2 = h2->next;
	while (p2 != NULL) {
		poz htemp = (poz)malloc(sizeof(poli));
		htemp->next = NULL;

		poz p1 = h1->next;
		poz ptemp = htemp;
		while (p1 != NULL) {
			poz mono = (poz)malloc(sizeof(poli));
			mono->koef = p1->koef * p2->koef;
			mono->eksp = p1->eksp + p2->eksp;

			ptemp->next = mono;
			mono->next = NULL;
			ptemp = mono;
			p1 = p1->next;
		}

		poz hnovi = zbroj(hu, htemp);

		while (htemp->next != NULL) {
			poz temp = htemp->next;
			htemp->next = temp->next;
			free(temp);
		}
		free(htemp);

		while (hu->next != NULL) {
			poz temp = hu->next;
			hu->next = temp->next;
			free(temp);
		}
		hu->next= hnovi->next;
		free(hnovi);

		p2 = p2->next;
	}
	
	return hu;
}

int main() {
	poz h1, h2;
	h1 = (poz)malloc(sizeof(poli));
	h2 = (poz)malloc(sizeof(poli));
	h1->next = NULL;
	h2->next = NULL;

	FILE* file = fopen("polinomi.txt", "r");
	if (file == NULL) {
		printf("Greska prilikom otvaranja datoteke!\n");
		return 1;
	}
	
	unos(file, h1);
	printf("Prvi polinom:\n");
	ispis(h1);
	unos(file, h2);
	printf("Drugi polinom:\n");
	ispis(h2);
	fclose(file);
	
	poz hz = zbroj(h1, h2);
	printf("Zbroj polinoma:\n");
	ispis(hz);
	poz hu = umnozak(h1, h2);
	printf("Umnozak polinoma:\n");
	ispis(hu);
	
	while (h1->next != NULL) {
		poz temp = h1->next;
		h1->next = temp->next;
		free(temp);
	}
	free(h1);

	while (h2->next != NULL) {
		poz temp = h2->next;
		h2->next = temp->next;
		free(temp);
	}
	free(h2);

	while (hz->next != NULL) {
		poz temp = hz->next;
		hz->next = temp->next;
		free(temp);
	}
	free(hz);

	while (hu->next != NULL) {
		poz temp = hu->next;
		hu->next = temp->next;
		free(temp);
	}
	free(hu);

	return 0;
}
