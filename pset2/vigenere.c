#include<stdio.h>
#include<string.h>
#include<cs50.h>

//function prototypes
string EncryptVigenere(string text, string key);

int main(int argc, string argv[])
{
    if(argc == 2)
    {
        string keyword = argv[1];
        int index=0;
        while(keyword[index] !='\0')
        {
            if((keyword[index] < 'A' || keyword[index] > 'Z' ) && (keyword[index] < 'a' || keyword[index] > 'z' ))
            {
                printf("The keyword should only cointain alphabets. Retry entering a valid keyword\n");
                return 1;
            }
            index++;
        }
        string text = GetString();
        string encrypted_text = EncryptVigenere(text,keyword);
        printf("%s\n",encrypted_text);
    }
    else if(argc == 1)
    {
        printf("Enter the keyword as command line arguement\n");
        return 1;
    }
    else
    {
        printf("Too many command line arguements! We need only one(the keyword)\n");
        return 1;
    }
    
}

/* Function EncryptVigenere
* It encrypts the given text using Vigenere encryption technique
* args :
    text : the orignal text which is to be encrypted
    keyword : the keyword used for encryption
* return value :
    encrypted_text : encryption value of the orignal text
*/
string EncryptVigenere(string text, string keyword)
{
    string encrypted_text=text;
    
    int keylen = strlen(keyword);
    int integerkey[keylen];
    int index=0,key_index=0;
    while(keyword[index] != '\0')
    {
        if(keyword[index]>='A' && keyword[index] <= 'Z')
        {
            integerkey[index] = keyword[index]-'A';
        }
        else // keyword only has alphabets, so i can direct jump to the else case 
        {
            integerkey[index] = keyword[index]-'a';
        }
        index++;
    }
    
    index=0;
    while(text[index] != '\0')
    {
        int offset = integerkey[key_index%keylen]; 
        
        if(text[index]>='A' && text[index] <= 'Z')
        {
            int position = text[index] - 'A';
            encrypted_text[index] = (char) ('A' + (position+offset)%26);
            key_index++;
        }
        else if(text[index]>='a' && text[index] <= 'z')
        {
            int position = text[index] - 'a';
            encrypted_text[index] = (char) ('a' + (position+offset)%26);
            key_index++;
        }
        else
        {
            encrypted_text[index] = text[index];
        }
        index++;
        
    }
    return encrypted_text;
}
//Negh zf av huf pcfx bt gzrwep oz