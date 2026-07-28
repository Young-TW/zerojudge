// o640. Re: A+B Problem — 兩運算元 in-place 位元語言,且「隨機一行會被忽略(跳過)」,ANS 保證不被跳過。
// A,B <= 2^60-1,和 <= 2^61,不溢位。
// 容錯策略:三重模組冗餘 + 逐位多數決。
//   1) 獨立算三份 A+B → 暫存 C、F、I(各用自己的工作暫存器,64 次漣波進位加法)。
//      任一行被丟只會毀損「其中一份」Si;另兩份仍正確。
//   2) 逐位多數決 maj(C,F,I) = (C&F) | ((C|F)&I)。只用 SET/AND/OR(重複執行等冪),
//      每行「寫兩次」;若被丟的正好是 maj 階段某行,孿生行仍執行一次→等冪→結果正確,
//      且此時三份 Si 皆正確。無論被丟的行落在哪,最終 ANS 都是正確的 A+B。
// 行數 ≈ 3*(2+64*5) + 12 + 1 = 979 < 3000。
#include <cstdio>
int main(){
    // 三份獨立加法:(a,b,carry,result)
    // S1: C D E  -> C ;  S2: F G H -> F ;  S3: I J K -> I
    const char* av[3] = {"C","F","I"};
    const char* bv[3] = {"D","G","J"};
    const char* cv[3] = {"E","H","K"};
    for(int s = 0; s < 3; ++s){
        printf("SET %s A\n", av[s]);      // a = A
        printf("SET %s B\n", bv[s]);      // b = B
        for(int i = 0; i < 64; ++i){
            printf("SET %s %s\n", cv[s], av[s]);   // c = a
            printf("AND %s %s\n", cv[s], bv[s]);   // c = a & b   (進位)
            printf("XOR %s %s\n", av[s], bv[s]);   // a = a ^ b   (無進位和)
            printf("SET %s %s\n", bv[s], cv[s]);   // b = 進位
            printf("LS %s 1\n",  bv[s]);           // b = 進位 << 1
        }
    }
    // maj(C,F,I) into L,使用 M 暫存;只用等冪 SET/AND/OR,每行重複一次以容錯。
    const char* maj[] = {
        "SET L C",   // L = C
        "AND L F",   // L = C & F
        "SET M C",   // M = C
        "OR M F",    // M = C | F
        "AND M I",   // M = (C|F) & I
        "OR L M",    // L = (C&F) | ((C|F)&I) = maj
    };
    for(int i = 0; i < 6; ++i){ puts(maj[i]); puts(maj[i]); }  // 每行寫兩次
    printf("ANS L\n");
    return 0;
}
