#include <sys/stdio.h>

int putchar(int ch) {
  if (stdout)
    return putc(ch, stdout);
  return EOF;
}
