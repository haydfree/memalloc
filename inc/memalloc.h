#ifndef MEMALLOC_H
#define MEMALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <stddef.h>

/* linked list to store metadata about mem blocks */
typedef struct MemoryBlockMeta {
    size_t size;
    struct MemoryBlockMeta* next;
    int free;
} MemoryBlockMeta;

/* HeapStart struct for storing head of freed mem block list */
typedef struct _HeapStart {
    MemoryBlockMeta* ptr;
} _HeapStart;
void init_heap_start();
_HeapStart* get_heap_start();
void set_heap_start(_HeapStart* hs);
MemoryBlockMeta* get_head(_HeapStart* hs);
void set_head(MemoryBlockMeta* head);

MemoryBlockMeta* find_free_block(_HeapStart* hs, size_t size);
MemoryBlockMeta* traverse(_HeapStart* hs);
MemoryBlockMeta* request_space(_HeapStart* hs, size_t size);
MemoryBlockMeta* get_block_addr(void* ptr);
void mem_copy(void* new_ptr, void* old_ptr, size_t size);
void mem_set(void* ptr, int val, size_t size);
void mem_free(void* ptr);
void* mem_alloc(size_t size);
void* mem_realloc(void* ptr, size_t size);
void* mem_calloc(size_t num_elements, size_t element_size);

void test_find_free_block();
void test_traverse();
void test_request_space();
void test_get_block_addr();
void test_mem_copy();
void test_mem_set();
void test_mem_free();
void test_mem_alloc();
void test_mem_realloc();
void test_mem_calloc();

#endif
