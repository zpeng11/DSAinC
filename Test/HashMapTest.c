#include "acutest.h"
#include "../HashMap.h"

void init_final_test(){
    HashMap * map = createHashMap();
    TEST_ASSERT_(map != NULL, "Create Hash Map failed");
    TEST_ASSERT_(map->_table != NULL && map->size == 0, "Hash Map object failed to initialize");
    freeHashMap(map);
}

void insert_get_test(){
    HashMap * map = createHashMap();
    insertHashMap(map, "key1", "val1");
    TEST_ASSERT_(map->size == 1, "insert size error");
    const char * val = getHashMap(map, "key1");
    TEST_ASSERT_(val != NULL, "Can not get the value");
    TEST_CHECK_(strcmp(val, "val1") == 0, "Get wrong result back from map");
    freeHashMap(map);
}

void insert_del_test(){
    HashMap * map = createHashMap();
    char str[100] = {0};
    for(int i = 0 ; i < 1024; i++){
        sprintf(str, "key%i", i);
        insertHashMap(map, str, NULL);
        TEST_ASSERT_(map->size == i+1, "Wrong Hash Map size number");
    }
    for(int i = 1023; i>= 0; i--){
        sprintf(str, "key%i", i);
        removeHashMap(map, str);
        TEST_ASSERT_(map->size == i, "Wrong Hash Map size number");
    }
    freeHashMap(map);
}

void in_test(){
    HashMap * map = createHashMap();
    char str[100] = {0};
    for(int i = 0 ; i < 1024; i++){
        sprintf(str, "key%i", i);
        insertHashMap(map, str, NULL);
        TEST_ASSERT_(map->size == i+1, "Wrong Hash Map size number");
        TEST_ASSERT_(inHashMap(map, str), "key is not in Hash Map");
    }
    freeHashMap(map);
}

void next_test(){
    HashMap * map = createHashMap();
    char str[100] = {0};
    for(int i = 0 ; i < 1024; i++){
        sprintf(str, "key%i", i);
        insertHashMap(map, str, NULL);
    }
    while(map->size){
        HashMapNode * next = nextHashMap(map);
        TEST_ASSERT_(next!= NULL, "Next element should not return NULL");
        size_t size_before = map->size;
        removeHashMap(map, next->key);
        size_t size_after = map->size;
        TEST_ASSERT_(size_before - size_after == 1, "The size did not change accordingly");
    }
    freeHashMap(map);
}


TEST_LIST = {
    {"Init and Destruct test", init_final_test},
    {"Insert and Get test", insert_get_test},
    {"Insert and Delete test", insert_del_test},
    {"In test", in_test},
    {"Next test", next_test},
    { NULL, NULL }
};