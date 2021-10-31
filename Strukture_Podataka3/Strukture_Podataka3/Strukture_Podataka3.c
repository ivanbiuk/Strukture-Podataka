#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)

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
int InsertAfterElement(Position first, Position sortedHead, char* surname);
int InsertBeforeElement(Position head, Position sortedHead, char* surname);
int InsertInSortedList(Position head, char* name, char* surname, int birthYear);
int CopyList(Position first, Position sortedFirst);
int PrintInFile(Position first);
int ReadFromFile(Position head, Position sortedHead);

int main(int argc, char** argv)
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;

	Person Head2 = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position sortedP = &Head2;

	Position searchedElement = NULL;
	int userInputInt = 0;
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;

	do {
		printf("Enter a number to choose an action:\n");
		printf("1 - Print all elements \n2 - Prepend a new element \n3 - Append a new element \n4 - Find an element (by surname) \n"
			"5 - Delete an element \n6 - Enter a new element after a specific element \n"
			"7 - Enter a new element before a specific element \n8 - Sort the list \n9 - Print the list in a file \n"
			"10 - Read the list from a file \n0 - Exit \n\n");

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
				InsertInSortedList(sortedP, name, surname, birthYear);
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
				InsertInSortedList(sortedP, name, surname, birthYear);
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
				DeletePerson(sortedP, surname);
				break;
			}
			case 6:
			{
				printf("Enter the surname of the person after which you want to add a new element: ");
				scanf("%s", surname);
				InsertAfterElement(p->next, sortedP, surname);
				break;
			}
			case 7:
			{
				printf("Enter the surname of the person before which you want to add a new element: ");
				scanf("%s", surname);
				InsertBeforeElement(p, sortedP, surname);
				break;
			}
			case 8:
			{
				CopyList(p->next, sortedP->next);
				break;
			}
			case 9:
			{
				PrintInFile(p->next);
				break;
			}
			case 10:
			{
				ReadFromFile(p, sortedP);
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
	while (temp->next != position)
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

int InsertAfterElement(Position first, Position sortedHead, char* surname)
{
	Position searchedElement = NULL;
	searchedElement = FindBySurname(first, surname);

	if (searchedElement)
	{
		char name[MAX_SIZE] = { 0 };
		char surname[MAX_SIZE] = { 0 };
		int birthYear = 0;

		Position newPerson = NULL;

		printf("Enter the data of the new person: \n");
		printf("Name: ");
		scanf("%s", name);
		printf("Surname: ");
		scanf("%s", surname);
		printf("Year of birth: ");
		birthYear = UserEnteringInt();

		newPerson = CreatePerson(name, surname, birthYear);

		if (!newPerson)
			return -1;

		InsertAfter(searchedElement, newPerson);
		InsertInSortedList(sortedHead, name, surname, birthYear);

		return EXIT_SUCCESS;
	}
	else
	{
		printf("There is no person with the surname: %s", surname);
		return EXIT_SUCCESS;
	}
}
int InsertBeforeElement(Position head, Position sortedHead, char* surname)
{
	Position searchedElement = NULL;
	searchedElement = FindBySurname(head->next, surname);

	if (searchedElement)
	{
		Position previousElement = NULL;
		previousElement = FindPrevious(head, searchedElement);

		char name[MAX_SIZE] = { 0 };
		char surname[MAX_SIZE] = { 0 };
		int birthYear = 0;

		Position newPerson = NULL;

		printf("Enter the data of the new person: \n");
		printf("Name: ");
		scanf("%s", name);
		printf("Surname: ");
		scanf("%s", surname);
		printf("Year of birth: ");
		birthYear = UserEnteringInt();

		newPerson = CreatePerson(name, surname, birthYear);

		if (!newPerson)
			return -1;

		InsertAfter(previousElement, newPerson);
		InsertInSortedList(sortedHead, name, surname, birthYear);

		return EXIT_SUCCESS;
	}
	else
	{
		printf("There is no person with the surname: %s", surname);
		return EXIT_SUCCESS;
	}
}

int PrintInFile(Position first)
{
	char fileName[MAX_SIZE] = { 0 };
	printf("Enter the name of the file to print in: \n");
	scanf("%s", fileName);

	FILE* file = NULL;
	file = fopen(fileName, "w");

	if (!file)
	{
		printf("Error: Could not open file");
		return -1;
	}

	Position temp = first;
	while (temp)
	{
		fprintf(file, "%s %s %d \n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	fclose(file);
	return EXIT_SUCCESS;
}

int InsertInSortedList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	newPerson = CreatePerson(name, surname, birthYear);

	Position previousElement = NULL;
	Position temp = head->next;

	if (!newPerson)
		return -1;

	if (!temp)
		InsertAfter(head, newPerson);
	
	else
	{
		while (temp && (strcmp(surname, temp->surname) > 0))
			temp = temp->next;

		previousElement = FindPrevious(head, temp);
		InsertAfter(previousElement, newPerson);
	}

	return EXIT_SUCCESS;
}

int CopyList(Position first, Position sortedFirst)
{
	Position temp = NULL;
	Position sortedTemp = NULL;

	temp = first;
	sortedTemp = sortedFirst;

	while (temp)
	{

		strcpy(temp->name, sortedTemp->name);
		strcpy(temp->surname, sortedTemp->surname);
		temp->birthYear = sortedTemp->birthYear;

		temp = temp->next;
		sortedTemp = sortedTemp->next;
	}

	return EXIT_SUCCESS;
}

int ReadFromFile(Position head, Position sortedHead)
{
	char fileName[MAX_SIZE] = { 0 };
	printf("Enter the name of the file to read from: \n");
	scanf("%s", fileName);

	FILE* file = NULL;
	file = fopen(fileName, "r");

	if (!file)
	{
		printf("Error: Could not open file");
		return -1;
	}
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;
	char buffer[MAX_LINE] = { 0 };

	Position temp = head;
	while (!feof(file))
	{
		if (fgets(buffer, MAX_LINE, file))
		{
			if (sscanf(buffer, " %s %s %d", name, surname, &birthYear) == 3)
			{
				AppendList(head, name, surname, birthYear);
				InsertInSortedList(sortedHead, name, surname, birthYear);
			}
		}
	}
	fclose(file);
	return EXIT_SUCCESS;
}
