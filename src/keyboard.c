#include "keyboard.h"

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

uint8_t keyboard_read_scancode() {
    uint8_t last_code = 0;
    // Đọc sạch bộ đệm để bắt phím mới nhất và nuốt byte 0xE0
    while (inb(0x64) & 1) {
        uint8_t code = inb(0x60);
        if (code != 0xE0) {
            last_code = code;
        }
    }
    return last_code;
}
