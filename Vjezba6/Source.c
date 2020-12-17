#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCESS 0
#define WARNING 1
#define ERROR -1
#define MIN_NUM 10
#define MAX_NUM 100
#define BUFFER_LENGTH 1024

struct SimulationStructure;
typedef struct SimulationStructure* Position;

struct SimulationStructure {
	int data;
	Position Next;
};

int MainMenu();
Position AllocationOfMemory();
int GetRadnomValue(int, int);
int PrintList(Position);
int PushOnStack(Position);
int Pop(Position);
int PushToRow(Position);
int GarbageCollector(Position);

int main() {
	struct SimulationStructure stack;
	struct SimulationStructure row;
	stack.Next = NULL;
	row.Next = NULL;

	int izbor = 0;



	while (izbor != 5) {
		izbor = MainMenu();

		switch (izbor) {
		case 1:
			PushOnStack(&stack);
			PrintList(stack.Next);
			break;
		case 2:
			Pop(&stack);
			PrintList(stack.Next);
			break;
		case 3:
			PushToRow(&row);
			PrintList(row.Next);
			break;
		case 4:
			Pop(&row);
			PrintList(row.Next);
			break;
		case 5:
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

	printf("\n-------VJEZBA BROJ 6-------\n");
	printf("---------Main Menu---------\n");
	printf("______________________________\n");
	printf("1 ---> Push on Stack\n");
	printf("2 ---> Pop from Stack\n");
	printf("3 ---> Push on Row\n");
	printf("4 ---> Pop from Row\n");
	printf("5 ---> EXIT/Izlaz iz programa\n\n");

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

int GetRadnomValue(int minValue, int maxValue)
{
	int value;
	value = rand() % (maxValue - minValue) + minValue;

	return value;
}

int PrintList(Position P)
{
	if (P == NULL) {
		printf("LISTA JE PRAZNA!\n");
		return SUCESS;
	}
	else {
		printf("\n---- Elementi ----\n");
		while (P != NULL) {
			printf("Data: %d\n", P->data);

			P = P->Next;
		}
	}

	return SUCESS;
}

int PushOnStack(Position P)
{

	Position q;
	q = AllocationOfMemory();

	if (q == NULL) {
		printf("Error in allocation\n");
		return ERROR;
	}
	else {
		q->data = GetRadnomValue(MIN_NUM, MAX_NUM);
		q->Next = P->Next;
		P->Next = q;
	}

	return SUCESS;
}

int Pop(Position P)
{

	Position q;

	if (P->Next != NULL) {
		q = P->Next;

		P->Next = q->Next;
		free(q);
	}

	return SUCESS;
}

int PushToRow(Position P)
{

	Position q;
	static Position last;

	if (P->Next == NULL)
		last = P;

	q = AllocationOfMemory();

	if (q == NULL) {
		printf("Error in allocation\n");
		return ERROR;
	}
	else {
		q->data = GetRadnomValue(MIN_NUM, MAX_NUM);
		q->Next = last->Next;
		last->Next = q;
		last = q;
	}

	return SUCESS;
}
