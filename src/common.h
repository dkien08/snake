#ifndef COMMON_H
#define COMMON_H

/* ==========================================================
 * SNAKE-OS: SNAKE GAME PROJECT
 * Purpose: Thống nhất kiểu dữ liệu và giao thức cho 5 thành viên
 * ========================================================== */

// 1. Kiểu dữ liệu chuẩn (Fixed-width types cho x86 32-bit)
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

// 2. Cấu hình màn hình (VGA Text Mode 80x25)
#define SCREEN_WIDTH  80
#define SCREEN_HEIGHT 25
#define VIDEO_ADDRESS 0xB8000

// 3. Định nghĩa màu sắc (Sử dụng cho Người 2 và Người 5)
typedef enum {
    COLOR_BLACK          = 0,
    COLOR_BLUE           = 1,
    COLOR_GREEN          = 2,
    COLOR_CYAN           = 3,
    COLOR_RED            = 4,
    COLOR_MAGENTA        = 5,
    COLOR_BROWN          = 6,
    COLOR_LIGHT_GREY     = 7,
    COLOR_DARK_GREY      = 8,
    COLOR_LIGHT_GREEN    = 10,
    COLOR_LIGHT_RED      = 12,
    COLOR_WHITE          = 15
} vga_color;

// 4. Hướng di chuyển (Dùng chung cho Người 3 và Người 4)
typedef enum {
    DIR_STOP = 0,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} direction_t;

// 5. Cấu trúc tọa độ và Game Object
typedef struct {
    s16int x;
    s16int y;
} vector2d;

#define MAX_SNAKE_LENGTH 100
typedef struct {
    vector2d body[MAX_SNAKE_LENGTH];
    u32int   length;
    direction_t head_dir;
} snake_t;

// 6. Hàm giao tiếp cổng I/O (Inline để tối ưu tốc độ)
static inline void outb(u16int port, u8int value) {
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

static inline u8int inb(u16int port) {
    u8int ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

// 7. Các phím điều khiển (Scancodes cho Người 3)
#define SCAN_UP    0x48
#define SCAN_DOWN  0x50
#define SCAN_LEFT  0x4B
#define SCAN_RIGHT 0x4D
#define SCAN_R     0x13
#define SCAN_P     0x19

#endif
