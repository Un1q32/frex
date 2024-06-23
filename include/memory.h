#ifndef _FREX_MEMORY_H_
#define _FREX_MEMORY_H_

#include <machine/param.h>

#define TABLE_SHIFT 9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)
#define SECTION_SIZE (1 << SECTION_SHIFT)
#define LOW_MEMORY (2 * SECTION_SIZE)

#ifndef __ASSEMBLER__
extern void memzero(unsigned long, unsigned int);
#endif

#endif
