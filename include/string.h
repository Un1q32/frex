#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS
extern size_t strlen(const char *);
extern char *strcpy(char *, const char *);
extern char *strerror(int);
__END_DECLS

#endif
