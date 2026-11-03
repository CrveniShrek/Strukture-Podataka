#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct stog {
	int br;
	struct stog* next;
} stog;
typedef struct stog* poz;

int main() {
	FILE* f = fopen("postfiks.txt", "r");
	poz head = (poz)malloc(sizeof(stog));
	head->next = NULL;
	int broj = 0;
	int ucitano = 0;

	while (1) {
		char c = fgetc(f);
		if (feof(f)) break;

		if (c>='0' && c<='9') {
			broj = broj * 10 + (c - '0');
			ucitano = 1;
		}

		if (c == ' ' && ucitano) {
			poz novi = (poz)malloc(sizeof(stog));
			novi->br = broj;
			novi->next = head->next;
			head->next = novi;
			broj = 0;
			ucitano = 0;
		}

		if (c == '+' || c == '-' || c == '*' || c == '/') {
			poz prvi = head->next;
			poz drugi = prvi->next;
			switch (c) {
			case '+':
			{
				drugi->br += prvi->br;
				head->next = drugi;
				free(prvi);
				break;
			}
			case '-':
			{
				drugi->br-= prvi->br;
				head->next = drugi;
				free(prvi);
				break;
			}
			case '*':
			{
				drugi->br *= prvi->br;
				head->next = drugi;
				free(prvi);
				break;
			}
			case '/':
			{
				drugi->br /= prvi->br;
				head->next = drugi;
				free(prvi);
				break;
			}
			}
		}
	}

	printf("Rezultat je: %d", head->next->br);

	free(head->next);
	free(head);
	fclose(f);

	return 0;
}