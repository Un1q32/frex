#include <stdio.h>
#include <uart.h>

void kernel_main(void) {
  puts("Hello, world!");

  while (1) {
    unsigned char c = uart_getc();
    if (c == '\r')
      uart_putc('\n');
    else if (c == 0x7f)
      uart_write(-1, "\b \b", 3);
    else
      uart_putc(c);
  }
}
