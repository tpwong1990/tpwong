// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1170;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //check the first letter
    int first_l = tolower(word[0]) - 96;
    //check the length of the word
    int word_l = sizeof(word);
    // returnt the number
    return (first_l - 1)*45 + word_l - 1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open file
    FILE *dic = fopen(dictionary, "r");
    //check if the file is valid
    if (dictionary == NULL)
    {
        return false;
    }
    char d_word[LENGTH + 1];
    char c;
    int word_l = 0;
    while (fread(&c, sizeof(char), 1, dic))
    {
        world_l++;
        //check the end of the word
        if (c == '/n')
        {
            //load the word to dic
            world_l = 0;

        }
        else
        {
            d_word[world_l - 1] = c;
        }

    }

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
