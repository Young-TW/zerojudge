#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        int K;
        cin >> K;
        vector<int> P_vals(K);
        int max_P = 0;
        for (int i = 0; i < K; ++i) {
            cin >> P_vals[i];
            if (P_vals[i] > max_P) {
                max_P = P_vals[i];
            }
        }
        
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        
        vector<bool> win(max_P + 1, false);
        for (int i = 1; i <= max_P; ++i) {
            for (int x : A) {
                if (x > i) break;
                if (!win[i - x]) {
                    win[i] = true;
                    break;
                }
            }
        }
        
        for (int i = 0; i < K; ++i) {
            if (win[P_vals[i]]) {
                cout << "OpenChan\n";
            } else {
                cout << "Kitty\n";
            }
        }
    }
    return 0;
}
