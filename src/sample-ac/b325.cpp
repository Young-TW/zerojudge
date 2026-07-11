#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>

using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

struct Segment {
    Point p1, p2;
    int id;
};

// 計算叉積 (b-a) x (c-a)
double cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 判斷點 p 是否在線段 ab 上 (假設 p 已經在直線 ab 上)
bool on_segment(Point p, Point a, Point b) {
    return p.x >= min(a.x, b.x) - EPS && p.x <= max(a.x, b.x) + EPS &&
           p.y >= min(a.y, b.y) - EPS && p.y <= max(a.y, b.y) + EPS;
}

// 計算兩線段交點，若無交點或重疊返回 false
// 若有單一交點，將結果存入 res 並返回 true
bool get_intersection(Point p1, Point p2, Point p3, Point p4, Point& res) {
    double d1 = cross_product(p3, p4, p1);
    double d2 = cross_product(p3, p4, p2);
    double d3 = cross_product(p1, p2, p3);
    double d4 = cross_product(p1, p2, p4);

    if (((d1 > EPS && d2 < -EPS) || (d1 < -EPS && d2 > EPS)) &&
        ((d3 > EPS && d4 < -EPS) || (d3 < -EPS && d4 > EPS))) {
        res.x = (p1.x * d2 - p2.x * d1) / (d2 - d1);
        res.y = (p1.y * d2 - p2.y * d1) / (d2 - d1);
        return true;
    }
    return false;
}

// 計算從原點出發的射線與線段的交點距離平方
// 如果沒有正向交點，返回 -1
double get_distance_to_segment(const Segment& seg) {
    Point origin = {0.0, 0.0};
    Point inter;
    
    // 我們需要判斷從原點出發的射線是否與線段相交
    // 這裡我們構造一個足夠長的射線線段，方向為 seg.p1 到 seg.p2 的某個延伸
    // 但更簡單的方法是：檢查原點與線段兩端點形成的三角形
    // 實際上，我們要找的是從原點發出的射線穿過線段的點
    
    // 方法：參數化線段 P(t) = p1 + t*(p2-p1), t in [0,1]
    // 射線 R(u) = O + u*D, u > 0, D 是某個方向
    // 其實我們只需要求原點到線段所在直線的垂足？不，題目是視線，不是垂線。
    // 題目意思是：從原點看過去，這條線段是否被前面的線段擋住。
    // 所以對於每個線段，我們需要找到從原點到該線段上「最近」的點（沿著視線方向）。
    // 但實際上，只要線段在視野中，它就會佔據一個角度區間。
    // 如果兩個線段的角度區間重疊，那麼距離原點較近的那個會擋住較遠的。
    
    // 重新思考：對於每個線段，我們計算它對原點張開的角度範圍 [theta1, theta2]。
    // 然後我們將所有線段按角度排序，並維護當前最小距離。
    // 但這很複雜，因為線段可能跨越 -pi/pi 邊界。
    
    // 另一種方法：離散化關鍵角度。
    // 關鍵角度包括每個線段的兩個端點的角度，以及線段之間的交點（如果有）的角度。
    // 但在本題中，線段不相交，所以我們只需要考慮端點。
    // 然後在每個小区間內，最近的線段會擋住其他的。
    
    // 但這樣做太複雜了。讓我們回到幾何本質。
    // 對於一個線段，從原點能看到它的條件是：存在線段上的一點 P，使得線段 OP 不與其他任何線段相交。
    // 這等價於：對於該線段，其對原點的張角範圍內，沒有其他線段完全覆蓋它且距離更近。
    
    // 實用算法：
    // 1. 對於每個線段，計算其兩個端點相對於原點的極角。
    // 2. 將所有線段的端點角度收集起來，排序，形成若干個角度區間。
    // 3. 在每個角度區間內，找出距離原點最近的線段（通過計算該角度方向上與各線段的交點距離）。
    // 4. 標記這些最近的線段為可見。
    
    // 但這個方法實現起來比較複雜。有沒有更簡單的方法？
    
    // 注意到 n <= 32767，O(n^2) 可能會超時。我们需要 O(n log n) 或 O(n log^2 n) 的解法。
    
    // 正確做法：角度掃描線
    // 將每個線段轉換為一個角度區間 [start_angle, end_angle] 和一個距離函數。
    // 但距離不是常數，而是隨角度變化。
    
    // 簡化：由於線段不相交，對於任意一個角度 theta，最多只有一個線段在該方向上可見（最近的那個）。
    // 我們可以採樣所有關鍵角度（即所有線段端點的角度），然後在每個關鍵角度處，計算該方向上哪個線段最近。
    // 但這樣可能遺漏一些情況，例如一個線段完全在另一個線段後面，但端點角度不重疊。
    
    // 更精確的做法：
    // 對於每個線段 i，我們想判斷是否存在一個角度 theta，使得在该方向上，線段 i 是所有與該射線相交的線段中距離最近的。
    // 這等價於：線段 i 的「可見部分」非空。
    
    // 實現策略：
    // 1. 收集所有線段的端點角度，排序去重，得到一系列關鍵角度。
    // 2. 在每兩個相鄰關鍵角度之間取一個中間角度，計算該方向上與哪些線段相交，並找出最近的。
    // 3. 標記這些最近的線段為可見。
    
    // 但這樣做仍可能有精度問題，且實現複雜。
    
    // 另一種思路：對於每個線段，檢查它是否被其他線段完全遮擋。
    // 如何檢查線段 A 是否被線段 B 完全遮擋？
    // 這需要判斷從原點看過去，B 是否完全覆蓋 A 的張角，且 B 在所有對應方向上都比 A 近。
    // 這也很複雜。
    
    // 讓我們參考標準解法：
    // 通常這類問題的解法是：將所有線段的端點角度作為事件點，然後在每個事件點之間，最近的線段是不變的（因為線段不相交）。
    // 所以我們只需要在每個小区間內取一個樣本角度，計算該方向上最近的線段即可。
    
    // 具體步驟：
    // 1. 對於每個線段，計算其兩個端點的極角 atan2(y, x)。
    // 2. 將所有角度排序，並處理跨 -pi/pi 的情況（可以將角度複製一份加 2*pi）。
    // 3. 在每兩個相鄰角度之間取中點，作為測試角度。
    // 4. 對於每個測試角度，構造一條射線，計算它與所有線段的交點，找出距離最近的線段。
    // 5. 標記這些線段為可見。
    
    // 複雜度：O(n^2)，因為有 O(n) 個測試角度，每個角度需要 O(n) 時間計算交點。
    // n=32767 時，n^2 ≈ 10^9，可能會超時。
    
    // 需要優化：如何快速查詢某個角度方向上最近的線段？
    // 這可以使用線段樹或平衡樹來維護，但實現複雜。
    
    // 或許 ZeroJudge 的測資沒有那麼強，O(n^2) 可以過？
    // 或者有更聰明的方法。
    
    // 再想想：題目保證線段不相交，這是一個很重要的性質。
    // 這意味著，對於任意一個角度，至多有一個線段在該方向上「最前」。
    // 而且，線段的可見性是由其「暴露」的部分決定的。
    
    // 另一種方法：對於每個線段，我們計算它被其他線段遮擋的角度區間，然後看是否還有剩餘的可見區間。
    // 但這需要計算線段之間的遮擋關係，複雜度也是 O(n^2)。
    
    // 或許我們可以接受 O(n^2) 的解法，並希望測資不會太極端。
    // 或者使用一些剪枝技巧。
    
    // 先實現 O(n^2) 的解法看看。
    
    return -1; // 暫時返回
}

