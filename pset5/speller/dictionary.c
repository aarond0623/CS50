// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 30420;

// Hash table
// The hash function below uses the first two letters of a word as well as the
// length of the word to create buckets. With 26 letters and a max word
// size of 45 letters, this will lead to a maximum of 30,420 buckets.
node *table[N];

// Size of the dictionary
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);

    // Load the first word at the hash index.
    node *current_word = table[index];

    while (current_word != NULL)
    {
        if (strcasecmp(word, current_word->word) == 0)
        {
            return true;
        }
        current_word = current_word->next;
    }

    return false;
}

// Hashes word to a number
// See comment above for the hash function.
unsigned int hash(const char *word)
{
    unsigned int word_len = strlen(word);
    unsigned int letter_1 = tolower(word[0]) - 'a';
    unsigned int letter_2;
    // Ensure the word is two letters long. If not, we'll just treat the second
    // letter as 'a'.
    if (word_len > 2)
    {
        letter_2 = tolower(word[0]) - 'a';
    }
    else
    {
        letter_2 = 0;
    }

    // Add them up with the first letter being the 1170th place and the second
    // letter being the 45th place.

    unsigned int index = word_len + (45 * letter_2) + (45 * 26 * letter_1) - 1;
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char dict_word[LENGTH + 1];

    // Read each entry in the dictionary and place it in the hash table.
    while (fscanf(file, "%s", dict_word) != EOF)
    {
        node *hash_word = malloc(sizeof(node));
        if (hash_word == NULL)
        {
            return false;
        }
        strcpy(hash_word->word, dict_word);
        hash_word->next = NULL;
        int index = hash(dict_word);

        // This index has no entries.
        if (table[index] == NULL)
        {
            table[index] = hash_word;
        }
        // Otherwise insert at the front of the linked list.
        else
        {
            hash_word->next = table[index];
            table[index] = hash_word;
        }
        // Add to the dictionary's size
        dict_size++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Will be zero if nothing loaded since it is initialized as zero.
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}
