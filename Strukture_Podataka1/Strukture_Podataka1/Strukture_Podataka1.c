#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME (128)
#define MAX_LINE (1024)

typedef struct{
    char ime[MAX_NAME];
    char prezime[MAX_NAME];
    int bodovi;
} student;

int procitajDatoteku(char* nazivDatoteke);
student* alocirajIProcitajIzDatoteke(char* nazivDatoteke, int brojStudenata);
int pronadiMaxBodove(student* studenti, int brojStudenata);
int ispisPodataka(student* studenti, int brojStudenata, int maxBodovi);

int main()
{
    int brojStudenata = 0;
    int maxBodovi = 0;
    char* datoteka = "studenti.txt";
    student* studenti = NULL;

    brojStudenata = procitajDatoteku(datoteka);
    studenti = alocirajIProcitajIzDatoteke(datoteka, brojStudenata);
    maxBodovi = pronadiMaxBodove(studenti, brojStudenata);
    ispisPodataka(studenti, brojStudenata, maxBodovi);

    free(studenti);

    return 0;
}

int procitajDatoteku(char* nazivDatoteke)
{
    FILE* datoteka = NULL;
    int brojac = 0;
    char buffer[MAX_LINE] = { 0 };

    datoteka = fopen(nazivDatoteke, "r");

    if (!datoteka)
    {
        printf("Neuspjesno otvaranje datoteke! \n");
        return -1;
    }

    while (!feof(datoteka))
    {
        fgets(buffer, MAX_LINE, datoteka);
        brojac++;
    }

    fclose(datoteka);
    return brojac;
}

student* alocirajIProcitajIzDatoteke(char* nazivDatoteke, int brojStudenata)
{
    FILE* datoteka = NULL;
    student* studenti = NULL;
    int brojac = 0;

    studenti = (student*)malloc(brojStudenata * sizeof(student));
    if (!studenti)
    {
        printf("Neuspjesna alokacija memorije! \n");
        return NULL;
    }

    datoteka = fopen(nazivDatoteke, "r");
    if (!datoteka)
    {
        printf("Neuspjesno otvaranje datoteke!");
        return NULL;
    }

    while (!feof(datoteka))
    {
        fscanf(datoteka, " %s %s %d\n", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
        brojac++;
    }
    fclose(datoteka);

    return studenti;
}

int pronadiMaxBodove(student* studenti, int brojStudenata)
{
    int brojac = 0;
    int maxBodovi = 0;
    while (brojac < brojStudenata)
    {
        if (studenti[brojac].bodovi > maxBodovi)
            maxBodovi = studenti[brojac].bodovi;

        brojac++;
    }
    return maxBodovi;
}

int ispisPodataka(student* studenti, int brojStudenata, int maxBodovi)
{
    int brojac = 0;
    while (brojac < brojStudenata)
    {
        printf("%s %s %d %.2lf\n", studenti[brojac].ime, studenti[brojac].prezime, studenti[brojac].bodovi, (float) studenti[brojac].bodovi / maxBodovi * 100);
        brojac++;
    }
    return 0;
}
