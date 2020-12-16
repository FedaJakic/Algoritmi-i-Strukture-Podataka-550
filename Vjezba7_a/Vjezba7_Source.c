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
	int Element;
	Position Next;
};

int MainMenu();
Position AllocationOfMemory();
int PrintList(Position, int);
int GetRadnomValue(int, int);
int Push(Position, int, int);
int Pop(Position, int);

int main()
{
	struct SimulationStructure head;
	int izbor = 0;
	int n = 0;
	int max = 0;

	head.Next = NULL;
	head.Element = -1;

	while (max < 5)
	{
		printf("\r\nUnesite velicinu stoga <5-100> : ");
		scanf_s(" %d", &max);
		if (max < 5 || max > 100)
		{
			max = 0;
			printf("\r\nPogresan unos!");
		}
	}

	head.Next = NULL;
	srand((unsigned)time(NULL));

	while (izbor != 'K' && izbor != 'k')
	{
		izbor = MainMenu();

		switch (izbor)
		{
		case 1:
			if (n < max)
				n = Push(&head, GetRadnomValue(MIN, MAX), n);
			else
				printf("\r\nStog je popunjen!\r\n");
			PrintList(head.Next, n);
			break;
		case 2:
			if (n > 0)
				n = Pop(&head, n);
			PrintList(head.Next, n);
			break;
		case 0:
			printf("\nIZLAZ IZ PROGRAMA\n");
			break;
		default:
			printf("\nPogresan izbor, pokusajte ponovno!\n\n");
		}
	}

	return SUCESS;
}

int MainMenu() {
	int izbor = 0;

	printf("\n-------VJEZBA BROJ 7-------\n");
	printf("---------Main Menu---------\n");
	printf("______________________________\n");
	printf("\n1 ---> Push na stog");
	printf("\n2 ---> Pop sa stoga");
	printf("\n0 ---> Kraj programa");

	printf("\nIzbor : ");
	scanf(" %d", &izbor);

	return izbor;
}


Position AllocationOfMemory()
{
	Position elementToAllocate;
	elementToAllocate = (Position)malloc(sizeof(struct SimulationStructure));

	return elementToAllocate;
}

int PrintList(Position P, int n)
{
	printf("\nU listi se nalazi %d elemenata, i to:\n");
	while (n > 0)
	{
		printf(" %d", P->Element);
		P = P->Next;
		n--;
	}

	return SUCESS;
}

int GetRadnomValue(int minValue, int maxValue)
{
	int value;
	value = rand() % (maxValue - minValue) + minValue;

	return value;
}

int Push(Position P, int x, int n)
{
	static Position last;
	Position q;

	q = AllocationOfMemory;
	if (q)
	{
		if (P->Next == NULL)
			last = q;

		q->Element = x;

		printf("\r\nNa listu se sprema %d.", x);
		q->Next = P->Next;
		P->Next = q;

		last->Next = q;
		n++;
	}
	return n;
}

int Pop(Position P, int n)
{
	static Position last = NULL;
	Position q;

	if (P->Next != NULL)
	{

		q = P->Next;

		printf("\nSa liste se skida: %d.", q->Element);

		P->Next = q->Next;

		if (last == NULL && n > 1)
		{
			while (P->Next != q)
				P = P->Next;
			last = P;
		}

		last->Next = q->Next;

		free(q);
		n--;
		if (n == 0)
			last = NULL;
	}
	else
		printf("\nLista je prazna.");

	return n;
}



