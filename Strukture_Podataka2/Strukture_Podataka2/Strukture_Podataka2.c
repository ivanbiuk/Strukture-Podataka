#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head, char* name, char* surname, int birthYear);
Position FindBySurname(Position first, char* surname);
Position FindPrevious(Position head, Position position);
int DeletePerson(Position head, char* surname);
int UserEnteringInt();

int main(int argc, char** argv)
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;
	Position searchedElement = NULL;
	int userInputInt = 0;
	char name[MAX_SIZE] = {0};
	char surname[MAX_SIZE] = {0};
	int birthYear = 0;

	do {
		printf("Enter a number to choose an action:\n");
		printf("1 - Print all elements \n2 - Prepend a new element \n3 - Append a new element \n4 - Find an element (by surname) \n"
			"5 - Delete an element \n0 - Exit \n\n");

		userInputInt = UserEnteringInt();
			
		switch (userInputInt)
		{
			case 1:
			{
				PrintList(p->next);
				break;
			}
			case 2:
			{
				printf("Enter the data of the new person: \n");
				printf("Name: ");
				scanf("%s", name);
				printf("Surname: ");
				scanf("%s", surname);
				printf("Year of birth: ");
				birthYear = UserEnteringInt();
				PrependList(p, name, surname, birthYear);
				break;
			}
			case 3:
			{
				printf("Enter the data of the new person: \n");
				printf("Name: ");
				scanf("%s", name);
				printf("Surname: ");
				scanf("%s", surname);
				printf("Year of birth: ");
				birthYear = UserEnteringInt();
				AppendList(p, name, surname, birthYear);
				break;
			}
			case 4:
			{
				printf("Enter the surname of the person you want to find: ");
				scanf("%s", surname);
				searchedElement = FindBySurname(p->next, surname);
				if (searchedElement)
					printf("Name: %s, Surname: %s, Year of birth: %d\n", searchedElement->name, searchedElement->surname, searchedElement->birthYear);
				else printf("There is no person with surname: %s\n", surname);
				break;
			}
			case 5:
			{
				printf("Enter the surname of the person you want to delete from the list: ");
				scanf("%s", surname);
				DeletePerson(p, surname);
				break;
			}
			default:
			{
				if (userInputInt != 0)
				{
					printf("Wrong input, please try again.\n\n");
					break;
				}
			}
		}
		puts("\n");
	} while (userInputInt != 0);

	return EXIT_SUCCESS;
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	
	if (!newPerson)
		return -1;

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;
	while (temp)
	{
		printf("Name: %s, Surname: %s, Birth Year: %d \n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int  birthYear)
{
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		perror("Can't allocate memory! \n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;
	return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
	Position temp = head;
	while (temp->next)
		temp = temp->next;

	return temp;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;
	newPerson = CreatePerson(name, surname, birthYear);

	if (!newPerson)
		return -1;

	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

Position FindBySurname(Position first, char* surname)
{
	Position temp = first;
	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
			return temp;
		temp = temp->next;
	}
	return temp;
}

Position FindPrevious(Position head, Position position)
{
	Position temp = head;
	while(temp->next != position)
	{
		temp = temp->next;
	}
	return temp;
}

int DeletePerson(Position head, char* surname)
{
	Position searchedElement = NULL;
	Position previous = NULL;
	searchedElement = FindBySurname(head->next, surname);
	if (searchedElement)
	{
		previous = FindPrevious(head, searchedElement);
		previous->next = searchedElement->next;
		free(searchedElement);
	}
	else
		printf("There is no person with surname: %s\n", surname);

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