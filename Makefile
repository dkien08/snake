# Makefile tối ưu cho Người 1
CC = gcc
AS = nasm
LD = ld

# Các cờ biên dịch chuẩn cho OS Dev
CFLAGS = -m32 -ffreestanding -O2 -Wall
LDFLAGS = -m32 -T src/linker.ld
ASFLAGS = -f elf32

# Danh sách các file object cần liên kết
OBJ = src/boot.o src/kernel.o src/screen.o src/keyboard.o src/timer.o

all: kernel.bin

# Quy tắc biên dịch file Assembly
src/boot.o: src/boot.s
	$(AS) $(ASFLAGS) src/boot.s -o src/boot.o

# Quy tắc biên dịch các file C (Dùng chung cho cả nhóm)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Liên kết tất cả thành file thực thi cuối cùng
kernel.bin: $(OBJ)
	$(LD) -m elf_i386 -T src/linker.ld -o kernel.bin $(OBJ)

# Lệnh chạy nhanh để kiểm thử
run: kernel.bin
	qemu-system-i386 -kernel kernel.bin

# Dọn dẹp các file rác
clean:
	rm -f src/*.o kernel.bin
