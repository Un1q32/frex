#include <stdbool.h>
#include <sys/stdio.h>

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if (stream->flags & __SNBF) {
    ssize_t writeret = stream->write(stream->fd, ptr, size * nmemb);
    if (writeret < 0) {
      stream->flags |= __SERR;
      return 0;
    }
    return writeret / size;
  } else {
    const char *src = ptr;
    size_t s = size * nmemb;
    char *data = stream->buf + stream->bufcount;
    while (s--) {
      if (stream->bufcount == BUFSIZ - 2) {
        fflush(stream);
        data = stream->buf;
      }
      *data++ = *src++;
      stream->bufcount++;
      if (stream->flags & __SLBF && *(src - 1) == '\n') {
        fflush(stream);
        data = stream->buf;
      }
    }
    return nmemb;
  }
}
