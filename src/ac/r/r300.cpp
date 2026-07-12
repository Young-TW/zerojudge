#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, K;
vector<long long> A, B;

bool check(long long R) {
    int lighthouse_idx = 0;
    int used = 0;
    for (int i = 0; i < M; ) {
        if (lighthouse_idx >= N) return false;
        if (A[lighthouse_idx] < B[i] - R) {
            lighthouse_idx++;
        } else if (A[lighthouse_idx] > B[i] + R) {
            return false;
        } else {
            used++;
            if (used > K) return false;
            while (i < M && A[lighthouse_idx] - R <= B[i] && B[i] <= A[lighthouse_idx] + R) {
                i++;
            }
            lighthouse_idx++;
        }
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
