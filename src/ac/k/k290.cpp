#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128  = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    int64 R;
    if (!(cin >> N >> R)) return 0;
    vector<int64> A(N);
    int64 sumA = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        sumA += A[i];
    }

    // suffix[i] = sum_{j=i}^{N-1} A[j]
    vector<int64> suffix(N + 1, 0);
    for (int i = N - 1; i >= 0; --i) suffix[i] = suffix[i + 1] + A[i];

    auto can = [&](int64 X0) -> bool {
        i128 cur = X0;
        for (int i = 0; i < N; ++i) {
            if (cur <= 0) return true;
            if (cur > (i128)suffix[i]) return false;          // Lemma 1
            i128 interest = (cur + R - 1) / R;                // ceil(cur / R)
            cur = cur + interest - A[i];
        }
        return cur <= 0;
    };

    int64 low = 0, high = sumA;          // inclusive search interval
    while (low < high) {
        int64 mid = low + (high - low + 1) / 2;
        if (can(mid))
            low = mid;
        else
            high = mid - 1;
    }
    cout << low << '\n';
    return 0;
}
