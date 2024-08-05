#include <stdint.h>
#include <sys/stdio.h>

int vsprintf(char *str, const char *format, va_list ap) {
  return vsnprintf(str, SIZE_MAX, format, ap);
}
