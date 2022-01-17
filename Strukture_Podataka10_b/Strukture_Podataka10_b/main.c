#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH (128)
#define MAX_LINE (1024)

struct _CountryTreeNode;
typedef struct _CountryTreeNode* CountryTreePosition;
struct _CityListNode;
typedef struct _CityListNode* CityListPosition;

typedef struct _CountryTreeNode {
	char countryName[MAX_LENGTH];
	CityListPosition head;
	CountryTreePosition left;
	CountryTreePosition right;
}CountryTreeNode;

typedef struct _CityListNode {
	char cityName[MAX_LENGTH];
	int populationNumber;
	CityListPosition next;
}CityListNode;


int SortedInsertIntoList(CityListPosition head, CityListPosition newElement);
CountryTreePosition CreateNewCountryElement(char name[]);
int InsertIntoTree(CountryTreePosition current, CountryTreePosition newElement);
CountryTreePosition ReadCountryFromFile();
CityListPosition CreateNewCityElement(char name[], int population);
int ReadCityFromFile(CityListPosition head, char fileName[]);
int InorderPrint(CountryTreePosition current);
int PrintCities(CityListPosition head);
CountryTreePosition FindCountry(CountryTreePosition root, char selectedName[]);
int FindLargerCities(CityListPosition head, int selectedPopulation);

int main()
{
	char selectedCountry[MAX_LENGTH] = { 0 };
	int selectedPopulation = 0;
	CountryTreePosition searchedCountry = NULL;
	CountryTreePosition root = NULL;

	root = ReadCountryFromFile();
	InorderPrint(root);

	puts(" ");
	printf("Enter a country and population: ");
	scanf(" %s %d", selectedCountry, &selectedPopulation);
	searchedCountry = FindCountry(root, selectedCountry);
	if (searchedCountry && searchedCountry->head)
		FindLargerCities(searchedCountry->head, selectedPopulation);

	return EXIT_SUCCESS;
}

int SortedInsertIntoList(CityListPosition head, CityListPosition newElement)
{
	CityListPosition temp = head;

	if (!head)
	{
		head = newElement;
	}

	else
	{
		while (temp->next && temp->populationNumber > newElement->populationNumber)
			temp = temp->next;

		if (temp->next && temp->next->populationNumber == newElement->populationNumber)
		{
			int nameCompareStatus = 0;
			nameCompareStatus = strcmp(temp->next->cityName, newElement->cityName);

			if (nameCompareStatus > 0)
			{
				newElement->next = temp->next;
				temp->next = newElement;
			}

			else if (nameCompareStatus < 0)
			{
				newElement->next = temp->next->next;
				temp->next->next = newElement;
			}

			else
			{
				printf("This element already exists!");
				free(newElement);
			}
		}
		else
		{
			newElement->next = temp->next;
			temp->next = newElement;
		}
	}


	return EXIT_SUCCESS;
}

CountryTreePosition CreateNewCountryElement(char name[])
{
	CountryTreePosition newElement = NULL;

	newElement = (CountryTreePosition)malloc(sizeof(CountryTreeNode));
	if (!newElement)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	strcpy(newElement->countryName, name);
	newElement->head = NULL;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

int InsertIntoTree(CountryTreePosition current, CountryTreePosition newElement)
{
	if (!current)
		return newElement;

	else if (strcmp(current->countryName, newElement->countryName) > 0)
		current->left = InsertIntoTree(current->left, newElement);

	else if (strcmp(current->countryName, newElement->countryName) < 0)
		current->right = InsertIntoTree(current->right, newElement);

	return current;
}

CountryTreePosition ReadCountryFromFile()
{
	FILE* file = NULL;
	char countryName[MAX_LENGTH] = { 0 };
	char fileName[MAX_LENGTH] = { 0 };
	int bytesRead = 0;
	CountryTreePosition newCountryElement = NULL;
	CountryTreePosition treeRoot = NULL;

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
			if (!treeRoot)
			{
				CountryTreeNode treeRootElement = { .countryName = countryName, .head = NULL, .left = NULL, .right = NULL };
				treeRoot = &treeRootElement;
				ReadCityFromFile(treeRoot->head, fileName);
			}
			else
			{
				newCountryElement = CreateNewCountryElement(countryName);
				treeRoot = InsertIntoTree(treeRoot, newCountryElement);
				ReadCityFromFile(newCountryElement->head, fileName);
			}
			buffer += bytesRead;
		}
		else
		{
			printf("Incorrect file form");
			return EXIT_FAILURE;
		}
	}
	fclose(file);

	return treeRoot;
}

CityListPosition CreateNewCityElement(char name[], int population)
{
	CityListPosition newElement = NULL;
	newElement = (CityListPosition)malloc(sizeof(CityListNode));

	if (!newElement)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	strcpy(newElement->cityName, name);
	newElement->populationNumber = population;
	newElement->next = NULL;

	return newElement;
}

int ReadCityFromFile(CityListPosition head, char fileName[])
{
	FILE* file = NULL;
	char cityName[MAX_LENGTH] = { 0 };
	int cityPopulation = 0;
	int bytesRead = 0;
	CityListPosition newCityElement = NULL;
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
			if (!head)
				head = newCityElement;
			else
				SortedInsertIntoList(head, newCityElement);

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

int InorderPrint(CountryTreePosition current)
{
	if (!current)
		return 0;

	InorderPrint(current->left);
	printf(" %s ", current->countryName);
	InorderPrint(current->right);

	return EXIT_SUCCESS;
}

int PrintCities(CityListPosition head)
{
	CityListPosition temp = NULL;
	temp = head;

	while (temp)
	{
		printf(" %s ", temp->cityName);
		temp = temp->next;
	}
	puts(" ");
	return EXIT_SUCCESS;
}

CountryTreePosition FindCountry(CountryTreePosition root, char selectedName[])
{
	CountryTreePosition temp = root;

	if (strcmp(temp->countryName, selectedName) > 0)
		FindCountry(temp->left, selectedName);

	else if (strcmp(temp->countryName, selectedName) < 0)
		FindCountry(temp->right, selectedName);

	else return temp;
}

int FindLargerCities(CityListPosition head, int selectedPopulation)
{
	CityListPosition temp = head;

	while (temp)
	{
		if (temp->populationNumber > selectedPopulation)
			printf("%s %d \n", temp->cityName, temp->populationNumber);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}