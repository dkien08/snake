#include "screen.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

void screen_draw_char(int x, int y, char c, uint8_t color) {
    if (x >= 80 || y >= 25) return;
    const int index = y * 80 + x;
    vga_buffer[index] = (uint16_t)c | (uint16_t)color << 8;
}

void screen_clear() {
    for (int i = 0; i < 80 * 25; i++) {
        // Sử dụng màu đen hoàn toàn (0x00) thay vì xám (0x0F)
        vga_buffer[i] = (uint16_t)' ' | (uint16_t)0x00 << 8;
    }
}

void screen_print(int x, int y, const char* str, uint8_t color) {
    for (int i = 0; str[i] != '\0'; i++) {
        screen_draw_char(x + i, y, str[i], color);
    }
}
