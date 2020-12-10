#include<stdio.h>
#include<stdlib.h>

#define SUCCES 0
#define ERROR -1
#define WARNING 1
#define BUFFER_LENGHT 1024

struct Polinom;
typedef struct Polinom* Position;

struct Polinom
{
	int konstanta;
	int eksponent;
	Position Next;
};

Position AllocatioOfMemory();
int ReadFromFile(Position);
int PrintList(Position);
int Sum(Position, Position, Position);
int Multiply(Position, Position, Position);


int main() {
	struct Polinom P, Q, S, M;
	P.Next = NULL;
	Q.Next = NULL;
	S.Next = NULL;
	M.Next = NULL;

	ReadFromFile(&P);
	ReadFromFile(&Q);
	printf("\n");

	printf("\nP(x) = ");
	PrintList(P.Next);
	printf("\nQ(x) = ");
	PrintList(Q.Next);

	printf("\n");
	Sum(P.Next, Q.Next, &S);
	printf("\nS(x) = P(x) + Q(x) = ");
	PrintList(S.Next);

	printf("\n");
	Multiply(P.Next, Q.Next, &M);
	printf("\nM(x) = P(x) * Q(x) = ");
	PrintList(M.Next);
	printf("\n");

	return 0;
}

Position AllocatioOfMemory()
{
	Position elementToAllocate;

	elementToAllocate = (Position)malloc(sizeof(struct Polinom));

	return elementToAllocate;
}

int ReadFromFile(Position P) {
	FILE* file1;
	Position q, start;

	start = P;

	char nameOfFile[BUFFER_LENGHT];


	printf("\n\nUnesite ime datoteke za ocitavanje polinoma: ");
	scanf(" %s", nameOfFile);

	file1 = fopen(nameOfFile, "r");

	if (file1 == NULL) {
		printf("\nNeuspjesno otvorena datoteka 1!\n");
		return ERROR;
	}
	else {

		while (!feof(file1)) {
			q = AllocatioOfMemory();

			fscanf(file1, " %d %d", &q->konstanta, &q->eksponent);

			while (P->Next != NULL && P->Next->eksponent > q->eksponent) {
				P = P->Next;
			}

			q->Next = P->Next;
			P->Next = q;
			P = start;
		}

	}

	return SUCCES;
}

int PrintList(Position P) {
	if (P == NULL) {
		printf("LISTA JE PRAZNA!\n");
		return SUCCES;
	}
	else {
		printf("\n\nIspis liste:\n");
		while (P != NULL) {
			printf("%d * x ^ %d + ", P->konstanta, P->eksponent);

			P = P->Next;
		}
	}

	return SUCCES;
}

int Sum(Position P, Position Q, Position S)
{
	Position q, i;
	while (P != NULL && Q != NULL)
	{
		q = AllocatioOfMemory();

		if (P->eksponent > Q->eksponent)
		{
			q->eksponent = P->eksponent;
			q->konstanta = P->konstanta;

			P = P->Next;
		}
		else if (P->eksponent < Q->eksponent)
		{
			q->eksponent = Q->eksponent;
			q->konstanta = Q->konstanta;

			Q = Q->Next;
		}
		else
		{
			q->eksponent = P->eksponent;
			q->konstanta = P->konstanta + Q->konstanta;

			P = P->Next;
			Q = Q->Next;
		}

		q->Next = S->Next;
		S->Next = q;
		S = S->Next;
	}

	if (P == NULL)
		i = Q;
	else
		i = P;

	while (i != NULL)
	{
		q = AllocatioOfMemory();

		q->eksponent = i->eksponent;
		q->konstanta = i->konstanta;

		i = i->Next;

		q->Next = S->Next;
		S->Next = q;
		S = S->Next;
	}

	return SUCCES;
}

int Multiply(Position P, Position Q, Position M)
{
	Position q, i, j, tmp;

	i = P;
	while (i != NULL)
	{
		j = Q;
		while (j != NULL)
		{
			q = AllocatioOfMemory();

			q->eksponent = i->eksponent + j->eksponent;
			q->konstanta = i->konstanta * j->konstanta;

			tmp = M;

			while (tmp->Next != NULL && tmp->Next->eksponent > q->eksponent)
				tmp = tmp->Next;

			if (tmp->Next != NULL && tmp->Next->eksponent == q->eksponent)
			{
				tmp->Next->konstanta += q->konstanta;
				free(q);
			}
			else
			{
				q->Next = tmp->Next;
				tmp->Next = q;
			}
			j = j->Next;
		}
		i = i->Next;
	}

	return SUCCES;
}