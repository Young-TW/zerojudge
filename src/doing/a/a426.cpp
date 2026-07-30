#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

struct Segment {
    int id;
    Point p1, p2;
    bool removed;
    
    // 判斷是否為水平線段 (題目說不會有，但保留邏輯完整性)
    bool isHorizontal() const {
        return abs(p1.y - p2.y) < EPS;
    }
    
    // 判斷是否為垂直線段 (題目說不會有)
    bool isVertical() const {
        return abs(p1.x - p2.x) < EPS;
    }
};

// 計算叉積 (b-a) x (c-a)
double cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 判斷點 p 是否在線段 s 上 (包含端點)
bool on_segment(const Segment& s, Point p) {
    double cp = cross_product(s.p1, s.p2, p);
    if (abs(cp) > EPS) return false;
    
    double min_x = min(s.p1.x, s.p2.x) - EPS;
    double max_x = max(s.p1.x, s.p2.x) + EPS;
    double min_y = min(s.p1.y, s.p2.y) - EPS;
    double max_y = max(s.p1.y, s.p2.y) + EPS;
    
    return (p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y);
}

// 判斷兩線段是否相交 (嚴格相交或端點接觸)
// 題目說：僅端點接觸不會造成阻礙。
// 但在幾何判斷中，如果兩線段交叉（內部相交），則一定阻礙。
// 如果僅端點接觸，根據題目描述，不算阻礙。
// 然而，本題的移動是平移至無窮遠。
// 如果线段 A 要向左移動，它會被任何在它左側且與它的掃描帶相交的線段 B 阻擋。
// 具體來說，如果 A 向左移，B 必須在 A 的左方路徑上。
// 由於線段不水平不垂直，我們可以用掃描線思想或直接幾何判斷。