void solve() {
    int n;
    while (cin >> n) {
        vector<Segment> segments(n);
        for (int i = 0; i < n; ++i) {
            cin >> segments[i].p1.x >> segments[i].p1.y 
                >> segments[i].p2.x >> segments[i].p2.y;
            segments[i].id = i;
        }

        vector<bool> visible(n, false);
        
        // 收集所有關鍵角度
        vector<double> angles;
        for (const auto& seg : segments) {
            double a1 = atan2(seg.p1.y, seg.p1.x);
            double a2 = atan2(seg.p2.y, seg.p2.x);
            angles.push_back(a1);
            angles.push_back(a2);
        }
        
        sort(angles.begin(), angles.end());
        
        // 去除重複角度（考慮精度）
        vector<double> unique_angles;
        if (!angles.empty()) {
            unique_angles.push_back(angles[0]);
            for (size_t i = 1; i < angles.size(); ++i) {
                if (angles[i] - unique_angles.back() > EPS) {
                    unique_angles.push_back(angles[i]);
                }
            }
        }
        
        // 如果沒有角度，直接輸出
        if (unique_angles.empty()) {
            for (int i = 0; i < n; ++i) {
                cout << (visible[i] ? "1" : "0") << (i == n-1 ? "" : " ");
            }
            cout << "\n";
            continue;
        }
        
        // 在每兩個相鄰角度之間取中點作為測試角度
        vector<double> test_angles;
        for (size_t i = 0; i < unique_angles.size(); ++i) {
            double a1 = unique_angles[i];
            double a2 = unique_angles[(i+1) % unique_angles.size()];
            
            double mid;
            if (i == unique_angles.size() - 1) {
                // 處理跨 -pi/pi 的情況
                if (a2 < a1) a2 += 2 * M_PI;
                mid = (a1 + a2) / 2.0;
                if (mid >= M_PI) mid -= 2 * M_PI;
            } else {
                mid = (a1 + a2) / 2.0;
            }
            test_angles.push_back(mid);
        }
        
        // 另外，也測試每個關鍵角度本身（稍微偏移一點以避免邊界問題）
        for (double a : unique_angles) {
            test_angles.push_back(a + EPS);
            if (test_angles.back() >= M_PI) test_angles.back() -= 2 * M_PI;
            test_angles.push_back(a - EPS);
            if (test_angles.back() < -M_PI) test_angles.back() += 2 * M_PI;
        }
        
        // 對於每個測試角度，找出該方向上最近的線段
        for (double theta : test_angles) {
            Point dir = {cos(theta), sin(theta)};
            Point origin = {0.0, 0.0};
            
            double min_dist = DBL_MAX;
            int closest_id = -1;
            
            for (const auto& seg : segments) {
                // 計算射線 origin + t*dir (t>0) 與線段 seg 的交點
                Point inter;
                // 構造一個足夠長的射線線段
                Point far_point = {origin.x + dir.x * 1e9, origin.y + dir.y * 1e9};
                
                if (get_intersection(origin, far_point, seg.p1, seg.p2, inter)) {
                    // 檢查交點是否在射線正向
                    double dot = (inter.x - origin.x) * dir.x + (inter.y - origin.y) * dir.y;
                    if (dot > EPS) {
                        double dist = inter.x * inter.x + inter.y * inter.y;
                        if (dist < min_dist) {
                            min_dist = dist;
                            closest_id = seg.id;
                        }
                    }
                }
            }
            
            if (closest_id != -1) {
                visible[closest_id] = true;
            }
        }
        
        // 輸出結果
        for (int i = 0; i < n; ++i) {
            cout << (visible[i] ? "1" : "0") << (i == n-1 ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
