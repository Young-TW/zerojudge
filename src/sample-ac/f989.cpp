#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n, q;
vector<int> m;
vector<int> tree;
int total_size;

// 將 n 維座標轉換為 1D 索引 (0-based)
int get_index(const vector<int>& coord) {
    int idx = 0;
    int stride = 1;
    for (int i = n - 1; i >= 0; --i) {
        idx += (coord[i] - 1) * stride;
        if (i > 0) stride *= m[i];
    }
    return idx;
}

// 計算範圍內元素個數
int count_range(const vector<int>& l, const vector<int>& r) {
    int cnt = 1;
    for (int i = 0; i < n; ++i) {
        cnt *= (r[i] - l[i] + 1);
    }
    return cnt;
}

// 更新 BIT: pos += val (pos is 1-based)
void update(int pos, int val) {
    while (pos <= total_size) {
        tree[pos] += val;
        pos += (pos & -pos);
    }
}

// 查詢 BIT 前綴和 (pos is 1-based)
int query(int pos) {
    int sum = 0;
    while (pos > 0) {
        sum += tree[pos];
        pos -= (pos & -pos);
    }
    return sum;
}

void solve() {
    if (!(cin >> n >> q)) return;
    
    m.resize(n);
    total_size = 1;
    for (int i = 0; i < n; ++i) {
        cin >> m[i];
        total_size *= m[i];
    }
    
    // 重置 tree，大小為 total_size + 1，初始值為 0
    tree.assign(total_size + 1, 0);
    
    // 用來記錄每個位置目前的狀態 (0: 熄滅，1: 點燃)，以便做 toggle
    // 由於 total_size <= 10^5，可以用 vector<bool> 或 vector<char>
    vector<char> state(total_size, 0);
    
    for (int k = 0; k < q; ++k) {
        int type;
        cin >> type;
        if (type == 1) {
            vector<int> x(n);
            for (int i = 0; i < n; ++i) cin >> x[i];
            int idx = get_index(x); // 0-based
            int bit_idx = idx + 1;  // 1-based for BIT
            
            if (state[idx] == 0) {
                // 從熄滅變點燃
                state[idx] = 1;
                update(bit_idx, 1);
            } else {
                // 從點燃變熄滅
                state[idx] = 0;
                update(bit_idx, -1);
            }
        } else if (type == 2) {
            vector<int> l(n), r(n);
            for (int i = 0; i < n; ++i) cin >> l[i];
            for (int i = 0; i < n; ++i) cin >> r[i];
            
            // 對於 n 維的情況，如果直接展開成 1D，範圍查詢會變成多個區間的合併
            // 但題目保證 product(m_i) <= 10^5，這意味著總格子數很少。
            // 然而，操作次數 q 可達 10^4，如果每次查詢都遍歷所有格子，複雜度是 O(q * total_size) = 10^9，可能會 TLE。
            // 但是，注意到 n <= 8 且 total_size <= 10^5。
            // 如果我們將 n 維映射到 1D，一個 n 維的長方體在 1D 上通常不是連續的區間（除非 n=1）。
            // 因此，單純用 1D BIT 無法直接處理 n>1 的範圍求和，除非我們將其分解為多個 1D 區間。
            
            // 重新思考：題目限制 product(m_i) <= 10^5。
            // 這表示無論維度如何，總格子數 N <= 100,000。
            // 如果我們使用暴力法：每次操作 2 遍歷指定範圍內的所有格子並檢查 state 陣列。
            // 最壞情況下，每次查詢遍歷 10^5 個格子，共 10^4 次查詢 -> 10^9 運算，這在 C++ 中可能勉強過或 TLE。
            // 但通常測資不會每次都查整個空間。
            // 不過，為了保險起見，我們需要更高效的方法。
            
            // 實際上，對於高維度的範圍查詢，如果總元素不多，可以考慮將多維座標映射到一維，
            // 但如前所述，多維長方體在一維映射下不一定是連續區間。
            // 例如 2D 2x2: (1,1)->0, (1,2)->1, (2,1)->2, (2,2)->3.
            // 查詢 (1,1) 到 (2,2) 是 [0, 3] 連續。
            // 查詢 (1,1) 到 (1,2) 是 [0, 1] 連續。
            // 查詢 (1,1) 到 (2,1) 是 {0, 2} 不連續。
            // 所以直接用 1D BIT 做前綴和相減是不行的。
            
            // 正確做法：由於 N <= 10^5，我們可以接受 O(N) 的預處理或較慢的查詢嗎？
            // 不，Q=10^4，O(N*Q) 太慢。
            // 我們需要一個能處理多維範圍查詢的數據結構，或者利用 N 小的特性。
            // 等等，題目說 product(m_i) <= 10^5，這非常小。
            // 也許我們可以將多維問題轉化為一維問題，但需要小心處理區間。
            // 或者，我們可以使用 n 維 BIT？
            // n 維 BIT 的空間複雜度是 O(product(m_i)) = 10^5，這是可行的。
            // 更新複雜度 O(2^n * log(m1)*...*log(mn))? 不，n 維 BIT 的更新是 O(log(m1) * log(m2) * ... * log(mn))。
            // 因為 n <= 8，且每個 m_i >= 1，最壞情況是所有 m_i 都很小，例如 2^16 > 10^5，所以 n 最大約 16? 但題目說 n<=8。
            // 如果 n=8, m_i=2 (2^8=256)，則 log(m_i)=1，更新次數 1。
            // 如果 n=1, m_1=10^5，更新次數 log(10^5) ≈ 17。
            // 一般來說，n 維 BIT 的更新複雜度是 O(prod_{i=1}^n log(m_i+1))。
            // 由於 prod(m_i) <= 10^5，這個乘積不會太大。
            // 讓我們實現 n 維 BIT。
            
            // 但剛才我已經寫了 1D BIT 的框架，現在發現不對。
            // 讓我們重構為 n 維 BIT。
            
            // 由於要重構，我們先清空當前的邏輯，並在下面重新實現 n 維 BIT。
            // 為了避免混淆，我將在這個函數內重新定義需要的變量。
            
            // 重新開始：使用 n 維 BIT
            // 由於 n 是運行時確定的，我們不能用靜態多維數組。
            // 我們可以用 1D vector 模擬 n 維數組，並手動計算索引。
            // BIT 的操作需要遍歷各維度的下一個/上一個索引。
            
            // 我們已經有 m 向量作為各維度的大小。
            // 我們需要一個 1D 的 tree 向量，大小為 total_size + 1。
            // 但 n 維 BIT 的更新和查詢需要遞迴或迭代地訪問相關節點。
            // 對於 n 維 BIT，更新 (x1, x2, ..., xn) 時，需要更新所有包含該點的超矩形對應的節點。
            // 標準做法是嵌套循環，但 n 是變量，所以需要遞迴或動態生成循環。
            // 由於 n <= 8，遞迴深度很小，是可行的。
            
            // 讓我們定義一個遞迴函數來處理 n 維 BIT 的更新和查詢。
            // 但為了效率，我們可以在 solve 函數內定義 lambda 或使用成員函數。
            // 這裡我們在 solve 內用 lambda。
            
            // 首先，重置 tree
            fill(tree.begin(), tree.end(), 0);
            // state 也需要重置，但我們會在下面重新宣告
            
            // 由於上面的代碼已經讀入了 type 和部分數據，我們需要回退或重新設計流程。
            // 更好的方式是：先讀完所有輸入，再處理？不，要在線處理。
            // 所以我們需要在讀入 n, q, m 後就初始化好 n 維 BIT。
            // 然後在循環中處理每個操作。
            
            // 讓我們重寫整個 solve 函數的邏輯。
        }
    }
    
    // 由於上述邏輯混亂，我們完全重寫 solve 函數。
}

