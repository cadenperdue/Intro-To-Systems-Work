//Caden Perdue
//Programming Assignment 3 - Strucutres
#include <stdio.h>
#include <string.h>
#include "structures.h"
void getOneDVD(dvd_t *dvd)
{
    char c;
    char c1;
    char c2; 
    printf("Enter title: ");
    scanf("%50[^\n]s", dvd->title);
    scanf("%c",&c);
    printf("Enter director: ");
    scanf("%50[^\n]s", dvd->director);
    scanf("%c",&c1);
    printf("Enter play time in minutes: ");
    scanf("%d", &dvd->playTime);
    scanf("%c",&c2);
}
void printOneDVD(dvd_t dvd)
{

    printf("%s:", dvd.title);
    printf("%s:", dvd.director);
    printf("%d\n", dvd.playTime);
}
void getCollection(dvd_t dvd[], int amt)
{
    int i = 0;
    for(i = 0; i < amt; i++)
    {
        getOneDVD(&dvd[i]);
    }
}
void printCollection(dvd_t dvd[], int amt)
{
    int i = 0;
    for(i = 0; i < amt; i++)
    {
        printOneDVD(dvd[i]);
    }
}
