#include <bits/stdc++.h>
using namespace std;

struct PairHash {
    size_t operator()(const long long &x) const noexcept {
        return std::hash<long long>()(x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // ---------- 1. 模擬並偵測高速公路 ----------
    const int MAX_SIM = 20000;          // 足夠覆蓋混沌期
    const int PERIOD   = 104;
    const long long DX = -2, DY = -2;   // 每個周期的位移
    
    vector<long long> xs, ys;          // pos[i] 為走 i 步後的座標
    vector<int> dirs;                  // 方向: 0=上,1=右,2=下,3=左
    xs.reserve(MAX_SIM + 1);
    ys.reserve(MAX_SIM + 1);
    dirs.reserve(MAX_SIM + 1);
    
    // 起始狀態
    long long x = 0, y = 0;
    int dir = 0; // 上
    xs.push_back(x);
    ys.push_back(y);
    dirs.push_back(dir);
    
    unordered_set<long long, PairHash> black; // 只記錄黑格
    auto encode = [](long long a, long long b)->long long{
        return (a<<32) ^ (b & 0xffffffffLL);
    };
    
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};
    
    for (int step = 1; step <= MAX_SIM; ++step) {
        long long key = encode(x, y);
        bool isBlack = black.find(key) != black.end();
        if (!isBlack) {               // 白格：右轉，塗黑
            dir = (dir + 1) & 3;
            black.insert(key);
        } else {                      // 黑格：左轉，塗白
            dir = (dir + 3) & 3;
            black.erase(key);
        }
        x += dx[dir];
        y += dy[dir];
        xs.push_back(x);
        ys.push_back(y);
        dirs.push_back(dir);
    }
    
    // ---------- 2. 找到高速公路的起點 ----------
    int startHighway = -1;
    for (int s = 0; s + 2*PERIOD <= (int)xs.size()-1; ++s) {
        bool ok = true;
        for (int k = 0; k < PERIOD; ++k) {
            long long dx1 = xs[s + k + PERIOD] - xs[s + k];
            long long dy1 = ys[s + k + PERIOD] - ys[s + k];
            if (dx1 != DX || dy1 != DY || dirs[s + k + PERIOD] != dirs[s + k]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            startHighway = s;
            break;
        }
    }
    if (startHighway == -1) { // 理論上不會發生，若發生就把整段當作表
        startHighway = (int)xs.size() - 1;
    }
    
    // ---------- 3. 處理輸入 ----------
    unsigned long long n;
    while (cin >> n) {
        long long ansX, ansY;
        if (n <= (unsigned long long)xs.size() - 1) {
            ansX = xs[(size_t)n];
            ansY = ys[(size_t)n];
        } else {
            // n > 模擬上限，使用高速公路公式
            unsigned long long offset = n - (unsigned long long)startHighway;
            unsigned long long cycles = offset / PERIOD;
            unsigned long long rem    = offset % PERIOD;
            
            __int128 baseX = xs[startHighway];
            __int128 baseY = ys[startHighway];
            __int128 addX  = (__int128)DX * ( (__int128)cycles );
            __int128 addY  = (__int128)DY * ( (__int128)cycles );
            __int128 intraX = xs[startHighway + (size_t)rem] - xs[startHighway];
            __int128 intraY = ys[startHighway + (size_t)rem] - ys[startHighway];
            
            __int128 resX = baseX + addX + intraX;
            __int128 resY = baseY + addY + intraY;
            ansX = (long long)resX;
            ansY = (long long)resY;
        }
        cout << '(' << ansX << ',' << ansY << ')' << '\n';
    }
    return 0;
}
