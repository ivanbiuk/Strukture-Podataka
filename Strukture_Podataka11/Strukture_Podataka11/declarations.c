#define _CRT_SECURE_NO_WARNINGS
#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SortedInsertIntoList(CountryListPosition head, CountryListPosition newElement)
{
	CountryListPosition temp = head;

	while (temp->next && strcmp(temp->next->countryName, newElement->countryName))
		temp = temp->next;

	newElement->next = temp->next;
	temp->next = newElement;

	return EXIT_SUCCESS;
}

CountryListPosition CreateNewCountryElement(char name[])
{
	CountryListPosition newElement = NULL;

	newElement = (CountryListPosition)malloc(sizeof(CountryListNode));
	if (!newElement)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	strcpy(newElement->countryName, name);
	newElement->root = NULL;
	newElement->next = NULL;

	return newElement;
}

CityTreePosition InsertIntoTree(CityTreePosition current, CityTreePosition newElement)
{
	if (!current)
		return newElement;

	else if (newElement->populationNumber < current->populationNumber)
		current->left = InsertIntoTree(current->left, newElement);

	else if (newElement->populationNumber > current->populationNumber)
		current->right = InsertIntoTree(current->right, newElement);

	else
	{
		int nameCompareStatus = 0;
		nameCompareStatus = strcmp(newElement->cityName, current->cityName);

		if (nameCompareStatus > 0)
			current->right = InsertIntoTree(current->right, newElement);

		else if (nameCompareStatus < 0)
			current->left = InsertIntoTree(current->left, newElement);

		else
		{
			printf("This element already exists!");
			free(newElement);
		}
	}

	return current;
}

int ReadCountryFromFile(CountryListPosition head)
{
	FILE* file = NULL;
	char countryName[MAX_LENGTH] = { 0 };
	char fileName[MAX_LENGTH] = { 0 };
	int bytesRead = 0;
	CountryListPosition newCountryElement = NULL;

	int hashNumber = 0;

	file = fopen("drzave.txt", "r");
	if (!file)
	{
		perror("Can't open file!\n");
		return EXIT_FAILURE;
	}
	char* buffer = (char*)malloc(MAX_LINE * sizeof(char));

	while (!feof(file))
	{
		fgets(buffer, MAX_LINE, file);

		if (sscanf(buffer, "%s %s %n", countryName, fileName, &bytesRead) == 2)
		{
			newCountryElement = CreateNewCountryElement(countryName);
			hashNumber = HashFunction(countryName);

			if (strcmp((head + hashNumber)->countryName, " ") == 0)
			{
				strcpy((head + hashNumber)->countryName, countryName);
				(head + hashNumber)->root = NULL;
			}
			else
				SortedInsertIntoList((head + hashNumber)->root, newCountryElement);

			newCountryElement->root = ReadCityFromFile(fileName);
			buffer += bytesRead;
		}
		else
		{
			printf("Incorrect file form");
			return EXIT_FAILURE;
		}
	}
	fclose(file);
	return EXIT_SUCCESS;
}

CityTreePosition CreateNewCityElement(char name[], int population)
{
	CityTreePosition newElement = NULL;
	newElement = (CityTreePosition)malloc(sizeof(CityTreeNode));

	if (!newElement)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	strcpy(newElement->cityName, name);
	newElement->populationNumber = population;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

int ReadCityFromFile(char fileName[])
{
	FILE* file = NULL;
	char cityName[MAX_LENGTH] = { 0 };
	int cityPopulation = 0;
	int bytesRead = 0;
	CityTreePosition newCityElement = NULL;
	CityTreePosition root = NULL;
	file = fopen(fileName, "r");

	if (!file)
	{
		perror("Can't open file!\n");
		return EXIT_FAILURE;
	}

	char* buffer = (char*)malloc(MAX_LINE * sizeof(char));

	while (!feof(file))
	{
		fgets(buffer, MAX_LINE, file);

		if (sscanf(buffer, "%s %d %n", cityName, &cityPopulation, &bytesRead) == 2)
		{
			newCityElement = CreateNewCityElement(cityName, cityPopulation);
			root = InsertIntoTree(root, newCityElement);
			buffer += bytesRead;
		}
		else
		{
			printf("Incorrect file form");
			return EXIT_FAILURE;
		}
	}
	fclose(file);
	return EXIT_SUCCESS;
}

int InorderPrint(CityTreePosition current)
{
	if (!current)
		return 0;

	InorderPrint(current->left);
	printf(" %s ", current->cityName);
	InorderPrint(current->right);

	return EXIT_SUCCESS;
}

int PrintAll(CountryListPosition head)
{
	CountryListPosition temp = NULL;
	int i = 0;

	for (i = 0; i < HASH_TABLE_SIZE; i++)
	{
		temp = (head + i);
		if (strcmp(temp->countryName, " "))
		{
			while (temp)
			{
				printf(" %s \n", temp->countryName);
				InorderPrint(temp->root);
				puts(" ");
				temp = temp->next;
			}
		}
	}
	return EXIT_SUCCESS;
}

CountryListPosition FindCountry(CountryListPosition head, char selectedName[])
{
	CountryListPosition temp = head;

	while (temp && strcmp(temp->countryName, selectedName))
		temp = temp->next;

	if (temp)
		return temp;
	else
	{
		printf("There is no such country");
		return NULL;
	}
}

int FindLargerCities(CityTreePosition current, int selectedPopulation)
{
	if (current)
	{
		FindLargerCities(current->left, selectedPopulation);
		if (current->populationNumber > selectedPopulation)
		{
			printf("%s ", current->cityName);
		}
		FindLargerCities(current->right, selectedPopulation);
	}

	return EXIT_SUCCESS;
}

int HashFunction(char countryName[])
{
	int i = 0;
	int hashCode = 0;
	int n = 0;
	int sum = 0;

	if (strlen(countryName) > NUMBER_OF_CHARACTERS_TO_COUNT_FOR_HASH)
		n = NUMBER_OF_CHARACTERS_TO_COUNT_FOR_HASH;
	else
		n = strlen(countryName);

	for (i = 0; i < n; ++i)
	{
		sum += countryName[i];
	}

	hashCode = sum % HASH_TABLE_SIZE;

	return hashCode;
}