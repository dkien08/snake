#include <stdint.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// Giữ nguyên kích thước màn hình
#define WIDTH  80 
#define HEIGHT 25
#define MAX_SNAKE 200

// Ký tự vẽ để tạo độ dày đồng nhất
#define SNAKE_HEAD   219 // Khối đặc █
#define SNAKE_BODY   219 // Khối đặc █
#define FOOD_CHAR    15  // Ký tự mặt trời ☼

int snake_x[MAX_SNAKE], snake_y[MAX_SNAKE], snake_len;
int dir_x, dir_y, food_x, food_y, game_running, score;

void int_to_str(int n, char* str) {
    int i = 0;
    if (n == 0) str[i++] = '0';
    else {
        while (n > 0) {
            str[i++] = (n % 10) + '0';
            n /= 10;
        }
    }
    str[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

void draw_score() {
    char score_str[10];
    int_to_str(score, score_str);
    screen_print(2, 0, " SCORE: ", 0x0E); 
    screen_print(10, 0, score_str, 0x0F); 
}

// Hàm vẽ đốt thân rắn thông minh (Bù trừ tỷ lệ VGA)
void draw_snake_unit(int x, int y, char c, uint8_t color, int is_clear) {
    if (is_clear) {
        screen_draw_char(x, y, ' ', 0x00);
    } else {
        screen_draw_char(x, y, c, color);
    }
}

void game_init() {
    screen_clear();
    snake_len = 5;
    score = 0;
    dir_x = 1; dir_y = 0;
    game_running = 1;
    
    for(int i = 0; i < snake_len; i++) {
        snake_x[i] = 40 - i;
        snake_y[i] = 12;
    }
    food_x = 20; food_y = 12;
    
    for(int i = 0; i < WIDTH; i++) {
        screen_draw_char(i, 0, '#', 0x0E);          
        screen_draw_char(i, HEIGHT - 1, '#', 0x0E); 
    }
    for(int i = 0; i < HEIGHT; i++) {
        screen_draw_char(0, i, '#', 0x0E);         
        screen_draw_char(WIDTH - 1, i, '#', 0x0E); 
    }
    draw_score();
}

void kernel_main() {
    timer_init(100); 

    while(1) {
        game_init();
        uint32_t frame_counter = 0;

        while(game_running) {
            uint8_t key = keyboard_read_scancode();
            if (key == 0x48 && dir_y == 0) { dir_x = 0; dir_y = -1; } 
            if (key == 0x50 && dir_y == 0) { dir_x = 0; dir_y = 1;  } 
            if (key == 0x4B && dir_x == 0) { dir_x = -1; dir_y = 0; } 
            if (key == 0x4D && dir_x == 0) { dir_x = 1; dir_y = 0;  }

            for(volatile int d = 0; d < 1200000; d++); 

            frame_counter++;
            
            /* TỐI ƯU ĐỘ ĐỀU:
               Tỷ lệ vàng cho VGA Text Mode là 2:1.
               Dọc (dir_y) bước 1 ô mất 44 nhịp.
               Ngang (dir_x) bước 1 ô mất 22 nhịp.
            */
            int threshold = (dir_y != 0) ? 44 : 22; 

            if (frame_counter < threshold) continue; 
            frame_counter = 0; 

            // Xóa đốt cuối
            draw_snake_unit(snake_x[snake_len - 1], snake_y[snake_len - 1], ' ', 0, 1);

            for(int i = snake_len - 1; i > 0; i--) {
                snake_x[i] = snake_x[i - 1];
                snake_y[i] = snake_y[i - 1];
            }
            snake_x[0] += dir_x;
            snake_y[0] += dir_y;

            if (snake_x[0] <= 0 || snake_x[0] >= WIDTH - 1 || 
                snake_y[0] <= 0 || snake_y[0] >= HEIGHT - 1) game_running = 0;

            for(int i = 1; i < snake_len; i++) {
                if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) game_running = 0;
            }

            if (snake_x[0] == food_x && snake_y[0] == food_y) {
                if (snake_len < MAX_SNAKE) snake_len++;
                score += 10;
                draw_score();
                food_x = (snake_x[0] * 7 + 13) % (WIDTH - 4) + 2;
                food_y = (snake_y[0] * 3 + 7) % (HEIGHT - 4) + 2;
            }

            // Vẽ mồi
            screen_draw_char(food_x, food_y, FOOD_CHAR, 0x0D); 

            // Vẽ rắn
            for(int i = 0; i < snake_len; i++) {
                uint8_t color = (i == 0) ? 0x0A : 0x02;
                draw_snake_unit(snake_x[i], snake_y[i], SNAKE_BODY, color, 0);
            }
        }

        screen_print(34, 11, " GAME OVER! ", 0x4F);
        char final_score[10];
        int_to_str(score, final_score);
        screen_print(32, 13, " Final Score: ", 0x0F);
        screen_print(46, 13, final_score, 0x0E);
        screen_print(28, 15, " Press SPACE to Restart ", 0x0F);
        while(keyboard_read_scancode() != 0x39); 
    }
}
