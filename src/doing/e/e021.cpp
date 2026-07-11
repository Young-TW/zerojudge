#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    long long x, y;
};

// 計算叉積 (b-a) x (c-a)
long long cross_product(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<Point> points(N);
    for (int i = 0; i < N; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    // 使用 vector 模擬多邊形頂點序列
    // 題目保證操作合法，且多邊形始終為簡單多邊形
    vector<int> polygon_indices;
    // 初始時多邊形為空？題目描述有點模糊，但根據範例，初始應該沒有點或是點還沒組合成多邊形
    // 重新閱讀題目： "泡泡從無開始慢慢變化"，但輸入先給了 N 個點。
    // 範例輸入先給了 5 個點，然後操作 1 插入點到序列。
    // 這表示初始序列是空的，操作 1 將點加入序列形成多邊形。
    // 讓我們再看一次範例。
    // 範例輸入: 5 14 (5個點，14個操作)
    // 接著列出 5 個點 p0 ~ p4
    // 操作: 1 0 0 -> 將 p0 插入位置 0. 序列: [p0]
    // 操作: 1 1 0 -> 將 p1 插入位置 0. 序列: [p1, p0] ? 還是 [p0, p1]?
    // 題目說: "將點 p_u 插入到序列 a 位置 k 上，意即 a_k = p_u"
    // 這通常意味著 insert at index k.
    // 如果序列是 [p0], 插入 p1 到位置 0, 則序列變為 [p1, p0].
    // 讓我們假設是標準的 insert 行為。

    // 但是，多邊形至少需要 3 個點才能構成內部。
    // 對於少於 3 個點的情況，任何點都不在內部。

    vector<Point> current_polygon;
    
    // 預留空間以避免多次配置
    current_polygon.reserve(N);

    char type;
    for (int i = 0; i < M; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, k;
            cin >> u >> k;
            // 插入點 p_u 到位置 k
            if (k < 0 || k > (int)current_polygon.size()) {
                // 理論上不會發生，因為題目保證 k 符合限制
                continue;
            }
            current_polygon.insert(current_polygon.begin() + k, points[u]);
        } else if (op == 2) {
            int k;
            cin >> k;
            if (k < 0 || k >= (int)current_polygon.size()) {
                continue;
            }
            current_polygon.erase(current_polygon.begin() + k);
        } else if (op == 3) {
            double fx, fy;
            cin >> fx >> fy;
            
            if (current_polygon.size() < 3) {
                cout << "0\n";
                continue;
            }

            // 使用射線法 (Ray Casting Algorithm) 判斷點是否在多邊形內部
            // 從點 (fx, fy) 向右發射一條水平射線，計算與多邊形邊相交的次數
            // 奇數次表示在內部，偶數次表示在外部
            
            bool inside = false;
            int n = current_polygon.size();
            
            // 為了處理浮點數精度問題，我們可以使用一個極小的 epsilon，或者仔細處理邊界情況
            // 題目要求 "嚴格在多邊形內部"，所以在邊界上算外部。
            // 射線法標準實現：
            // 對於每條邊 (p[i], p[j])，檢查射線是否穿過該邊。
            // 條件： ((yi > y) != (yj > y)) 且 (x < (xj - xi) * (y - yi) / (yj - yi) + xi)
            // 這裡 y 是測試點的 y 座標，x 是測試點的 x 座標
            
            for (int j = 0; j < n; ++j) {
                Point p1 = current_polygon[j];
                Point p2 = current_polygon[(j + 1) % n];
                
                double y1 = p1.y;
                double y2 = p2.y;
                double x1 = p1.x;
                double x2 = p2.x;
                
                // 檢查點是否在邊的 y 範圍內 (半開區間，避免重複計算頂點)
                // 我們定義區間為 (min(y1, y2), max(y1, y2)] 或 [min, max)
                // 標準寫法是：((y1 > fy) != (y2 > fy))
                if ((y1 > fy) != (y2 > fy)) {
                    // 計算交點的 x 座標
                    // x_intersect = x1 + (fy - y1) * (x2 - x1) / (y2 - y1)
                    double x_intersect = x1 + (fy - y1) * (double)(x2 - x1) / (y2 - y1);
                    
                    if (fx < x_intersect) {
                        inside = !inside;
                    } else if (fx == x_intersect) {
                        // 點在邊上，根據題目要求 "嚴格在內部"，所以在邊上視為外部
                        // 一旦發現點在邊上，可以直接判定為不在嚴格內部
                        inside = false;
                        break;
                    }
                }
            }
            
            // 額外檢查：如果點恰好落在頂點上，也不算嚴格內部
            // 上面的射線法在某些實現中可能無法完美捕捉頂點情況，或者需要特殊處理
            // 讓我們顯式檢查點是否在任何邊上（包括頂點）
            bool on_boundary = false;
            for (int j = 0; j < n; ++j) {
                Point p1 = current_polygon[j];
                Point p2 = current_polygon[(j + 1) % n];
                
                // 檢查點 (fx, fy) 是否在線段 p1-p2 上
                // 首先檢查叉積是否為 0 (三點共線)
                // 由於 fx, fy 是 double，我们需要容忍誤差，但題目說小數點最多兩位，且坐標是整數
                // 如果點在邊上，叉積應為 0。
                // 為了精確，我們將 fx, fy 轉換為與整數運算兼容的方式，或者使用帶有 eps 的比較
                // 但最穩健的方法是：如果點在邊上，cross product 為 0，且點在 bounding box 內
                
                double cp = (double)(p2.x - p1.x) * (fy - p1.y) - (double)(p2.y - p1.y) * (fx - p1.x);
                if (fabs(cp) < 1e-9) {
                    // 共線，檢查是否在線段範圍內
                    double min_x = min(p1.x, p2.x);
                    double max_x = max(p1.x, p2.x);
                    double min_y = min(p1.y, p2.y);
                    double max_y = max(p1.y, p2.y);
                    
                    if (fx >= min_x - 1e-9 && fx <= max_x + 1e-9 &&
                        fy >= min_y - 1e-9 && fy <= max_y + 1e-9) {
                        on_boundary = true;
                        break;
                    }
                }
            }
            
            if (on_boundary) {
                cout << "0\n";
            } else {
                cout << (inside ? "1" : "0") << "\n";
            }
        }
    }

    return 0;
}
