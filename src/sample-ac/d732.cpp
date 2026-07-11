#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K;
    while (cin >> N >> K) {
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        for (int i = 0; i < K; ++i) {
            int X;
            cin >> X;
            auto it = lower_bound(A.begin(), A.end(), X);
            if (it != A.end() && *it == X) {
                cout << (it - A.begin() + 1) << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
    }
    
    return 0;
}
