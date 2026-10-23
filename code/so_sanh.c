#include <stdio.h>
#include <math.h>
#include "day_cung.h"
#include "ham_mau.h"

/* ------------------------------------------------------------------ */
/* Cau hinh so sanh                                                    */
/* ------------------------------------------------------------------ */
#define EPS    1e-4    /* sai so chung cho ca 3 phuong phap            */
#define N_MAX  1000    /* so vong lap toi da (du de moi phuong phap    */
                       /* hoi tu voi EPS = 1e-4 tren T1-T8)           */

/* ================================================================
 * PHUONG PHAP CHIA DOI (Bisection)
 *
 * Moi vong: tinh diem giua mid = (a+b)/2, thu hep khoang.
 * Dieu kien dung:
 *   - f(mid) = 0 chinh xac
 *   - n > 1 va |mid_n - mid_{n-1}| < eps
 * Tra ve:
 *    0 : dau mut la nghiem
 *   -1 : [a,b] khong phan ly nghiem (f(a)*f(b) > 0)
 *   >0 : so vong lap thuc hien
 * ================================================================ */
static int chia_doi(HamSo f, double a, double b, double eps,
                    int n_max, double *nghiem)
{
    double fa   = f(a);
    double fb   = f(b);
    double mid  = 0.0;
    double mid_cu = 0.0;   /* mid cua vong truoc */
    int    n;

    /* Dau mut chinh la nghiem */
    if (fa == 0.0) { *nghiem = a; return 0; }
    if (fb == 0.0) { *nghiem = b; return 0; }

    /* Khong phan ly nghiem */
    if (fa * fb > 0.0) { *nghiem = 0.0; return -1; }

    for (n = 1; n <= n_max; n++) {
        mid = (a + b) / 2.0;
        double fmid = f(mid);

        /* Gap dung nghiem chinh xac */
        if (fmid == 0.0) { *nghiem = mid; return n; }

        /* Dieu kien dung: |mid_n - mid_{n-1}| < eps */
        if (n > 1 && fabs(mid - mid_cu) < eps) {
            *nghiem = mid;
            return n;
        }

        /* Thu hep khoang */
        if (fa * fmid < 0.0) {
            b = mid; fb = fmid;
        } else {
            a = mid; fa = fmid;
        }
        mid_cu = mid;
    }

    *nghiem = mid;
    return n_max;   /* da het n_max vong ma chua hoi tu */
}

/* ================================================================
 * PHUONG PHAP NEWTON (Tiep tuyen)
 *
 * Chon diem xuat phat x0 theo dieu kien Fourier: f(x0)*f''(x0) > 0
 * (dam bao phuong phap hoi tu khi x0 thoa man dieu kien Fourier).
 *
 * f''(x) duoc uoc luong bang sai phan trung tam cua df:
 *   f''(x) ≈ (df(x+h) - df(x-h)) / (2h),  h = 1e-5
 *
 * Neu ca hai dau mut deu khong thoa dieu kien Fourier,
 * dung diem giua (a+b)/2 (du phong).
 *
 * Cong thuc lap: x_{n+1} = x_n - f(x_n) / f'(x_n)
 *
 * Dieu kien dung:
 *   - f(x_{n+1}) = 0 chinh xac
 *   - n > 1 va |x_n - x_{n-1}| < eps
 *
 * Tra ve:
 *   -1 : df = NULL (khong co dao ham)
 *    0 : dau mut la nghiem
 *   >0 : so vong lap thuc hien
 * ================================================================ */
