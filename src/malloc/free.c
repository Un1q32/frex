#include <stdlib.h>

void free(void *ptr) {
  if (!ptr)
    return;

  /* make sure the pointer is from inside the heap */
  if (ptr <= (void *)__heap_start ||
      (char *)ptr > (char *)__heap_start + __heap_size)
    abort();

  struct __malloc_block *block = (struct __malloc_block *)ptr - 1;

  if (block->next) {
    block->next->prev = block->prev;
    if (block->prev)
      block->prev->next = block->next;
    else /* this is the first block in the heap */
      *__heap_start = block->next;
    return;
  }

  if (block->prev) {
    block->prev->next = NULL;
    return;
  }

  /* this is the last block in the heap, uninitalize the heap */
  *__heap_start = NULL;
}
