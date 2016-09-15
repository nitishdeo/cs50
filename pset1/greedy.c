#include<stdio.h>
#include<math.h>
#include<cs50.h>
int main()
{
    float owed;
    do
    {
        printf("O hai! How much change is owed?\n");
        owed=GetFloat();
    }while(owed<=0);
    //cents:25,10,5,1
    //dollars to cents
    owed=owed*100;
    int rounded_amount = (int) round(owed);
    int coins=0;
    while(rounded_amount !=0)
    {
        if(rounded_amount>=25)
        {
            rounded_amount-=25;
        }
        else if(rounded_amount>=10)
        {
            rounded_amount-=10;
        }
        else if(rounded_amount>=5)
        {
            rounded_amount-=5;
        }
        else
        {
            rounded_amount-=1;
        }
        coins++;
    }
    printf("%d\n",coins);
    
}