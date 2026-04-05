#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

// Hàm khởi tạo bộ đếm thời gian với tần số mong muốn (Hz)
void timer_init(uint32_t frequency);

// Hàm tạm dừng chương trình trong một số lượng 'ticks' nhất định
void timer_wait(uint32_t ticks);

// Hàm lấy số lượng tick đã trôi qua kể từ khi khởi động
uint32_t timer_get_ticks();

#endif
