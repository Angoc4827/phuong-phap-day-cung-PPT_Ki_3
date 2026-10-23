# Bộ test case cho phương pháp dây cung 
# Môn học: Phương pháp tính - Khoa CNTT, ĐH Kinh tế Quốc dân 
# Thành viên thực hiện: TV 8 

| #  | f(x) | Khoảng | Nghiệm mong đợi | Vòng lặp (ε=10⁻¹⁰) | Nguồn / mục đích |
| T1 | x³ − x − 1 | (1, 2) | 1,3247179572 | 27 | Ví dụ slide tr. 43: x₁ = 1,1667; x₂ = 1,2531 |
| T2 | x³ + x − 5 | (1, 2) | 1,5159802277 | 17 | Ví dụ slide tr. 46: so khớp bảng 5 dòng đầu |
| T3 | x⁴ − 3x + 1 | (0, 1) | 0,3376667656 | 9 | Bài tập tr. 48 (ε = 10⁻²: 0,3381 sau 3 vòng) |
| T4 | x⁴ − 3x + 1 | (1, 2) | 1,3074861008 | 47 | Bài tập tr. 48, **minh họa dừng sớm** khi ε = 10⁻² (ra 1,2958) |
| T5 | x³ + 3x² + 5 | (−4, −3) | −3,4259887574 | 17 | Bài tập tr. 49 (ε = 10⁻²: −3,4244) |
| T6 | 2ˣ + x − 4 | (1, 2) | 1,3861669801 | 13 | Ví dụ khoảng phân ly tr. 11 |
| T7 | 2ˣ − 4x | (0, 1) | 0,3099069324 | 8 | Bài tập tr. 50 (đổi sang dây cung) |
| T8 | x² − 2 | (1, 2) | 1,4142135624 | 14 | Bài tập tr. 39: tính √2 |
| T9 | cos x − x | (0, 1) | 0,7390851332 | 9 | Ví dụ lặp đơn tr. 30, hàm siêu việt |
| T10 | x¹⁰ − 1 | (0; 1,3) | 1 | 91 | Hội tụ rất chậm, một đầu mút đứng yên |
| T11 | x² + 1 | (−1, 1) | (lỗi) | — | f(a)·f(b) > 0 → KHONG_DOI_DAU |
| T12 | x² − 4 | (2, 3) | 2 | 0 | Đầu mút chính là nghiệm |
| T13 | bất kỳ | a ≥ b, ε ≤ 0, N_max = 0 | (lỗi) | — | DAU_VAO_SAI |
| T14 | T1 với N_max = 5 | (1, 2) | (chưa đạt) | 5 | VUOT_NMAX |
| T15 | x³ − x − 1 dùng `b − a < ε` | (1, 2) | (không dừng) | — | Chứng minh lỗi của sơ đồ tr. 45 (chạy có N_max để không treo) |


Tiêu chí ĐẠT: `|x − x_mong_đợi| ≤ 10⁻⁸` với ε = 10⁻¹⁰, đúng trạng thái với các ca lỗi. Thêm bảng so sánh số vòng dây cung / chia đôi / Newton cho T1–T8.

Lưu ý khi đối chiếu bảng slide tr. 46: dòng cuối (a = 1,514032, x = 1,5143843) không khớp dòng trên; chạy đúng thì vòng 6 là a = 1,5155206, x = 1,5158718. `[SUY LUẬN]` từ chạy lại công thức; nên ghi nhận nhẹ nhàng trong báo cáo.
