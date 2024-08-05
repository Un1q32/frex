#include <stdbool.h>
#include <sys/stdio.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  fflush(stream);
  ssize_t readret = stream->read(stream->fd, ptr, size * nmemb);
  if (readret < 0) {
    stream->flags |= __SERR;
    return 0;
  } else if (readret == 0) {
    stream->flags |= __SEOF;
    return 0;
  }
  return readret / size;
}
