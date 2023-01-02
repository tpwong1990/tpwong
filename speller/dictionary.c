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
    char *d_word;
    int d_word_count;
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
        free(n);
    }
    fclose(dic);
    return true;
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
