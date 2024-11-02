#include <stdio.h>

int setvbuf(FILE *restrict stream, char *restrict buf, int mode, size_t size) {
  if (mode != _IONBF && mode != _IOLBF && mode != _IOFBF)
    return -1;

  stream->buf = buf;
  stream->bufsize = size;
  stream->flags &= ~__SFREEBUF;
  if (mode == _IONBF) {
    stream->flags |= __SNBF;
    stream->flags &= ~__SLBF;
  } else {
    stream->flags &= ~_IONBF;
    if (mode == _IOLBF)
      stream->flags |= __SLBF;
    else
      stream->flags &= ~__SLBF;
  }

  return 0;
}
