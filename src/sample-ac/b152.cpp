#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> t(n);
        for (int i = 0; i < n; ++i) {
            cin >> t[i];
        }
        
        vector<int> L(n, 1), R(n, 1);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (t[j] < t[i]) {
                    L[i] = max(L[i], L[j] + 1);
                }
            }
        }
        
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j > i; --j) {
                if (t[j] < t[i]) {
                    R[i] = max(R[i], R[j] + 1);
                }
            }
        }
        
        int max_len = 0;
        for (int i = 0; i < n; ++i) {
            max_len = max(max_len, L[i] + R[i] - 1);
        }
        
        cout << n - max_len << "\n";
    }
    
    return 0;
}
