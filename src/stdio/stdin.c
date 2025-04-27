#include <stdio.h>
#include <uart.h>

char __stdin_buf[BUFSIZ];

FILE __stdin = {'\0', 0, -1, NULL,      __stdin_buf, NULL, 0,   0,
                0,    0, 0,  uart_read, NULL,        NULL, NULL};

FILE *stdin = &__stdin;
