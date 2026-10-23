#include <math.h>
#include "ham_mau.h"

/* ==================================================================
 * T1:  f(x) = x^3 - x - 1          khoang (1, 2)
 *      Nghiem: x ≈ 1.3247179572
 *      Nguon : vi du slide trang 43, bang 5 vong dau (trang 46)
 * ================================================================== */
static double f1 (double x) { return x*x*x - x - 1.0; }
static double df1(double x) { return 3.0*x*x - 1.0; }

/* ==================================================================
 * T2:  f(x) = x^3 + x - 5          khoang (1, 2)
 *      Nghiem: x ≈ 1.5159546734
 *      Nguon : vi du slide trang 46 (bang 5 vong)
 *      Ghi chu: b = 2 dung yen suot, b - a khong hoi tu ve 0
 * ================================================================== */
static double f2 (double x) { return x*x*x + x - 5.0; }
static double df2(double x) { return 3.0*x*x + 1.0; }

/* ==================================================================
 * T3/T4:  f(x) = x^4 - 3x + 1
 *   T3: khoang (0, 1) - Nghiem: x ≈ 0.3376673882  (hoi tu som)
 *   T4: khoang (1, 2) - Nghiem: x ≈ 1.3074861008  (hoi tu cham)
 *      Nguon : bai tap slide trang 48
 *      Ghi chu T4: minh hoa |x_n - x_{n-1}| < eps co the dung som
 *                  (vong 8 voi eps=0.01 → x=1.2958, sai 0.0116 > eps)
 * ================================================================== */
static double f3 (double x) { return x*x*x*x - 3.0*x + 1.0; }
static double df3(double x) { return 4.0*x*x*x - 3.0; }

/* ==================================================================
 * T5:  f(x) = x^3 + 3x^2 + 5       khoang (-4, -3)
 *      Nghiem: x ≈ -3.4256264378
 *      Nguon : bai tap slide trang 49
 * ================================================================== */
static double f5 (double x) { return x*x*x + 3.0*x*x + 5.0; }
static double df5(double x) { return 3.0*x*x + 6.0*x; }

/* ==================================================================
 * T6:  f(x) = 2^x + x - 4          khoang (1, 2)
 *      Nghiem: x ≈ 1.3861483566
 *      Nguon : vi du khoang phan ly slide trang 11
 *      Dung: pow(2,x) = exp(x * log(2))
 * ================================================================== */
static double f6 (double x) { return pow(2.0, x) + x - 4.0; }
static double df6(double x) { return log(2.0) * pow(2.0, x) + 1.0; }

/* ==================================================================
 * T7:  f(x) = 2^x - 4x             khoang (0, 1)
 *      Nghiem: x ≈ 0.3099073796  (hoi tu o vong 4)
 *      Nguon : bai tap slide trang 50
 * ================================================================== */
static double f7 (double x) { return pow(2.0, x) - 4.0 * x; }
static double df7(double x) { return log(2.0) * pow(2.0, x) - 4.0; }

/* ==================================================================
 * T8:  f(x) = x^2 - 2              khoang (1, 2)
 *      Nghiem: x = sqrt(2) ≈ 1.4142135624
 *      Nguon : bai tap slide trang 39 (tinh can bac hai)
 * ================================================================== */
static double f8 (double x) { return x*x - 2.0; }
static double df8(double x) { return 2.0 * x; }

/* ==================================================================
 * T9:  f(x) = cos(x) - x           khoang (0, 1)
 *      Nghiem: x ≈ 0.7390851332  (diem bat dong cua cosine)
 *      Nguon : vi du lap don slide trang 30, ham sieu viet
 * ================================================================== */
static double f9 (double x) { return cos(x) - x; }
static double df9(double x) { return -sin(x) - 1.0; }

/* ==================================================================
 * T10: f(x) = x^10 - 1             khoang (0, 1.3)
 *      Nghiem: x = 1  (hoi tu rat cham, mot dau mut dung yen)
 *      Nguon : minh hoa hoi tu cham khi mot dau mut dung yen
 * ================================================================== */
static double f10 (double x) { return pow(x, 10.0) - 1.0; }
static double df10(double x) { return 10.0 * pow(x, 9.0); }

/* ==================================================================
 * DS_HAM: mang cac ham mau (T1-T10, T3 va T4 dung chung chi so 2)
 *
 * Truong 'ten': hien thi trong menu chuong trinh chinh va trong
 *               bang so sanh cua so_sanh.c
 * Truong 'df' : NULL neu chua dinh nghia dao ham (khong co trong
 *               bo test hien tai, nhung de phong tuong lai)
 * ================================================================== */
MucHam DS_HAM[] = {
    /* ten hien thi            f      df      ghi chu           */
    { "x^3 - x - 1",          f1,    df1  }, /* T1              */
    { "x^3 + x - 5",          f2,    df2  }, /* T2              */
    { "x^4 - 3x + 1",         f3,    df3  }, /* T3 (0,1)        */
                                              /* T4 (1,2) cung ham */
    { "x^3 + 3x^2 + 5",       f5,    df5  }, /* T5              */
    { "2^x + x - 4",          f6,    df6  }, /* T6              */
    { "2^x - 4x",             f7,    df7  }, /* T7              */
    { "x^2 - 2",              f8,    df8  }, /* T8              */
    { "cos(x) - x",           f9,    df9  }, /* T9              */
    { "x^10 - 1",             f10,   df10 }  /* T10             */
};

/* SO_HAM tinh tu kich thuoc mang tai thoi diem bien dich */
const int SO_HAM = (int)(sizeof(DS_HAM) / sizeof(DS_HAM[0]));
