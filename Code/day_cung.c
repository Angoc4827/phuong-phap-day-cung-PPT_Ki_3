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
static double f11(double x) { return x*x + 1.0; }                 /* T11: x^2 + 1 */
static double f12(double x) { return x*x - 4.0; }                 /* T12: x^2 - 4 */

static const MucHam DS_HAM[] = {
    { "x^3 - x - 1",    f1  },
    { "x^3 + x - 5",    f2  },
    { "x^4 - 3x + 1",   f3  },
    { "x^3 + 3x^2 + 5", f5  },
    { "2^x + x - 4",    f6  },
    { "2^x - 4x",       f7  },
    { "x^2 - 2",        f8  },
    { "cos(x) - x",     f9  },
    { "x^10 - 1",       f10 },
    { "x^2 + 1",        f11 },
    { "x^2 - 4",        f12 }
};
static const int SO_HAM = (int)(sizeof DS_HAM / sizeof DS_HAM[0]);

/* ===================================================================
 * KHOI 5: HAM day_cung() (TV5)
 * =================================================================== */
KetQua day_cung(HamSo f, double a, double b, double eps, int n_lap, FILE *bang) {
    KetQua kq = {0};
    kq.sai_so = -1.0;
    kq.so_vong = 0;
    kq.so_dong = 0;

    /* 1. Kiem tra dau vao co ban */
    if (a >= b || eps <= 0 || n_lap <= 0) {
        kq.trang_thai = DAU_VAO_SAI;
        return kq;
    }

    /* 2. Tinh fa, fb mot lan. Kiem tra mien xac dinh */
    double fa = f(a);
    double fb = f(b);
    if (isnan(fa) || isnan(fb) || isinf(fa) || isinf(fb)) {
        kq.trang_thai = DAU_VAO_SAI;
        return kq;
    }

    /* 3. Kiem tra nghiem dung tai mut */
    if (fa == 0.0) {
        kq.nghiem = a;
        kq.so_vong = 0;
        kq.trang_thai = HOI_TU;
        return kq;
    }
    if (fb == 0.0) {
        kq.nghiem = b;
        kq.so_vong = 0;
        kq.trang_thai = HOI_TU;
        return kq;
    }

    /* 4. Kiem tra dieu kien trai dau */
    if (fa * fb > 0.0) {
        kq.trang_thai = KHONG_DOI_DAU;
        return kq;
    }

    /* 5. Vong lap day cung */
    if (bang != NULL) {
        fprintf(bang, "%3s | %13s | %13s | %13s | %13s | %13s\n",
                "n", "a", "b", "x", "f(x)", "|x - x_cu|");
    }
    double x_cu = a;
    for (int n = 1; n <= n_lap; n++) {
        // Tinh diem cat truc hoanh x va fx
        double x = (a * fb - b * fa) / (fb - fa);
        double fx = f(x);
        
        // Tinh sai so (vong 1 gan -1)
        double sai_so_buoc = (n > 1) ? fabs(x - x_cu) : -1.0;

        // Ghi vao lich su (khong vuot qua MAX_LICH_SU)
        if (kq.so_dong < MAX_LICH_SU) {
            kq.lich_su[kq.so_dong].n = n;
            kq.lich_su[kq.so_dong].a = a;
            kq.lich_su[kq.so_dong].b = b;
            kq.lich_su[kq.so_dong].x = x;
            kq.lich_su[kq.so_dong].fx = fx;
            kq.lich_su[kq.so_dong].sai_so = sai_so_buoc;
            kq.so_dong++;
        }

        // In 1 dong ra file (neu bang != NULL)
        if (bang != NULL) {
            if (n == 1) {
                fprintf(bang, "%3d | %13.10f | %13.10f | %13.10f | %13.10f | %13s\n",
                        n, a, b, x, fx, "-");
            } else {
                fprintf(bang, "%3d | %13.10f | %13.10f | %13.10f | %13.10f | %13.10f\n",
                        n, a, b, x, fx, sai_so_buoc);
            }
        }

        // Kiem tra dieu kien dung
        if (fx == 0.0 || (n > 1 && sai_so_buoc < eps)) {
            kq.nghiem = x;
            kq.so_vong = n;
            kq.sai_so = sai_so_buoc;
            kq.trang_thai = HOI_TU;
            return kq;
        }

        // Thu hep khoang phan ly nghiem
        if (fa * fx < 0.0) {
            b = x;
            fb = fx;
        } else {
            a = x;
            fa = fx;
        }
        
        x_cu = x;
    }

    /* 6. Het vong lap chua hoi tu */
    kq.nghiem = x_cu;
    kq.so_vong = n_lap;
    if (kq.so_dong > 0) {
        kq.sai_so = kq.lich_su[kq.so_dong - 1].sai_so;
    }
    kq.trang_thai = DU_SO_LAN_LAP;
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
            if (kq.trang_thai == HOI_TU && kq.so_vong == 0)
                printf(">> Dau mut a hoac b chinh la nghiem.\n");
            else if (kq.trang_thai == HOI_TU)
                printf(">> Dung vi dat sai so eps.\n");
            else
                printf(">> Dung vi da lap du %d vong (N).\n", kq.so_vong);
            printf(">> Nghiem gan dung: %.10f\n", kq.nghiem);
            printf(">> So vong lap: %d\n", kq.so_vong);
            if (kq.sai_so >= 0)
                printf(">> Sai so |x_n - x_(n-1)|: %.3e\n", kq.sai_so);
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
typedef struct{
    const char *id; 
    HamSo f; 
    double a,b; // khoảng phân ly a,b
    double eps; // Sai số cho phép (điều kiện dừng theo sai số) 
    int nmax;  // số lần lặp tối đa 
    double x_mong_doi;  //không đúng với test lỗi 
    int so_vong_chay;  // Số vòng chạy để ra kết quả  
    TrangThai tt_mong_doi; 
} CaTest; 
static const char *ten_tt(TrangThai t){
    switch(t){
        case HOI_TU: return "HOI TU";
        case DU_SO_LAN_LAP: return "DU SO LAN LAP";
        case KHONG_DOI_DAU: return "KHONG DOI DAU";
        case DAU_VAO_SAI: return "DAU VAO SAI";
    }
    return "?";
} 
void chay_bo_test(void) {
    // khai báo 15 ca test
    static const CaTest ds_test[15] = 
    {
        // id   f    a    b    eps  N   x mong doi   vong   trang thai 
        { "T1", f1, 1.0, 2.0, 1e-4, 2, 1.2531120332, 2, DU_SO_LAN_LAP },  //T1 dừng khi đủ 2 vòng 
        { "T2", f2, 1.0, 2.0, 1e-4,  5, 1.5155206007, 5,  DU_SO_LAN_LAP },  //T2 dừng khi đủ 5 vòng 
        { "T3", f3, 0.0, 1.0, 1e-4, 100, 0.3376673882, 5,  HOI_TU },
        { "T4",  f3,  1.0, 2.0, 1e-4, 100, 1.3073768960, 18, HOI_TU },
        { "T5",  f5, -4.0,-3.0, 1e-4, 100, -3.4259687126, 7, HOI_TU },
        { "T6",  f6,  1.0, 2.0, 1e-4, 100, 1.3861644283, 6,  HOI_TU },
        { "T7",  f7,  0.0, 1.0, 1e-4, 100, 0.3099073796, 4,  HOI_TU },
        { "T8",  f8,  1.0, 2.0, 1e-4, 100, 1.4142011834, 6,  HOI_TU },
        { "T9",  f9,  0.0, 1.0, 1e-4, 5,   0.7390847824, 5,  HOI_TU },
        { "T10", f10, 0.0, 1.3, 1e-4, 100, 0.9996886513, 39, HOI_TU },
        { "T11", f11,-1.0, 1.0, 1e-4, 5,   0.0,          0,  KHONG_DOI_DAU },
        { "T12", f12, 2.0, 3.0, 1e-4, 5,   2.0,          0,  HOI_TU }, // hoặc đầu mút là nghiệm
        { "T13", f8,  2.0, 1.0, 0.0,  5,   0.0,          0,  DAU_VAO_SAI },
        { "T14", f2,  1.0, 2.0, 1e-4, 100, 1.5159546734, 7,  HOI_TU },
        { "T15", f1,  1.0, 2.0, 1e-4, 30,  1.3246845152, 11, HOI_TU }  // T1 voi N=30: dung o vong 11 theo |x - x_cu| < eps (neu dung b - a < eps thi khong bao gio dung)
        
    };
    const int so_ca = (int)(sizeof ds_test/ sizeof ds_test[0]);
    int dat = 0; 

    printf("\n====================================================================================================================\n");
    printf("\n%-5s | %-14s | %-14s | %-5s | %-5s | %-15s | %-15s | %-10s | %s\n",
           "Ma", "TT thuc te", "TT mong doi", "Vong", "V.md",
           "Nghiem tinh", "Nghiem mong doi", "Sai so", "Ket luan");
    printf("====================================================================================================================\n");

    for (int i = 0; i < so_ca; i++) {
        const CaTest *ct = &ds_test[i];
        KetQua kq = day_cung(ct->f, ct->a, ct->b, ct->eps, ct->nmax, NULL);

        int la_loi = (ct->tt_mong_doi == KHONG_DOI_DAU || ct->tt_mong_doi == DAU_VAO_SAI);
        int khop_trang_thai = (kq.trang_thai == ct->tt_mong_doi);
        int khop_vong = (kq.so_vong == ct->so_vong_chay);
        int khop_nghiem = la_loi || (fabs(kq.nghiem - ct->x_mong_doi) < 1e-8);
        int ok = khop_trang_thai && khop_vong && khop_nghiem;
        if(ok) dat++;

        printf("%-5s | %-14s | %-14s | %-5d | %-5d | ", ct->id, ten_tt(kq.trang_thai), ten_tt(ct->tt_mong_doi), kq.so_vong, ct->so_vong_chay);
        if(la_loi){
            printf("%-15s | %-15s | %-10s | ", "-", "-", "-");
        }
        else{
            printf("%-15.10f | %-15.10f | ", kq.nghiem, ct->x_mong_doi);
            if (kq.sai_so >= 0) printf("%-10.2e | ", kq.sai_so);
            else                printf("%-10s | ", "-");
        }
        printf("%s\n", ok ? "DAT" : "KHONG DAT");
    }
    printf(">> Tong ket: Dat %d/%d ca test.\n", dat, so_ca);
}
