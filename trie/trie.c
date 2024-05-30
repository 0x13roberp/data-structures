#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define ALPHABET_SIZE 26

struct node{
  struct node *children[ALPHABET_SIZE];
  unsigned int is_end_of_word;
};

struct trie{
  struct node *root;
};

struct node *node_new(){
  struct node *n = malloc(sizeof(struct node));
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    n->children[i] = NULL;
  }
  n->is_end_of_word = 0;
  return n;
}

struct trie *trie_new(){
  struct trie *t = malloc(sizeof(struct trie));
  t->root = node_new();
  return t;
};

unsigned int char_to_index(char c){
  return (unsigned int) c - (unsigned int) 'a';
}

char index_to_char(unsigned int i){
  return (char) ((unsigned int) 'a' + i);
}

void trie_insert(struct trie *t, char *word){
  struct node *n = t->root;
  char *c = word;

  while(*c != '\0'){
    unsigned int index = char_to_index(*c);
    if(n->children[index] == NULL){
      n->children[index] = node_new();
    }
    n = n->children[index];
  }
  n->is_end_of_word = 1;
}

void *trie_find_words(struct node *n, char *prefix){
  if(n->is_end_of_word){
    printf("%s\n", prefix);
  }
  for(int i = 0; i < ALPHABET_SIZE; i++){
    if(n->children[i] != NULL){
      char *new_prefix = malloc(strlen(prefix) + 2);
      strcpy(new_prefix, prefix);
      new_prefix[strlen(prefix)] = index_to_char(i);
      new_prefix[strlen(prefix) + 1] = '\0';
      trie_find_words(n->children[i], new_prefix);
    }
  }
}

void trie_suggest(struct trie *t, char *prefix){
  struct node *n = t->root;

  for(char *c = prefix; *c != '\0'; c++){
    unsigned int index = char_to_index(*c);

    if(n->children[index] == NULL){
      return;
    }
    n = n->children[index];
  }
}

int main(){
  struct trie *t = trie_new();
  
  trie_insert(t, "hello");
  trie_insert(t, "world");
  trie_insert(t, "rober");
  trie_find_words(t->root, "w");

  return 0;
}
