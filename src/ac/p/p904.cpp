#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    while (cin >> n) {
        long long sum = 0;
        for (long long i = 0; i < n; i++) {
            long long x;
            cin >> x;
            sum += x;
        }

        long long mult = 100; // 以百分比表示,避免浮點誤差
        if (n >= 11 && n <= 20) mult = 95;
        else if (n >= 21 && n <= 40) mult = 90;
        else if (n >= 41) mult = 85;

        long long scaled = sum * mult; // 實際金額 = scaled / 100

        if (scaled >= 1200LL * 100) {
            cout << 1200 << "\n";
        } else {
            // 四捨五入( half up )
            cout << (scaled + 50) / 100 << "\n";
        }
    }
    return 0;
}
