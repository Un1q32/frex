#ifndef _FREX_UTILS_H_
#define _FREX_UTILS_H_

#include <stddef.h>
#include <stdint.h>

extern void delay(uint64_t);
extern void put32(size_t, uint32_t);
extern uint32_t get32(size_t);

#endif
