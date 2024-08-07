#ifndef _SYS_CTYPE_H_
#define _SYS_CTYPE_H_

#include <sys/cdefs.h>

__BEGIN_DECLS
extern int isalnum(int);
extern int isalpha(int);
extern int isascii(int);
extern int isblank(int);
extern int iscntrl(int);
extern int isdigit(int);
extern int isgraph(int);
extern int islower(int);
extern int isprint(int);
extern int ispunct(int);
extern int isspace(int);
extern int isupper(int);
extern int isxdigit(int);
extern int toupper(int);
extern int tolower(int);
__END_DECLS

#endif
