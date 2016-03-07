#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = 0;
    do
    {
        printf("Give me a pyramid height (max 23): ");
        height = GetInt();
    // Get a height number from user between 1 and 23
    }
    while (height > 23 || height < 0);
    // Prompt again if number is invalid
    for (int n = 0; n < height; n++)
    {
        for (int space = (height - 1); space > n; space--)
        {
            printf(" ");
        // Prints spaces starting at 1 less than height
        // Reduces 1 space for each row
        }
        for (int hash = 0; hash < (n + 2); hash++)
        {
            printf("#");
        // Prints hashmarks starting at 2
        // Adds 1 hashmark for each row    
        }
        printf("\n");
    }
}
