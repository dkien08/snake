#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

// Định nghĩa các mã màu cơ bản của VGA
#define COLOR_BLACK  0
#define COLOR_GREEN  2  // Dùng cho thân rắn
#define COLOR_RED    4  // Dùng cho mồi (quả táo)
#define COLOR_GRAY   7  // Dùng cho khung tường
#define COLOR_WHITE  15 // Dùng cho chữ

// Các hàm mà Thành viên 2 sẽ cung cấp cho nhóm
void screen_clear();
void screen_draw_char(int x, int y, char c, uint8_t color);
void screen_print(int x, int y, const char* str, uint8_t color);

#endif