static int newton(HamSo f, HamSo df, double a, double b,
                  double eps, int n_max, double *nghiem)
{
    /* Khong co dao ham: khong chay Newton */
    if (df == NULL) { *nghiem = 0.0; return -1; }

    /* Dau mut chinh la nghiem */
    double fa = f(a), fb = f(b);
    if (fa == 0.0) { *nghiem = a; return 0; }
    if (fb == 0.0) { *nghiem = b; return 0; }

    /* Uoc luong f''(x) = (df(x+h) - df(x-h)) / (2h) */
    const double h   = 1e-5;
    double fpp_a = (df(a + h) - df(a - h)) / (2.0 * h);
    double fpp_b = (df(b + h) - df(b - h)) / (2.0 * h);

    /* Chon diem bat dau x0 theo dieu kien Fourier */
    double x;
    if      (fa * fpp_a > 0.0) x = a;         /* a thoa Fourier      */
    else if (fb * fpp_b > 0.0) x = b;         /* b thoa Fourier      */
    else                       x = (a+b)/2.0; /* du phong: diem giua */

    int n;
    for (n = 1; n <= n_max; n++) {
        double dfx = df(x);

        /* Dao ham qua nho → co the phan ky */
        if (fabs(dfx) < 1e-15) { *nghiem = x; return n; }

        /* Cong thuc tiep tuyen Newton */
        double x_moi = x - f(x) / dfx;

        /* Truong hop gap dung nghiem chinh xac */
        if (f(x_moi) == 0.0) { *nghiem = x_moi; return n; }

        /* Dieu kien dung: |x_n - x_{n-1}| < eps
         * Tai day x = x_{n-1}, x_moi = x_n → |x_moi - x| dung */
        if (n > 1 && fabs(x_moi - x) < eps) {
            *nghiem = x_moi;
            return n;
        }

        x = x_moi;   /* chuan bi cho vong lap tiep theo */
    }

    *nghiem = x;
    return n_max;   /* khong hoi tu trong n_max vong */
}

/* ================================================================
 * Cau hinh cac ca thu T1-T8 de so sanh
 * (khoang, chi so ham trong DS_HAM, nhan hien thi)
 * ================================================================ */
typedef struct {
    const char *nhan;    /* "T1", "T2", ...                 */
    int         idx;     /* chi so trong DS_HAM             */
    double      a, b;    /* khoang phan ly nghiem           */
} CaThu;

static const CaThu CA_THU[] = {
    { "T1", 0,  1.0,  2.0 },   /* x^3 - x - 1       (1, 2)   */
    { "T2", 1,  1.0,  2.0 },   /* x^3 + x - 5       (1, 2)   */
    { "T3", 2,  0.0,  1.0 },   /* x^4 - 3x + 1      (0, 1)   */
    { "T4", 2,  1.0,  2.0 },   /* x^4 - 3x + 1      (1, 2)   */
    { "T5", 3, -4.0, -3.0 },   /* x^3 + 3x^2 + 5  (-4, -3)   */
    { "T6", 4,  1.0,  2.0 },   /* 2^x + x - 4       (1, 2)   */
    { "T7", 5,  0.0,  1.0 },   /* 2^x - 4x          (0, 1)   */
    { "T8", 6,  1.0,  2.0 }    /* x^2 - 2           (1, 2)   */
};

/* ================================================================
 * In mot so nguyen (hoac nhan dac biet) trong do rong w ky tu
 * ================================================================ */
static void in_vong(int vong, const char *loi_str, int w)
{
    if (vong < 0)
        printf("%*s", w, loi_str);
    else
        printf("%*d", w, vong);
}

/* ================================================================
 * MAIN
 * ================================================================ */
