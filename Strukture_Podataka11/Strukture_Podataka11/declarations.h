#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX_LENGTH (128)
#define MAX_LINE (1024)
#define HASH_TABLE_SIZE (11)
#define NUMBER_OF_CHARACTERS_TO_COUNT_FOR_HASH (5)

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
CityTreePosition InsertIntoTree(CityTreePosition current, CityTreePosition newElement);
int ReadCountryFromFile(CountryListPosition head);
CityTreePosition CreateNewCityElement(char name[], int population);
int ReadCityFromFile(char fileName[]);
int InorderPrint(CityTreePosition current);
int PrintAll(CountryListPosition head);
CountryListPosition FindCountry(CountryListPosition head, char selectedName[]);
int FindLargerCities(CityTreePosition current, int selectedPopulation);
int HashFunction(char countryName[]);

#endif
