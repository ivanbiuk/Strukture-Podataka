#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

Position Insert(Position current, Position newElement)
{
	if (!current)
		return newElement;

	if (current->number < newElement->number)
		current->right = Insert(current->right, newElement);

	else if (current->number > newElement->number)
		current->left = Insert(current->left, newElement);

	else
		free(newElement);

	return current;
}

Position CreateNewElement(int number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(BinaryNode));

	if (!newElement)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	newElement->number = number;
	newElement->left = NULL;
	newElement->right = NULL;
	return newElement;
}

int InorderPrint(Position current)
{
	if (!current)
		return 0;

	InorderPrint(current->left);
	printf(" %d ", current->number);
	InorderPrint(current->right);

	return EXIT_SUCCESS;
}

int PreorderPrint(Position current)
{
	if (!current)
		return 0;

	printf(" %d ", current->number);
	InorderPrint(current->left);
	InorderPrint(current->right);

	return EXIT_SUCCESS;
}

int PostorderPrint(Position current)
{
	if (!current)
		return 0;

	InorderPrint(current->left);
	InorderPrint(current->right);
	printf(" %d ", current->number);

	return EXIT_SUCCESS;

}

int LevelorderPrint(Position current, QPosition qHead)
{
	QPosition temp = qHead;
	Position currentNode = NULL;
	QPosition newElement = NULL;
	QPosition newElement2 = NULL;

	newElement = CreateQueueElement(current);
	Push(temp, newElement);

	while (temp->next)
	{
		currentNode = Pop(temp);
		if (currentNode)
		{
			printf(" %d ", currentNode->number);
			newElement = CreateQueueElement(currentNode->right);
			newElement2 = CreateQueueElement(currentNode->left);
			Push(temp, newElement);
			Push(temp, newElement2);
		}
	}

	return EXIT_SUCCESS;
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

Position SearchTree(Position current, int number)
{
	if (!current)
	{
		printf("Element %d doesn't exist \n", number);
		return NULL;
	}

	if (current->number == number)
	{
		printf("Element %d found \n", number);
		return current;
	}
	else if (number > current->number)
		SearchTree(current->right, number);

	else if (number < current->number)
		SearchTree(current->left, number);
}

Position FindMaxInLeft(Position current)
{
	Position maxElement = current;
	while (maxElement && maxElement->right)
	{
		if (maxElement->number < maxElement->right->number)
			maxElement = maxElement->right;
	}
	return maxElement;
}

Position DeleteElement(Position current, int searchedNum)
{
	if (!current)
	{
		printf("Searched element does not exist");
		return current;
	}

	if (searchedNum < current->number)
		current->left = DeleteElement(current->left, searchedNum);

	else if (searchedNum > current->number)
		current->right = DeleteElement(current->right, searchedNum);

	else if (current->number = searchedNum)
	{
		if (current->left && current->right)
		{
			Position maxSubLeft = NULL;
			maxSubLeft = FindMaxInLeft(current->left);
			current->number = maxSubLeft->number;
			current->left = DeleteElement(current->left, current->number);
		}
		else if (!current->right)
			return current->left;
		else
			return current->right;
	}
	return current;
}

QPosition CreateQueueElement(Position node)
{
	QPosition newElement = NULL;
	newElement = (QPosition)malloc(sizeof(QueueElement));

	if (!newElement)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	newElement->treeNode = node;
	newElement->next = NULL;

	return newElement;
}

int Push(QPosition head, QPosition newQElement)
{
	newQElement->next = head->next;
	head->next = newQElement;

	return EXIT_SUCCESS;
}

Position Pop(QPosition head)
{
	if (!(head->next))
		return NULL;

	QPosition penultimateElement = NULL;
	QPosition lastElement = NULL;
	Position current = NULL;
	penultimateElement = FindPenultimateQElement(head);
	lastElement = penultimateElement->next;

	current = lastElement->treeNode;
	penultimateElement->next = NULL;
	free(lastElement);

	return current;
}

QPosition FindPenultimateQElement(QPosition head)
{
	QPosition penultimateElement = head;
	while (penultimateElement->next->next)
		penultimateElement = penultimateElement->next;

	return penultimateElement;
}