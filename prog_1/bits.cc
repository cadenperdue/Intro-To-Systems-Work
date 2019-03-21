#include<stdio.h>
void printIP (int n)
{   
    int firstDig = n & 0x000000FF;
    int secondDig = (n & 0x0000FF00) >> 8;
    int thirdDig = (n & 0x00FF0000) >> 16;
    int fourthDig = (n & 0xFF000000) >> 24;
    printf("%d.%d.%d.%d\n", fourthDig, thirdDig, secondDig, firstDig);
}
int reverseEndian (int n){
    int firstDig = n & 0x000000FF ;
    firstDig = firstDig << 24;
    int secondDig = n & 0x0000FF00;
    secondDig = secondDig << 8;
    int thirdDig = n & 0x00FF0000;
    thirdDig =  thirdDig >> 8;
    int fourthDig = n & 0xFF000000;
    fourthDig = fourthDig >> 24;
    int newEndian = fourthDig + thirdDig + secondDig + firstDig;
    return newEndian;
}
int countGroups (int n){
    unsigned int x = n;
    int count = 0;
    while (x > 0){
        if ((x & 1) == 1){
            count = count + 1;
            x = x >> 1;
            while ((x & 1) == 1)
            {
                x = x >> 1;
            }
        }
        else 
        {
            x = x >> 1;
        }
    }
    return count;
}   
