#pragma once


//Defenitions
#define NUM_LETTERS ((int)26)
#define boolean

// Signatures of Node & Trie Structures
struct _Node;
struct _Trie;

//TypeDefs of Node & Trie
typedef struct _Node Node;
typedef struct _Trie Trie;

// Signatures of Node Functions
Node* new_node(char letter);
void assign_word_to_node(Node **node, const char *word);
void print_node(Node **node);
void print_node_backwards(Node **node);
void free_node(Node *node);


// Signatures of Trie Functions
Trie* new_trie();
void add_word_to_trie(Trie **trie, char *word);
void print_trie(Trie **trie) ;
void print_trie_backwards(Trie **trie) ;
void free_trie(Trie *trie);

//Signature of Util Functions
int getWord(char **w);