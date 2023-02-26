#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//the VALTYPE should be copyable/calculatable (int, float, ptr), recommend void ptr
#define HASHMAP_VAL_TYPE void *
//Please wishly choose a prime number
#define HASHMAP_TABLE_SIZE 1723

typedef struct HashMapNode {
    HASHMAP_VAL_TYPE val;
    char* key;
    struct HashMapNode *next;
} HashMapNode;

void _freeHashMapNode(HashMapNode * node){
    assert(node != NULL);
    free(node->key);
    free(node);
}

typedef struct HashMap{
    HashMapNode ** _table;
    size_t size;
}HashMap;

HashMap* createHashMap(){
    HashMap* m = malloc(sizeof(HashMap));
    memset(m, 0, sizeof(HashMap));
    m->_table = malloc(sizeof(HashMapNode *) *HASHMAP_TABLE_SIZE);
    memset(m->_table, 0, sizeof(HashMapNode *) *HASHMAP_TABLE_SIZE);
    m->size = 0;
    return m;
}

void freeHashMap(HashMap* m){
    assert(m != NULL);
    for(int i = 0 ; i < HASHMAP_TABLE_SIZE; i++){
        HashMapNode * node = m->_table[i];
        while(node != NULL){
            HashMapNode * next = node->next;
            _freeHashMapNode(node);
            node = next;
        }
    }
    free(m->_table);
    free(m);
}


unsigned int _hash_func(const char * key, size_t table_size){
    assert(key != NULL);
    unsigned int hash_val = 0;
    unsigned int seed = 131;
    while(*key) hash_val = hash_val * seed + (*key++);
    return hash_val % table_size;
}

bool inHashMap(HashMap * m, const char * key){
    assert(m != NULL);
    unsigned int tableIdx = _hash_func(key, HASHMAP_TABLE_SIZE);
    HashMapNode * node = m->_table[tableIdx];
    while(node != NULL)
    {
        if (strcmp(key, node->key) == 0) return true;
        node = node->next;
    } 
    return false;
}

HASHMAP_VAL_TYPE getHashMap(HashMap * m, const char * key){
    assert(m != NULL);
    assert(m->size > 0 && "Getting element from an empty map");
    unsigned int tableIdx = _hash_func(key, HASHMAP_TABLE_SIZE);
    HashMapNode * node = m->_table[tableIdx];
    while(node != NULL)
    {
        if (strcmp(key, node->key) == 0) return node->val;
        node = node->next;
    } 
    return (HASHMAP_VAL_TYPE)0;
}

void insertHashMap(HashMap * m, const char * key, HASHMAP_VAL_TYPE val){
    assert(m != NULL);
    unsigned int tableIdx = _hash_func(key, HASHMAP_TABLE_SIZE);
    HashMapNode ** loc = &(m->_table[tableIdx]);
    HashMapNode * next = m->_table[tableIdx];
    *loc = malloc(sizeof(HashMapNode));
    memset(*loc, 0, sizeof(HashMapNode));
    size_t keylen = strlen(key)+1;
    (*loc)->key = malloc(keylen);
    memset((*loc)->key, 0, keylen);
    strcpy((*loc)->key, key);
    (*loc)->val = val;
    (*loc)->next = next;
    m->size += 1;
    return;
}


void removeHashMap(HashMap * m, const char * key){
    assert(m != NULL);
    assert(m->size > 0 && "Removing element from an empty map");
    unsigned int tableIdx = _hash_func(key, HASHMAP_TABLE_SIZE);
    HashMapNode ** loc = &(m->_table[tableIdx]);
    while((*loc) != NULL){
        HashMapNode * cur = (*loc);
        if(strcmp(key, cur->key) == 0){
            *loc = (cur->next); 
            _freeHashMapNode(cur);
            m->size -= 1;
            return;
        }
        loc = &(cur->next);
    }
}

HashMapNode * nextHashMap(HashMap * m){
    assert(m != NULL);
    assert(m->size > 0 && "Getting one next element from an empty map");
    for(int i = 0 ; i < HASHMAP_TABLE_SIZE; i++){
        HashMapNode * node = m->_table[i];
        if(node != NULL)
        {
            return node;
        } 
    }
    return NULL;
}

#endif //HASH_MAP_H