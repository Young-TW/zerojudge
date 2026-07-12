#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) continue;
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            sum += x;
        }
        long long sum100 = sum * 100;
        long long q = sum100 / n;
        long long r = sum100 % n;
        if (r * 2 >= n) {
            q++;
        }
        printf("%g\n", q / 100.0);
    }
    return 0;
}
