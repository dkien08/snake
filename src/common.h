#ifndef COMMON_H
#define COMMON_H

/* ==========================================================
 * KIEN-OS: SNAKE GAME PROJECT
 * File: common.h
 * Purpose: Dùng chung cho cả 5 thành viên để thống nhất kiểu dữ liệu.
 * ========================================================== */

// 1. Định nghĩa kiểu dữ liệu chuẩn (32-bit x86)
// Giúp Người 2, 3, 4 không bị lệch kích thước byte
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

// 2. Các hàm giao tiếp cổng I/O (Sử dụng cho Keyboard, Timer, Screen)
// Hàm ghi dữ liệu ra cổng phần cứng
static inline void outb(u16int port, u8int value) {
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

// Hàm đọc dữ liệu từ cổng phần cứng
static inline u8int inb(u16int port) {
    u8int ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

// 3. Cấu trúc tọa độ dùng chung cho Game Snake
// (Người 4 dùng tính toán, Người 2 dùng để vẽ)
typedef struct {
    s16int x;
    s16int y;
} vector2d;

// 4. Định nghĩa các màu sắc cơ bản (VGA Text Mode)
#define COLOR_BLACK 0x0
#define COLOR_GREEN 0x2
#define COLOR_RED   0x4
#define COLOR_WHITE 0xF

#endif
