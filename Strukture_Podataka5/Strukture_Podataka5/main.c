#define _CRT_SECURE_NO_WARNINGS
#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	char fileName[MAX_LENGTH] = { 0 };
	double postfixResult = 0;

	InputFileName(fileName);

	if (CalculatePostfixFile(&postfixResult, fileName) == EXIT_SUCCESS)
	{
		printf("The result is: %.2lf \n", postfixResult);
		return EXIT_SUCCESS;
	}

	else
		return EXIT_FAILURE;
}