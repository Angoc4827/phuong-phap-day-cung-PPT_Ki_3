# phuong-phap-day-cung-PPT_Ki_3
Đồ án môn Phương pháp tính - Nhóm 3: Trình bày thuật toán dây cung trong bài toán tìm nghiệm gần đúng của phương trình phi tuyến

## Cấu trúc thư mục

Theo §3.1 và §3.7 của kế hoạch nhóm. Mỗi file đã được tạo sẵn (rỗng hoặc chỉ có dòng chú thích) để mọi người biết mình phụ trách file nào.

```
.
├── README.md                  giới thiệu đồ án và cấu trúc thư mục
├── code/                      toàn bộ code C nộp (C99, chỉ dùng thư viện chuẩn)
│   ├── README.md              cách biên dịch, chạy, ví dụ kết quả          (TV 7)
│   ├── Makefile               make / make test / make clean               (TV 7)
│   ├── day_cung.h             khai báo hàm, typedef struct KetQua, typedef enum TrangThai (TV 5)
│   ├── day_cung.c             hàm day_cung() và danh_gia_sai_so()         (TV 5)
│   ├── ham_mau.h              khai báo các hàm mẫu                        (TV 6)
│   ├── ham_mau.c              các hàm f(x), f'(x) có sẵn (bài tập slide + test case) (TV 6)
│   ├── main.c                 menu: chọn hàm, nhập a, b, ε, N_max; in bảng; xuất CSV (TV 7)
│   ├── so_sanh.c              chia đôi + Newton để so sánh số vòng lặp    (TV 6)
│   ├── test_day_cung.c        chạy toàn bộ test case, in ĐẠT / KHÔNG ĐẠT  (TV 8)
│   ├── test_cases.md          bộ 15 test case: hàm, khoảng, ε, N_max, kết quả mong đợi (TV 8)
│   └── ket_qua/               file .csv chương trình sinh ra, dùng vẽ biểu đồ bằng Excel
└── hinh/                      ảnh kết quả chạy và biểu đồ, cho báo cáo và slide (TV 9, TV 10 lấy)
```

Báo cáo Word và slide không để trên GitHub mà viết chung trên OneDrive. File `.csv` trong `code/ket_qua/` và file biên dịch (`*.exe`, `*.o`, `bin/`, `obj/`) đã được loại trừ trong `.gitignore`.

## Biên dịch nhanh

```bash
cd code
make              # hoặc mingw32-make trên Windows; make test để chạy test

# hoặc gõ tay:
gcc -std=c99 -Wall -Wextra -o day_cung main.c day_cung.c ham_mau.c -lm
gcc -std=c99 -Wall -Wextra -o test_day_cung test_day_cung.c day_cung.c ham_mau.c -lm
gcc -std=c99 -Wall -Wextra -o so_sanh so_sanh.c day_cung.c ham_mau.c -lm
```
