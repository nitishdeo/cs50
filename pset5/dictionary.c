/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Root node to the trie containing dictionary
NODE *root= NULL;

// Total number of words in the dictionary
int total_words=0;

/**
 * Creates a new trie node and returns a pointer to that node
 */
NODE* createNewNode(void)
{
    NODE *new_node = (NODE*) calloc(1,sizeof(NODE));
    if(new_node != NULL)
    {
        return new_node;
    }
    return NULL;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // search for the word in dictionary
    int index=0;
    int char_index;
    
    NODE * traverse = root;
    while(word[index] != '\0')
    {
        char_index = getCharIndex(word[index]);
        // if corresponding element in children array points to NULL, word is mispelled
        if(traverse->children[char_index] == NULL)
        {
            return false;
        }
        traverse = traverse->children[char_index];
        index++;
    }
    return traverse->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the dictionary file
    FILE *fp = fopen(dictionary, "r");
    
    if(fp == NULL)
    {
        printf("Could not open the file\n");
        return false;
    }
   
    // create root trie node
    root = createNewNode();
    NODE *traverse = root;
    int char_index;
    
    // loading each word from the dictionary file
    char ch;
    while((ch = fgetc(fp)) != EOF)
    {
        if(ch =='\n')
        {
            // end of the word, so make is_word true for current node
            traverse->is_word = true;
            total_words++;
            
            // reset traverse to root node
            traverse = root;
        }
        else
        {
            char_index = getCharIndex(ch);
            // if children[letter] points to NULL, make a new node
            if(traverse->children[char_index] == NULL)
            {
                // create a new node
                traverse->children[char_index] = createNewNode();
            }
            
            // goto the next node
            traverse = traverse->children[char_index];
        }
    }
   
    //close dictionary
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return total_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // making sure that the dictionary is loaded
    if(root != NULL)
    {
        // function to free dict memory
        bool done = unloadDict(root);
        root = NULL;
        return done;
    }
    else
    {
        return false;
    }
}

/**
 * This function frees up the heap space occupied by the dictionary trie
 */ 
bool unloadDict( NODE *traverse)
{
    // if the node is non leaf traverse to the bottom
    if(traverse != NULL)
    {
        if(traverse->is_word == false)
        {
            for(int i=0;i<ALPHABETS;i++)
            {
                unloadDict(traverse->children[i]);
            }
        }
        // if the node is leaf, free the memory
        free(traverse);
        // point traverse to NULL
        traverse = NULL;
    }
    return true;
}

/**
 * Returns index of the character
 */
int getCharIndex(char c)
{
    if( c == '\'')
    {
        return APOSTROPHE_INDEX;
    }
    if( c >= 'A' && c <='Z')
    {
        return (int)(c - 'A');
    }
    else
    {
        return (int)(c - 'a');
    }
}