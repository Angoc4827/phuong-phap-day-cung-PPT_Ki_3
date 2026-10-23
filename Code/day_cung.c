/*
 * GIAI GAN DUNG PHUONG TRINH f(x) = 0 BANG PHUONG PHAP DAY CUNG
 * Nhom 4 - Mon Phuong phap tinh - DH Kinh te Quoc dan
 *
 * File nop duy nhat: mo bang Code::Blocks / Dev-C++ roi bam F9,
 * hoac: gcc -std=c99 -Wall -Wextra day_cung.c -o day_cung -lm
 *
 * Trang thai 23/10: khoi 1-4, 6 da co; khoi 5 (TV5) va khoi 7 (TV8) con TODO.
 * Thanh vien gui code cho TV1 qua Zalo, TV1 ghep vao dung khoi.
 * Khong sua ten ham, kieu du lieu trong khoi 1 va khoi 2 (API chot 23/10).
 */

/* ===================================================================
 * KHOI 1: THU VIEN VA KIEU DU LIEU (TV5) - API da chot, phuong an A
 * =================================================================== */
#include <stdio.h>
#include <math.h>

#define MAX_LICH_SU 1000

typedef double (*HamSo)(double);

typedef enum {
    HOI_TU,          /* dung vi |x_n - x_(n-1)| < eps (n > 1) hoac f(x_n) = 0 */
    DU_SO_LAN_LAP,   /* dung vi da lap du N lan (ket qua hop le) */
    KHONG_DOI_DAU,   /* f(a)*f(b) > 0 */
    DAU_VAO_SAI      /* a >= b, eps <= 0, N <= 0, hoac f(a)/f(b) NaN/inf */
} TrangThai;

typedef struct {
    int    n;
    double a, b, x, fx;
    double sai_so;          /* |x_n - x_(n-1)|; vong 1 ghi -1 */
} BuocLap;

typedef struct {
    double     nghiem;
    int        so_vong;     /* 0 neu dau mut la nghiem hoac loi dau vao */
    double     sai_so;      /* |x_n - x_(n-1)| luc dung; -1 neu chua co */
    TrangThai  trang_thai;
    int        so_dong;     /* so dong hop le trong lich_su */
    BuocLap    lich_su[MAX_LICH_SU];
} KetQua;

typedef struct {
    const char *ten;        /* ten hien thi trong menu, vi du "x^3 - x - 1" */
    HamSo       f;
} MucHam;

/* ===================================================================
 * KHOI 2: KHAI BAO NGUYEN MAU CAC HAM (TV1)
 * =================================================================== */
/* Khoi 4 - ham mau */
static double f1(double x);
static double f2(double x);
static double f3(double x);
static double f5(double x);
static double f6(double x);
static double f7(double x);
static double f8(double x);
static double f9(double x);
static double f10(double x);

/* Khoi 5 - thuat toan */
KetQua day_cung(HamSo f, double a, double b, double eps, int n_lap, FILE *bang);

/* Khoi 6 - nhap lieu, in ket qua */
double nhap_so_thuc(const char *loi_nhac);
int    nhap_so_nguyen(const char *loi_nhac);
void   in_ket_qua(KetQua kq);
void   giai_phuong_trinh(void);

/* Khoi 7 - bo test */
void chay_bo_test(void);

/* ===================================================================
 * KHOI 3: HAM MAIN - MENU (TV7)
 * =================================================================== */
static KetQua kq_chung;   /* KetQua lon (~48 KB) nen de ngoai stack */

int main(void) {
    int chon;
    do {
        printf("\n===== PHUONG PHAP DAY CUNG =====\n");
        printf("1. Giai phuong trinh\n");
        printf("2. Chay bo test (15 ca)\n");
        printf("0. Thoat\n");
        chon = nhap_so_nguyen(">> Chon: ");
        switch (chon) {
            case 1: giai_phuong_trinh(); break;
            case 2: chay_bo_test();      break;
            case 0: break;
            default: printf(">> Lua chon khong hop le\n");
        }
    } while (chon != 0);
    return 0;
}

/* ===================================================================
 * KHOI 4: CAC HAM f(x) MAU (TV6) - lay tu ham_mau.c cua TV6
 * =================================================================== */
