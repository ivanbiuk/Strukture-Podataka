#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int main()
{
	Polynom Head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Position poly1 = &Head1;

	Polynom Head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Position poly2 = &Head2;

	Polynom Head3 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Position additionResult = &Head3;

	Polynom Head4 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Position multiplicationResult = &Head4;

	int inputStatus = 0;

	inputStatus = ReadFromFile(poly1, poly2);
	
	if (inputStatus == EXIT_SUCCESS)
	{
		PrintPoly(poly1->next, "P1");
		PrintPoly(poly2->next, "P2");

		AdditionPoly(poly1, poly2, additionResult);
		PrintPoly(additionResult->next, "P1 + P2");

		MultiplicationPoly(poly1, poly2, multiplicationResult);
		PrintPoly(multiplicationResult->next, "P1 * P2");

		FreeMemory(poly1);
		FreeMemory(poly2);
		FreeMemory(additionResult);
		FreeMemory(multiplicationResult);
	}
	else
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}