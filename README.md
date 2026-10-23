# Phương pháp dây cung — Nhóm 4, môn Phương pháp tính
Trình bày thuật toán dây cung tìm nghiệm gần đúng phương trình phi tuyến f(x) = 0, viết bằng C. Hạn nộp: **28/10/2026**.

## Cấu trúc thư mục

```
.
├── Code/
│   └── day_cung.c        BÀI NỘP: toàn bộ chương trình trong 1 file (7 khối)
├── BaoCao/               BÀI NỘP: báo cáo Word + PDF (TV9 bỏ vào ngày 27/10)
├── Slide/                BÀI NỘP: slide PPTX + PDF (TV10 bỏ vào ngày 27/10)
├── hinh/                 ảnh chạy chương trình, sơ đồ khối, hình dây cung
└── tai_lieu/             tài liệu làm việc, KHÔNG nộp
    ├── Ly_thuyet_A.md        TV2
    ├── Ly_thuyet_B.md        TV3
    ├── tv4_thuat_toan_day_cung.docx   TV4 (giả mã)
    ├── test_cases.md         TV8
    └── code_rieng_cu/        code tách nhiều file trước 23/10, giữ để tham khảo
```

Khi nộp: nén `Code/`, `BaoCao/`, `Slide/` thành `Nhom4_DayCung.zip`.

## Chạy chương trình
- Code::Blocks / Dev-C++: File → Open → `Code/day_cung.c` → F9.
- Dòng lệnh: `gcc -std=c99 -Wall -Wextra Code/day_cung.c -o day_cung -lm`
- OnlineGDB: dán nội dung file, chọn ngôn ngữ C, bấm Run.

## 7 khối trong `Code/day_cung.c`

| Khối | Nội dung | Người viết | Trạng thái 23/10 |
|---|---|---|---|
| 1 | Thư viện, kiểu dữ liệu (API chốt 23/10) | TV5 | Xong |
| 2 | Khai báo nguyên mẫu hàm | TV1 | Xong |
| 3 | `main()`: menu | TV7 | Xong (khung) |
| 4 | 9 hàm f(x) mẫu, mảng `DS_HAM` | TV6 | Xong |
| 5 | Hàm `day_cung()` | TV5 | **Chờ TV5** (xem hướng dẫn sửa) |
| 6 | Nhập số an toàn, in kết quả | TV7 | Xong (khung), TV7 rà lại |
| 7 | `chay_bo_test()` 15 ca | TV8 | **Chờ TV8** |

## Cách nộp code
Thành viên **không cần dùng Git**: sửa xong khối của mình, tự bấm F9 thấy chạy được, gửi file cho TV1 qua Zalo (ghi rõ tên, TV mấy, sửa gì). TV1 chuyển Claude review và mở Pull Request.
