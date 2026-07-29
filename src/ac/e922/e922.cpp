// e922. pA. ISO日曆系統(一)
// 每年皆 365 天，故 1/1 的星期會逐年循環經過全部 7 種。
// 一個日期在「所有年份」週數相同 <=> 對 1/1 為任一星期時該日期週數皆相同。
// ISO(依題意「最靠近 1/1 的星期一為第一週的星期一」)下，第一週星期一相對
// 1/1 的位移落在 {-3,-2,-1,0,1,2,3}。設日期距 1/1 的位移為 n(1/1 為 0),
// 週數 = floor((n - m)/7)+1。要對 m 的 7 個連續值皆相同，需 n-3..n+3 同屬一個
// 7 的整除區塊，即 n ≡ 3 (mod 7)。此處直接以模擬 7 種起始星期驗證後輸出。
#include <bits/stdc++.h>
using namespace std;

int mlen[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31}; // 非閏年

int floordiv(int a, int b) {
    int q = a / b, r = a % b;
    if (r != 0 && ((r < 0) != (b < 0))) q--;
    return q;
}

int main() {
    for (int month = 1; month <= 2; month++) {
        for (int day = 1; day <= mlen[month]; day++) {
            int n = 0;
            for (int mm = 1; mm < month; mm++) n += mlen[mm];
            n += day - 1; // 距 1/1 的位移
            set<int> weeks;
            for (int d = 0; d < 7; d++) {         // 1/1 星期(Mon=0..Sun=6)
                int m1 = (d <= 3) ? -d : 7 - d;   // 第一週星期一相對 1/1 位移
                weeks.insert(floordiv(n - m1, 7) + 1);
            }
            if (weeks.size() == 1)                 // 各年週數皆相同
                printf("%d/%d\n", month, day);
        }
    }
    return 0;
}
