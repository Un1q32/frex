#include <sys/stdio.h>
#include <sys/string.h>
#include <sys/uart.h>

void kernel_main(void) {
  uart_write(-1, "Hello, world!\n", 14);

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
