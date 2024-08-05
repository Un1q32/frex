#include <sys/ctype.h>

int ispunct(int c) { return isgraph(c) && !isalnum(c); }
