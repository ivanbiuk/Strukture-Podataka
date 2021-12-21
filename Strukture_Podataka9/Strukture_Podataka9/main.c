#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "declarations.h"

int main()
{
	time_t t;
	Position root = NULL;
	ListPosition initialListHead = NULL;
	ListPosition replacedListHead = NULL;

	ListNode headListElement1 = { .number = 0, .next = NULL };
	initialListHead = &headListElement1;

	ListNode headListElement2 = { .number = 0, .next = NULL };
	replacedListHead = &headListElement2;

	int userInput = 0;
	int newNumber = 0;

	srand((unsigned)time(&t));

	do
	{
		printf("Enter a number to choose an action: \n");
		printf(" 1 - Insert a new random number from <10, 90> \n 2 - Replace each node value with the sum of it's descendants"
			"and print both trees into a file\n"
			" 0 - Exit \n");

		userInput = UserEnteringInt();
		switch (userInput)
		{
		case 1:
		{
			Position newElement = NULL;
			ListPosition newListElement = NULL;
			if (!root)
			{
				newNumber = rand() % (MAX_NUMBER - MIN_NUMBER + 1) + MIN_NUMBER;
				BinaryNode headElement = { .number = newNumber, .left = NULL, .right = NULL };
				root = &headElement;
			}
			else
			{
				newNumber = rand() % (MAX_NUMBER - MIN_NUMBER + 1) + MIN_NUMBER;
				newElement = CreateNewElement(newNumber);
				Insert(root, newElement);
			}
			printf("Number inserted: %d \n", newNumber);
			break;
		}
		case 2:
		{
			InsertTreeIntoList(root, initialListHead);
			Replace(root);
			InsertTreeIntoList(root, replacedListHead);
			PrintIntoFile(initialListHead, replacedListHead);
			break;
		}
		default:
		{
			if (userInput != 0)
			{
				printf("Wrong input, please try again \n \n");
				break;
			}
		}

		}

	} while (userInput != 0);

	return 0;
}