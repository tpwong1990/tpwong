// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

int d_word_count = 0;

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
    //get hash index from the word
    unsigned int h_i = hash(word);

    //check the word is in the dic or not
    node *n = table[h_i];
    while (n->next == NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            free(n);
            return true;
        }
        else
        {
            //point to next word;
            n = n->next;
        }
    }
    free(n);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //check the first letter
    int first_l = tolower(word[0]) - 96;
    //check the length of the word
    int word_l = 0;
    while (word[word_l] != '\0')
    {
        word_l++;
    }
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
    char *d_word = NULL;
    while (fscanf(dic, "%s", d_word) != EOF)
    {
        //allocate memory
        node *n = malloc(sizeof(node));
        n->next = NULL;

        //copy word from dic to table
        strcpy(n->word, d_word);

        //hash the word
        int hash_table_i = hash(d_word);

        //link the node to hash table
        n->next = table[hash_table_i];
        table[hash_table_i] = n;
        d_word_count++;
        free(n);
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return d_word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // loop the whole tabel and check it is nothing or not

    for (int i = 0; i < N; i++)
    {
        if !(table[i]->word = '\0')
        {
            node *n = malloc(sizeof(node));
            n = table[i];
            while (!(n->next == NUll))
            {
                free(n);
                n->next = n;
            }
            free(n);
        }
    }
    return false;
}
