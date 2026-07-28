// k683. A+B Problem - Revisited  (output-only 自訂位元語言)
// 用只有 AND/OR/XOR/RS/LS/SET/MUL/DIV 的兩運算元 in-place 指令算 A+B。
// 作法:展開 64 次「漣波進位加法」——
//   C = A & B (進位),  A = A ^ B (無進位和),  B = (A&B) << 1
//   不變量 A+B 恆等,每輪進位左移一位,64 輪後 B=0,A 即為 A+B (mod 2^64)。
// 每輪 5 行 × 64 = 320 行,加 ANS 共 321 行 (< 2000 上限)。
#include <cstdio>
int main(){
    for(int i = 0; i < 64; ++i){
        puts("SET C A");   // C = A
        puts("AND C B");   // C = A & B        (進位位元)
        puts("XOR A B");   // A = A ^ B         (無進位和)
        puts("SET B C");   // B = 進位
        puts("LS B 1");    // B = 進位 << 1
    }
    puts("ANS A");
    return 0;
}
