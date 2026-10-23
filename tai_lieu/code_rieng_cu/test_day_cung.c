/* test_day_cung.c - chay toan bo test case, in DAT / KHONG DAT (TV 8, H-08) */
#ifndef TEST_DAY_CUNG_H
#define TEST_DAY_CUNG_H

#include <stdio.h> 
#include <math.h> 
#include "day_cung.c"
#include "ham_mau.h" //chứa f1,f2,... 

// Dinh nghia cau truc 1 test case
typedef struct{
    char* id;
    HamSo f; // dinh nghia ham so trong ham_mau.h 
    double a;
    double b;
    double eps;  //sai so cho phep (theo test mau: 1e-10)
    int nmax; // so buoc lap 
    double mong_doi; // nghiem mong doi 
    TrangThai trang_thai_mong_doi; 
} TestCase; 

void chayKiemThu(){
    // chuyen test cases 
    TestCase ds_test[] = {
        // {id, ham so f, a, b, eps, nmax, nghiem mong doi, trang thai mong doi}
        {"T1",  f_t1,   1.0,   2.0,   1e-10, 27,  1.3247179572, HOAN_THANH},
        {"T2",  f_t2,   1.0,   2.0,   1e-10, 17,  1.5159802277, HOAN_THANH},
        {"T3",  f_t3,   0.0,   1.0,   1e-10, 9,   0.3376667656, HOAN_THANH},
        {"T4",  f_t4,   1.0,   2.0,   1e-10, 47,  1.3074861008, HOAN_THANH},
        {"T5",  f_t5,  -4.0,  -3.0,   1e-10, 17,  -3.4259887574, HOAN_THANH},
        {"T6",  f_t6,   1.0,   2.0,   1e-10, 13,  1.3861669801, HOAN_THANH},
        {"T7",  f_t7,   0.0,   1.0,   1e-10, 8,   0.3099069324, HOAN_THANH},
        {"T8",  f_t8,   1.0,   2.0,   1e-10, 14,  1.4142135624, HOAN_THANH},
        {"T9",  f_t9,   0.0,   1.0,   1e-10, 9,   0.7390851332, HOAN_THANH},
        {"T10", f_t10,  0.0,   1.3,   1e-10, 91,  1.0000000000, HOAN_THANH}, // Hội tụ chậm
        {"T11", f_t11, -1.0,   1.0,   1e-10, 0,   0.0000000000, KHOANG_KHONG_HOP_LE}, // f(a)*f(b) > 0
        {"T12", f_t12,  2.0,   3.0,   1e-10, 0,   2.0000000000, HOAN_THANH}, // Đầu mút là nghiệm
        {"T13", f_t13,  2.0,   1.0,   0.0,   0,   0.0000000000, KHOANG_KHONG_HOP_LE}, // Lỗi đầu vào (a >= b, eps <= 0)
        {"T14", f_t1,   1.0,   2.0,   1e-10, 5,   0.0000000000, VUOT_QUA_SO_BUOC}, // Vượt quá N_max = 5
        {"T15", f_t1,   1.0,   2.0,   1e-10, 100, 1.3247179572, HOAN_THANH}
          // T1 với cơ chế chống treo (hoặc điều kiện b-a < epsilon kèm nmax)

    };
    int tong_so_ca = sizeof(ds_test) / sizeof(ds_test[0]);
    int so_ca_dat = 0; 

    for(int i=0; i< tong_so_ca; i++){
        KetQua kq = day_cung(ds_test[i].f, ds_test[i].a, ds_test[i].b, ds_test[i].eps, ds_test[i].nmax);

        //so sanh ket qua thuc te voi nghiem mong doi 
        if (kq.trang_thai == ds_test[i].trang_thai_mong_doi && fabs(kq.nghiem - ds_test[i].mong_doi) <= 1e-8){
            printf("[%s] DAT\n", ds_test[i].id);
            so_ca_dat++; 
        }
        else{
            printf("[%s] KHONG DAT\n", ds_test[i].id);
        }
    }
    printf("Ket qua: %d/%d ca DAT\n", so_ca_dat, tong_so_ca);
}

#endif 