// 全局變量用於 n 維 BIT
int g_n;
vector<int> g_m;
vector<int> g_tree;
int g_total_size;

// 將 n 維座標 (1-based) 轉換為 1D 索引 (1-based) 用於存儲
// 注意：BIT 內部我們還是需要用某種方式訪問節點。
// 其實，n 維 BIT 的標準實現是使用 n 重循環，但 n 不定時，我們用遞迴。
// 我們定義一個函數，給定當前維度 cur_dim 和當前座標 coord (1-based)，以及 delta，進行更新。
// 但這樣每次更新都要遞迴，可能稍慢，但 n<=8 應該沒問題。

// 另一種思路：既然總格子數 <= 10^5，我們可以將 n 維座標映射到 0~N-1 的整數。
// 然後，對於範圍查詢，我們無法直接用 1D BIT，除非我們將查詢分解。
// 但分解多維長方體到 1D 區間可能很複雜。
// 所以還是用 n 維 BIT 比較直接。

// 實現 n 維 BIT：
// tree 是一個 1D 向量，大小為 (m1+1)*(m2+1)*...*(mn+1) ? 
// 不，BIT 的大小通常和各維度大小相同，即 m1*m2*...*mn，但索引從 1 開始。
// 我們用 1D 向量模擬 n 維數組，大小為 prod(m_i) + 1 (為了 1-based)。
// 但實際上，BIT 的每個節點對應一個 n 維座標 (i1, i2, ..., in)，其中 1<=ik<=mk。
// 我們可以將 (i1, i2, ..., in) 映射到 1D 索引。
// 映射公式：idx = (...((i1-1)*m2 + (i2-1))*m3 + ... )*(mn) + (in-1) + 1 (1-based)
// 但這樣計算比較麻煩，而且 BIT 的更新需要跳躍，跳躍規則在各維度獨立。
// 例如，在第 k 維，下一步是 i_k += (i_k & -i_k)。
// 所以我們需要能夠從 1D 索引反推出 n 維座標，或者在遞迴時維護當前座標。

