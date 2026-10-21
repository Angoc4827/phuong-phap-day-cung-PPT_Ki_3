#include "day_cung.h"
#include <math.h>

#define EPS_MAU_SO 1e-15

KetQua day_cung(double (*f)(double), double a, double b, double eps, int max_iter) {
    KetQua kq = {0};
    kq.so_buoc_lap = 0;
    
    double f_a = f(a);
    double f_b = f(b);

    // Trường hợp 1: Kiểm tra khoảng phân ly và tập xác định
    if (isnan(f_a) || isnan(f_b) || isinf(f_a) || isinf(f_b)) {
        kq.trang_thai = NGOAI_MIEN_XAC_DINH;
        return kq;
    }
    
    if (f_a * f_b > 0) {
        kq.trang_thai = KHOANG_KHONG_HOP_LE;
        return kq;
    }

    // Nếu a hoặc b vô tình là nghiệm đúng ngay từ đầu
    if (fabs(f_a) < EPS_MAU_SO) { kq.nghiem = a; kq.trang_thai = HOAN_THANH; return kq; }
    if (fabs(f_b) < EPS_MAU_SO) { kq.nghiem = b; kq.trang_thai = HOAN_THANH; return kq; }

    double x_prev = a; // Biến lưu x cũ để tính sai số thực tế

    for (int k = 1; k <= max_iter; k++) {
        f_a = f(a);
        f_b = f(b);

        // Trường hợp 2: Bắt lỗi chia cho 0
        if (fabs(f_b - f_a) < EPS_MAU_SO) {
            kq.nghiem = x_prev;
            kq.trang_thai = LOI_MAU_SO_0;
            return kq;
        }

        // Công thức Slide 40: x1 = (a*f(b) - b*f(a)) / (f(b) - f(a))
        double x_curr = (a * f_b - b * f_a) / (f_b - f_a);
        double f_curr = f(x_curr);
        
        // Tính sai số giữa 2 bước lặp (thực tế) và sai số e = |b-a| (theo sơ đồ Slide 45)
        double sai_so_buoc = fabs(x_curr - x_prev);
        double e_khoang = fabs(b - a);

        // Lưu vào mảng lịch sử (giống bảng Slide 59)
        if (kq.so_buoc_lap < MAX_LICH_SU) {
            kq.lich_su[k-1].buoc = k;
            kq.lich_su[k-1].a = a;
            kq.lich_su[k-1].b = b;
            kq.lich_su[k-1].x = x_curr;
            kq.lich_su[k-1].f_x = f_curr;
            kq.lich_su[k-1].sai_so = sai_so_buoc;
        }
        kq.so_buoc_lap = k;

        // Trường hợp 3: Thỏa mãn điều kiện dừng
        // Dừng khi: sai số khoảng < eps, HOẶC sai số bước < eps, HOẶC f(x) = 0
        if (e_khoang < eps || sai_so_buoc < eps || fabs(f_curr) < EPS_MAU_SO) {
            kq.nghiem = x_curr;
            kq.f_nghiem = f_curr;
            kq.sai_so_cuoi = sai_so_buoc;
            kq.trang_thai = HOAN_THANH;
            return kq;
        }

        // Bước cập nhật khoảng phân ly nghiệm (Slide 41 & Sơ đồ Slide 45)
        if (f_curr * f_a < 0) {
            b = x_curr; // Thay b = x_1
        } else {
            a = x_curr; // Thay a = x_1
        }
        
        x_prev = x_curr;
    }

    // Trường hợp 4: Chạy hết max_iter mà vẫn chưa hội tụ
    kq.nghiem = x_prev;
    kq.f_nghiem = f(x_prev);
    kq.sai_so_cuoi = fabs(b - a);
    kq.trang_thai = VUOT_QUA_SO_BUOC;
    return kq;
}