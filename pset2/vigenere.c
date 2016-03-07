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
    string key = (argv[1]);
    for (int acheck = 0, length = strlen(key); acheck < length; acheck++)
    {       
        if (!isalpha(key[acheck]))
        {
            printf("Error\n");
            return 1;
        }
    }
    // Loop through key to check for alpha characters
    // If any non-alpha characters in key, show error and exit program
    string ptext = GetString();
    for (int i = 0, n = strlen(ptext), j = 0; i < n; i++)
    {
    // Get plaintext from user and loop through plaintext   
        if (isalpha(ptext[i]))
        {
        // Only apply cipher to alpha characters in plaintext
            if (islower(key[j]))
            {
                if (islower(ptext[i])) 
                {
                    printf("%c", ((ptext[i] - 'a') 
                        + key[j] % 97) % 26 + 'a');
                }
                // Shift lowercase letters if lowercase character in key
                if (isupper(ptext[i]))
                {
                    printf("%c", ((ptext[i] - 'A') 
                        + key[j] % 97) % 26 + 'A');             
                }
                // Shift uppercase letters if lowercase character in key
            }
            if (isupper(key[j]))
            {
                if (islower(ptext[i])) 
                {    
                    printf("%c", ((ptext[i] - 'a') 
                        + key[j] % 65) % 26 + 'a');
                }
                // Shift lowercase letters if uppercase character in key
                if (isupper(ptext[i]))
                {
                    printf("%c", ((ptext[i] - 'A') 
                        + key[j] % 65) % 26 + 'A');             
                }
                // Shift uppercase letters if uppercase character in key
            }
            j = ((j + 1) % strlen(key));
            // Loop through key and repeat for all plaintext 
        }
        else
        {
            printf("%c", ptext[i]);
        // If non-alpha character in plaintext, simply print character
        }
    }   
    printf("\n");
    return 0;
}
