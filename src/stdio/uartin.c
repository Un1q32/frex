#include <sys/stdio.h>
#include <sys/uart.h>

static char uartin_buf[BUFSIZ];

FILE _uartin = {-1, __SRD, uartin_buf, 0, uart_read, uart_write};

FILE *uartin = &_uartin;
