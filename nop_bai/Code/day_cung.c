/*
 * GIAI GAN DUNG PHUONG TRINH f(x) = 0 BANG PHUONG PHAP DAY CUNG
 * Nhom 4 - Mon Phuong phap tinh - DH Kinh te Quoc dan
 *
 * File nop duy nhat: mo bang Code::Blocks / Dev-C++ roi bam F9,
 * hoac: gcc -std=c99 -Wall -Wextra day_cung.c -o day_cung -lm
 *
 * KHUNG (23/10): cac khoi danh dau TODO se duoc TV1 chep code that vao
 * toi 25/10 tu cac file rieng trong thu muc code/. Khong sua ten ham,
 * kieu du lieu trong khoi 1 va khoi 2 (API da chot ngay 23/10).
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
 * KHOI 4: CAC HAM f(x) MAU (TV6)
 * TODO TV6: chep f1..f10 tu code/ham_mau.c, them vao DS_HAM.
 * =================================================================== */
static double f1(double x) { return x*x*x - x - 1.0; }   /* T1 */

static const MucHam DS_HAM[] = {
    { "x^3 - x - 1", f1 },
    /* TODO TV6: them cac ham con lai */
};
static const int SO_HAM = (int)(sizeof DS_HAM / sizeof DS_HAM[0]);

/* ===================================================================
 * KHOI 5: HAM day_cung() (TV5)
 * TODO TV5: chep than ham tu code/day_cung.c (sau khi sua theo API chot).
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
 * TODO TV7: chep tu code/main.c (kiem tra nhap chu thay so, a < b, ...).
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
 * TODO TV8: chep 15 ca tu code/test_day_cung.c, in DAT / KHONG DAT.
 * =================================================================== */
void chay_bo_test(void) {
    printf(">> Bo test chua duoc ghep vao (TV8)\n");
}
