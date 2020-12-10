#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define SUCCES 0
#define WARNING 1
#define ERROR -1
#define BUFFER_LENGTH 1024

struct Podatak;
typedef struct Podatak* Position;

struct Podatak {
	int data;
	Position Next;
};

int ReadFromFile(Position);
Position AllocationOfMemory();
int PrintList(Position);
int FindUnion(Position, Position, Position);
int FindSameElements(Position, Position, Position);
int Insert(int, Position);


int main() {
	struct Podatak L1, L2, Union, SameElements;
	L1.Next = NULL;
	L2.Next = NULL;
	Union.Next = NULL;
	SameElements.Next = NULL;

	ReadFromFile(&L1);
	ReadFromFile(&L2);
	PrintList(L1.Next);
	PrintList(L2.Next);
	FindUnion(L1.Next, L2.Next, &Union);
	PrintList(Union.Next);
	FindSameElements(L1.Next, L2.Next, &SameElements);
	PrintList(SameElements.Next);

	return SUCCES;
}

int ReadFromFile(Position P)
{
	Position q, Start;
	FILE* file;
	char nameOfFile[BUFFER_LENGTH];
	
	Start = P;

	printf("Unesite ime datoteke za citanje: ");
	scanf(" %s", nameOfFile);

	file = fopen(nameOfFile, "r");

	if (file == NULL) {
		printf("\n---- ERROR ---- Datoteka nije otvorena\n");
		return ERROR;
	}

	else {
		while (!feof(file)) {
			q = AllocationOfMemory();
			fscanf(file," %d", &q->data);
			while (P->Next != NULL && P->Next->data < q->data)
			{
				P = P->Next;
			}

			q->Next = P->Next;
			P->Next = q;
			P = Start;
		}
	}

	fclose(file);

	return SUCCES;
}

Position AllocationOfMemory()
{
	Position elementToAllocate;
	elementToAllocate = (Position)malloc(sizeof(struct Podatak));

	return elementToAllocate;
}

int PrintList(Position P)
{
	if (P == NULL) {
		printf("\n\n-----LIST IS EMPTY!-----\n\\n");
		return WARNING;
	}
	else
	{
		printf("\n---------\nIspis liste: \n");
		while (P != NULL) {
			printf("Data = %d\n", P->data);
			P = P->Next;
		}
	}

	return SUCCES;
}

int FindUnion(Position L1, Position L2, Position Union)
{
	Position q;

	printf("\n\n----Unija elemenata: ----\n");

	while (L1 != NULL && L2 != NULL) {
		if (L1->data < L2->data) {
			q = AllocationOfMemory();

			if (q == NULL) {
				printf("\n---- ERROR ---- Greska u alokaciji memorije u Uniji\n");
				return ERROR;
			}

			q->data = L1->data;
			q->Next = Union->Next;
			Union->Next = q;
			L1 = L1->Next;
		}
		else if (L1->data > L2->data) {
			q = AllocationOfMemory();

			if (q == NULL) {
				printf("\n---- ERROR ---- Greska u alokaciji memorije u Uniji\n");
				return ERROR;
			}

			q->data = L2->data;
			q->Next = Union->Next;
			Union->Next = q;
			L2 = L2->Next;
		}
		else {
			q = AllocationOfMemory();
			if (q == NULL) {
				printf("\n---- ERROR ---- Greska u alokaciji memorije u Uniji\n");
				return ERROR;
			}

			q->data = L1->data;
			q->Next = Union->Next;
			Union->Next = q;
			L1 = L1->Next;
			L2 = L2->Next;
		}

		Union = Union->Next;

		if (L1 == NULL) {
			q = L2;
		}
		else {
			q = L1;
		}
		while (q != NULL) {
			Union->Next = q;
			q = q->Next;
		}
	}

	return SUCCES;
}

int FindSameElements(Position L1, Position L2, Position SameElements)
{
	Position q;

	printf("\n\n----Presjek elemenata: ----\n");
	
	while (L1 != NULL && L2 != NULL) {
		if (L1->data < L2->data) {
			L1 = L1->Next;
		}
		else if (L1->data > L2->data) {
			L2 = L2->Next;
		}
		else{
			q = AllocationOfMemory();

			if (q == NULL) {
				printf("\n---- ERROR ---- Greska u alokaciji memorije u Presjeku\n");
				return ERROR;
			}

			q->data = L1->data;
			q->Next = SameElements->Next;
			SameElements->Next = q;
			L1 = L1->Next;
			L2 = L2->Next;
			SameElements = SameElements->Next;
		}
	}

	return SUCCES;
}