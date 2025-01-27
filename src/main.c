#include "memalloc.h"

/* function to find free block of memory using block_meta linked list */
MemoryBlockMeta* find_free_block(_HeapStart* hs, size_t size) {
    MemoryBlockMeta* cur = get_head(hs);
    while (cur != NULL) {
        if (cur->size >= size && cur->free == 1) { return cur; }

        cur = cur->next;
    }

    return NULL;
}

MemoryBlockMeta* traverse(_HeapStart* hs) {
    MemoryBlockMeta* cur = get_head(hs);

    if (hs == NULL || cur == NULL) { return NULL; }
    while (cur->next != NULL) { cur = cur->next; }
    return cur;
}

/* request space from OS, add buffer for metadata, return ptr to buffer */
MemoryBlockMeta* request_space(_HeapStart* hs, size_t size) {
    MemoryBlockMeta* block; 
    void* request;
    MemoryBlockMeta* last;

    block = sbrk(0);
    request = sbrk(size + sizeof(MemoryBlockMeta));
    assert(request == block);
    if (block == (void*) -1) { return NULL; }

    block->size = size;
    block->next = NULL;
    block->free = 0;

    last = traverse(hs);
    if (last != NULL) { last->next = block; }
    else { 
        init_heap_start();
        set_head(block);
    }

    return block;
}

MemoryBlockMeta* get_block_addr(void* ptr) {
    return (MemoryBlockMeta*) ptr - 1;
}

void mem_copy(void* new_ptr, void* old_ptr, size_t size) {
    size_t i = 0;
    unsigned char* n_ptr = new_ptr;
    unsigned char* o_ptr = old_ptr;
    while (i < size) {
        *(n_ptr+i) = *(o_ptr+i);

        i+=1;
    }
}

void mem_set(void* ptr, int val, size_t size) {
    size_t i = 0;
    unsigned char *p = ptr;
    while (i < size) {
        *(p+i) = val; 

        i+=1;
    }
}

void mem_free(void* ptr) {
    MemoryBlockMeta* block_ptr; 
    if (ptr == NULL) { return; }

    block_ptr = get_block_addr(ptr);
    block_ptr->free = 1;
}

void* mem_alloc(size_t size) {
    _HeapStart* hs;
    MemoryBlockMeta* block = NULL;
    hs = get_heap_start();

    if (size <= 0) { return NULL; }

    if (hs == NULL) { block = request_space(hs, size); }
    else { block = find_free_block(hs, size); }

    if (block == NULL) { block = request_space(hs, size); }
    if (block == NULL) { return NULL; }

    return (block+1);
}

void* mem_realloc(void* ptr, size_t size) {
    MemoryBlockMeta* block_addr;
    void* new_ptr;
    if (ptr == NULL) { return mem_alloc(size); }

    block_addr = get_block_addr(ptr);
    if (block_addr->size >= size) { return ptr; }

    new_ptr = mem_alloc(size);
    if (new_ptr == NULL) { return NULL; }
    mem_copy(new_ptr, ptr, block_addr->size);
    mem_free(ptr);
    return new_ptr;
}

void* mem_calloc(size_t num_elements, size_t element_size) {
    size_t size = num_elements * element_size;
    void* ptr = mem_alloc(size);
    mem_set(ptr, 0, size);
    return ptr;
}

int main() {
    test_find_free_block();
    
    return 0;
}
