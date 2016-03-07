#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string name = GetString();
    // Prompts user to enter name

    if (name != NULL)
    // Make sure string is not null
    {
        for (int i = 0; i < 1; i++)
        {
            printf("%c", toupper(name[0]));
        }
        // Print 1st initial
        // Capitalize if needed
        for (int n = 0; n < strlen(name); n++)
        {
            if (name[n] == ' ')
            {
                printf("%c", toupper(name[n + 1]));
            }
            // Print each initial that occurs immediately after a space
            // Capitalize if needed
        }
    }
    printf("\n");
}
