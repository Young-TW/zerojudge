#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int arr[32005];

struct Op {
    char type;
    int a, b, c;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while (cin >> N >> M) {
        vector<int> vals;
        vals.reserve(N + M + 5);
        for (int i = 1; i <= N; ++i) {
            cin >> arr[i];
            vals.push_back(arr[i]);
        }
        vector<Op> ops(M);
        for (int i = 0; i < M; ++i) {
            cin >> ops[i].type;
            if (ops[i].type == 'Q') {
                cin >> ops[i].a >> ops[i].b >> ops[i].c;
            } else {
                cin >> ops[i].a >> ops[i].b;
                vals.push_back(ops[i].b);
            }
        }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        
        int B = sqrt(N) + 1;
        int num_blocks = (N + B - 1) / B;
        vector<vector<int>> block(num_blocks);
        for (int i = 1; i <= N; ++i) {
            int b = (i - 1) / B;
            block[b].push_back(arr[i]);
        }
        for (int i = 0; i < num_blocks; ++i) {
            sort(block[i].begin(), block[i].end());
        }
        
        for (int i = 0; i < M; ++i) {
            if (ops[i].type == 'C') {
                int idx = ops[i].a;
                int new_val = ops[i].b;
                int b = (idx - 1) / B;
                int old_val = arr[idx];
                auto it = lower_bound(block[b].begin(), block[b].end(), old_val);
                if (it != block[b].end() && *it == old_val) {
                    block[b].erase(it);
                }
                auto pos = lower_bound(block[b].begin(), block[b].end(), new_val);
                block[b].insert(pos, new_val);
                arr[idx] = new_val;
            } else {
                int l = ops[i].a;
                int r = ops[i].b;
                int k = ops[i].c;
                if (l > r) swap(l, r);
                
                int low = 0, high = vals.size() - 1;
                while (low < high) {
                    int mid = low + (high - low) / 2;
                    int val = vals[mid];
                    
                    int cnt = 0;
                    int b_l = (l - 1) / B;
                    int b_r = (r - 1) / B;
                    
                    if (b_l == b_r) {
                        for (int j = l; j <= r; ++j) {
                            if (arr[j] <= val) cnt++;
                        }
                    } else {
                        for (int j = l; j <= (b_l + 1) * B; ++j) {
                            if (arr[j] <= val) cnt++;
                        }
                        for (int j = b_l + 1; j < b_r; ++j) {
                            cnt += upper_bound(block[j].begin(), block[j].end(), val) - block[j].begin();
                        }
                        for (int j = b_r * B + 1; j <= r; ++j) {
                            if (arr[j] <= val) cnt++;
                        }
                    }
                    
                    if (cnt >= k) {
                        high = mid;
                    } else {
                        low = mid + 1;
                    }
                }
                cout << vals[low] << "\n";
            }
        }
    }
    return 0;
}
