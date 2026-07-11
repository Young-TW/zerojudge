#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Beaver {
    int id;
    int H;
    int W;
    bool reachable = false;
    bool is_end = false;
};

struct BIT {
    vector<int> tree;
    int n;
    void init(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }
    void update(int i, int delta) {
        for (; i <= n; i += i & (-i))
            tree[i] += delta;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & (-i))
            sum += tree[i];
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<Beaver> beavers(N);
        vector<int> ws(N);
        
        for (int i = 0; i < N; ++i) {
            beavers[i].id = i + 1;
            cin >> beavers[i].H >> beavers[i].W;
            ws[i] = beavers[i].W;
        }
        
        sort(ws.begin(), ws.end());
        ws.erase(unique(ws.begin(), ws.end()), ws.end());
        for (int i = 0; i < N; ++i) {
            beavers[i].W = lower_bound(ws.begin(), ws.end(), beavers[i].W) - ws.begin() + 1;
        }
        
        sort(beavers.begin(), beavers.end(), [](const Beaver& a, const Beaver& b) {
            if (a.H != b.H) return a.H < b.H;
            return a.W < b.W;
        });
        
        BIT bit;
        bit.init(ws.size());
        
        for (int i = 0; i < N; ) {
            int j = i;
            while (j < N && beavers[j].H == beavers[i].H) {
                j++;
            }
            for (int k = i; k < j; ++k) {
                if (beavers[k].id == M) {
                    beavers[k].reachable = true;
                } else {
                    if (beavers[k].W > 1) {
                        if (bit.query(beavers[k].W - 1) > 0) {
                            beavers[k].reachable = true;
                        }
                    }
                }
            }
            for (int k = i; k < j; ++k) {
                if (beavers[k].reachable) {
                    bit.update(beavers[k].W, 1);
                }
            }
            i = j;
        }
        
        int max_W = 0;
        for (int i = N - 1; i >= 0; ) {
            int j = i;
            while (j >= 0 && beavers[j].H == beavers[i].H) {
                j--;
            }
            for (int k = i; k > j; --k) {
                if (beavers[k].reachable) {
                    if (beavers[k].W >= max_W) {
                        beavers[k].is_end = true;
                    }
                }
            }
            for (int k = i; k > j; --k) {
                if (beavers[k].reachable) {
                    max_W = max(max_W, beavers[k].W);
                }
            }
            i = j;
        }
        
        vector<int> ans;
        for (int i = 0; i < N; ++i) {
            if (beavers[i].is_end) {
                ans.push_back(beavers[i].id);
            }
        }
        sort(ans.begin(), ans.end());
        
        cout << ans.size() << "\n";
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i] << (i == ans.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}
