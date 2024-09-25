#include <sys/stdio.h>

int setvbuf(FILE *stream, char *buf, int mode, size_t size) {
  if (mode != _IONBF && mode != _IOLBF && mode != _IOFBF)
    return -1;

  stream->buf = buf;
  stream->bufsize = size;
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
