/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)  
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    //remember n
    int n  = atoi(argv[1]);
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    //printf("%i \n%s\n%s",n,infile,outfile);    
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // orignal image properties
    int orignal_width = bi.biWidth;
    int orignal_height =bi.biHeight;
    
    //updating bitmap image headers
    bi.biWidth*=n;
    bi.biHeight*=n;
    
    // required padding in the resized image file 
    int new_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("%i",new_padding);
    
    // padding in the orignal image file
    int orignal_padding = (4 - (orignal_width * sizeof(RGBTRIPLE)) % 4) % 4;
    
    int new_image_size = (bi.biWidth*sizeof(RGBTRIPLE) + new_padding)*abs(bi.biHeight);
    bi.biSizeImage = new_image_size;
    
    // file size is image size plus header size(54 bytes)
    bf.bfSize = new_image_size+54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(orignal_height); i < biHeight; i++)
    {
        for(int vcount = 0;vcount <n;vcount++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < orignal_width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                for(int hcount =0;hcount<n;hcount++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add padding to the resized file
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
            
            // get to the beginning of the line
            fseek(inptr,-(orignal_width*sizeof(RGBTRIPLE)),SEEK_CUR);
        }  
        
        fseek(inptr,((orignal_width*sizeof(RGBTRIPLE))+orignal_padding),SEEK_CUR);
        
        // // skip over padding, if any
        // fseek(inptr, orignal_padding, SEEK_CUR);
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
