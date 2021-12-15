#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

int main()
{
	Position root = NULL;
	int userInput = 0;
	int newInt = 0;
	Position newElement = NULL;

	do
	{
		printf("Enter a number to choose an action: \n");
		printf(" 1 - Insert a new element \n 2 - Print elements \n 3 - Delete an element \n 4 - Find an element \n 5 - Exit \n");

		userInput = UserEnteringInt();

		switch (userInput)
		{
		case 1:
		{
			printf("Enter the new element: ");
			newInt = UserEnteringInt();
			newElement = CreateNewElement(newInt);
			if (!root)
			{
				BinaryNode headElement = { .number = newInt, .left = NULL, .right = NULL };
				root = &headElement;
			}
			else
				root = Insert(root, newElement);
			break;
		}

		case 2:
		{
			int submenuChoice = 0;
			do {
				printf("  1 - Inorder print \n  2 - Preorder print \n  3 - Postorder print \n  4 - Levelorder print \n  5 - Return to main menu \n");
				submenuChoice = UserEnteringInt();

				switch (submenuChoice)
				{
				case 1:
				{
					InorderPrint(root);
					puts(" ");
					break;
				}
				case 2:
				{
					PreorderPrint(root);
					puts(" ");
					break;
				}
				case 3:
				{
					PostorderPrint(root);
					puts(" ");
					break;
				}
				case 4:
				{
					if (root)
					{
						QueueElement HeadQElement = { .treeNode = NULL, .next = NULL };
						QPosition qHead = &HeadQElement;
						LevelorderPrint(root, qHead);
						puts(" ");
					}
					break;
				}
				default:
				{
					if (submenuChoice != 5)
					{
						printf("Wrong input, please try again \n \n");
						break;
					}
				}
				}
			} while (submenuChoice != 5);
			break;
		}
		case 3:
		{
			printf("Enter a number you want to delete from the list: ");
			newInt = UserEnteringInt();
			DeleteElement(root, newInt);
			break;
		}
		case 4:
		{
			printf("Enter a number you want to search for: ");
			newInt = UserEnteringInt();
			SearchTree(root, newInt);
			puts(" ");
			break;
		}
		}
	} while (userInput != 5);

	return 0;

}
