#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100005;
const int INF = 2e9 + 7;

int n, m;
int a[MAXN];
int prev_occ[MAXN], next_occ[MAXN];
int last_pos[MAXN];

// 莫隊算法相關
int BLOCK_SIZE;
int cnt[MAXN * 2]; // 計數陣列，需要偏移處理負數或大數，但題目說 int 範圍，離散化後用索引
int max_val = -INF;
int ans[MAXN];

struct Query {
    int l, r, id;
    int block_idx;

    bool operator<(const Query& other) const {
        if (block_idx != other.block_idx)
            return block_idx < other.block_idx;
        return (block_idx & 1) ? (r < other.r) : (r > other.r);
    }
};

// 離散化
vector<int> values;
int get_id(int x) {
    return lower_bound(values.begin(), values.end(), x) - values.begin();
}

// 用於快速查詢區間最大值且出現次數為 1 的數據結構
// 由於莫隊移動指針時需要動態維護「出現次數為 1 的最大值」，
// 單純的計數陣列無法高效查詢。
// 我們可以使用一個線段樹或分塊來維護每個值的出現次數，並查詢滿足條件的最大值。
// 但這裡值域經過離散化後最大為 N，我們可以對「值」建立線段樹。
// 線段樹的每個葉節點代表一個離散化後的值，儲存該值在當前區間的出現次數。
// 每個內部節點儲存該區間內「出現次數為 1 的最大值」（若無則為 -1）。

int tree_max[4 * MAXN]; // 儲存該區間內出現次數為 1 的最大原始值
int freq_in_range[4 * MAXN]; // 其實不需要，因為我們有全局 cnt 陣列，但線段樹需要知道子節點狀態
// 修正：線段樹應該維護的是：對於每個值 v (離散化後)，如果 cnt[v] == 1，則貢獻為 values[v]，否則貢獻為 -1。
// 然後區間最大值就是答案。

void update_node(int node, int l, int r, const vector<int>& vals, const int* global_cnt) {
    if (l == r) {
        if (global_cnt[l] == 1) {
            tree_max[node] = vals[l];
        } else {
            tree_max[node] = -1;
        }
        return;
    }
    tree_max[node] = max(tree_max[2 * node], tree_max[2 * node + 1]);
}

void build(int node, int l, int r, const vector<int>& vals, const int* global_cnt) {
    if (l == r) {
        if (global_cnt[l] == 1) {
            tree_max[node] = vals[l];
        } else {
            tree_max[node] = -1;
        }
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid, vals, global_cnt);
    build(2 * node + 1, mid + 1, r, vals, global_cnt);
    tree_max[node] = max(tree_max[2 * node], tree_max[2 * node + 1]);
}

void point_update(int node, int l, int r, int idx, const vector<int>& vals, const int* global_cnt) {
    if (l == r) {
        if (global_cnt[idx] == 1) {
            tree_max[node] = vals[idx];
        } else {
            tree_max[node] = -1;
        }
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid) point_update(2 * node, l, mid, idx, vals, global_cnt);
    else point_update(2 * node + 1, mid + 1, r, idx, vals, global_cnt);
    tree_max[node] = max(tree_max[2 * node], tree_max[2 * node + 1]);
}

// 莫隊移動函數
void add(int idx, const vector<int>& vals) {
    int val_id = get_id(a[idx]);
    int old_cnt = cnt[val_id];
    cnt[val_id]++;
    
    // 只有當計數變化影響到「是否為 1」時才更新線段樹
    if (old_cnt == 0) {
        // 0 -> 1: 現在變成唯一，需要更新線段樹
        point_update(1, 0, (int)values.size() - 1, val_id, vals, cnt);
    } else if (old_cnt == 1) {
        // 1 -> 2: 不再是唯一，需要更新線段樹
        point_update(1, 0, (int)values.size() - 1, val_id, vals, cnt);
    }
    // 其他情況 (2->3, 3->4...) 不影響「是否為 1」的狀態，無需更新線段樹
}

void remove(int idx, const vector<int>& vals) {
    int val_id = get_id(a[idx]);
    int old_cnt = cnt[val_id];
    cnt[val_id]--;

    if (old_cnt == 1) {
        // 1 -> 0: 不再是唯一（變成沒有），需要更新
        point_update(1, 0, (int)values.size() - 1, val_id, vals, cnt);
    } else if (old_cnt == 2) {
        // 2 -> 1: 變成唯一，需要更新
        point_update(1, 0, (int)values.size() - 1, val_id, vals, cnt);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        values.push_back(a[i]);
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    vector<Query> queries(m);
    BLOCK_SIZE = max(1, (int)(n / sqrt(m)));
    if (BLOCK_SIZE == 0) BLOCK_SIZE = 1;

    for (int i = 0; i < m; ++i) {
        cin >> queries[i].l >> queries[i].r;
        if (queries[i].l > queries[i].r) swap(queries[i].l, queries[i].r);
        queries[i].id = i;
        queries[i].block_idx = queries[i].l / BLOCK_SIZE;
    }

    sort(queries.begin(), queries.end());

    // 初始化計數陣列和線段樹
    // cnt 全域變數已初始化為 0
    build(1, 0, (int)values.size() - 1, values, cnt);

    int cur_l = 1;
    int cur_r = 0;

    for (const auto& q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l, values);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r, values);
        }
        while (cur_l < q.l) {
            remove(cur_l, values);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r, values);
            cur_r--;
        }

        int res = tree_max[1];
        ans[q.id] = (res == -1 ? 0 : res);
    }

    for (int i = 0; i < m; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}
