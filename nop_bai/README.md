# Thư mục nộp bài — Nhóm 4

Cấu trúc giống file zip nộp cho giảng viên (`Nhom4_DayCung.zip`):

```
nop_bai/
├── BaoCao/   Nhom4_BaoCao_DayCung.docx + .pdf   (TV9 bỏ vào ngày 27/10)
├── Slide/    Nhom4_Slide_DayCung.pptx + .pdf    (TV10 bỏ vào ngày 27/10)
└── Code/
    └── day_cung.c    toàn bộ chương trình trong 1 file
```

## Chạy chương trình
- Code::Blocks / Dev-C++: File → Open → `Code/day_cung.c` → F9.
- Dòng lệnh: `gcc -std=c99 -Wall -Wextra day_cung.c -o day_cung -lm`

## 7 khối trong `day_cung.c`

| Khối | Nội dung | Người viết | Lấy từ |
|---|---|---|---|
| 1 | Thư viện, kiểu dữ liệu (API chốt 23/10) | TV5 | `code/day_cung.h` |
| 2 | Khai báo nguyên mẫu hàm | TV1 | — |
| 3 | `main()`: menu | TV7 | `code/main.c` |
| 4 | Các hàm f(x) mẫu, mảng `DS_HAM` | TV6 | `code/ham_mau.c` |
| 5 | Hàm `day_cung()` | TV5 | `code/day_cung.c` |
| 6 | Nhập số an toàn, in kết quả | TV7 | `code/main.c` |
| 7 | `chay_bo_test()` 15 ca | TV8 | `code/test_day_cung.c` |

Hiện tại đây là **khung**: chạy được menu, nhưng các khối có `TODO` còn dùng code tạm. Đến tối 25/10 (chốt code), TV1 chép code thật từ thư mục `code/` vào đúng khối.

Thành viên không cần dùng Git: code xong gửi file cho TV1 qua Zalo.
