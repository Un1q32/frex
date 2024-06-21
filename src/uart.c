#include <gpio.h>
#include <peripherals/aux.h>
#include <uart.h>

#define TXD 14
#define RXD 15

void uart_init(void) {
  gpio_pin_set_func(TXD, GFAlt5);
  gpio_pin_set_func(RXD, GFAlt5);

  gpio_pin_enable(TXD);
  gpio_pin_enable(RXD);

  REGS_AUX->enables = 1;
  REGS_AUX->mu_control = 0;
  REGS_AUX->mu_ier = 0;
  REGS_AUX->mu_lcr = 3;
  REGS_AUX->mu_mcr = 0;
  REGS_AUX->mu_baud = 541;
  REGS_AUX->mu_control = 3;

  uart_send('\r');
  uart_send('\n');
  uart_send('\n');
}

void uart_send(char c) {
  while (!(REGS_AUX->mu_lsr & 0x20))
    ;
  REGS_AUX->mu_io = c;
}

char uart_recv(void) {
  while (!(REGS_AUX->mu_lsr & 1))
    ;
  return REGS_AUX->mu_io & 0xFF;
}

int uart_putchar(int c) {
  if (c == '\n')
    uart_send('\r');
  uart_send(c);
  return c;
}

int uart_getchar(void) { return uart_recv(); }
