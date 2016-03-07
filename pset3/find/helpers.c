/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n)
{
    // initialize minimum and maximum
    int min = 0;
    int max = n - 1;
    
    // while length of list > 0, search
    while (min <= max)
    {
        // set midpoint halfway through list
        int mid = (min + max) / 2;
        
        // if midpoint is the number searching for,
        // return true, end program
        if (values[mid] == value)
        {
            return true;
        }
        // if midpoint is less than number searching for,
        // set minimum as former midpoint + 1
        else if (values[mid] < value)
        {
            min = mid + 1;
        }
        // if midpoint is greater than number searching for,
        // set maximum as former midpoint - 1
        else if (values[mid] > value)
        {
            max = mid - 1;
        }
    }
    // if not found, return false
    return false;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // loop through array of values
    for (int j = 0; j < n - 1; j++)
    {
        int swaps = 0;
            
        // again, loop through array to swap values
        for (int k = 0; k < n - 1 - j; k++)
        {
            // compare values and swap if necessary
            if (values[k] > values[k + 1])
            {
                int temp = values[k + 1];
                values[k + 1] = values[k];
                values[k] = temp;
                swaps++;
            }
        }
        // if no more swaps, list is sorted, break out of loop
        if (!swaps)
        {
            break;
        }
    }
    return;
}
