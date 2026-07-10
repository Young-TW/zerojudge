#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    while (cin >> N) {
        if (N == -1) break;
        long long F = 5LL * (N + 1);
        int months = 0;
        while (F > 0) {
            long long burn = (F + 4) / 5; // ceil(F/5)
            F -= burn;
            months++;
        }
        cout << months << "\n";
    }
    return 0;
}
