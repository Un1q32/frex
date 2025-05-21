#include <stdio.h>

int ungetc(int c, FILE *stream) {
  stream->ungetcchar = c;
  stream->ungetcbufcount = 1;
  return c;
}
