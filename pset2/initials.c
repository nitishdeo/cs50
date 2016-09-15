#include<stdio.h>
#include<cs50.h>
#include<string.h>

//function prototypes
void printInitials(string name);

int main()
{
    string name = GetString();
    printInitials(name);
    printf("\n");
}

/* Function printinitials
* takes the name of a person as an input
* and prints the initials of thaat person
inputs:
  name : string var that stores the name of that person
returns nothing
*/
void printInitials(string name)
{
    int word_start=0,index=0;
    int word_end_flag=0;
    while(name[index] != '\0')
    {
        // for the start of a new word or end of the string
        if( (name[index+1] =='\0' ) || (name[index] == ' ' && word_end_flag ==0))
        {
            word_end_flag=1;
            char initial = name[word_start];
            if(initial >= 'a' && initial <= 'z')
            {
                initial = initial - 'a' +'A';
            }
            printf("%c",initial);
            word_start = index+1;
        }
        else
        {
            if(name[index] != ' ')
            {
                word_end_flag=0;
            }
            else
            {
                word_start++;
            }
        }
        index++;
    }
}