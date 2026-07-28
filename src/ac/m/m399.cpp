// m399. print(max(A,B))  (output-only 自訂位元語言,三運算元 X = f(Y,Z))
// 無分支的 unsigned 64-bit max(A,B):
//   借位判定 A<B(Hacker's Delight):
//     borrow = (~A & B) | (~(A^B) & (A-B)) ,其 bit63 = 1 ⟺ A<B (unsigned)
//   lt = borrow >> 63 (0/1);  mask = ~(lt-1) (全1 若 A<B 否則 0)
//   result = (A & ~mask) | (B & mask)  = A 若 A>=B 否則 B
// ONES = 2^64-1 = 18446744073709551615,用來做 NOT (XOR ONES)。
#include <cstdio>
int main(){
    const char* O = "18446744073709551615";
    printf("XOR C A %s\n", O);   // C = ~A
    printf("AND C C B\n");       // C = ~A & B
    printf("XOR D A B\n");       // D = A ^ B
    printf("XOR E D %s\n", O);   // E = ~(A^B)
    printf("SUB F A B\n");       // F = A - B  (mod 2^64)
    printf("AND E E F\n");       // E = ~(A^B) & (A-B)
    printf("OR C C E\n");        // C = borrow 位元 (bit63 = (A<B))
    printf("RS G C 63\n");       // G = lt (0 或 1)
    printf("SUB T G 1\n");       // T = lt - 1
    printf("XOR M T %s\n", O);   // M = ~T = mask (全1 若 A<B 否則 0)
    printf("XOR N M %s\n", O);   // N = ~mask
    printf("AND P A N\n");       // P = A & ~mask
    printf("AND Q B M\n");       // Q = B & mask
    printf("OR R P Q\n");        // R = max(A,B)
    printf("ANS R\n");
    return 0;
}
