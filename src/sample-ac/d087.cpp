#include <iostream>
using namespace std;

long long ipow_checked(long long base, int exp, long long limit) {
    if (base <= 0) return -1;
    if (base == 1) return 1;
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        if (result > limit / base) return -1;
        result *= base;
    }
    return result;
}

long long find_root(long long target, int k) {
    if (target == 1) return 1;
    long long lo = 2, hi = target;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        long long p = ipow_checked(mid, k, target);
        if (p == -1) {
            hi = mid - 1;
        } else if (p == target) {
            return mid;
        } else if (p < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}

int main() {
    long long H, W;
    while (cin >> H >> W && (H || W)) {
        if (H == 1) {
            cout << 0 << " " << 1 << endl;
            continue;
        }
        
        for (int k = 1; k <= 63; k++) {
            long long a = find_root(H, k);
            if (a >= 2) {
                long long b = a - 1;
                long long p = ipow_checked(b, k, W);
                if (p == W) {
                    long long N = b;
                    long long not_working;
                    if (N == 1) not_working = k;
                    else not_working = (W - 1) / (N - 1);
                    long long total_height = H * (N + 1) - W * N;
                    cout << not_working << " " << total_height << endl;
                    break;
                }
            }
        }
    }
    return 0;
}
