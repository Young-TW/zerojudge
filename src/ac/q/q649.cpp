#include <iostream>

using namespace std;

long long min_sum(long long h, long long len) {
    if (len <= 0) return 0;
    if (h <= 1) return len;
    if (h <= len) {
        return (h + 1) * h / 2 + (len - h);
    } else {
        long long peak = h - len + 1;
        return (h + peak) * len / 2;
    }
}

bool check(long long h, long long N, long long M, long long K) {
    long long L = K - 1;
    long long R = N - K;
    long long sum = h + min_sum(h - 1, L) + min_sum(h - 1, R);
    return sum <= M;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            long long N, M, K;
            cin >> N >> M >> K;
            long long low = 1, high = M, ans = 1;
            while (low <= high) {
                long long mid = low + (high - low) / 2;
                if (check(mid, N, M, K)) {
                    ans = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
