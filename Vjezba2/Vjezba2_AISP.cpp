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

	

	while (izbor != 6) {
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
	printf("6 ---> EXIT/Izlaz iz programa\n\n");

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