static double f1 (double x) { return x*x*x - x - 1.0; }          /* T1  (1, 2), slide tr. 43 */
static double f2 (double x) { return x*x*x + x - 5.0; }          /* T2  (1, 2), slide tr. 46 */
static double f3 (double x) { return x*x*x*x - 3.0*x + 1.0; }    /* T3 (0, 1), T4 (1, 2), tr. 48 */
static double f5 (double x) { return x*x*x + 3.0*x*x + 5.0; }    /* T5  (-4, -3), tr. 49 */
static double f6 (double x) { return pow(2.0, x) + x - 4.0; }    /* T6  (1, 2), tr. 11 */
static double f7 (double x) { return pow(2.0, x) - 4.0 * x; }    /* T7  (0, 1), tr. 50 */
static double f8 (double x) { return x*x - 2.0; }                /* T8  (1, 2), tr. 39 */
static double f9 (double x) { return cos(x) - x; }               /* T9  (0, 1), tr. 30 */
static double f10(double x) { return pow(x, 10.0) - 1.0; }       /* T10 (0, 1.3) */

static const MucHam DS_HAM[] = {
    { "x^3 - x - 1",    f1  },
    { "x^3 + x - 5",    f2  },
    { "x^4 - 3x + 1",   f3  },
    { "x^3 + 3x^2 + 5", f5  },
    { "2^x + x - 4",    f6  },
    { "2^x - 4x",       f7  },
    { "x^2 - 2",        f8  },
    { "cos(x) - x",     f9  },
    { "x^10 - 1",       f10 }
};
static const int SO_HAM = (int)(sizeof DS_HAM / sizeof DS_HAM[0]);

/* ===================================================================
 * KHOI 5: HAM day_cung() (TV5)
 * TODO TV5: thay than ham bang code da sua theo API chot (huong_dan_sua_TV5).
 * =================================================================== */
KetQua day_cung(HamSo f, double a, double b, double eps, int n_lap, FILE *bang) {
    KetQua kq = {0};
    (void)f; (void)a; (void)b; (void)eps; (void)n_lap; (void)bang;
    kq.sai_so = -1;
    kq.trang_thai = DAU_VAO_SAI;   /* tam thoi: chua co code that */
    return kq;
}

/* ===================================================================
 * KHOI 6: NHAP LIEU AN TOAN VA IN KET QUA (TV7)
 * TV7 kiem tra lai va bo sung neu can (thong bao loi ro hon, ...).
 * =================================================================== */
double nhap_so_thuc(const char *loi_nhac) {
    double x;
    int c;
    printf("%s", loi_nhac);
    while (scanf("%lf", &x) != 1) {
        while ((c = getchar()) != '\n' && c != EOF) { }
        printf(">> Nhap lai: ");
    }
    return x;
}

int nhap_so_nguyen(const char *loi_nhac) {
    int n, c;
    printf("%s", loi_nhac);
    while (scanf("%d", &n) != 1) {
        while ((c = getchar()) != '\n' && c != EOF) { }
        printf(">> Nhap lai: ");
    }
    return n;
}

void in_ket_qua(KetQua kq) {
    switch (kq.trang_thai) {
        case HOI_TU:
        case DU_SO_LAN_LAP:
            printf(">> Nghiem gan dung: %.10f\n", kq.nghiem);
            printf(">> So vong lap: %d\n", kq.so_vong);
            break;
        case KHONG_DOI_DAU:
            printf(">> f(a)*f(b) > 0: (a, b) khong phai khoang phan ly nghiem\n");
            break;
        case DAU_VAO_SAI:
            printf(">> Dau vao khong hop le\n");
            break;
    }
}

void giai_phuong_trinh(void) {
    int i, chon;
    double a, b, eps;
    int n_lap;

    for (i = 0; i < SO_HAM; i++)
        printf("%d. f(x) = %s\n", i + 1, DS_HAM[i].ten);
    do {
        chon = nhap_so_nguyen(">> Chon ham: ");
    } while (chon < 1 || chon > SO_HAM);

    a     = nhap_so_thuc(">> Nhap a: ");
    b     = nhap_so_thuc(">> Nhap b: ");
    eps   = nhap_so_thuc(">> Nhap sai so eps: ");
    n_lap = nhap_so_nguyen(">> Nhap so lan lap N: ");

    kq_chung = day_cung(DS_HAM[chon - 1].f, a, b, eps, n_lap, stdout);
    in_ket_qua(kq_chung);
}

/* ===================================================================
 * KHOI 7: BO TEST (TV8)
 * TODO TV8: 15 ca theo bang test case, in DAT / KHONG DAT.
 * =================================================================== */
void chay_bo_test(void) {
    printf(">> Bo test chua duoc ghep vao (TV8)\n");
}
