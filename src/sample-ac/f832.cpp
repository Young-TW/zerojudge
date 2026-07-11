#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<int> W(N);
        vector<int> C(M);

        for (int i = 0; i < N; ++i) {
            cin >> W[i];
        }
        for (int i = 0; i < M; ++i) {
            cin >> C[i];
        }

        sort(W.begin(), W.end(), greater<int>());
        sort(C.begin(), C.end(), greater<int>());

        long long ans = 0;
        int i = 0, j = 0;
        while (i < N && j < M) {
            if (C[j] >= W[i]) {
                ans += W[i];
                ++i;
                ++j;
            } else {
                ++i;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
