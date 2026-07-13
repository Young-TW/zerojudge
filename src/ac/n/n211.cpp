#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

long long cost(long long A, long long B, long long Ca, long long Cb) {
    if (A == 1 && B == 1) return 0;
    if (A == 1) return (B - 1) * Cb;
    if (B == 1) return (A - 1) * Ca;
    if (A > B) {
        long long k = (A - 1) / B;
        long long r = A - k * B;
        return k * Ca + cost(r, B, Ca, Cb);
    } else {
        long long k = (B - 1) / A;
        long long r = B - k * A;
        return k * Cb + cost(A, r, Ca, Cb);
    }
}

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long X, Ca, Cb;
    while (cin >> X >> Ca >> Cb) {
        long long ans = -1;
        long long target = X + 2;
        for (long long A = 1; A <= target - 1; ++A) {
            long long B = target - A;
            if (gcd(A, B) == 1) {
                long long c = cost(A, B, Ca, Cb);
                if (ans == -1 || c < ans) {
                    ans = c;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
