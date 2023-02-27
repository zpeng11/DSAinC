#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define HASHMAP_VAL_TYPE void *
#define HASHMAP_KEY_LEN 64
#define HASHMAP_TABLE_SIZE 1723
typedef struct HashMapNode {
    char key[HASHMAP_KEY_LEN];
    HASHMAP_VAL_TYPE val;
    struct HashMapNode *next;
} HashMapNode;

HashMapNode * hashMap[HASHMAP_TABLE_SIZE] = {NULL};
size_t hashMapSize;

void initHashMap(){
    memset(hashMap, 0, sizeof(HashMapNode *) * HASHMAP_TABLE_SIZE);
    hashMapSize = 0;
}
void freeHashMap(){
    for(int i = 0; i < HASHMAP_TABLE_SIZE; i++){
        HashMapNode * node = hashMap[i];
        while (node != NULL){
            HashMapNode * next = node->next;
            free(node);
            node = next;
        }
    } 
}

HashMapNode ** findHashMap(const char * key){
    const char * hash_key = key;
    unsigned int hash_idx = 0, seed = 131;
    while(*hash_key) hash_idx = hash_idx * seed + (*hash_key++);
    hash_idx %= HASHMAP_TABLE_SIZE;
    HashMapNode ** loc = &hashMap[hash_idx];
    while((*loc) != NULL){
        if (strcmp(key, (*loc)->key) == 0) 
            return loc;
        loc = &((*loc)->next);
    } 
    return loc;
}

#define getHashMap(key) (*findHashMap(key))->val

void insertHashMap(HashMapNode ** loc, const char * key, HASHMAP_VAL_TYPE val){
    HashMapNode * next = *loc;
    *loc = malloc(sizeof(HashMapNode));
    strcpy((*loc)->key, key);
    (*loc)->val = val;
    (*loc)->next = next;
    hashMapSize += 1;
}

void removeHashMap(HashMapNode ** loc){
    HashMapNode * next = (*loc)->next;
    free(*loc);
    *loc = next;
    hashMapSize -= 1;
}

int main(){
    initHashMap();
    char str[64] = {0};
    for(int i = 0; i <1024; i++){
        sprintf(str, "%i", i);
        insertHashMap(findHashMap(str), str, NULL);
    }
    for(int i = 0; i <1024; i++){
        sprintf(str, "%i", i);
        removeHashMap(findHashMap(str));
    }
    freeHashMap();
}