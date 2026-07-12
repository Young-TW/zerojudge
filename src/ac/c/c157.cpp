#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    bool first = true;
    
    while (cin >> n >> m >> k) {
        if (!first) {
            cout << "\n";
        }
        first = false;
        
        string A, B;
        cin >> A >> B;
        
        int K = k + 1;
        int size = (m + 1) * K;
        
        vector<int> cur0(size, 0), cur1(size, 0);
        vector<int> nxt0(size, 0), nxt1(size, 0);
        
        cur0[0] = 1;
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int p = 0; p <= k; ++p) {
                    int id = j * K + p;
                    nxt0[id] = cur0[id] + cur1[id];
                    if (nxt0[id] >= MOD) {
                        nxt0[id] -= MOD;
                    }
                    nxt1[id] = 0;
                }
            }
            
            for (int j = 1; j <= m; ++j) {
                for (int p = 1; p <= k; ++p) {
                    if (A[i-1] == B[j-1]) {
                        int val = cur1[(j-1) * K + p] + nxt0[(j-1) * K + p - 1];
                        if (val >= MOD) {
                            val -= MOD;
                        }
                        nxt1[j * K + p] = val;
                    }
                }
            }
            
            cur0.swap(nxt0);
            cur1.swap(nxt1);
        }
        
        int ans = cur0[m * K + k] + cur1[m * K + k];
        if (ans >= MOD) {
            ans -= MOD;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
