#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCESS 0
#define WARNING 1
#define ERROR -1
#define BUFFER_LENGTH 1024

struct PodatciOsobe;
typedef struct PodatciOsobe* Position;

int MainMenu();
int InsertAtBeginnig(Position);
Position AllocationOfMemory();
int PrintList(Position);
int InsertAtEnd(Position);
Position FindElement(Position);
Position FindPrevElementByLastName(Position P);
int ClearElementByLastName(Position);
int GarbageCollector(Position);
int InsertElementAfter(Position);
int InsertElementBefore(Position);
int SortList(Position);
int InsertInFile(Position);
int ReadFromFile(Position);

struct PodatciOsobe {
	char ime[BUFFER_LENGTH];
	char prezime[BUFFER_LENGTH];
	int godinaRodjenja;
	Position Next;
};


int main() {
	struct PodatciOsobe head;
	head.Next = NULL;

	int izbor = 0;



	while (izbor != 11) {
		izbor = MainMenu();

		switch (izbor) {
		case 1:
			InsertAtBeginnig(&head);
			break;
		case 2:
			PrintList(head.Next);
			break;
		case 3:
			InsertAtEnd(&head);
			break;
		case 4:
			FindElement(head.Next);
			break;
		case 5:
			ClearElementByLastName(&head);
			break;
		case 6:
			InsertElementAfter(&head);
			break;
		case 7:
			InsertElementBefore(&head);
			break;
		case 8:
			SortList(&head);
			break;
		case 9:
			InsertInFile(head.Next);
			break;
		case 10:
			ReadFromFile(&head);
			break;
		case 11:
			GarbageCollector(&head);
			printf("\nIZLAZ IZ PROGRAMA\n");
			break;
		default:
			printf("\nPogresan izbor, pokusajte ponovno!\n\n");
			break;
		}
	}

	return SUCESS;
}

int MainMenu() {
	int izbor = 0;

	printf("\n-------VJEZBA BROJ 1-------\n");
	printf("---------Main Menu---------\n");
	printf("______________________________\n");
	printf("1 ---> Dodavanje elementa na pocetak liste\n");
	printf("2 ---> Ispis liste\n");
	printf("3 ---> Dodavanje elementa na kraj liste\n");
	printf("4 ---> Pronaci element u listi po prezimenu\n");
	printf("5 ---> Birsanje elementa u listi po prezimenu\n");
	printf("6 ---> Dinamicki dodaje novi element iza odredjenog elementa\n");
	printf("7 ---> Dinamicki dodaje novi element ispred odredjenog elementa\n");
	printf("8 ---> Sortira listu po prezimenima osoba\n");
	printf("9 ---> Upisuje listu u datoteku,\n");
	printf("10 ---> Cita listu iz datoteke\n");
	printf("11 ---> EXIT/Izlaz iz programa\n\n");

	printf("\nVas izbor: ");
	scanf(" %d", &izbor);

	return izbor;
}

int InsertAtBeginnig(Position P)
{
	Position q;

	q = AllocationOfMemory();

	if (q == NULL) {
		printf("\n----WARNING-----\nNew element of list isn`t allocated!\n");
		return WARNING;
	}
	printf("\n---- Input ---- UNOSENJE PODATAKA(IME, PREZIME, GODINA RODJENJA)\n");
	printf("Unesite ime: ");
	scanf(" %s", q->ime);
	printf("Unesite prezime: ");
	scanf(" %s", q->prezime);
	printf("Unesite godina rodenja: ");
	scanf(" %d", &q->godinaRodjenja);

	q->Next = P->Next;
	P->Next = q;

	return SUCESS;
}

Position AllocationOfMemory()
{
	Position elementToAllocate;
	elementToAllocate = (Position)malloc(sizeof(struct PodatciOsobe));

	return elementToAllocate;
}

int PrintList(Position P) {
	if (P == NULL) {
		printf("LISTA JE PRAZNA!\n");
		return SUCESS;
	}
	else {
		while (P != NULL) {
			printf("\n---- Elementi liste ----\n");
			printf("Ime: %s\n", P->ime);
			printf("Prezime: %s\n", P->prezime);
			printf("Godina Rodjenja: %d\n\n", P->godinaRodjenja);

			P = P->Next;
		}
	}

	return SUCESS;
}

int InsertAtEnd(Position P)
{
	while (P->Next != NULL) {
		P = P->Next;
	}

	InsertAtBeginnig(P);

	return SUCESS;
}

