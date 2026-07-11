#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 200005; 
const int INF = 1e9 + 7;

struct Node {
    int val;
    int priority;
    int size;
    int max_val;
    int min_val;
    long long sum;
    int lazy_add;
    bool lazy_rev;
    int ch[2];
    
    Node() : val(0), priority(0), size(0), max_val(-INF), min_val(INF), sum(0), lazy_add(0), lazy_rev(false) {
        ch[0] = ch[1] = 0;
    }
} tree[MAXN];

int root_pool = 0;
int roots[MAXN]; 
int n, q;
long long last_ans = 0;

int new_node(int v) {
    int id = ++root_pool;
    tree[id].val = v;
    tree[id].priority = rand();
    tree[id].size = 1;
    tree[id].max_val = v;
    tree[id].min_val = v;
    tree[id].sum = v;
    tree[id].lazy_add = 0;
    tree[id].lazy_rev = false;
    tree[id].ch[0] = tree[id].ch[1] = 0;
    return id;
}

void push_up(int u) {
    if (!u) return;
    tree[u].size = 1 + tree[tree[u].ch[0]].size + tree[tree[u].ch[1]].size;
    tree[u].max_val = tree[u].val;
    tree[u].min_val = tree[u].val;
    tree[u].sum = tree[u].val;
    
    if (tree[u].ch[0]) {
        tree[u].max_val = max(tree[u].max_val, tree[tree[u].ch[0]].max_val);
        tree[u].min_val = min(tree[u].min_val, tree[tree[u].ch[0]].min_val);
        tree[u].sum += tree[tree[u].ch[0]].sum;
    }
    if (tree[u].ch[1]) {
        tree[u].max_val = max(tree[u].max_val, tree[tree[u].ch[1]].max_val);
        tree[u].min_val = min(tree[u].min_val, tree[tree[u].ch[1]].min_val);
        tree[u].sum += tree[tree[u].ch[1]].sum;
    }
}

void push_down(int u) {
    if (!u) return;
    
    if (tree[u].lazy_add != 0) {
        int add_val = tree[u].lazy_add;
        if (tree[u].ch[0]) {
            tree[tree[u].ch[0]].val += add_val;
            tree[tree[u].ch[0]].max_val += add_val;
            tree[tree[u].ch[0]].min_val += add_val;
            tree[tree[u].ch[0]].sum += (long long)add_val * tree[tree[u].ch[0]].size;
            tree[tree[u].ch[0]].lazy_add += add_val;
        }
        if (tree[u].ch[1]) {
            tree[tree[u].ch[1]].val += add_val;
            tree[tree[u].ch[1]].max_val += add_val;
            tree[tree[u].ch[1]].min_val += add_val;
            tree[tree[u].ch[1]].sum += (long long)add_val * tree[tree[u].ch[1]].size;
            tree[tree[u].ch[1]].lazy_add += add_val;
        }
        tree[u].lazy_add = 0;
    }
    
    if (tree[u].lazy_rev) {
        swap(tree[u].ch[0], tree[u].ch[1]);
        if (tree[u].ch[0]) tree[tree[u].ch[0]].lazy_rev ^= 1;
        if (tree[u].ch[1]) tree[tree[u].ch[1]].lazy_rev ^= 1;
        tree[u].lazy_rev = false;
    }
}

void split(int u, int k, int &x, int &y) {
    if (!u) {
        x = y = 0;
        return;
    }
    push_down(u);
    int left_size = tree[tree[u].ch[0]].size;
    if (left_size < k) {
        x = u;
        split(tree[u].ch[1], k - left_size - 1, tree[x].ch[1], y);
    } else {
        y = u;
        split(tree[u].ch[0], k, x, tree[y].ch[0]);
    }
    push_up(u);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    push_down(x);
    push_down(y);
    if (tree[x].priority > tree[y].priority) {
        tree[x].ch[1] = merge(tree[x].ch[1], y);
        push_up(x);
        return x;
    } else {
        tree[y].ch[0] = merge(x, tree[y].ch[0]);
        push_up(y);
        return y;
    }
}

int build_tree(const vector<int>& arr, int l, int r) {
    if (l > r) return 0;
    int mid = (l + r) / 2;
    int u = new_node(arr[mid]);
    tree[u].ch[0] = build_tree(arr, l, mid - 1);
    tree[u].ch[1] = build_tree(arr, mid + 1, r);
    push_up(u);
    return u;
}

int main() {
    srand(233333);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;
    
    vector<int> initial(n);
    for (int i = 0; i < n; ++i) {
        cin >> initial[i];
    }

    roots[0] = build_tree(initial, 0, n - 1);
    
    cin >> q;
    
    for (int d = 1; d <= q; ++d) {
        int t;
        cin >> t;
        t ^= last_ans;
        
        int current_root = roots[d-1];
        int next_root = current_root; 
        
        if (t == 0) {
            int k;
            cin >> k;
            k ^= last_ans;
            next_root = roots[k];
        } else if (t == 1) {
            int x, v;
            cin >> x >> v;
            x ^= last_ans;
            v ^= last_ans;
            
            int t1, t2, t3;
            split(current_root, x, t1, t2);
            int new_node_id = new_node(v);
            next_root = merge(merge(t1, new_node_id), t2);
        } else if (t == 2) {
            int x;
            cin >> x;
            x ^= last_ans;
            
            int t1, t2, t3;
            split(current_root, x - 1, t1, t2);
            split(t2, 1, t2, t3);
            next_root = merge(t1, t3);
        } else if (t == 3) {
            int x, y;
            cin >> x >> y;
            x ^= last_ans;
            y ^= last_ans;
            
            int t1, t2, t3;
            split(current_root, x - 1, t1, t2);
            split(t2, y - x + 1, t2, t3);
            tree[t2].lazy_rev ^= 1;
            next_root = merge(merge(t1, t2), t3);
        } else if (t == 4) {
            int x, y, v;
            cin >> x >> y >> v;
            x ^= last_ans;
            y ^= last_ans;
            v ^= last_ans;
            
            int t1, t2, t3;
            split(current_root, x - 1, t1, t2);
            split(t2, y - x + 1, t2, t3);
            tree[t2].lazy_add += v;
            tree[t2].val += v;
            tree[t2].max_val += v;
            tree[t2].min_val += v;
            tree[t2].sum += (long long)v * tree[t2].size;
            next_root = merge(merge(t1, t2), t3);
        } else if (t == 5) {
            int x, y;
            cin >> x >> y;
            x ^= last_ans;
            y ^= last_ans;
            
            int t1, t2, t3;
            split(current_root, x - 1, t1, t2);
            split(t2, y - x + 1, t2, t3);
            last_ans = tree[t2].max_val;
            cout << last_ans << "\n";
            next_root = merge(merge(t1, t2), t3);
        } else if (t == 6) {
            int x, y;
            cin >> x >> y;
            x ^= last_ans;
            y ^= last_ans;
            
            int t1, t2, t3;
            split(current_root, x - 1, t1, t2);
            split(t2, y - x + 1, t2, t3);
            last_ans = tree[t2].min_val;
            cout << last_ans << "\n";
            next_root = merge(merge(t1, t2), t3);
        } else if (t == 7) {
            int x, y;
            cin >> x >> y;
            x ^= last_ans;
            y ^= last_ans;
            
            int t1, t2, t3;
            split(current_root, x - 1, t1, t2);
            split(t2, y - x + 1, t2, t3);
            last_ans = tree[t2].sum;
            cout << last_ans << "\n";
            next_root = merge(merge(t1, t2), t3);
        }
        
        roots[d] = next_root;
    }

    return 0;
}
