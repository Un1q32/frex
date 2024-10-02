#include <stdio.h>

int ungetc(int c, FILE *stream) {
  stream->uchar = c;
  stream->ubufcount = 1;
  return c;
}
