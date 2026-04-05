SnakeOS - A Simple Bootable Operating System
SnakeOS là một hệ điều hành mini được viết bằng C và Assembly, được thiết kế để khởi động trực tiếp từ bộ nạp khởi động (bootloader) và chạy trò chơi "Rắn săn mồi" (Snake) ở chế độ kernel mode. Dự án này minh họa cách tương tác với phần cứng ở mức thấp, quản lý màn hình VGA và xử lý ngắt bàn phím mà không cần một hệ điều hành cơ sở.

🚀 Tính năng
Bootable: Có thể khởi động trực tiếp từ file ISO thông qua GRUB.

VGA Text Mode: Hiển thị giao diện trò chơi trực tiếp lên màn hình thông qua bộ nhớ video VGA (địa chỉ 0xB8000).

Keyboard Driver: Xử lý nhập liệu từ bàn phím mức thấp để điều khiển hướng di chuyển của rắn.

Game Logic: Xử lý va chạm, tạo thức ăn ngẫu nhiên và tăng độ dài của rắn.

📂 Cấu trúc dự án
src/: Chứa mã nguồn chính bao gồm mã nguồn C (.c) và Assembly (.s).

isodir/: Cấu trúc thư mục để tạo file hình ảnh ISO (chứa cấu hình GRUB).

Makefile: Script tự động hóa quá trình biên dịch và đóng gói.

my_os.bin: File thực thi sau khi biên dịch.

🛠 Yêu cầu hệ thống
Để biên dịch và chạy dự án này, bạn cần:

Bộ công cụ biên dịch chéo (Cross-compiler): i686-elf-gcc và i686-elf-binutils.

Assembler: nasm.

Trình tạo file ISO: grub-mkrescue và xorriso.

Trình giả lập: QEMU (để chạy thử).

🔨 Hướng dẫn cài đặt và khởi chạy
1. Biên dịch dự án
Mở terminal tại thư mục gốc và chạy lệnh:

Bash
make
Lệnh này sẽ biên dịch các tệp nguồn và tạo ra tệp my_os.bin, sau đó đóng gói thành my_os.iso.

2. Chạy trên trình giả lập QEMU
Để kiểm tra hệ điều hành mà không cần ghi vào USB, hãy sử dụng QEMU:

Bash
qemu-system-i386 -cdrom my_os.iso
🎮 Cách chơi
Sử dụng các phím mũi tên (hoặc các phím điều hướng được định nghĩa trong code) để điều khiển rắn.

Ăn thức ăn để tăng điểm và chiều dài.

Trò chơi kết thúc nếu rắn va vào tường hoặc tự đâm vào chính mình.
