#include <stdio.h>
#include <stdlib.h>
#include "frequency.h"

// Util Functions

//gets a word from stdin and puts it in w (which is a allocated memory in the heap). returns the number of chars read. returns -1 if reached EOF.
int getWord(char **w) {
    char *word = (char*)malloc(sizeof(char));
    if (word == NULL) return-1; //we shouldn't arrive here because there will be enough memory for normal strings, but if we do we just return -1 to emulate EOF. 
    char get_char = 0;
    int counter = 0;
    do {
        get_char = getchar();
        if (get_char >= 'A' && get_char <= 'Z')
            get_char += 32;
        if (get_char >= 'a' && get_char <= 'z') {
            word = (char *)realloc(word, (++counter+1) * sizeof(char));
            if (word == NULL) return-1; //we shouldn't arrive here because there will be enough memory for normal strings, but if we do we just return -1 to emulate EOF. 
            word[counter-1] = get_char;
        }
    //This loop will break when reached EOF, space, tab, or line break
    } while (get_char != EOF && get_char != '\n' &&  get_char != '\t' && get_char != ' ');
    if (get_char == EOF) return -1; //return -1 because reached EOF.
    if (counter == 0) return 0;
    word[counter] = '\0';
    *w=word;
    return counter;
}

// Node Structure implementation
struct _Node {
    char _letter;
    char *_word;
    long unsigned int _count;
    struct _Node* _children[NUM_LETTERS];
};

// Node Functions

/*
Allocates memory for a new Node, initialize default values
Then returns the allocated memory address.
*/
Node* new_node(char letter) {
    Node *node_p = (Node*)malloc(sizeof(Node));
    node_p -> _letter = letter;
    node_p -> _word = NULL;
    node_p -> _count = 0;
    for (int i=0; i<NUM_LETTERS; i++) {
        node_p -> _children[i] = NULL;
    }
    return node_p;
}

void assign_word_to_node(Node **node, char *word) {
    (*node) ->_word = word;
}

void print_node(Node **node) {
    if ((*node) -> _count > 0) {
        printf("%s", (*node) -> _word);
        printf(" %ld\n", (*node) -> _count);
    }
    for (int i=0; i<NUM_LETTERS; i++) {
        if ((*node) ->_children[i] != NULL) {
            print_node(&((*node) ->_children[i]));
        }
    }
}

void print_node_backwards(Node **node) {
    if ((*node) -> _count > 0) {
        printf("%s", (*node) -> _word);
        printf(" %ld\n", (*node) -> _count);
    }
    for (int i=NUM_LETTERS-1; i>=0; i--) {
        if ((*node) ->_children[i] != NULL) {
            print_node_backwards(&((*node) ->_children[i]));
        }
    }
}


//frees a Node from heap memory
void free_node(Node *node) {
    if (node == NULL) return;
    for (int i=0; i<NUM_LETTERS; i++){
        if (node -> _children[i] != NULL)
            free_node(node -> _children[i]);
    }
    if (node -> _word != NULL)
        free(node -> _word);
    free(node);
}


// Trie Structure implementation
struct _Trie {
    int _size;
    Node *_head;
};

// Trie Functions

/*
Allocates memory for a new Trie, initialize default values
and assigns a default Node as head
Then returns the allocated memory address
*/
Trie* new_trie() {
    Trie *trie_p = (Trie*)malloc(sizeof(Trie));
    trie_p -> _size = 0;
    trie_p -> _head = new_node(0);
    return trie_p;
}

void add_word_to_trie(Trie **trie, char *word) {
    Node *current_node = (*trie) -> _head;
    char *wordPtr = word;
    while(*wordPtr != '\0') {
        int i = *wordPtr-'a'; //convert from char to index

        //if the current node has a child with that letter
        if (current_node -> _children[i] != NULL) {
            //traverse to the char in the trie
            current_node = current_node -> _children[i];
        }
        
        /*
        else - the current node does not have a child
        with that letter. so we want to make a new node
        with that letter and traverse to it.
        */
        else {
            current_node -> _children[i] = new_node(*wordPtr);
            current_node = current_node -> _children[i];
        }
        wordPtr++;
    }

    /*
    if the current word is the head of the trie that means
    the word was empty so we don't want to increase the counter
    */
    if (current_node == (*trie) -> _head) return;
    
    current_node -> _count++;
    assign_word_to_node(&current_node, word);
}

void print_trie(Trie **trie) {
    Node *current_node = (*trie) -> _head;
    print_node(&current_node);
}

void print_trie_backwards(Trie **trie) {
    Node *current_node = (*trie) -> _head;
    print_node_backwards(&current_node);
}

//frees a Trie from heap memory
void free_trie(Trie *trie) {
    if (trie == NULL) return;
    free_node(trie -> _head);
    free(trie);
}


