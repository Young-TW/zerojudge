#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long m, n;
    while (cin >> m >> n) {
        long long sumA = 0, sumG = 0, x;
        for (long long i = 0; i < m; i++) {
            cin >> x;
            sumA += x;
        }
        for (long long i = 0; i < n; i++) {
            cin >> x;
            sumG += x;
        }
        if (m > n && sumA > sumG) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
