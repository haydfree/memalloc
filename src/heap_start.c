#include "memalloc.h"

/* ptr to store addr of first freed mem block on heap */

static _HeapStart* _hs = NULL;

void init_heap_start() {
    if (_hs != NULL) { return; } 

    _hs = sbrk(sizeof(_HeapStart));
    if (_hs == (void*) -1) { return; }
}

_HeapStart* get_heap_start() {
    return _hs;
}

void set_heap_start(_HeapStart* hs) {
    _hs = hs;
}

MemoryBlockMeta* get_head(_HeapStart* hs) {
    if (hs == NULL) { return NULL; }
    return hs->ptr;
}

void set_head(MemoryBlockMeta* head) {
    _hs->ptr = head;
}

