#include <stdio.h>
#include <uart.h>

static char uartout_buf[BUFSIZ];

FILE __uartout = {'\0', __SWR | __SLBF, -1,         uartout_buf, NULL,
                  NULL, BUFSIZ,         0,          0,           0,
                  0,    uart_read,      uart_write, NULL,        NULL};

FILE *uartout = &__uartout;
