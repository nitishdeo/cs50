#include<stdio.h>
#include<stdlib.h>
#include<cs50.h>

// function prototypes
string HailCaesar(string text, int key);

int main(int argc, string argv[])
{
    if(argc == 2)
    {
        int key = atoi(argv[1]);
        key = key%26; //27 and 1 are practically same
        string text = GetString();
        string encrypted_text = HailCaesar(text,key);
        printf("%s\n",encrypted_text);
    }
    else if(argc == 1)
    {
        printf("Enter the secret key as command line arguement\n");
        return 1;        
    }
    else
    {
        printf("Too many command line arguements! We need just one(the secret key)\n");
    }

}

/* Function HailCaesar 
* It encrypts the given text using caesar encryption technique and returns the encrypted text
*arguements given:
    text : the orignal text which is to be encrypted
    key  : the secret key used for encryption
* return value:
    encrypted_text : encryption value of the orignal text provided
*/
string HailCaesar(string text, int key)
{
    string encrypted_text=text;
    int index=0;
    while(text[index] != '\0')
    {
        if(text[index]>='A' && text[index] <= 'Z')
        {
            int position = text[index] - 'A';
            encrypted_text[index] = (char) ('A' + (position+key)%26);
        }
        else if(text[index]>='a' && text[index] <= 'z')
        {
            int position = text[index] - 'a';
            encrypted_text[index] = (char) ('a' + (position+key)%26);
        }
        else
        {
            encrypted_text[index] = text[index];
        }
        index++;
    }
    return encrypted_text;
}