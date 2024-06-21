#ifndef _FREX_UART_H_
#define _FREX_UART_H_

extern void uart_init(void);
extern char uart_recv(void);
extern void uart_send(char);
extern int uart_putchar(int);
extern int uart_getchar(void);

#endif
