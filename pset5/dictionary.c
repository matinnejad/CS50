/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// initialize word counter
int counter = 0;

// hash function - credit: delipity - reddit
int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    
    for (int i = 0, n = strlen(needs_hashing); i < n; i++)
    {
        hash = (hash << 2) ^ needs_hashing[i];
    }
    return hash % HASHTABLE_SIZE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    char checkword[LENGTH + 1];
    int length = strlen(word);
    
    for (int i = 0; i < length; i++)
    {
        checkword[i] = tolower(word[i]);
        checkword[length] = '\0';
    }
    
    int bucket = hash_it(checkword);
    
    node* checker = malloc(sizeof(node));
    
    checker = hash[bucket];
    
    while (checker != NULL)
    {
        if (strcmp(checkword, checker->word) == 0)
        {
            return true;
        }
        checker = checker->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* dictopen = fopen(dictionary, "r");
    char word[LENGTH+1];
    
    if (dictopen == NULL)
    {
        return false;
    }

    while (fscanf(dictopen, "%s", word) !=EOF)
    {
            node* new_node = malloc(sizeof(node));

            strcpy(new_node->word, word);
            
            // count words for dictionary size
            counter++;
            
            int i = hash_it(word);
            
            if (hash[i] == NULL)
            {
               hash[i] = new_node;
               new_node->next = NULL;
            }
            else
            {
                new_node->next = hash[i];
                hash[i] = new_node;
            }
    }
    
    fclose(dictopen);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //Return dictionary size from load function
    return counter;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // Loop through hashtable freeing from memory
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node* cursor = hash[i];
    
        while(cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
            return true;
        }
    }
    return false;
}
