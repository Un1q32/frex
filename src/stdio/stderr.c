#include <stdio.h>
#include <uart.h>

FILE __stderr = {
    '\0', __STDIO_UNBUFFERED, -1,   NULL, NULL, NULL, BUFSIZ, 0, 0, 0, 0,
    NULL, uart_write,         NULL, NULL};

FILE *stderr = &__stderr;
