#include "avr8.h"
#include <avr/io.h>

#define MEM_SIZE 0x01c0
#define UART_BAUD 9600


static lsp_int16_t avr8_getchar(lsp_in_stream_t *s) {
    while (!(UCSR0A & (1 << 7)))
        ;
    return UDR0;
}


static lsp_int16_t avr8_putchar(lsp_out_stream_t *s, lsp_int16_t c) {
    while (!(UCSR0A & (1 << 5)))
        ;
    UDR0 = c;
}


static lsp_uint8_t avr8_mem[sizeof(lsp_mem_t) + MEM_SIZE * sizeof(lsp_cell_t)];

static lsp_in_stream_t avr8_in_stream;

static lsp_out_stream_t avr8_out_stream;


void lsp_arch_avr8_init() {
    UBRR0 = F_CPU / 16 / UART_BAUD - 1;
    UCSR0B |= _BV(TXEN0) | _BV(RXEN0);
}


lsp_mem_t *lsp_arch_avr8_create_mem() {
    lsp_mem_t *m = (void *)avr8_mem;
    if (lsp_mem_init(m, MEM_SIZE) != LSP_SUCCESS)
        return NULL;
    return m;
}


void lsp_arch_avr8_free_mem(lsp_mem_t *m) {}


lsp_in_stream_t *lsp_arch_avr8_create_in_stream() {
    lsp_in_stream_t *s = &avr8_in_stream;
    lsp_in_stream_init(s, avr8_getchar);
    return s;
}


void lsp_arch_avr8_free_in_stream(lsp_in_stream_t *s) {}


lsp_out_stream_t *lsp_arch_avr8_create_out_stream() {
    lsp_out_stream_t *s = &avr8_out_stream;
    lsp_out_stream_init(s, avr8_putchar);
    return s;
}


void lsp_arch_avr8_free_out_stream(lsp_out_stream_t *s) {}
