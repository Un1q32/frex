#include <stdio.h>
#include <uart.h>

static char uartout_buf[BUFSIZ];

FILE _uartout = {-1, __SWR | __SLBF, uartout_buf, BUFSIZ, 0,   '\0', NULL, 0,
                 0,  uart_read,      uart_write,  NULL,   NULL};

FILE *uartout = &_uartout;
