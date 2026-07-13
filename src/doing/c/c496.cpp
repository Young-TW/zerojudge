#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Edge {
    int u, v, w;
};

struct DSU {
    vector<int> parent;
    int components;

    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) parent[i] = i;
        components = n;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx != ry) {
            parent[rx] = ry;
            components--;
            return true;
        }
        return false;
    }

    bool isConnected() {
        return components == 1;
    }
};

const int INF = 1e9 + 7;

// 檢查是否存在一瓶頸權重 <= limit 的生成樹
// 並回傳該生成樹的最大邊權（即瓶頸）
// 若無法形成生成樹，回傳 -1
int check(int limit, int n, const vector<Edge>& edges) {
    DSU dsu(n);
    int max_w = -1;
    int count = 0;

    // 只使用權重 <= limit 的邊
    for (const auto& e : edges) {
        if (e.w <= limit) {
            if (dsu.unite(e.u, e.v)) {
                max_w = max(max_w, e.w);
                count++;
                if (count == n - 1) break;
            }
        }
    }

    if (dsu.isConnected()) {
        return max_w;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    while (cin >> N >> M >> K) {
        vector<Edge> edges(M);
        vector<int> weights;
        weights.reserve(M);

        for (int i = 0; i < M; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            weights.push_back(edges[i].w);
        }

        // 排序並去重權重，作為二分搜尋的候補答案
        sort(weights.begin(), weights.end());
        weights.erase(unique(weights.begin(), weights.end()), weights.end());

        // 首先檢查圖是否連通，若不連通則直接輸出 -1
        // 我們用最大的權重限制來檢查是否能形成生成樹
        int full_check = check(INF, N, edges);
        if (full_check == -1) {
            cout << -1 << "\n";
            continue;
        }

        // 我們要找嚴格第 K 小的瓶頸值
        // 可能的瓶頸值一定出現在 edges 的權重中
        // 我們收集所有可能的瓶頸值
        
        vector<int> possible_bottlenecks;
        
        // 對於每個可能的權重 w，檢查以 w 為上限時，最小生成樹的瓶頸是多少
        // 如果該瓶頸恰好等於 w，則 w 是一個可能的瓶頸值
        // 注意：這裡的邏輯是，如果存在一個生成樹其最大邊為 w，且不存在最大邊小於 w 的生成樹能達到同樣的連通效果（在限制下），
        // 但題目定義的是「第 K 小瓶頸生成樹」，指的是所有生成樹按照瓶頸大小排序後的第 K 個。
        // 然而，不同生成樹可能有相同的瓶頸值。題目問的是「嚴格第 K 小」，這通常意味著去重後的第 K 個值。
        // 讓我們重新解讀題目：「嚴格第 K 小瓶頸生成樹的瓶頸權重」。
        // 這表示我們將所有可能的生成樹的瓶頸值收集起來，排序，去重，然後取第 K 個。
        
        // 更簡單的方法：
        // 一個值 W 是某個生成樹的瓶頸，若且唯若：
        // 1. 僅用權重 <= W 的邊可以構成生成樹。
        // 2. 該生成樹的最大邊權恰好為 W。
        // 這等價於：僅用權重 <= W 的邊可以構成生成樹，且僅用權重 < W 的邊無法構成生成樹？
        // 不完全是。因為可能存在一個生成樹，其所有邊都 < W，但我們強迫選了一條 W 的邊。
        // 但「瓶頸」定義為該生成樹中最大的邊。所以如果一个生成樹的瓶頸是 W，代表它至少有一條邊是 W，且沒有邊大於 W。
        // 並且，如果存在一個生成樹其所有邊都 < W，那麼它的瓶頸就 < W。
        // 我們關心的是「可能的瓶頸值有哪些」。
        // 一個值 X 是可能的瓶頸值，若存在一棵生成樹 T，使得 T 中最大邊權為 X。
        // 這等價於：
        // (A) 使用所有權重 <= X 的邊，圖是連通的。
        // (B) 存在一條權重為 X 的邊 e=(u,v)，使得在不使用任何權重 > X 的邊的情況下，e 是連接 u 和 v 所在连通分量的必要邊？
        // 或者更簡單的判斷：
        // 令 f(X) = 僅用權重 <= X 的邊所能構成的生成樹的最小瓶頸（即標準 MST 在限制下的最大邊）。
        // 如果 f(X) == X，則 X 是一個可能的瓶頸值嗎？
        // 是的，因為我們可以構造出一個 MST，其最大邊為 X。
        // 那如果 f(X) < X 呢？這表示僅用 < X 的邊就能構成生成樹了。那我們還能構造出一個瓶頸為 X 的生成樹嗎？
        // 可以，只要我們強迫納入一條權重為 X 的邊，並移除環上另一條邊（如果有的話）。
        // 但是，如果我們強迫納入一條權重為 X 的邊，新的生成樹的瓶頸會是 max(原瓶頸, X) = X (因為 X > 原瓶頸)。
        // 所以，只要圖在限制 <= X 下連通，且存在一條權重為 X 的邊，我們就能構造出瓶頸為 X 的生成樹嗎？
        // 不一定。如果所有權重為 X 的邊都是「多餘」的（即兩個端點已經由 < X 的邊連通），我們仍可選它來替換掉某條邊，使新樹瓶頸為 X。
        // 除非... 圖中根本沒有權重為 X 的邊？那當然不行。
        // 所以條件是：
        // 1. 僅用權重 <= X 的邊，圖連通。
        // 2. 存在至少一條權重為 X 的邊。
        // 這樣就能構造出瓶頸為 X 的生成樹嗎？
        // 是的。先構建一個僅用 <= X 邊的 MST，設其瓶頸為 B (B <= X)。
        // 如果 B == X，完成。
        // 如果 B < X，由於存在權重為 X 的邊 e=(u,v)，將 e 加入會形成環。環上必有一條邊 e' 可以被移除。
        // 移除 e' 後得到新生成樹。新生成樹的最大邊權為 max(B, X) = X。
        // 所以，只要 (1) 和 (2) 成立，X 就是一個可能的瓶頸值。
        
        // 因此，所有可能的瓶頸值就是那些滿足「僅用權重 <= X 的邊圖連通」的 X，且 X 必須出現在輸入邊權中。
        // 我們將這些 X 收集起來，排序去重，然後找第 K 個。
        
        for (int w : weights) {
            if (check(w, N, edges) != -1) {
                possible_bottlenecks.push_back(w);
            }
        }
        
        if (K > (int)possible_bottlenecks.size()) {
            cout << -1 << "\n";
        } else {
            // possible_bottlenecks 已經是排序好的（因為 weights 是排序過的）
            cout << possible_bottlenecks[K-1] << "\n";
        }
    }

    return 0;
}
