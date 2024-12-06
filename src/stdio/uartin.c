#include <stdio.h>
#include <uart.h>

char __uartin_buf[BUFSIZ];

FILE __uartin = {'\0', __SRD, -1, NULL,      __uartin_buf, NULL, 0,   0,
                 0,    0,     0,  uart_read, uart_write,   NULL, NULL};

FILE *uartin = &__uartin;
