#include <stdio.h>
#include <uart.h>

static char stdout_buf[BUFSIZ];

FILE __stdout = {'\0',       __STDIO_LINEBUFFERED,
                 -1,         stdout_buf,
                 NULL,       NULL,
                 BUFSIZ,     0,
                 0,          0,
                 0,          NULL,
                 uart_write, NULL,
                 NULL};

FILE *stdout = &__stdout;
