// d236. 畢氏的定理 — Project Euler #9。
// 找唯一滿足 a+b+c=1000 且 a^2+b^2=c^2 的三元組,輸出 a*b*c。無輸入,固定答案。
// (本地 1.in/1.out 是抓取殘留的 "<無>" 佔位字,真測資要固定乘積。)
#include <iostream>
using namespace std;
int main() {
    for (long long a = 1; a < 1000; ++a)
        for (long long b = a + 1; a + b < 1000; ++b) {
            long long c = 1000 - a - b;
            if (c > b && a * a + b * b == c * c) {
                cout << a * b * c << '\n';
                return 0;
            }
        }
    return 0;
}
