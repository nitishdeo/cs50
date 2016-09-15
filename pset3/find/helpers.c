/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include<stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
   //binary search implementation
   int left=0,right=n-1,middle;
   
   while(left <= right)
   {
       middle = (left+right)/2;
       if(values[middle] == value)
       {
           return true;
       }
       else if(values[middle] > value)
       {
           right = middle-1;
       }
       else
       {
           left = middle+1;
       }
   }
   return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    printf("%i",n);
    if(n>0)
    {
        int i,j,temp;
        for(i=0;i<n-1;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(values[i] > values[j])
                {
                    //swap
                    temp=values[i];
                    values[i]=values[j];
                    values[j]= temp;
                }
            }
        }
    }
    return;
}