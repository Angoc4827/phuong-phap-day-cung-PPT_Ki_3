/* test_day_cung.c - chay toan bo test case, in DAT / KHONG DAT (TV 8, H-08) */

#include <stdio.h> 
#include <math.h> 
#include "day_cung.c"
#include "ham_mau.h"

// Dinh nghia cau truc 1 test case
typedef struct{
    char* id;
    HamSo f; // dinh nghia ham so trong ham_mau 
    double a;
    double b;
    double eps; 
    int nmax; // so buoc lap 
    double mong_doi; 
    TrangThai trang_thai_mong_doi; 
} TestCase; 

void chayKiemThu(){
    // chuyen test cases 
    TestCase ds_test[] = {

    };
    int tong_so_ca = sizeof(ds_test) / sizeof(ds_test[0]);
    int so_ca_dat = 0; 

    for(int i=0; i< tong_so_ca; i++){
        KetQua kq = day_cung(ds_test[i].f, ds_test[i].a, ds_test[i].b, ds_test[i].eps, ds_test[i].nmax, NULL);

        //so sanh ket qua thuc te voi nghiem mong doi 
        if (kq.trang_thai == ds_test[i].trang_thai_mong_doi && fabs(kq.nghiem - ds_test[i].mong_doi <= 1e-8)){
            printf("[%s] DAT\n", ds_test[i].id);
            so_ca_dat++; 
        }
        else{
            printf("[%s] KHONG DAT\n", ds_test[i].id);
        }
    }
    printf("Ket qua: %d/%d ca DAT\n", so_ca_dat, tong_so_ca);
}