int main(void)
{
    int so_ca = (int)(sizeof(CA_THU) / sizeof(CA_THU[0]));

    /* ----- Tieu de -------------------------------------------- */
    printf("\n");
    printf("+====================================================================+\n");
    printf("|    BANG SO SANH SO VONG LAP: DAY CUNG / CHIA DOI / NEWTON        |\n");
    printf("+====================================================================+\n");
    printf("| Dieu kien dung chung : |x_n - x_{n-1}| < eps                     |\n");
    printf("| eps = %.0e              So vong toi da = %4d                     |\n",
           EPS, N_MAX);
    printf("| Newton: bat dau tu diem thoa dieu kien Fourier f(x0)*f''(x0)>0   |\n");
    printf("+====================================================================+\n");
    printf("\n");

    /* ----- Bang chinh ----------------------------------------- */
    printf("%-3s  %-20s  %-11s  %8s  %8s  %8s  %s\n",
           "CA", "Ham f(x)", "[a,  b]",
           "DayCung", "ChiaDoi", "Newton", "Nhan xet");
    printf("---  --------------------  -----------  "
           "--------  --------  --------  ---------\n");

    for (int i = 0; i < so_ca; i++) {
        const CaThu  *ca = &CA_THU[i];
        const MucHam *mh = &DS_HAM[ca->idx];

        /* --- Phuong phap day cung (goi tu day_cung.c) ---------- */
        KetQua kq      = day_cung(mh->f, ca->a, ca->b, EPS, N_MAX);
        int    vong_dc = (kq.trang_thai == KHOANG_KHONG_HOP_LE) ? -1 : kq.so_buoc_lap;

        /* --- Phuong phap chia doi ------------------------------- */
        double ng_cd  = 0.0;
        int    vong_cd = chia_doi(mh->f, ca->a, ca->b, EPS, N_MAX, &ng_cd);

        /* --- Phuong phap Newton --------------------------------- */
        double ng_nt  = 0.0;
        int    vong_nt = newton(mh->f, mh->df, ca->a, ca->b,
                                EPS, N_MAX, &ng_nt);

        /* --- Nhan xet ngan (Newton vs day cung) ---------------- */
        const char *nx = "";
        if (vong_nt < 0)
            nx = "N/A (thieu df)";
        else if (vong_nt < vong_dc && vong_dc >= 0)
            nx = "Newton nhanh hon";
        else if (vong_nt == vong_dc)
            nx = "Ngang nhau";
        else
            nx = "DayCung nhanh hon";

        /* --- Dinh dang khoang [a, b] --------------------------- */
        char khoang[14];
        snprintf(khoang, sizeof(khoang), "(%g, %g)", ca->a, ca->b);

        /* --- In hang ------------------------------------------- */
        printf("%-3s  %-20s  %-11s  ",
               ca->nhan, mh->ten, khoang);
        in_vong(vong_dc, "LOI",  8); printf("  ");
        in_vong(vong_cd, "LOI",  8); printf("  ");
        in_vong(vong_nt, "N/A",  8);
        printf("  %s\n", nx);
    }

    /* ----- Chu thich ------------------------------------------ */
    printf("---  --------------------  -----------  "
           "--------  --------  --------\n");
    printf("\nChu thich:\n");
    printf("  DayCung : phuong phap day cung (day_cung.c)\n");
    printf("  ChiaDoi : x = (a+b)/2 moi vong; dung khi |mid_n-mid_{n-1}|<eps\n");
    printf("  Newton  : tiep tuyen; x_moi = x - f(x)/f'(x)\n");
    printf("  LOI     : [a,b] khong la khoang phan ly nghiem\n");
    printf("  N/A     : khong co dao ham f'(x) de chay Newton\n\n");

    /* ----- Bang chinh xac (10 chu so) ------------------------- */
    printf("+==============================================================+\n");
    printf("|          NGHIEM TINH TOAN (10 chu so thap phan)             |\n");
    printf("+==============================================================+\n");
    printf("%-3s  %-20s  %-14s  %-14s  %-14s\n",
           "CA", "Ham f(x)", "DayCung", "ChiaDoi", "Newton");
    printf("---  --------------------  --------------  "
           "--------------  --------------\n");

    for (int i = 0; i < so_ca; i++) {
        const CaThu  *ca = &CA_THU[i];
        const MucHam *mh = &DS_HAM[ca->idx];

        KetQua kq     = day_cung(mh->f, ca->a, ca->b, EPS, N_MAX);
        double ng_cd  = 0.0;
        double ng_nt  = 0.0;
        chia_doi(mh->f, ca->a, ca->b, EPS, N_MAX, &ng_cd);
        newton(mh->f, mh->df, ca->a, ca->b, EPS, N_MAX, &ng_nt);

        printf("%-3s  %-20s  %14.10f  %14.10f  %14.10f\n",
               ca->nhan, mh->ten,
               (kq.trang_thai != KHOANG_KHONG_HOP_LE) ? kq.nghiem : 0.0,
               ng_cd, ng_nt);
    }
    printf("\n");

    return 0;
}
