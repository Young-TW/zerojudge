#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long count_ge(long long V, const vector<long long>& A, int n) {
    long long cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (2 * A[i] >= V) {
            cnt++;
        }
    }
    int j = n;
    for (int i = 0; i < n; ++i) {
        if (j <= i + 1) j = i + 1;
        while (j - 1 > i && A[i] + A[j - 1] >= V) {
            j--;
        }
        if (j < n) {
            cnt += (n - j);
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    long long k;
    while (cin >> n >> k) {
        vector<long long> w(n);
        for (int i = 0; i < n; ++i) {
            cin >> w[i];
        }
        sort(w.begin(), w.end());
        long long L = -4000000005LL, R = 4000000005LL;
        long long ansV = L;
        while (L <= R) {
            long long mid = L + (R - L) / 2;
            if (count_ge(mid, w, n) >= k) {
                ansV = mid;
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        if (ansV % 2 == 0) {
            cout << ansV / 2 << "\n" << 1 << "\n";
        } else {
            cout << ansV << "\n" << 2 << "\n";
        }
    }
    return 0;
}
