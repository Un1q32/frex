#include <stdio.h>
#include <uart.h>

FILE _uartin = {'\0', __SRD, -1,        NULL,       0,    0,   NULL,
                0,    0,     uart_read, uart_write, NULL, NULL};

FILE *uartin = &_uartin;
