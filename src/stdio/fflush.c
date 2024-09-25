#include <sys/stdio.h>

int fflush(FILE *stream) {
  if (!(stream->flags & __SWR) && !(stream->flags & __SRW))
    return 0;
  if (stream->write) {
    ssize_t writeret = stream->write(stream->fd, stream->buf, stream->bufcount);
    if (writeret == -1)
      return EOF;
    else
      stream->bufcount = 0;
  }
  return 0;
}
