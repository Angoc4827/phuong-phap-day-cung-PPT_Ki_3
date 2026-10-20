# phuong-phap-day-cung-PPT_Ki_3
Đồ án môn Phương pháp tính - Nhóm 3: Trình bày thuật toán dây cung trong bài toán tìm nghiệm gần đúng của phương trình phi tuyến

## Cấu trúc thư mục

Theo §3.1 và §3.7 của kế hoạch nhóm. Mỗi file đã được tạo sẵn (rỗng hoặc chỉ có dòng chú thích) để mọi người biết mình phụ trách file nào.

```
.
├── README.md                  giới thiệu đồ án và cấu trúc thư mục
├── code/                      toàn bộ code C++ nộp (C++17, chỉ dùng thư viện chuẩn)
│   ├── README.md              cách biên dịch, chạy, ví dụ kết quả          (TV 7)
│   ├── Makefile               make / make test / make clean               (TV 7)
│   ├── day_cung.h             khai báo hàm, struct KetQua, enum class TrangThai (TV 5)
│   ├── day_cung.cpp           hàm day_cung() và danh_gia_sai_so()         (TV 5)
│   ├── ham_mau.h              khai báo các hàm mẫu                        (TV 6)
│   ├── ham_mau.cpp            các hàm f(x), f'(x) có sẵn (bài tập slide + test case) (TV 6)
│   ├── main.cpp               menu: chọn hàm, nhập a, b, ε, N_max; in bảng; xuất CSV (TV 7)
│   ├── so_sanh.cpp            chia đôi + Newton để so sánh số vòng lặp    (TV 6)
│   ├── test_day_cung.cpp      chạy toàn bộ test case, in ĐẠT / KHÔNG ĐẠT  (TV 8)
│   └── ket_qua/               file .csv chương trình sinh ra, dùng vẽ biểu đồ bằng Excel
└── hinh/                      ảnh kết quả chạy và biểu đồ, cho báo cáo và slide (TV 9, TV 10 lấy)
```

Báo cáo Word và slide không để trên GitHub mà viết chung trên OneDrive. File `.csv` trong `code/ket_qua/` và file biên dịch (`*.exe`, `*.o`, `bin/`, `obj/`) đã được loại trừ trong `.gitignore`.

## Biên dịch nhanh

```bash
cd code
g++ -std=c++17 -Wall -Wextra -o day_cung main.cpp day_cung.cpp ham_mau.cpp
g++ -std=c++17 -Wall -Wextra -o test_day_cung test_day_cung.cpp day_cung.cpp ham_mau.cpp
g++ -std=c++17 -Wall -Wextra -o so_sanh so_sanh.cpp day_cung.cpp ham_mau.cpp
```
