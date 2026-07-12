#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, M;
    while (cin >> N >> M) {
        if (N == 1) {
            cout << 1 << "\n";
        } else if (N == 10) {
            cout << M + 1 << "\n";
        } else {
            long double res = (long double)M * log10l((long double)N);
            cout << (long long)floorl(res + 1e-9L) + 1 << "\n";
        }
    }
    
    return 0;
}
