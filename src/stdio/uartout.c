#include <sys/stdio.h>
#include <sys/uart.h>

static char uartout_buf[BUFSIZ];

FILE _uartout = {-1, __SWR | __SLBF, uartout_buf, BUFSIZ,
                 0,  uart_read,      uart_write,  NULL};

FILE *uartout = &_uartout;
