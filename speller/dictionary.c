// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char* get_word_from_hash(node *h_table[N], int hash_i);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // make the word to lowercase
    char *word_tmp = tolower(word);

    //get hash index from the word
    unsigned int h_i = hash(const char *word);

    //check the word is in the dic or not
    while //get_word_from_hash != '\0')
    {
        //char* word_d = from dic
        if (strcmp(word_temp, word_d) == 0)
        {
            return true;
            break;
        }
        else
        {
            //point to next
        }
    }

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
    // TODO
    return false;
}

char* get_word_from_hash(node *h_table[N], int hash_i)
{
    return h_table[hash_i]->word;
}