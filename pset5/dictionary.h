/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// 26 alphabets and apostrophe(') symbol  
#define ALPHABETS 27
#define APOSTROPHE_INDEX 26

// node structure for trie
typedef struct node
{
    bool is_word;
    struct node *children[ALPHABETS];
}NODE;


// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// prototypes

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Helper function 
 * Creates new Trie node 
 */
NODE * createNewNode(void);

/** Helper Function
 * Returns the index of character
 */
int getCharIndex(char c);

/**
 * This function frees up the heap space occupied by the dictionary trie
 */ 
bool unloadDict( NODE *traverse);

#endif // DICTIONARY_H
