#define CRT_SECURE_NO_WARNINGS
#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	CountryListNode headElement[HASH_TABLE_SIZE] = { 0 };
	CountryListPosition head = &headElement;
	int i = 0;

	for (i = 0; i < HASH_TABLE_SIZE; i++)
	{
		strcpy(headElement[i].countryName , " ");
		headElement[i].root = NULL;
		headElement[i].next = NULL;
	}

	char selectedCountry[MAX_LENGTH] = { 0 };
	int selectedPopulation = 0;
	CountryListPosition searchedCountry = NULL;

	ReadCountryFromFile(head);
	PrintAll(head);

	/*printf("Enter a country and population: ");
	scanf(" %s %d", selectedCountry, &selectedPopulation);
	searchedCountry = FindCountry(listHead, selectedCountry);
	if (searchedCountry && searchedCountry->root)
		FindLargerCities(searchedCountry->root, selectedPopulation);*/

	return EXIT_SUCCESS;


}