// 判斷線段 blocker 是否會阻擋線段 mover 向 dir 方向移動
// dir: 0=Left, 1=Up, 2=Right, 3=Down
bool blocks(const Segment& mover, const Segment& blocker, int dir) {
    if (mover.removed || blocker.removed) return false;
    if (mover.id == blocker.id) return false;

    // 快速排斥實驗：檢查 bounding box 關係
    double m_min_x = min(mover.p1.x, mover.p2.x);
    double m_max_x = max(mover.p1.x, mover.p2.x);
    double m_min_y = min(mover.p1.y, mover.p2.y);
    double m_max_y = max(mover.p1.y, mover.p2.y);

    double b_min_x = min(blocker.p1.x, blocker.p2.x);
    double b_max_x = max(blocker.p1.x, blocker.p2.x);
    double b_min_y = min(blocker.p1.y, blocker.p2.y);
    double b_max_y = max(blocker.p1.y, blocker.p2.y);

    if (dir == 0) { // Left: mover 需要向左，blocker 必須在 mover 的左側範圍內，且 y 範圍有重疊
        // blocker 必須在 mover 的左邊 (blocker 的右邊界 <= mover 的左邊界？不完全是，因為是斜的)
        // 準確條件：blocker 的 x 範圍必須與 (-inf, m_min_x] 有交集 (這總是成立除非 blocker 完全在右邊)
        // 關鍵：blocker 必須位於 mover 向左射出的掃描區域內。
        // 如果 blocker 完全在 mover 的右側 (b_min_x > m_max_x)，則不阻擋。
        if (b_min_x > m_max_x + EPS) return false;
        
        // 如果 blocker 完全在 mover 的上方或下方，且 y 區間無重疊，則不阻擋
        if (b_min_y > m_max_y + EPS || b_max_y < m_min_y - EPS) return false;
        
        // 詳細幾何判斷：
        // 構造 mover 向左無限延伸的多邊形區域 (實際上是 mover 線段向左的掃描帶)
        // 由於線段是斜的，這個掃描帶是一個平行四邊形延伸到無窮遠。
        // 簡化判斷：檢查 blocker 是否與 "mover 向左的射線束" 相交。
        // 對於非水平非垂直線段，若 blocker 與 mover 的 y 投影有重疊，且 blocker 有部分在 mover 左側，
        // 則需判斷是否真的擋住。
        
        // 更簡單的邏輯：如果 blocker 的任何部分位於 mover 的左側路徑上。
        // 考慮 mover 的兩個端點向左發射水平射線。如果 blocker 與這兩條射線之一相交，
        // 或者 blocker 完全跨越了 mover 的 y 範圍且在左側。
        
        // 通用方法：檢查 blocker 是否與由 mover 向左平移產生的半無限帶相交。
        // 由於題目保證線段不相交，我們只需檢查 blocker 是否 "擋在" mover 和 -infinity 之間。
        // 這等價於：是否存在一個 y，使得在该 y 處，blocker 的 x 小於 mover 的 x，且該 y 同時屬於兩線段的 y 範圍。
        // 並且，在該 y 處，mover 和 blocker 之間沒有其他空隙（但因為只有一對一判斷，我們只看這兩個）。
        // 實際上，只要 blocker 的 x 區間和 mover 的 x 區間在 y 重疊部分有 "交錯" 且 blocker 在左，就會擋住。
        
        // 精確算法：
        // 1. 找出兩線段 y 範圍的重疊區間 [y_low, y_high]
        double y_low = max(m_min_y, b_min_y);
        double y_high = min(m_max_y, b_max_y);
        
        if (y_low > y_high - EPS) return false; // y 範圍無重疊
        
        // 2. 在重疊的 y 範圍內，取一個或多個測試點，比較 x 座標
        // 由於線段是線性的，我們只需要檢查端點或交點。
        // 簡單起見，檢查 y_low 和 y_high 對應的 x 值（如果在線段上）
        vector<double> test_ys;
        test_ys.push_back(y_low);
        test_ys.push_back(y_high);
        
        // 加入 blocker 的端點 y (如果在重疊區間內)
        if (blocker.p1.y >= y_low - EPS && blocker.p1.y <= y_high + EPS) test_ys.push_back(blocker.p1.y);
        if (blocker.p2.y >= y_low - EPS && blocker.p2.y <= y_high + EPS) test_ys.push_back(blocker.p2.y);
        // 加入 mover 的端點 y
        if (mover.p1.y >= y_low - EPS && mover.p1.y <= y_high + EPS) test_ys.push_back(mover.p1.y);
        if (mover.p2.y >= y_low - EPS && mover.p2.y <= y_high + EPS) test_ys.push_back(mover.p2.y);
        
        for (double y : test_ys) {
            // 計算 mover 在 y 處的 x
            double mx = -1e18;
            if (abs(mover.p1.y - mover.p2.y) > EPS) {
                double t = (y - mover.p1.y) / (mover.p2.y - mover.p1.y);
                if (t >= -EPS && t <= 1.0 + EPS) {
                    mx = mover.p1.x + t * (mover.p2.x - mover.p1.x);
                }
            } else {
                // 水平線段 (題目說沒有，但防衛性編程)
                if (abs(y - mover.p1.y) < EPS) mx = min(mover.p1.x, mover.p2.x); 
            }
            
            // 計算 blocker 在 y 處的 x
            double bx = 1e18;
            if (abs(blocker.p1.y - blocker.p2.y) > EPS) {
                double t = (y - blocker.p1.y) / (blocker.p2.y - blocker.p1.y);
                if (t >= -EPS && t <= 1.0 + EPS) {
                    bx = blocker.p1.x + t * (blocker.p2.x - blocker.p1.x);
                }
            } else {
                 if (abs(y - blocker.p1.y) < EPS) bx = min(blocker.p1.x, blocker.p2.x);
            }
            
            // 如果在该 y 處，mover 存在且 blocker 存在，且 blocker 在 mover 左側 (嚴格小於，因為端點接觸不算)
            // 題目說：僅端點接觸不會造成阻礙。
            // 這意味著如果 bx == mx，不算阻擋。只有 bx < mx 才算。
            if (mx > -1e17 && bx < 1e17) {
                if (bx < mx - EPS) return true;
            }
        }
        return false;
    }
    else if (dir == 2) { // Right
        if (b_max_x < m_min_x - EPS) return false;
        if (b_min_y > m_max_y + EPS || b_max_y < m_min_y - EPS) return false;
        
        double y_low = max(m_min_y, b_min_y);
        double y_high = min(m_max_y, b_max_y);
        if (y_low > y_high - EPS) return false;
        
        vector<double> test_ys;
        test_ys.push_back(y_low);
        test_ys.push_back(y_high);
        if (blocker.p1.y >= y_low - EPS && blocker.p1.y <= y_high + EPS) test_ys.push_back(blocker.p1.y);
        if (blocker.p2.y >= y_low - EPS && blocker.p2.y <= y_high + EPS) test_ys.push_back(blocker.p2.y);
        if (mover.p1.y >= y_low - EPS && mover.p1.y <= y_high + EPS) test_ys.push_back(mover.p1.y);
        if (mover.p2.y >= y_low - EPS && mover.p2.y <= y_high + EPS) test_ys.push_back(mover.p2.y);
        
        for (double y : test_ys) {
            double mx = -1e18;
            if (abs(mover.p1.y - mover.p2.y) > EPS) {
                double t = (y - mover.p1.y) / (mover.p2.y - mover.p1.y);
                if (t >= -EPS && t <= 1.0 + EPS) mx = mover.p1.x + t * (mover.p2.x - mover.p1.x);
            } else {
                if (abs(y - mover.p1.y) < EPS) mx = max(mover.p1.x, mover.p2.x);
            }
            
            double bx = -1e18;
            if (abs(blocker.p1.y - blocker.p2.y) > EPS) {
                double t = (y - blocker.p1.y) / (blocker.p2.y - blocker.p1.y);
                if (t >= -EPS && t <= 1.0 + EPS) bx = blocker.p1.x + t * (blocker.p2.x - blocker.p1.x);
            } else {
                if (abs(y - blocker.p1.y) < EPS) bx = max(blocker.p1.x, blocker.p2.x);
            }
            
            if (mx > -1e17 && bx > -1e17) {
                if (bx > mx + EPS) return true;
            }
        }
        return false;
    }
    else if (dir == 1) { // Up
        if (b_max_y < m_min_y - EPS) return false;
        if (b_min_x > m_max_x + EPS || b_max_x < m_min_x - EPS) return false;
        
        double x_low = max(m_min_x, b_min_x);
        double x_high = min(m_max_x, b_max_x);
        if (x_low > x_high - EPS) return false;
        
        vector<double> test_xs;
        test_xs.push_back(x_low);
        test_xs.push_back(x_high);
        if (blocker.p1.x >= x_low - EPS && blocker.p1.x <= x_high + EPS) test_xs.push_back(blocker.p1.x);
        if (blocker.p2.x >= x_low - EPS && blocker.p2.x <= x_high + EPS) test_xs.push_back(blocker.p2.x);
        if (mover.p1.x >= x_low - EPS && mover.p1.x <= x_high + EPS) test_xs.push_back(mover.p1.x);
        if (mover.p2.x >= x_low - EPS && mover.p2.x <= x_high + EPS) test_xs.push_back(mover.p2.x);
        
        for (double x : test_xs) {
            double my = -1e18;
            if (abs(mover.p1.x - mover.p2.x) > EPS) {
                double t = (x - mover.p1.x) / (mover.p2.x - mover.p1.x);
                if (t >= -EPS && t <= 1.0 + EPS) my = mover.p1.y + t * (mover.p2.y - mover.p1.y);
            } else {
                if (abs(x - mover.p1.x) < EPS) my = max(mover.p1.y, mover.p2.y);
            }
            
            double by = -1e18;
            if (abs(blocker.p1.x - blocker.p2.x) > EPS) {
                double t = (x - blocker.p1.x) / (blocker.p2.x - blocker.p1.x);
                if (t >= -EPS && t <= 1.0 + EPS) by = blocker.p1.y + t * (blocker.p2.y - blocker.p1.y);
            } else {
                if (abs(x - blocker.p1.x) < EPS) by = max(blocker.p1.y, blocker.p2.y);
            }
            
            if (my > -1e17 && by > -1e17) {
                if (by > my + EPS) return true;
            }
        }
        return false;
    }
    else if (dir == 3) { // Down
        if (b_min_y > m_max_y + EPS) return false;
        if (b_min_x > m_max_x + EPS || b_max_x < m_min_x - EPS) return false;
        
        double x_low = max(m_min_x, b_min_x);
        double x_high = min(m_max_x, b_max_x);
        if (x_low > x_high - EPS) return false;
        
        vector<double> test_xs;
        test_xs.push_back(x_low);
        test_xs.push_back(x_high);
        if (blocker.p1.x >= x_low - EPS && blocker.p1.x <= x_high + EPS) test_xs.push_back(blocker.p1.x);
        if (blocker.p2.x >= x_low - EPS && blocker.p2.x <= x_high + EPS) test_xs.push_back(blocker.p2.x);
        if (mover.p1.x >= x_low - EPS && mover.p1.x <= x_high + EPS) test_xs.push_back(mover.p1.x);
        if (mover.p2.x >= x_low - EPS && mover.p2.x <= x_high + EPS) test_xs.push_back(mover.p2.x);
        
        for (double x : test_xs) {
            double my = 1e18;
            if (abs(mover.p1.x - mover.p2.x) > EPS) {
                double t = (x - mover.p1.x) / (mover.p2.x - mover.p1.x);
                if (t >= -EPS && t <= 1.0 + EPS) my = mover.p1.y + t * (mover.p2.y - mover.p1.y);
            } else {
                if (abs(x - mover.p1.x) < EPS) my = min(mover.p1.y, mover.p2.y);
            }
            
            double by = 1e18;
            if (abs(blocker.p1.x - blocker.p2.x) > EPS) {
                double t = (x - blocker.p1.x) / (blocker.p2.x - blocker.p1.x);
                if (t >= -EPS && t <= 1.0 + EPS) by = blocker.p1.y + t * (blocker.p2.y - blocker.p1.y);
            } else {
                if (abs(x - blocker.p1.x) < EPS) by = min(blocker.p1.y, blocker.p2.y);
            }
            
            if (my < 1e17 && by < 1e17) {
                if (by < my - EPS) return true;
            }
        }
        return false;
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<Segment> segs(n + 1);
        for (int i = 1; i <= n; ++i) {
            segs[i].id = i;
            cin >> segs[i].p1.x >> segs[i].p1.y >> segs[i].p2.x >> segs[i].p2.y;
            segs[i].removed = false;
        }
        
        vector<pair<int, int>> ops(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> ops[i].first >> ops[i].second;
        }
        
        int first_invalid = -1;
        
        // 第一部分：找出最早非法移動
        // 模擬過程
        vector<bool> temp_removed(n + 1, false);
        
        for (int i = 1; i <= n; ++i) {
            int id = ops[i].first;
            int dir = ops[i].second;
            
            bool can_move = true;
            for (int j = 1; j <= n; ++j) {
                if (i == j) continue; // 自己不會擋自己 (邏輯上已移除或尚未處理)
                // 注意：這裡我們要檢查的是當前狀態下，id 是否被任何未移除的 j 擋住
                if (!temp_removed[j]) {
                    // 構造臨時對象用於檢查
                    Segment mover = segs[id];
                    mover.removed = false; // 在檢查時它還沒被移除
                    Segment blocker = segs[j];
                    blocker.removed = false;
                    
                    if (blocks(mover, blocker, dir)) {
                        can_move = false;
                        break;
                    }
                }
            }
            
            if (!can_move) {
                first_invalid = i;
                break;
            }
            
            // 執行移除
            temp_removed[id] = true;
        }
        
        cout << first_invalid << "\n";
        
        // 第二部分：輸出一個合法的移動方案
        // 由於題目保證存在合法方案，且 N 不大 (通常此類題 N<=1000 或更小，若 N 大則需優化)
        // 這裡採用貪心模擬：每一輪找一個可以移動的線段移除。
        // 但題目要求輸出什麼？題目描述說："給出一個合法的移動方案完成這個遊戲"
        // 但輸出說明只說："输出包含一个 1 到 n 之间的整数，表示最早出现非法移动的是哪一轮。"
        // 仔細看題目：輸出說明只要求輸出最早非法輪次。
        // 問題描述中的 "2) 給出一個合法的移動方案" 可能是指在找到非法後，需要重新規劃？
        // 不，再看 ZeroJudge a426 的實際要求。通常這類題目如果輸出說明只寫一個整數，那就只輸出一個整數。
        // 但是題目內容確實写了兩點要求。讓我們再讀一次輸出說明。
        // "输出包含一个 1 到 n 之间的整数，表示最早出现非法移动的是哪一轮。"
        // 這很奇怪。難道只需要輸出第一問？
        // 查閱類似題目或經驗：有些題目描述會有背景故事或多餘要求，以輸出說明為準。
        // 如果真的要輸出方案，格式會是怎樣？題目沒說。
        // 假設只需輸出第一問的輪次。
        // 等等，如果題目真的要求輸出方案，通常會說 "接下來一行..." 或 "第二行..."。
        // 這裡完全沒提。極大機率只需輸出第一問。
        // 為了保險，我再確認一下題意邏輯。
        // 題目說："請你幫助他：1)... 2)..."
        // 然後 "輸出說明：输出包含一个...整数..."
        // 這通常意味著只需要輸出第一問的答案。第二問可能是題目背景的敘述，或者是需要在程式內部驗證但不需輸出？
        // 或者，這題的原始來源 (WC2012) 可能有不同要求，但 ZeroJudge 改版後只要求第一問。
        // 根據 ZeroJudge 常見的尿性，以輸出說明為準。只輸出那個整數。
        
        // 如果之後發現需要輸出方案，邏輯如下：
        // 重置 removed 狀態
        // 進行 n 輪，每輪遍歷所有未移除線段，找到第一個可以移動的 (任意方向？不，題目沒指定第二問的方向)
        // 啊，第二問是 "給出一個合法的移動方案"，意味著我們要自己決定順序和方向嗎？
        // 不，題目說 "Will 還將給出每一輪游戏中，他想要移動的針葉編號以及移動方向"，這是針對第一問的。
        // 第二問可能意指：如果 Will 的操作序列有錯，請你給出一個能全部移完的序列？
        // 但輸出格式完全沒提。
        // 結論：只輸出第一問的整數。
    }
    
    return 0;
}
