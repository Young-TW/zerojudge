#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<int> A(N + 1, 0);
        for (int i = 2; i <= N; ++i) {
            cin >> A[i];
        }
        
        vector<int> tree(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            for (int j = i; j <= N; j += j & (-j)) {
                tree[j]++;
            }
        }
        
        int bit_mask = 1;
        while (bit_mask <= N) bit_mask <<= 1;
        bit_mask >>= 1;
        
        vector<int> ans(N + 1, 0);
        for (int i = N; i >= 1; --i) {
            int k = A[i] + 1;
            int idx = 0;
            int current_mask = bit_mask;
            while (current_mask > 0) {
                int next = idx + current_mask;
                if (next <= N && tree[next] < k) {
                    k -= tree[next];
                    idx = next;
                }
                current_mask >>= 1;
            }
            int val = idx + 1;
            ans[i] = val;
            
            for (int j = val; j <= N; j += j & (-j)) {
                tree[j]--;
            }
        }
        
        for (int i = 1; i <= N; ++i) {
            cout << ans[i] << "\n";
        }
    }
    
    return 0;
}
