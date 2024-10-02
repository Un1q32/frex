#ifndef _STDIO_H_
#define _STDIO_H_

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#define L_ctermid PATH_MAX
#define L_tmpnam PATH_MAX

#define FILENAME_MAX PATH_MAX

typedef struct {
  int fd;
  short flags;
  char *buf;
  size_t bufsize;
  size_t bufcount;
  char uchar;
  char *ubuf;
  size_t ubufcount;
  size_t listpos;
  ssize_t (*read)(int, void *, size_t);
  ssize_t (*write)(int, const void *, size_t);
  off_t (*seek)(int, off_t, int);
  int (*close)(int);
} FILE;

#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SRD 0x0004
#define __SWR 0x0008
#define __SRW 0x0010
#define __SEOF 0x0020
#define __SERR 0x0040
#define __SFREESTREAM 0x0080
#define __SFREEBUF 0x0100

#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

#define BUFSIZ 1024
#define EOF (-1)

#define stdin stdin
#define stdout stdout
#define stderr stderr

#define getc(a) getc(a)

__BEGIN_DECLS
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

extern FILE *uartin;
extern FILE *uartout;

extern int fputc(int, FILE *);
extern int putc(int, FILE *);
extern int putchar(int);
extern int puts(const char *);
extern int fputs(const char *, FILE *);
extern int printf(const char *, ...);
extern int fprintf(FILE *, const char *, ...);
extern int sprintf(char *, const char *, ...);
extern int snprintf(char *, size_t, const char *, ...);
extern int vprintf(const char *, va_list);
extern int vfprintf(FILE *, const char *, va_list);
extern int vsprintf(char *, const char *, va_list);
extern int vsnprintf(char *, size_t, const char *, va_list);
extern int setvbuf(FILE *, char *, int, size_t);
extern int setlinebuf(FILE *);
extern void setbuffer(FILE *, char *, size_t);
extern void setbuf(FILE *, char *);
extern int fseek(FILE *, long, int);
extern void rewind(FILE *);
extern long ftell(FILE *);
extern int ferror(FILE *);
extern int fflush(FILE *);
extern int fpurge(FILE *);
extern int feof(FILE *);
extern void clearerr(FILE *);
extern int fgetc(FILE *);
extern int getc(FILE *);
extern int getchar(void);
extern int ungetc(int, FILE *);
extern char *fgets(char *, int, FILE *);
extern char *gets(char *);
extern size_t fread(void *, size_t, size_t, FILE *);
extern size_t fwrite(const void *, size_t, size_t, FILE *);
extern char *ctermid(char *);
extern int fileno(FILE *);
extern char *tmpnam(char *);
extern int sscanf(const char *, const char *, ...);
extern int vsscanf(const char *, const char *, va_list);
__END_DECLS

#endif
