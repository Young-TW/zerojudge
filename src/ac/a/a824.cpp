#include <iostream>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long sum_div(int n, int x) {
    if (x == 0) return 0;
    long long k = n / x;
    return (long long)x * k * (k + 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, c;
    while (cin >> a >> b >> c) {
        int g = gcd(a, b);
        long long lcm = (long long)a / g * b;
        long long S = sum_div(c, a) + sum_div(c, b) - sum_div(c, lcm);
        int idx = (S - 1) % 26 + 1;
        cout << (char)('A' + idx - 1) << "\n";
    }
    
    return 0;
}
