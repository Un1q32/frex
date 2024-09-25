#include <sys/stdio.h>
#include <sys/uart.h>

FILE _uartin = {-1, __SRD, NULL, 0, 0, uart_read, uart_write, NULL};

FILE *uartin = &_uartin;
