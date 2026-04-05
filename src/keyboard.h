#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

// Định nghĩa mã quét (Scan codes) cho các phím mũi tên
#define KEY_UP    0x48
#define KEY_DOWN  0x50
#define KEY_LEFT  0x4B
#define KEY_RIGHT 0x4D
#define KEY_ESC   0x01

// Hàm kiểm tra xem có phím nào đang được nhấn không
uint8_t keyboard_read_scancode();

// Hàm chuyển đổi mã quét thành hướng di chuyển cho rắn
char keyboard_get_direction(uint8_t scancode);

#endif
