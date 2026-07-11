#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<int> A(n);
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
        }
        sort(A.begin(), A.end(), greater<int>());
        long long dp_prev = 0;
        for (int i = n - 1; i >= 0; --i) {
            long long dp_curr = max((long long)A[i] - dp_prev, dp_prev);
            dp_prev = dp_curr;
        }
        cout << dp_prev << "\n";
    }
    return 0;
}
