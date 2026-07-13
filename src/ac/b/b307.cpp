#include <iostream>
#include <algorithm>

using namespace std;

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
    int T;
    while (cin >> T) {
        while (T--) {
            long long a, b, q;
            cin >> a >> b >> q;
            long long diff = a - b;
            if (diff < 0) {
                diff = -diff;
            }
            if (diff == 0) {
                cout << "SAFE\n";
            } else {
                long long M = 10007;
                long long g = gcd(diff, M);
                long long period = M / g;
                if (q % period == 0) {
                    cout << "SAFE\n";
                } else {
                    cout << "BOOM\n";
                }
            }
        }
    }
    return 0;
}