Position FindElement(Position P)
{
	char lastNameToFind[BUFFER_LENGTH];

	printf("Unesite trazeno prezime: ");
	scanf(" %s", &lastNameToFind);

	while (P != NULL && strcmp(lastNameToFind, P->prezime) != 0) {
		P = P->Next;
	}

	if (P == NULL) {
		printf("Nema elementa sa navedenim prezimenom\n");
		return NULL;
	}
	else {
		printf("Pronadjen element\n");
		printf("Pronadjeni element: \n");
		printf("Ime: %s\n", P->ime);
		printf("Prezime: %s\n", P->prezime);
		printf("Godina rodjenja: %d\n", P->godinaRodjenja);
		return P;
	}
}

Position FindPrevElementByLastName(Position P)
{
	char lastNameToFind[BUFFER_LENGTH];

	printf("Unesite trazeno prezime: ");
	scanf(" %s", &lastNameToFind);

	while (P->Next != NULL && strcmp(lastNameToFind, P->Next->prezime) != 0) {
		P = P->Next;
	}

	if (P->Next == NULL) {
		printf("Nema elementa sa navedenim prezimenom\n");
		return NULL;
	}
	else {
		printf("Pronadjen element\n");
		return P;
	}
}

int ClearElementByLastName(Position P)
{
	P = FindPrevElementByLastName(P);
	Position temp;

	if (P == NULL) {
		printf("Nije moguce brisanje!\n");
		return WARNING;
	}
	else {
		temp = P->Next;
		P->Next = temp->Next;
		printf("Brisanje elementa %s %s %d", temp->ime, temp->prezime, temp->godinaRodjenja);
		free(temp);
	}
	return SUCESS;
}

int GarbageCollector(Position P)
{
	if (P->Next == NULL) {
		free(P);
		return SUCESS;
	}
	else {
		P = P->Next;
		GarbageCollector(P);
	}
	return SUCESS;
}

int InsertElementAfter(Position P)
{
	P = FindElement(P);

	if (P == NULL) {
		printf("---- WARNING ----- Nije moguce ubacivanje novog elementa\n\n");
		return WARNING;
	}
	else {
		InsertAtBeginnig(P);
	}

	return SUCESS;
}

int InsertElementBefore(Position P)
{
	P = FindPrevElementByLastName(P);

	if (P == NULL) {
		printf("---- WARNING ----- Nije moguce ubacivanje novog elementa\n\n");
		return WARNING;
	}
	else {
		InsertAtBeginnig(P);
	}

	return SUCESS;
}

int SortList(Position P)
{
	Position end = NULL, i, j, prev_j, tmp;

	while (P->Next != end)
	{
		i = P;
		prev_j = i->Next;
		j = prev_j->Next;

		while (j != end)
		{
			if (strcmp(prev_j->prezime, j->prezime) > 0)
			{
				prev_j->Next = j->Next;
				i->Next = j;
				j->Next = prev_j;
			}
			else {
				i = prev_j;
			}
				
			prev_j = j;
			j = j->Next;
		}
		end = prev_j;
	}

	return SUCESS;
}

int InsertInFile(Position P)
{
	FILE* file;
	char nameOfFIle[128];

	printf("\nUnesite ime datoteke: ");
	scanf(" %s", nameOfFIle);

	file = fopen(nameOfFIle, "w+");

	if (file == NULL) {
		printf("\n---- ERROR ---- Datoteka nije kreirana\n");
		return ERROR;
	}
	else {
		while (P != NULL) {
			fprintf(file, "\nIme: %s\nPrezime: %s\nGodina rodjenja: %d\n\n", P->ime, P->prezime, P->godinaRodjenja);
			P = P->Next;
		}
	}

	fclose(file);


	return SUCESS;
}

int ReadFromFile(Position P)
{
	FILE* file;
	char nameOfFile[128];
	Position q;

	printf("\nUnesite ime datoteke za citanje: ");
	scanf(" %s", nameOfFile);

	file = fopen(nameOfFile, "r");

	if (file == NULL) {
		printf("\n---- ERROR ---- Datoteka nije otvorena\n");
		return ERROR;
	}
	else {
		while (!feof(file)) {
			q = AllocationOfMemory();

			fscanf(file, "%s %s %d", q->ime, q->prezime, &q->godinaRodjenja);

			q->Next = P->Next;
			P->Next = q;
		}
	}


	return SUCESS;
}