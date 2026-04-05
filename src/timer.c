#include "timer.h"
#include <stdint.h>

uint32_t tick = 0;

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

void timer_init(uint32_t frequency) {
    uint32_t divisor = 1193180 / frequency;
    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}

void timer_wait(uint32_t ticks) {
    // Giảm xuống 1 triệu để CPU nhạy hơn với bàn phím
    for(volatile uint32_t i = 0; i < ticks * 7000000; i++) {
        __asm__("nop");
    }
    tick += ticks;
}
