#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

#define SUCESS 0
#define WARNING 1
#define ERROR -1
#define MIN 0
#define MAX 10000

struct SimulationStructure;
typedef struct SimulationStructure* Position;

struct SimulationStructure
{
	int data;
	int Priority;
	Position Next;
};

Position AllocationOfMemory();
int PrintList(Position);
int GetRadnomValue(int, int);
void Push(Position, int);
void Pop(Position);
int PrintList(Position);

int main()
{
	struct SimulationStructure head;
	int izbor = 0;
	head.Next = NULL;

	srand((unsigned)time(NULL));

	while (izbor != 3)
	{
		izbor = MainMenu();

		switch (izbor)
		{
		case 1:
			Push(&head, GetRadnomValue(MIN, MAX));
			PrintList(head.Next);
			break;
		case 2:
			Pop(&head);
			PrintList(head.Next);
			break;
		case 3:
			printf("\nIZLAZ IZ PROGRAMA\n");
			break;
		default:
			printf("\nPogresan izbor, pokusajte ponovno!\n\n");
		}
	}


}

int MainMenu() {
	int izbor = 0;

	printf("\n-------VJEZBA BROJ 7b-------\n");
	printf("---------Main Menu---------\n");
	printf("______________________________\n");
	printf("\n1 ---> Push na stog");
	printf("\n2 ---> Pop sa stoga");
	printf("\n3 ---> Kraj programa");

	printf("\nVas izbor: ");
	scanf(" %d", &izbor);

	return izbor;
}

Position AllocationOfMemory()
{
	Position elementToAllocate;
	elementToAllocate = (Position)malloc(sizeof(struct SimulationStructure));

	return elementToAllocate;
}

int GetRadnomValue(int maxValue, int minValue)
{
	int value;
	value = rand() % (maxValue - minValue) + minValue;

	return value;
}

void Pop(Position P)
{
	Position q;

	if (P->Next != NULL)
	{
		q = P->Next;

		printf("\nSa liste se skida: %d.", q->data);

		P->Next = q->Next;
		free(q);
	}
	else
		printf("\nList is Empty.");
}

int PrintList(Position P) {
	if (P == NULL) {
		printf("LISTA JE PRAZNA!\n");
		return SUCESS;
	}
	else {
		printf("\n---- Elementi liste ----\n");
		while (P != NULL) {
			printf(" ( %d %d )", P->data, P->Priority);

			P = P->Next;
		}
	}

	return SUCESS;
}

void Push(Position P, int n)
{
	Position q;

	q = AllocationOfMemory();
	if (q)
	{
		q->data = n;
		q->Priority = GetRadnomValue(1, 5);
		printf("\r\nNa listu se sprema ( %d %d )", q->data, q->Priority);

		while (P->Next != NULL && P->Next->Priority >= q->Priority)
			P = P->Next;

		q->Next = P->Next;
		P->Next = q;
	}
}