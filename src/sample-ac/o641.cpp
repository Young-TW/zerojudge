#include <iostream>
#include <vector>

using namespace std;

int solve(int k, int L, int* B, int* B_next) {
    if (L <= 0) return 0;
    if (k == 0 || L == 1) return B[0];
    
    int b = k & 1;
    int k_next = k >> 1;
    
    if (b == 0) {
        int L_next = (L + 1) / 2;
        for (int i = 0; i < L_next; ++i) {
            B_next[i] = B[2 * i];
        }
        return solve(k_next, L_next, B_next, B);
    } else {
        int L_next = L / 2;
        for (int i = 0; i < L_next; ++i) {
            B_next[i] = B[2 * i] ^ B[2 * i + 1];
        }
        int res = solve(k_next, L_next, B_next, B);
        if (L % 2 == 1) {
            int t_prime = L / 2;
            if ((t_prime & k_next) == t_prime) {
                res ^= B[L - 1];
            }
        }
        return res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, m;
    while (cin >> n >> k >> m) {
        vector<int> A(n);
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
        }
        
        if (m >= n) {
            cout << 0 << "\n";
            continue;
        }
        
        int L = n - m;
        vector<int> B(L);
        for (int i = 0; i < L; ++i) {
            B[i] = A[m + i];
        }
        
        vector<int> B_next(L);
        int res = solve(k, L, B.data(), B_next.data());
        cout << res << "\n";
    }
    
    return 0;
}
