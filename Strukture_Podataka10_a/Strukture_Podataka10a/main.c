#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH (128)
#define MAX_LINE (1024)

struct _CountryListNode;
typedef struct _CountryListNode* CountryListPosition;
struct _CityTreeNode;
typedef struct _CityTreeNode* CityTreePosition;

typedef struct _CountryListNode {
	char countryName[MAX_LENGTH];
	CityTreePosition root;
	CountryListPosition next;
}CountryListNode;

typedef struct _CityTreeNode {
	char cityName[MAX_LENGTH];
	int populationNumber;
	CityTreePosition left;
	CityTreePosition right;
}CityTreeNode;


int SortedInsertIntoList(CountryListPosition head, CountryListPosition newElement);
CountryListPosition CreateNewCountryElement(char name[]);
int InsertIntoTree(CityTreePosition current, CityTreePosition newElement);
int ReadCountryFromFile(CountryListPosition head);
CityTreePosition CreateNewCityElement(char name[], int population);
int ReadCityFromFile(char fileName[]);
int InorderPrint(CityTreePosition current);
int PrintAll(CountryListPosition head);
CountryListPosition FindCountry(CountryListPosition head, char selectedName[]);
int FindLargerCities(CityTreePosition current, int selectedPopulation);

int main()
{
	CountryListNode listHeadElement = { .countryName = " ", .root = NULL, .next = NULL };
	CountryListPosition listHead = &listHeadElement;
	char selectedCountry[MAX_LENGTH] = { 0 };
	int selectedPopulation = 0;
	CountryListPosition searchedCountry = NULL;

	ReadCountryFromFile(listHead);
	PrintAll(listHead->next);

	printf("Enter a country and population: ");
	scanf(" %s %d", selectedCountry, &selectedPopulation);
	searchedCountry = FindCountry(listHead, selectedCountry);
	if(searchedCountry && searchedCountry->root)
		FindLargerCities(searchedCountry->root, selectedPopulation);

	return EXIT_SUCCESS;
}

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

int InsertIntoTree(CityTreePosition current, CityTreePosition newElement)
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
			SortedInsertIntoList(head, newCountryElement);
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
	return root;
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
	temp = head;
	while (temp)
	{
		printf(" %s \n", temp->countryName);
		InorderPrint(temp->root);
		puts(" ");
		temp = temp->next;
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