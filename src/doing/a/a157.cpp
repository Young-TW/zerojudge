#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Node {
    int l, r;
    int lc, rc; // 左端顏色，右端顏色
    int seg;    // 區段數量
    int lazy;   // 懶惰標記，0 表示無
    int len;    // 區間長度
};

const int MAXN = 500005;
Node tree[MAXN * 4];
int arr[MAXN];
int N, C;

void push_up(int node) {
    int left = node * 2;
    int right = node * 2 + 1;
    
    tree[node].lc = tree[left].lc;
    tree[node].rc = tree[right].rc;
    tree[node].seg = tree[left].seg + tree[right].seg;
    
    if (tree[left].rc == tree[right].lc) {
        tree[node].seg--;
    }
}

void push_down(int node) {
    if (tree[node].lazy != 0) {
        int left = node * 2;
        int right = node * 2 + 1;
        int color = tree[node].lazy;
        
        tree[left].lazy = color;
        tree[left].lc = color;
        tree[left].rc = color;
        tree[left].seg = 1;
        
        tree[right].lazy = color;
        tree[right].lc = color;
        tree[right].rc = color;
        tree[right].seg = 1;
        
        tree[node].lazy = 0;
    }
}

void build(int node, int start, int end) {
    tree[node].l = start;
    tree[node].r = end;
    tree[node].len = end - start + 1;
    tree[node].lazy = 0;
    
    if (start == end) {
        tree[node].lc = tree[node].rc = arr[start];
        tree[node].seg = 1;
        return;
    }
    
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    push_up(node);
}

void update_range(int node, int l, int r, int color) {
    if (tree[node].l >= l && tree[node].r <= r) {
        tree[node].lazy = color;
        tree[node].lc = color;
        tree[node].rc = color;
        tree[node].seg = 1;
        return;
    }
    
    push_down(node);
    int mid = (tree[node].l + tree[node].r) / 2;
    if (l <= mid) update_range(node * 2, l, r, color);
    if (r > mid) update_range(node * 2 + 1, l, r, color);
    push_up(node);
}

// 查詢區間 [l, r] 的資訊，返回一個臨時的 Node 結構
Node query_node(int node, int l, int r) {
    if (tree[node].l >= l && tree[node].r <= r) {
        return tree[node];
    }
    
    push_down(node);
    int mid = (tree[node].l + tree[node].r) / 2;
    
    if (r <= mid) return query_node(node * 2, l, r);
    if (l > mid) return query_node(node * 2 + 1, l, r);
    
    Node left_res = query_node(node * 2, l, r);
    Node right_res = query_node(node * 2 + 1, l, r);
    
    Node res;
    res.lc = left_res.lc;
    res.rc = right_res.rc;
    res.seg = left_res.seg + right_res.seg;
    if (left_res.rc == right_res.lc) res.seg--;
    res.len = left_res.len + right_res.len;
    res.lazy = 0;
    res.l = l; 
    res.r = r;
    
    return res;
}

// 獲取單點顏色
int get_color(int node, int idx) {
    if (tree[node].l == tree[node].r) {
        return tree[node].lc;
    }
    push_down(node);
    int mid = (tree[node].l + tree[node].r) / 2;
    if (idx <= mid) return get_color(node * 2, idx);
    else return get_color(node * 2 + 1, idx);
}

// 全局旋轉偏移量
int rotate_offset = 0;
// 是否翻轉
bool is_flipped = false;

// 將邏輯位置轉換為物理位置 (1-based)
int to_physical(int logical_pos) {
    if (logical_pos < 1) logical_pos = (logical_pos - 1) % N + N + 1;
    if (logical_pos > N) logical_pos = (logical_pos - 1) % N + 1;
    
    int pos = logical_pos;
    
    if (is_flipped) {
        // 翻轉後：位置 1 不變，其他對稱
        // 原始: 1, 2, 3, ..., N
        // 翻轉: 1, N, N-1, ..., 2
        // 映射關係: if p==1 -> 1, else -> N - p + 2
        if (pos == 1) pos = 1;
        else pos = N - pos + 2;
    }
    
    // 應用旋轉 (順時針旋轉 k，意味著原本在 1 的現在在 1+k)
    // 邏輯位置 p 對應的物理位置是 (p - offset - 1) mod N + 1 ?
    // 讓我們重新思考旋轉定義：
    // Rotate k: 原來位置 1 -> 位置 k+1
    // 這意味著現在的邏輯位置 1 其實是原來的物理位置 (1 - k)
    // 或者說，邏輯位置 p 對應的物理位置是 (p - rotate_offset)
    
    pos = pos - rotate_offset;
    if (pos <= 0) pos += N;
    if (pos > N) pos -= N;
    
    return pos;
}

// 將物理位置轉換為邏輯位置 (用於理解，本題主要需要 logical -> physical 來查線段樹)
// 但我們的線段樹維護的是物理位置的靜態數組，操作通過映射邏輯坐標來完成。

int main() {
    // 優化輸入輸出
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> C)) return 0;

    for (int i = 1; i <= N; ++i) {
        cin >> arr[i];
    }

    build(1, 1, N);

    int Q;
    cin >> Q;

    while (Q--) {
        string cmd;
        cin >> cmd;

        if (cmd == "R") {
            int k;
            cin >> k;
            // 順時針旋轉 k: 邏輯 1 移到 1+k
            // 這意味著對於新的邏輯位置 x，它對應的舊邏輯位置是 x-k
            // 我們增加 offset，使得 to_physical 計算時減去更多
            rotate_offset = (rotate_offset + k) % N;
        } else if (cmd == "F") {
            is_flipped = !is_flipped;
        } else if (cmd == "S") {
            int i, j;
            cin >> i >> j;
            int pi = to_physical(i);
            int pj = to_physical(j);
            
            int ci = get_color(1, pi);
            int cj = get_color(1, pj);
            
            if (ci != cj) {
                update_range(1, pi, pi, cj);
                update_range(1, pj, pj, ci);
            }
        } else if (cmd == "P") {
            int i, j, x;
            cin >> i >> j >> x;
            int pi = to_physical(i);
            int pj = to_physical(j);
            
            if (pi <= pj) {
                update_range(1, pi, pj, x);
            } else {
                update_range(1, pi, N, x);
                update_range(1, 1, pj, x);
            }
        } else if (cmd == "C") {
            // 查詢整個項鍊的段數
            // 需要特殊處理環狀結構：如果頭尾顏色相同，段數 -1
            if (N == 1) {
                cout << 1 << "\n";
                continue;
            }
            
            Node res = query_node(1, 1, N);
            int total_seg = res.seg;
            
            // 檢查環狀連接處
            int c1 = get_color(1, to_physical(1));
            int cN = get_color(1, to_physical(N));
            
            if (c1 == cN && total_seg > 0) {
                total_seg--;
            }
            cout << total_seg << "\n";
        } else if (cmd == "CS") {
            int i, j;
            cin >> i >> j;
            
            if (i == j) {
                cout << 1 << "\n";
                continue;
            }
            
            int pi = to_physical(i);
            int pj = to_physical(j);
            
            int ans = 0;
            if (pi <= pj) {
                Node res = query_node(1, pi, pj);
                ans = res.seg;
            } else {
                // 跨過邊界
                Node left_part = query_node(1, pi, N);
                Node right_part = query_node(1, 1, pj);
                
                ans = left_part.seg + right_part.seg;
                if (left_part.rc == right_part.lc) {
                    ans--;
                }
            }
            cout << ans << "\n";
        }
    }

    return 0;
}
