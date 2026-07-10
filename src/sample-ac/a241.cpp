#include <iostream>
using namespace std;

int main() {
    int m;
    cin >> m;
    while (m--) {
        long long n;
        cin >> n;
        long long cnt = 0;
        for (long long a = 1; a <= n; a *= 2) {
            for (long long b = a; b <= n; b *= 5) {
                cnt++;
            }
        }
        cout << cnt - 1 << "\n";
    }
    return 0;
}
