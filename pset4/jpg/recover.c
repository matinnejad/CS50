/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // Open memory card file
    FILE* card = fopen("card.raw", "r");
    
    unsigned char buffer[512];
    int counter = 0;
    char title[8];
    
    // read 512 bytes at a time into buffer
    fread(&buffer, 512, 1, card);
    
    // while there are blocks to read
    while (fread(&buffer, 512, 1, card) == 1)
    {
        // if start of jpeg found, create new jpeg, update counter
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && 
        (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            sprintf(title, "%03d.jpg", counter); 
            FILE* img = fopen(title, "a");
            counter++;
            // write jpeg while not start of new jpeg and not end of file
            do
            {
                fwrite(&buffer, 512, 1, img);
                fread(&buffer, 512, 1, card);
            }
            while (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] == 0xe0 || buffer[3] == 0xe1)) && feof(card) == 0);
            
            // close image and move back one block
            fclose(img);
            fseek(card, -512, SEEK_CUR);
        }
    }
    // close input card file and end program
    fclose(card);
    return 0;
}  

