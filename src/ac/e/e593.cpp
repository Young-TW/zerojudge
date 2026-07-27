#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int M, N;
        cin >> M >> N;
        vector<int> R(M), C(N);
        for (int i = 0; i < M; ++i) cin >> R[i];
        for (int j = 0; j < N; ++j) cin >> C[j];

        // 降序排序，取最大的需求優先滿足
        sort(R.begin(), R.end(), greater<int>());
        sort(C.begin(), C.end(), greater<int>());

        // 前綴和
        vector<long long> P(M + 1, 0), Q(N + 1, 0);
        for (int i = 0; i < M; ++i) P[i + 1] = P[i] + R[i];
        for (int j = 0; j < N; ++j) Q[j + 1] = Q[j] + C[j];

        // bestB[a] = 最大的 b 使得前 b 個 C 都 >= a
        vector<int> bestB(M + 1, 0);
        int b = 0;
        for (int a = M; a >= 0; --a) {
            while (b < N && C[b] >= a) {
                ++b;
            }
            bestB[a] = b;
        }

        long long ans = 0;
        for (int a = 0; a <= M; ++a) {
            int b = bestB[a];
            long long val = P[a] + Q[b] - 1LL * a * b;
            if (val > ans) ans = val;
        }
        cout << ans << '\n';
    }
    return 0;
}
