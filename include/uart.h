#ifndef _UART_H_
#define _UART_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/cdefs.h>
#include <sys/types.h>

static inline void write32(size_t reg, uint32_t data) {
  *(volatile uint32_t *)reg = data;
}

static inline uint32_t read32(size_t reg) { return *(volatile uint32_t *)reg; }

/* UART registers */
#define UART0_BASE 0x3F201000
#define UART0_DR (UART0_BASE + 0x00)
#define UART0_FR (UART0_BASE + 0x18)
#define UART0_IBRD (UART0_BASE + 0x24)
#define UART0_FBRD (UART0_BASE + 0x28)
#define UART0_LCRH (UART0_BASE + 0x2C)
#define UART0_CR (UART0_BASE + 0x30)
#define UART0_IMSC (UART0_BASE + 0x38)
#define UART0_ICR (UART0_BASE + 0x44)

__BEGIN_DECLS
extern FILE *uartin;
extern FILE *uartout;

extern void uart_init(void);
extern void uart_putc(unsigned char);
extern unsigned char uart_getc(void);
extern ssize_t uart_read(int, void *, size_t);
extern ssize_t uart_write(int, const void *, size_t);
__END_DECLS

#endif
