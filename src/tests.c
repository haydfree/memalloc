#include "memalloc.h"

_HeapStart* hs;

void set_up() {
    init_heap_start();
    hs = get_heap_start();
}

void tear_down() {
    mem_free(hs);
}

void test_mem_alloc() {
    size_t i;
    set_up();


    tear_down();
}

void test_find_free_block() {
    MemoryBlockMeta* head;
    MemoryBlockMeta* res;
    size_t size = 4;
    
    set_up();
    head = mem_alloc(sizeof(MemoryBlockMeta));
    head->size = size;
    head->next = NULL;
    head->free = 1;
    set_head(head);

    /* check with hs exists */
    res = find_free_block(hs, size);
    assert(res == head);

    /* check that null hs does not find res */
    res = find_free_block(NULL, size);
    assert(res != head);
   
    /* check that null hs = null res */ 
    hs = NULL;
    head = NULL;
    set_head(head);
    res = find_free_block(hs, size);
    assert(res == head);

    mem_free(hs);
    printf("all find_free_block tests passed\n");
}

void test_traverse() {
     
}

void test_request_space();
void test_get_block_addr();
void test_mem_copy();
void test_mem_set();
void test_mem_free();
void test_mem_alloc();
void test_mem_realloc();
void test_mem_calloc();

