#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    long long W, H;
    while (cin >> n >> m >> W >> H) {
        vector<long long> A(n), B(m);
        for (int i = 0; i < n; ++i) cin >> A[i];
        for (int i = 0; i < m; ++i) cin >> B[i];
        
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        
        sort(B.begin(), B.end());
        B.erase(unique(B.begin(), B.end()), B.end());
        
        if (W % 3 != 0) {
            cout << "impossible\n";
            continue;
        }
        
        long long target1 = 2 * W / 3;
        long long target2 = 4 * W / 3;
        
        vector<long long> valid_A2;
        for (long long a : A) {
            long long b2 = target2 - a;
            if (binary_search(B.begin(), B.end(), b2)) {
                valid_A2.push_back(a);
            }
        }
        
        bool found = false;
        for (long long a1 : A) {
            long long b1 = target1 - a1;
            if (binary_search(B.begin(), B.end(), b1)) {
                auto it = upper_bound(valid_A2.begin(), valid_A2.end(), a1);
                if (it != valid_A2.end()) {
                    long long a2 = *it;
                    if (a2 < target2 - b1) {
                        cout << "(" << a1 << "," << b1 << ")-(" << a2 << "," << target2 - a2 << ")\n";
                        found = true;
                        break;
                    }
                }
            }
        }
        
        if (!found) {
            cout << "impossible\n";
        }
    }
    
    return 0;
}
