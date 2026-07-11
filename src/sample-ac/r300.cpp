#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, K;
vector<long long> A, B;

bool check(long long R) {
    int used = 0;
    int j = 0;
    while (j < M) {
        if (used >= K) return false;
        // 挑選能照到目前這座島（B[j]）且座標最大的燈塔，
        // 使覆蓋範圍盡量往右延伸，才能用最少燈塔覆蓋所有島。
        long long target = B[j] + R;
        int i = (int)(upper_bound(A.begin(), A.end(), target) - A.begin()) - 1;
        if (i < 0) return false;              // 沒有燈塔的座標 <= B[j]+R
        if (A[i] < B[j] - R) return false;     // 最靠右的候選也照不到 B[j]
        long long cover_until = A[i] + R;
        while (j < M && B[j] <= cover_until) {
            j++;
        }
        used++;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N >> M >> K) {
        A.resize(N);
        B.resize(M);
        for (int i = 0; i < N; i++) cin >> A[i];
        for (int i = 0; i < M; i++) cin >> B[i];

        if (M == 0) {
            cout << 0 << "\n";
            continue;
        }
        if (N == 0 || K == 0) {
            cout << -1 << "\n";
            continue;
        }

        long long low = 0, high = 1000000000LL;
        long long ans = -1;
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
