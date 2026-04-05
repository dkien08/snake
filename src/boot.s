; --- Multiboot Header ---
MBALIGN  equ  1 << 0            ; Căn lề bộ nhớ
MEMINFO  equ  1 << 1            ; Yêu cầu thông tin bộ nhớ
FLAGS    equ  MBALIGN | MEMINFO ; Kết hợp các cờ
MAGIC    equ  0x1BADB002        ; Số ma thuật cho GRUB
CHECKSUM equ -(MAGIC + FLAGS)   ; Kiểm tra lỗi

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; --- Thiết lập Stack (Ngăn xếp) ---
section .bss
align 16
stack_bottom:
    resb 16384 ; Dự phòng 16 KiB cho stack
stack_top:

; --- Điểm bắt đầu của OS ---
section .text
global _start:function (_start.end - _start)
_start:
    mov esp, stack_top    ; Thiết lập con trỏ stack
    
    extern kernel_main
    call kernel_main      ; Gọi hàm chính trong file kernel.c

    cli                   ; Ngắt hệ thống nếu thoát khỏi kernel
.hang:  hlt
    jmp .hang
.end:
