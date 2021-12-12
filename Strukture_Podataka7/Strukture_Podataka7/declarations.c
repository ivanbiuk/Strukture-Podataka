#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

Position Insert(Position current, Position newElement)
{
	if (!current)
		return newElement;

	if (strcmp(current->name, newElement->name) < 0)
		current->sibling = Insert(current->sibling, newElement);

	else if (strcmp(current->name, newElement->name) > 0)
	{
		newElement->sibling = current;
		return newElement;
	}
	return current;
}

Position CreateNewDirectory(char name[])
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(Directory));

	if (!newElement)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	strcpy(newElement->name, name);
	newElement->sibling = NULL;
	newElement->child = NULL;

	return newElement;
}

StackPosition CreateStackElement(Position currentDirectory)
{
	StackPosition newElement = NULL;
	newElement = (StackPosition)malloc(sizeof(StackElement));

	if (!newElement)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	newElement->directory = currentDirectory;
	newElement->next = NULL;

	return newElement;
}


int Push(StackPosition head, StackPosition newStackElement)
{
	newStackElement->next = head->next;
	head->next = newStackElement;

	return EXIT_SUCCESS;
}

Position Pop(StackPosition head, Position current)
{
	StackPosition first = NULL;
	first = head->next;

	Position temp = NULL;

	if (!first)
	{
		printf("This directory does not have a parent");
		return current;
	}
	temp = first->directory;

	head->next = first->next;
	free(first);

	return temp;
}

int PrintAllSubdirectories(Position current)
{
	Position temp = current->child;

	while (temp)
	{
		printf(" -%s \n", temp->name);
		temp = temp->sibling;
	}

	return EXIT_SUCCESS;
}

Position MoveToSubdirectory(Position current, char* destinationName, StackPosition stack)
{
	Position temp = current->child;
	while (temp && strcmp(temp->name, destinationName))
		temp = temp->sibling;

	if (temp == NULL)
	{
		printf("There is no subdirectory with name: %s ", destinationName);
		return current;
	}
	else
	{
		StackPosition newStackElement = CreateStackElement(current);
		Push(stack, newStackElement);
		return temp;
	}
	return temp;
}

int UserEnteringInt()
{
	char userInput[MAX_SIZE] = { 0 };
	int userInputInt = 0;
	int inputStatus = 0;
	do {

		scanf("%s", userInput);
		for (int i = 0; i < strlen(userInput); i++)
		{
			inputStatus = 0;

			if (isdigit(userInput[i]) == 0)
			{
				inputStatus = 1;
				printf("Wrong input, please enter a number \n");
				break;
			}
		}

	} while (inputStatus == 1);

	userInputInt = atoi(userInput);

	return userInputInt;
}

int FreeMemory(Position current)
{
	if (current && current->sibling)
		FreeMemory(current->sibling);

	if (current && current->child)
		FreeMemory(current->child);

	free(current);

	return EXIT_SUCCESS;
}