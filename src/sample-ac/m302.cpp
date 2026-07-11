#include <iostream>

using namespace std;

long long find_v(long long k) {
    long long l = 3, r = 1000000000LL;
    while (l < r) {
        long long mid = l + (r - l) / 2;
        if (mid * (mid - 3) / 2 >= k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    while (cin >> T) {
        while (T--) {
            long long N, M;
            cin >> N >> M;
            if (M == N - 1) {
                cout << N - 1 << "\n";
            } else {
                long long k = M - N;
                long long v = find_v(k);
                cout << N - v << "\n";
            }
        }
    }
    return 0;
}
