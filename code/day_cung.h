#ifndef DAY_CUNG_H
#define DAY_CUNG_H

#include <stdbool.h>

#define MAX_LICH_SU 1000

// Bao phủ toàn bộ 5 trường hợp có thể xảy ra
typedef enum {
    HOAN_THANH = 0,          // Tìm thấy nghiệm thành công
    VUOT_QUA_SO_BUOC,        // Đạt N_max mà chưa thỏa mãn epsilon (chống lặp vô hạn)
    LOI_MAU_SO_0,            // f(a) - f(b) = 0 (không thể chia)
    KHOANG_KHONG_HOP_LE,     // f(a) * f(b) > 0 (không chứa nghiệm)
    NGOAI_MIEN_XAC_DINH      // f(x) bị NaN hoặc vô cực
} TrangThai;

// Cấu trúc bám sát bảng kết quả Slide 59: a, b, x, f(x)
typedef struct {
    int buoc;
    double a;
    double b;
    double x;
    double f_x;
    double sai_so;
} BuocLap;

typedef struct {
    double nghiem;
    double f_nghiem;
    double sai_so_cuoi;
    int so_buoc_lap;
    TrangThai trang_thai;
    BuocLap lich_su[MAX_LICH_SU];
} KetQua;

KetQua day_cung(double (*f)(double), double a, double b, double eps, int max_iter);

#endif // DAY_CUNG_H