// 我們採用遞迴方式：
// update_recursive(dim, current_coord, delta)
// 但這樣需要知道完整的座標才能計算 1D 索引來更新 tree。
// 或者，我們不將 tree 壓平，而是用 vector<vector<...>>? 不行，n 不定。
// 所以還是壓平，並在遞迴時計算索引。

// 為了提高效率，我們預先計算好各維度的 stride。
vector<int> strides;

int coord_to_index(const vector<int>& coord) {
    // coord is 1-based
    int idx = 0;
    for (int i = 0; i < g_n; ++i) {
        idx += (coord[i] - 1) * strides[i];
    }
    return idx + 1; // 1-based index for tree
}

void update_nd(vector<int>& coord, int delta) {
    // 使用遞迴或迭代來模擬 n 重循環
    // 這裡用一個 stack 或遞迴來遍歷所有需要更新的節點
    // 由於 n 很小，我們用遞迴。
    // 但遞迴函數需要修改 coord，這會很麻煩。
    // 另一種方法：迭代法，用一個向量來存儲當前各維度的索引，然後模擬進位。
    // 但這等同於自己實現多重循環。
    
    // 簡單起見，我們用遞迴函數，參數為當前維度和當前座標向量。
    // 但這樣會複製向量，效率稍低。我們可以傳引用並在回溯時恢復。
    
    // 定義一個 lambda 或輔助函數
    // 由於不能在函數內定義遞迴 lambda 容易（需 std::function），我們寫一個單獨的輔助函數。
    // 但輔助函數需要訪問 g_tree, g_m, strides 等全局變量。
    
    // 我們改寫為非遞迴：用一個队列或栈来存储当前状态？
    // 或者，我們注意到 n 維 BIT 的更新規則是：對於每個維度 i，從 x_i 開始，每次加上 lowbit(x_i)，直到超過 m_i。
    // 所有這些組合都需要更新。
    // 總共有 prod(log(m_i)) 個節點需要更新。
    // 我們可以生成所有這些組合。
    
    vector<vector<int>> all_coords;
    // 生成所有組合
    // 用遞迴生成
    auto generate = [&](auto&& self, int dim, vector<int>& current) -> void {
        if (dim == g_n) {
            all_coords.push_back(current);
            return;
        }
        for (int i = coord[dim]; i <= g_m[dim]; i += (i & -i)) {
            current[dim] = i;
            self(self, dim + 1, current);
        }
    };
    
    vector<int> current_coord = coord;
    generate(generate, 0, current_coord);
    
    for (const auto& c : all_coords) {
        int idx = coord_to_index(c);
        g_tree[idx] += delta;
    }
}

int query_nd(vector<int>& coord) {
    // 查詢前綴和 (1,1,...,1) 到 coord
    // 同樣需要生成所有組合，但這次是減去 lowbit
    vector<vector<int>> all_coords;
    
    auto generate = [&](auto&& self, int dim, vector<int>& current) -> void {
        if (dim == g_n) {
            all_coords.push_back(current);
            return;
        }
        for (int i = coord[dim]; i > 0; i -= (i & -i)) {
            current[dim] = i;
            self(self, dim + 1, current);
        }
    };
    
    vector<int> current_coord = coord;
    generate(generate, 0, current_coord);
    
    int sum = 0;
    for (const auto& c : all_coords) {
        int idx = coord_to_index(c);
        sum += g_tree[idx];
    }
    return sum;
}

