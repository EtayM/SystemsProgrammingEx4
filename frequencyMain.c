#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency.h"


int main(int argc, char *argv[]) {
    Trie *trie = new_trie();
    char *word = NULL;
    int num_of_letters = 0;
    while ((num_of_letters = getWord(&word)) != -1) {
        if (num_of_letters > 0) {
            add_word_to_trie(&trie, word);
        }
        free(word);
    }
    if (argc <2) {
        print_trie(&trie);
        free_trie(trie);
        exit(0);
    }
    else {
        for (int i=0; i< argc; i++) {
            if(strcmp(argv[i], "r") == 0) {
                print_trie_backwards(&trie);
                free_trie(trie);
                exit(0);
            }
        }
    }
}