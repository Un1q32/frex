#include <sys/stdio.h>

int feof(FILE *stream) { return stream->flags & __SEOF; }
