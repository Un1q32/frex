#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>

static bool expand_heap(size_t size) {
  (void)size;
  return false;
}

static void uninitialize_heap(void) {}

/* first fit aligned_alloc */
void *aligned_alloc(size_t alignment, size_t size) {
  /* ensure alignment is a power of 2 */
  if (alignment > 0 && (alignment & (alignment - 1)) != 0) {
    errno = EINVAL;
    return NULL;
  }

  /* avoid unaligned access */
  if (alignment < sizeof(void *))
    alignment = sizeof(void *);

  /* initialize the heap if it isn't already */
  if (!__heap_start) {
    size_t new_heap_size = size + alignment - 1;
    /* overflow check */
    if (new_heap_size < size) {
      errno = ENOMEM;
      return NULL;
    }
    new_heap_size += sizeof(struct __malloc_block);
    /* overflow check */
    if (new_heap_size < sizeof(struct __malloc_block)) {
      errno = ENOMEM;
      return NULL;
    }

    if (!expand_heap(new_heap_size)) {
      errno = ENOMEM;
      return NULL;
    }

    /* setup first block */
    uintptr_t ptr = (uintptr_t)__heap_start + sizeof(void *);
    /* overflow check */
    if (ptr < sizeof(void *)) {
      uninitialize_heap();
      errno = ENOMEM;
      return NULL;
    }
    ptr += sizeof(struct __malloc_block);
    /* overflow check */
    if (ptr < sizeof(struct __malloc_block)) {
      uninitialize_heap();
      errno = ENOMEM;
      return NULL;
    }
    /* round up if not already aligned */
    if ((ptr & (alignment - 1)) != 0)
      ptr = (ptr | (alignment - 1)) + 1;
    /* overflow check */
    if (ptr == 0) {
      uninitialize_heap();
      errno = ENOMEM;
      return NULL;
    }

    struct __malloc_block *block = (struct __malloc_block *)ptr - 1;

    block->size = size;
    block->prev = NULL;
    block->next = NULL;

    /* the heap start has a pointer to the first block */
    *__heap_start = block;

    return block + 1;
  }

  /* see if there's space at the start of the heap */
  struct __malloc_block *block = *__heap_start;
  uintptr_t ptr =
      (uintptr_t)__heap_start + sizeof(void *) + sizeof(struct __malloc_block);
  /* round up if not already aligned */
  if ((ptr & (alignment - 1)) != 0)
    ptr = (ptr | (alignment - 1)) + 1;
  /* overflow check */
  if (ptr == 0) {
    errno = ENOMEM;
    return NULL;
  }
  uintptr_t ptrsize = ptr + size;
  /* overflow check */
  if (ptrsize < ptr) {
    errno = ENOMEM;
    return NULL;
  }
  if (ptrsize < (uintptr_t)block) {
    /* fit found */
    struct __malloc_block *new_block = (struct __malloc_block *)ptr - 1;
    new_block->size = size;
    new_block->prev = NULL;
    new_block->next = block;
    block->prev = new_block;
    *__heap_start = new_block;
    return (void *)ptr;
  }

  /* see if there's space between blocks */
  while (block->next) {
    ptr = (uintptr_t)block + (sizeof(struct __malloc_block) * 2) + block->size;
    /* overflow check */
    if (ptr < sizeof(struct __malloc_block)) {
      errno = ENOMEM;
      return NULL;
    }
    /* round up if not already aligned */
    if ((ptr & (alignment - 1)) != 0)
      ptr = (ptr | (alignment - 1)) + 1;
    /* overflow check */
    if (ptr == 0) {
      errno = ENOMEM;
      return NULL;
    }
    ptrsize = ptr + size;
    /* overflow check */
    if (ptrsize < ptr) {
      errno = ENOMEM;
      return NULL;
    }
    if (ptrsize < (uintptr_t)(block->next)) {
      /* fit found */
      struct __malloc_block *new_block = (struct __malloc_block *)ptr - 1;
      new_block->size = size;
      new_block->prev = block;
      new_block->next = block->next;
      block->next->prev = new_block;
      block->next = new_block;
      return (void *)ptr;
    }
    block = block->next;
  }

  /* see if there's space at the end of the heap */
  ptr = (uintptr_t)block + (sizeof(struct __malloc_block) * 2) + block->size;
  /* overflow check */
  if (ptr < sizeof(struct __malloc_block)) {
    errno = ENOMEM;
    return NULL;
  }
  /* round up if not already aligned */
  if ((ptr & (alignment - 1)) != 0)
    ptr = (ptr | (alignment - 1)) + 1;
  /* overflow check */
  if (ptr == 0) {
    errno = ENOMEM;
    return NULL;
  }
  ptrsize = ptr + size;
  /* overflow check */
  if (ptrsize < ptr) {
    errno = ENOMEM;
    return NULL;
  }
  uintptr_t heap_end = (uintptr_t)__heap_start + __heap_size;
  if (ptrsize < heap_end) {
    /* fit found */
    struct __malloc_block *new_block = (struct __malloc_block *)ptr - 1;
    new_block->size = size;
    new_block->prev = block;
    new_block->next = NULL;
    block->next = new_block;
    return (void *)ptr;
  }

  /* no space was found, must request more memory from the kernel */
  if (!expand_heap(ptrsize - heap_end)) {
    errno = ENOMEM;
    return NULL;
  }

  struct __malloc_block *new_block =
      (struct __malloc_block *)(ptr - sizeof(struct __malloc_block));
  new_block->size = size;
  new_block->prev = block;
  new_block->next = NULL;
  block->next = new_block;
  return (void *)ptr;
}
