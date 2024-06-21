#include <uart.h>

int putchar(int c) { return uart_putchar(c); }

int getchar(void) { return uart_getchar(); }

int _puts(const char *s) {
  while (*s)
    putchar(*s++);
  return 0;
}

int puts(const char *s) {
  _puts(s);
  putchar('\n');
  return 0;
}
