#include <sys/stdio.h>
#include <sys/string.h>

int puts(const char *str) {
  if (stdout)
    return fwrite(str, 1, strlen(str), stdout) + fwrite("\n", 1, 1, stdout);
  else
    return -1;
}
