#include <sys/stdlib.h>

int atoi(const char *nptr) { return (int)strtol(nptr, NULL, 10); }
