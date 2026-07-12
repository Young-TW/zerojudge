#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

void solve() {
    int M, N;
    if (!(cin >> M >> N)) return;
    vector<int> R(M), C(N);
    for (int i = 0; i < M; ++i) cin >> R[i];
    for (int i = 0; i < N; ++i) cin >> C[i];
    
    sort(R.begin(), R.end(), greater<int>());
    sort(C.begin(), C.end(), greater<int>());
    
    int ans = 0;
    for (int i = 0; i < M; ++i) {
        if (R[i] == 0) break;
        for (int j = 0; j < N && R[i] > 0; ++j) {
            if (C[j] > 0) {
                R[i]--;
                C[j]--;
                ans++;
            }
        }
    }
    
    ans += accumulate(R.begin(), R.end(), 0);
    ans += accumulate(C.begin(), C.end(), 0);
    
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
