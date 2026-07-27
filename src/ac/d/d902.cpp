#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    while (cin >> N) {
        vector<long long> max1(N, 0), max2(N, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                long long v;
                cin >> v;
                if (v > max1[i]) {
                    max2[i] = max1[i];
                    max1[i] = v;
                } else if (v > max2[i]) {
                    max2[i] = v;
                }
                if (v > max1[j]) {
                    max2[j] = max1[j];
                    max1[j] = v;
                } else if (v > max2[j]) {
                    max2[j] = v;
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            if (max2[i] > ans) ans = max2[i];
        }
        cout << 1 << '\n' << ans << '\n';
    }
    return 0;
}