// 容斥原理計算多維範圍和
int range_query(const vector<int>& l, const vector<int>& r) {
    // 使用容斥原理，2^n 個角點
    // 對於每個角點，根據其在 l 或 r 的選擇決定符號
    // 如果某維選 l[i]-1，則該維貢獻負號？標準容斥：
    // Sum(l..r) = sum_{S subset of {1..n}} (-1)^{|S|} Query( p_S )
    // 其中 p_S 在第 i 維，如果 i in S 則為 l[i]-1，否則為 r[i]。
    // 符號：如果 |S| 是偶數則正，奇數則負？
    // 實際上，標準公式是：
    // F(r1, r2, ..., rn) - F(l1-1, r2, ..., rn) - F(r1, l2-1, ..., rn) + F(l1-1, l2-1, ..., rn) ...
    // 符號由 (l[i]-1) 的個數決定：如果有 k 個維度选了 l[i]-1，則符號為 (-1)^k。
    
    int total = 0;
    int num_corners = 1 << g_n;
    
    for (int mask = 0; mask < num_corners; ++mask) {
        vector<int> point(g_n);
        int bits = 0;
        for (int i = 0; i < g_n; ++i) {
            if ((mask >> i) & 1) {
                point[i] = l[i] - 1;
                bits++;
            } else {
                point[i] = r[i];
            }
        }
        
        // 如果任何維度 < 1，則該點的前綴和為 0
        bool valid = true;
        for (int i = 0; i < g_n; ++i) {
            if (point[i] < 1) {
                valid = false;
                break;
            }
        }
        
        if (!valid) continue;
        
        int val = query_nd(point);
        if (bits % 2 == 1) {
            total -= val;
        } else {
            total += val;
        }
    }
    
    return total;
}

void solve_correct() {
    if (!(cin >> g_n >> q)) return;
    
    g_m.resize(g_n);
    g_total_size = 1;
    for (int i = 0; i < g_n; ++i) {
        cin >> g_m[i];
        g_total_size *= g_m[i];
    }
    
    // 計算 strides 用於將 n 維座標映射到 1D
    strides.resize(g_n);
    strides[g_n - 1] = 1;
    for (int i = g_n - 2; i >= 0; --i) {
        strides[i] = strides[i + 1] * (g_m[i + 1]);
    }
    // 注意：上面的 strides 計算假設座標是 (d0, d1, ..., dn-1)
    // 索引 = d0*stride0 + d1*stride1 + ... + dn-1*stride_n-1
    // 但我們的 coord_to_index 用的是 (coord[i]-1)*strides[i]
    // 並且 tree 大小應該是 prod(m_i) + 1? 
    // 實際上，最大索引是當所有 coord[i] = g_m[i] 時，
    // idx = sum((g_m[i]-1)*strides[i]) + 1
    // 讓我們驗證：如果 g_n=2, g_m={2,2}, strides[1]=1, strides[0]=2.
    // coord=(2,2): idx = (1)*2 + (1)*1 + 1 = 4. 正確，因為總共有 4 個元素。
    // 所以 tree 大小應為 g_total_size + 1.
    
    g_tree.assign(g_total_size + 1, 0);
    
    // 記錄狀態
    vector<char> state(g_total_size + 1, 0); // 1-based indexing for convenience
    
    for (int k = 0; k < q; ++k) {
        int type;
        cin >> type;
        if (type == 1) {
            vector<int> x(g_n);
            for (int i = 0; i < g_n; ++i) cin >> x[i];
            int idx = coord_to_index(x);
            
            if (state[idx] == 0) {
                state[idx] = 1;
                update_nd(x, 1);
            } else {
                state[idx] = 0;
                update_nd(x, -1);
            }
        } else if (type == 2) {
            vector<int> l(g_n), r(g_n);
            for (int i = 0; i < g_n; ++i) cin >> l[i];
            for (int i = 0; i < g_n; ++i) cin >> r[i];
            
            cout << range_query(l, r) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve_correct();
        }
    }
    return 0;
}
