#include <stdio.h>
#include <uart.h>
#include <utils.h>

void kernel_main(void) {
  uart_init();
  while (1) {
    puts("Hello, World!");
    delay(1000000);
  }
}
