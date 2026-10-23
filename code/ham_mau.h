#ifndef HAM_MAU_H
#define HAM_MAU_H

#include "day_cung.h"   /* lay typedef HamSo */

/* ------------------------------------------------------------------ */
/* MucHam: mot ban ghi mo ta mot ham trong danh sach ham mau           */
/* ------------------------------------------------------------------ */
typedef struct {
    const char *ten;   /* ten hien thi trong menu, vi du "x^3 - x - 1" */
    HamSo       f;     /* con tro toi ham f(x)                          */
    HamSo       df;    /* con tro toi dao ham f'(x); NULL neu chua co   */
} MucHam;

/* ------------------------------------------------------------------ */
/* DS_HAM : mang cac ham mau (T1-T10, T3 va T4 dung chung ham so 2)   */
/* SO_HAM : so phan tu cua DS_HAM (tinh tu sizeof trong ham_mau.c)     */
/* ------------------------------------------------------------------ */
extern MucHam    DS_HAM[];
extern const int SO_HAM;

/*
 * Chi so trong DS_HAM:
 *   0  x^3 - x - 1        T1  khoang (1, 2)
 *   1  x^3 + x - 5        T2  khoang (1, 2)
 *   2  x^4 - 3x + 1       T3  khoang (0, 1)
 *                          T4  khoang (1, 2)   <- cung ham nay
 *   3  x^3 + 3x^2 + 5     T5  khoang (-4, -3)
 *   4  2^x + x - 4        T6  khoang (1, 2)
 *   5  2^x - 4x           T7  khoang (0, 1)
 *   6  x^2 - 2            T8  khoang (1, 2)
 *   7  cos(x) - x         T9  khoang (0, 1)
 *   8  x^10 - 1           T10 khoang (0, 1.3)
 */

#endif /* HAM_MAU_H */
