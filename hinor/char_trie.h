#ifndef __CHAR_TRIE__
#define __CHAR_TRIE__
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

typedef struct AutoCompResponse{
    char *resp_string;
    int num_strings;
    int max_size;
    int curr_size;
} AutoCompResponse;

typedef struct QueryOptions{
    int max_strings;
} QueryOptions;

typedef struct TrieNode{
    char *value;
    struct TrieNode *left;
    struct TrieNode *right;
    struct TrieNode *center;
    char ch;
    int word_end:1;
} TrieNode;

typedef struct TrieOptions{
    int ph;
} TrieOptions;

typedef struct Trie{
    TrieNode *root;
    TrieOptions *options;
//    AutoCompResponse *pre_allocd_response;
} Trie;


void free_response(AutoCompResponse *resp);

void add(Trie *tree,char *s);
void add_value(Trie *tree,char *s,char *value);

int contains(Trie *tree,char *s);
char *get(Trie *tree,char *s);

AutoCompResponse *autocomp(Trie *tree,char *s);
AutoCompResponse *autocomp_limit(Trie *tree,char *s, int limit);

Trie *init_trie(void);
TrieNode *init_node(void);

void free_node(TrieNode *node);
void free_trie(Trie *trie);

int count_nodes(TrieNode *node);
int count_empty_pointers(TrieNode *node);
int count_memory(TrieNode *node);

#endif
