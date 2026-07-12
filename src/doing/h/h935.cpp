#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long N, K;
        cin >> N >> K;

        if (N == 1) {
            cout << 1 << '\n';
            continue;
        }

        long long low = 1, high = N;
        long long best = 0;
        while (low <= high) {
            long long mid = (low + high) / 2;
            long long total = mid * (mid + 1) * (2 * mid + 1) / 6;

            if (total <= K) {
                best = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if (best == N) {
            cout << N * (N + 1) / 2 << '\n';
            continue;
        }

        long long sum = best * (best + 1) / 2;
        long long weight = best * (best + 1) * (2 * best + 1) / 6;

        if (weight > K) {
            cout << sum - 1 << '\n';
            continue;
        }

        long long remaining = K - weight;
        long long next = best + 1;
        if (next <= N && next * next <= remaining) {
            sum += next;
        } else {
            long long max_add = min(N - best, remaining / (best + 1));
            sum += max_add;
        }

        cout << sum << '\n';
    }

    return 0;
}
