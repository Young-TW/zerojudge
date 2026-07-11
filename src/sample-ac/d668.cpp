#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    while (cin >> N >> Q) {
        vector<int> arr(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> arr[i];
        }
        
        vector<int> log2_val(N + 2);
        log2_val[1] = 0;
        for (int i = 2; i <= N; ++i) {
            log2_val[i] = log2_val[i / 2] + 1;
        }
        
        int K = log2_val[N] + 1;
        vector<vector<int>> st_max(N + 1, vector<int>(K));
        vector<vector<int>> st_min(N + 1, vector<int>(K));
        
        for (int i = 1; i <= N; ++i) {
            st_max[i][0] = arr[i];
            st_min[i][0] = arr[i];
        }
        
        for (int j = 1; j < K; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= N; ++i) {
                st_max[i][j] = max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1]);
                st_min[i][j] = min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1]);
            }
        }
        
        for (int k = 0; k < Q; ++k) {
            int a, b;
            cin >> a >> b;
            int len = b - a + 1;
            int j = log2_val[len];
            int mx = max(st_max[a][j], st_max[b - (1 << j) + 1][j]);
            int mn = min(st_min[a][j], st_min[b - (1 << j) + 1][j]);
            cout << mx - mn << "\n";
        }
    }
    
    return 0;
}
