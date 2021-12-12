#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

int main()
{
	Directory rootDirectory = { .name = "root", .sibling = NULL, .child = NULL };
	Position root = &rootDirectory;
	Position current = root;

	StackElement stackHead = { .directory = NULL, .next = NULL };
	StackPosition stack = &stackHead;

	int userInput = 0;
	char directoryName[MAX_SIZE] = { 0 };
	do
	{
		printf("Enter a number to choose an action: \n");
		printf(" 1 - md (Make directory) \n 2 - cd dir (Change position to an another directory) \n 3 - cd .. (Move to parent directory) \n"
			" 4 - dir (Print the content of the directory) \n 5 - exit \n");

		userInput = UserEnteringInt();

		switch (userInput)
		{
		case 1:
		{
			printf("Enter the name of the new directory: ");
			scanf(" %s", directoryName);
			Position newDirectory = CreateNewDirectory(directoryName);
			current->child = Insert(current->child, newDirectory);
			break;
		}

		case 2:
		{
			printf("Enter the name of the destination directory: ");
			scanf(" %s", directoryName);
			current = MoveToSubdirectory(current, directoryName, stack);
			break;
		}
		case 3:
		{
			current = Pop(stack, current);
			break;
		}
		case 4:
		{
			printf("/%s: \n", current->name);
			PrintAllSubdirectories(current);
			break;
		}
		default:
		{
			if (userInput != 5)
			{
				printf("Wrong input, please try again.\n\n");
				break;
			}
		}
		}
		puts("\n");

	} while (userInput != 5);

	FreeMemory(root->child);

	return EXIT_SUCCESS;
}