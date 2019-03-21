#include <stdio.h>
#include <string.h>
#define TEXT_SIZE 80
#define NUM_DVDS 10
typedef struct dvd_t {
    char title [TEXT_SIZE];
    char director [TEXT_SIZE];
    int playTime;
} dvd_t;
void getOneDVD(dvd_t *dvd);
void printOneDVD(dvd_t dvd);
void getCollection(dvd_t dvd[NUM_DVDS], int amt);
void printCollection(dvd_t dvd[NUM_DVDS], int amt);
