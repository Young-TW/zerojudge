#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_VAL = 1005;

int bit[MAX_VAL];

void update(int idx, int val) {
    for (; idx < MAX_VAL; idx += idx & -idx)
        bit[idx] += val;
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum += bit[idx];
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    while (cin >> N >> K) {
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        memset(bit, 0, sizeof(bit));
        long long ans = 0;
        
        for (int i = N - 1; i >= 0; --i) {
            int limit = (A[i] - 1) / K;
            if (limit > 1000) limit = 1000;
            if (limit > 0) {
                ans += query(limit);
            }
            update(A[i], 1);
        }

        cout << ans << "\n";
    }

    return 0;
}
