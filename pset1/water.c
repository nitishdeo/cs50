#include<stdio.h>
#include <cs50.h>
int main()
{
    int minutes=0, wastage;
    do{
        printf("minutes: ");
        minutes = GetInt();
    }while(minutes<=0);
    wastage = minutes*12;
    printf("bottles: %d\n",wastage);
}