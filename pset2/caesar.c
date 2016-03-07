#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error\n");
        return 1;
    }
    // If there are not 2 arguments, show error and exit program
    int key = atoi(argv[1]);
    if (key < 0)
    {
        printf("Error\n");
        return 1;
    }
    // If key is less than zero, show error and exit program
    else
    {
        string ptext = GetString();
        for (int i = 0, j = strlen(ptext); i < j; i++)
        // Get plaintext from user and loop through plaintext 
        {
            if (isalpha(ptext[i]))
            {
            // Only apply cipher to alpha characters in plaintext
                if (islower(ptext[i])) 
                {
                    printf("%c", ((ptext[i] - 'a') + key) % 26 + 'a');
                }
                // Shift lowercase letters per key
                if (isupper(ptext[i]))
                {
                    printf("%c", ((ptext[i] - 'A') + key) % 26 + 'A');
                }
                // Shift uppercase letters per key
            }
            else
            {
                printf("%c", ptext[i]);
            }
            // If non-alpha character in plaintext, simply print character
        }
        printf("\n");
        return 0;
    }
}

