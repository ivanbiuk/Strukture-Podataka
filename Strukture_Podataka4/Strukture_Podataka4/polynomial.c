#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int ReadFromFile(Position head1, Position head2)
{
	char fileName[MAX_LINE] = { 0 };

	printf("Enter the file name: \n");
	scanf("%s", fileName);

	FILE* file = NULL;
	file = fopen(fileName, "r");

	if (!file)
	{
		perror("Error: Could not open file");
		return -1;
	}

	int lineCounter = 0;
	int coefficient = 0;
	int exponent = 0;
	int numberOfBytesRead = 0;
	char* buffer = (char*)malloc(MAX_LINE * sizeof(char));

	while (!feof(file))
	{
		fgets(buffer, MAX_LINE, file);

		while (strlen(buffer) > 0)
		{
			if (sscanf(buffer, " %d %d %n", &coefficient, &exponent, &numberOfBytesRead) != 2)
			{
				printf("Error: Wrong format in file \n");
				return -1;
			}
			if (lineCounter == 0)
			{
				SortedInsert(head1, coefficient, exponent);
			}
			else
			{
				SortedInsert(head2, coefficient, exponent);
			}
			buffer += numberOfBytesRead;
		}
		lineCounter++;
	}
	fclose(file);
	return EXIT_SUCCESS;
}

int SortedInsert(Position head, int coefficient, int exponent)
{
	Position newElement = NULL;
	newElement = CreateNewElement(coefficient, exponent);

	Position temp = NULL;
	temp = head->next;

	Position previousElement = NULL;

	if (!temp)
	{
		InsertAfter(head, newElement);
	}
	else
	{
		while (temp && (abs(newElement->exponent) < abs(temp->exponent)))
			temp = temp->next;

		if (temp && (exponent == temp->exponent))
		{
			temp->coefficient += coefficient;
			if (!temp->coefficient)
			{
				free(newElement);
				DeleteElement(head, temp);
			}
		}

		else
		{
			previousElement = FindPrevious(head, temp);
			InsertAfter(previousElement, newElement);
		}
	}

	return EXIT_SUCCESS;
}

Position CreateNewElement(int coefficient, int exponent)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(Polynom));

	if (!newElement)
	{
		perror("Could not allocate memory");
		return -1;
	}

	newElement->coefficient = coefficient;
	newElement->exponent = exponent;
	newElement->next = NULL;

	return newElement;
}

int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;
	return EXIT_SUCCESS;
}

Position FindPrevious(Position head, Position position)
{
	Position previous = NULL;
	previous = head;

	while (previous->next != position)
		previous = previous->next;

	return previous;
}

int DeleteElement(Position head, Position currentElement)
{
	Position previousElement = NULL;
	previousElement = FindPrevious(head, currentElement);

	previousElement->next = currentElement->next;
	free(currentElement);

	return EXIT_SUCCESS;
}

int AppendPoly(Position head, Position newElement)
{
	Position temp = NULL;
	temp = head;

	while (temp->next)
		temp = temp->next;

	InsertAfter(temp, newElement);
	return EXIT_SUCCESS;
}

int AdditionPoly(Position poly1, Position poly2, Position additionResult)
{
	Position current1 = poly1->next;
	Position current2 = poly2->next;

	while (current1 || current2)
	{
		if (current1 && !current2)
		{
			SortedInsert(additionResult, current1->coefficient, current1->exponent);
			current1 = current1->next;
		}
		else if (current2 && !current1)
		{
			SortedInsert(additionResult, current2->coefficient, current2->exponent);
			current2 = current2->next;
		}

		else
		{
			if (current1->exponent == current2->exponent)
			{
				SortedInsert(additionResult, current1->coefficient + current2->coefficient, current1->exponent);
				current1 = current1->next;
				current2 = current2->next;
			}
			else if (current1->exponent > current2->exponent)
			{
				SortedInsert(additionResult, current1->coefficient, current1->exponent);
				current1 = current1->next;
			}
			else
			{
				SortedInsert(additionResult, current2->coefficient, current2->exponent);
				current2 = current2->next;
			}
		}
	}
}

int MultiplicationPoly(Position poly1, Position poly2, Position multiplicationResult)
{
	Position current1 = poly1->next;
	Position current2 = poly2->next;

	Position result = NULL;

	while (current1)
	{
		current2 = poly2->next;
		while (current2)
		{
			SortedInsert(multiplicationResult, current1->coefficient * current2->coefficient, current1->exponent + current2->exponent);
			current2 = current2->next;
		}
		current1 = current1->next;
	}
}

int PrintPoly(Position first, char* polyName)
{
	printf("%s = ", polyName);

	if (first)
	{
		if (first->exponent < 0)
		{
			if (first->coefficient == 1)
				printf("x^(%d)", first->exponent);

			else
				printf("%dx^(%d)", first->coefficient, first->exponent);
		}
		else
		{
			if (first->coefficient == 1)
				printf("x^%d", first->exponent);

			else
				printf("%dx^%d", first->coefficient, first->exponent);
		}

	}
	first = first->next;

	while (first)
	{
		if (first->exponent < 0)
		{
			if (first->coefficient > 0)
			{
				if (first->coefficient == 1)
					printf(" + x^(%d) ", first->exponent);
				else
					printf(" + %dx^(%d)", first->coefficient, first->exponent);
			}
			else
			{
				if (first->coefficient == -1)
					printf(" - x^(%d)", first->exponent);
				else
					printf(" - %dx^(%d)", abs(first->coefficient), first->exponent);
			}
		}
		else
		{
			if (first->coefficient > 0)
			{
				if (first->coefficient == 1)
					printf(" + x^%d ", first->exponent);
				else
					printf(" + %dx^%d", first->coefficient, first->exponent);
			}
			else
			{
				if (first->coefficient == -1)
					printf(" - x^%d", first->exponent);
				else
					printf(" - %dx^%d", abs(first->coefficient), first->exponent);
			}
		}
		first = first->next;
	}
	puts(" ");
	return EXIT_SUCCESS;
}

int FreeMemory(Position head)
{
	Position temp = head->next;
	Position previous = NULL;

	while (temp)
	{
		previous = FindPrevious(head, temp);
		previous->next = temp->next;
		free(temp);
		temp = previous->next;
	}

	return EXIT_SUCCESS;
}