#include <stdbool.h>
#include <sys/types.h>
#include <uart.h>

bool uart_initalized = false;

void uart_init(void) {
  write32(UART0_CR, 0x00000000);
  write32(UART0_IBRD, 1);
  write32(UART0_FBRD, 0x3);
  write32(UART0_LCRH, 0x00000070);
  write32(UART0_CR, 0x00000301);
  uart_initalized = true;
}

void uart_putc(unsigned char c) {
  if (c == '\n')
    uart_putc('\r');
  while (read32(UART0_FR) & 0x20) {
  }
  write32(UART0_DR, c);
}

unsigned char uart_getc(void) {
  while (read32(UART0_FR) & 0x10) {
  }
  return read32(UART0_DR);
}

ssize_t uart_write(int fd, const void *buf, size_t count) {
  (void)fd;
  if (!uart_initalized)
    uart_init();
  const char *cbuf = buf;
  for (size_t i = 0; i < count; i++)
    uart_putc(cbuf[i]);
  return count;
}

ssize_t uart_read(int fd, void *buf, size_t count) {
  (void)fd;
  if (!uart_initalized)
    uart_init();
  char *cbuf = buf;
  for (size_t i = 0; i < count; i++) {
    unsigned char c = uart_getc();
    cbuf[i] = c;
    if (c == '\n')
      break;
  }
  return count;
}
