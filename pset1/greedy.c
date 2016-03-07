#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change = 0;
    do
    {
        printf("O Hai! How much change is owed?\n");
        change = GetFloat();
    }
    while (change < 0);
    // Ask user for a positive amount of change given
    int cents = round(change * 100);
    // Round change and convert from dollars to cents
    int coins = 0;
    while (cents >= 25)
    {
        coins++, cents -= 25;
    }
    // If there are at least 25 cents, add quarters to coins
    // Loop and reduce by 25 cents for each quarter
    while (cents >= 10)
    {
        coins++, cents -= 10;
    }
    // Perform same loop for dimes
    while (cents >= 5)
    {
        coins++, cents -= 5;
    }
    // Perform same loop for nickels
    while (cents >= 1)
    {
        coins++, cents -= 1;
    }
    // Perform same loop for pennies
    printf("%i\n", coins);
}
