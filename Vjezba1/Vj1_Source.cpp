#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
	char ime[1024] = { 0 };
	char prezime[1024] = { 0 };
	int bodovi;
}_student;

int FileReader();
int ReadFormFile(_student*, int);

int main() {
	int test, counter, i = 0;
	_student* stud;

	counter = FileReader();

	stud = (_student*)malloc(counter * sizeof(_student));

	if (stud == NULL) {
		printf("Struktura nije alocirana!\n");
		return 1;
	}

	test = ReadFormFile(stud, counter);

	if (test == 0) {
		for (i = 0; i < counter; i++) {
			printf("\nIme: %s\nPrezime %s\nBodovi: %d\n\n", stud->ime, stud->prezime, stud->bodovi);
			stud++;
		}
	}
	return 0;
}

int FileReader() {
	FILE* file;
	int counter = 0;
	char popis[1024];

	file = fopen("Studenti.txt", "r");

	if (file == NULL) {
		printf("Nije ocitan file!\n");
		return 1;
	}

	while (!feof(file)) {
		fgets(popis, 1023, file);
		counter++;
	}

	fclose(file);
	return counter;
}

int ReadFormFile(_student* stud, int counter) {
	int i = 0;

	FILE* file;

	file = fopen("Studenti.txt", "r");

	if (file == NULL) {
		printf("Nije ocitan file!\n");
		return 1;
	}

	for (i = 0; i < counter; i++) {
		fscanf(file, " %s %s %d", stud->ime, stud->prezime, &stud->bodovi);
		stud++;
	}

	fclose(file);
	return 0;
}