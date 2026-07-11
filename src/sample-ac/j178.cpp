#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long M;
    while (cin >> N >> M) {
        vector<long long> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        sort(A.begin(), A.end());
        long long ans = M;
        for (int i = 0; i < N; ++i) {
            if (ans > A[i]) {
                ans += A[i];
            } else {
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
