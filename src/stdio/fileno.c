#include <sys/stdio.h>

int fileno(FILE *stream) { return stream->fd; }
