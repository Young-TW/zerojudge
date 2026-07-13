#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int parent[65540];
int sz[65540];

int find_set(int x) {
    if (parent[x] != x) {
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

void union_set(int x, int y) {
    int px = find_set(x);
    int py = find_set(y);
    if (px != py) {
        if (sz[px] < sz[py]) {
            swap(px, py);
        }
        parent[py] = px;
        sz[px] += sz[py];
    }
}

struct Op {
    char type;
    int val;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<pair<int, int>> edges(M + 1);
        for (int i = 1; i <= M; ++i) {
            cin >> edges[i].first >> edges[i].second;
        }
        
        int Q;
        cin >> Q;
        vector<Op> ops(Q);
        vector<bool> deleted(M + 1, false);
        
        for (int i = 0; i < Q; ++i) {
            char type;
            int val;
            cin >> type >> val;
            ops[i] = {type, val};
            if (type == 'D') {
                deleted[val] = true;
            }
        }
        
        for (int i = 1; i <= N; ++i) {
            parent[i] = i;
            sz[i] = 1;
        }
        
        for (int i = 1; i <= M; ++i) {
            if (!deleted[i]) {
                union_set(edges[i].first, edges[i].second);
            }
        }
        
        vector<int> ans;
        for (int i = Q - 1; i >= 0; --i) {
            if (ops[i].type == 'Q') {
                ans.push_back(sz[find_set(ops[i].val)]);
            } else {
                union_set(edges[ops[i].val].first, edges[ops[i].val].second);
            }
        }
        
        for (int i = ans.size() - 1; i >= 0; --i) {
            cout << ans[i] << "\n";
        }
    }
    
    return 0;
}
