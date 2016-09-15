/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

// constants
#define BLOCK_SIZE 512

// custom data types
typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    
    // open the card file
    FILE *fp = fopen("card.raw","r");
    
    if(fp == NULL)
    {
        printf("Could not open the card file.\n");
        return 1;
    }
    
    // buffer
    BYTE buffer[BLOCK_SIZE];
    
    //flag variable
    int jpeg_start=0;
    
    // new image file
    FILE *new_file;
    
    //file counter
    int counter = 0;
    
    //file name
    char *file_name=  (char*) malloc(sizeof(char)*8);
    
    // read the file in blocks of 512 bytes
    while(fread(&buffer, BLOCK_SIZE, 1 , fp) == 1)
    {
        
        if(jpeg_start == 0)
        {
                if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef) )
                {
                    jpeg_start=1;
                    sprintf(file_name,"%03d",counter);
                    strcat(file_name, ".jpg");
                    
                    // make a new .jpg file  
                    new_file = fopen(file_name, "a");
                    counter++;
                    
                    // write this block in newly created file
                    fwrite(&buffer, BLOCK_SIZE, 1, new_file);
                }
   
        }
        else
        {
                if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef) )
                {
                    // close the previous file 
                    fclose(new_file);
                    
                    // make a new .jpg file name
                    sprintf(file_name,"%03d",counter);
                    strcat(file_name, ".jpg");
                    
                    // create a new .jpg file  
                    new_file = fopen(file_name, "a");
                    counter++;
                    
                    // write this block in newly created file
                    fwrite(&buffer, BLOCK_SIZE, 1, new_file);

                }
                else
                {
                    // write this block in the current file
                    fwrite(&buffer, BLOCK_SIZE, 1, new_file);   
                }
        }
    }
    
    // close image file
    fclose(new_file);
    
    // close memory card file
    fclose(fp);
    
    // free filename bytes
    free(file_name);
        return 0;
}
