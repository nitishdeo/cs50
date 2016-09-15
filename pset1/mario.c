#include<stdio.h>
#include<cs50.h>
int main()
{
    int height,i,j,k;
    do{
        printf("height: ");
        height=GetInt();
    }while(height<0 || height >23);
    
    //building a half pyramid
    for(i=0;i<height;i++)
    {
        //loop for spaces
        for(j=0;j<height-i-1;j++)
        {
            printf(" ");
        }
        //loop to print #
        for(k=0;k<i+2;k++)
        {
            printf("#");
        }
        printf("\n");
        
    }
}