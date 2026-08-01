// b579. 恢復分數 — 已知 n-1 人的分數與全部 n 人的 Y/N 作答,判斷第 n 人分數能否唯一確定。
//
// 解法:答案卷 key 是 p 個 Y/N。第 i 人分數 = 與 key 相符的題數。把「欄位作答樣式」相同的題分組
// (m=n-1 位樣式 + 第 n 人該題答案),同組題只需決定「多少題 key 設為 Y」(k∈[0,cnt])。
// 令 w[g][i]=+1(第 i 人在組 g 答 Y)否則 -1;需 Σ w[g][i]·k_g = Ti[i](Ti=score[i]+Si-p)。
// 用「狀態合併 DP」:state = 目前各人的 cur 向量 → 可達第 n 人分數的 (min,max)。相同 cur 向量合併,
// 把指數 DFS 壓成「可達向量數」(靠後綴上下界剪枝而多項式化),根治舊版 2^p 暴力的 RE/爆炸。
// 終盤看 cur==Ti 的狀態:不存在→矛盾 'c';min==max→'y min';否則無法確定→'n'。
#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <cmath>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        if (n == 0) break;
        int p;
        if (!(cin >> p)) break;
        int m = n - 1;

        // 讀 n-1 人的分數 + p 題作答,及第 n 人的 p 題作答
        vector<int> score(m);
        vector<vector<char>> a(m, vector<char>(p));   // 'Y'/'N'
        for (int i = 0; i < m; ++i) {
            cin >> score[i];
            for (int j = 0; j < p; ++j) cin >> a[i][j];
        }
        vector<char> last(p);
        for (int j = 0; j < p; ++j) cin >> last[j];

        // 依「m 位作答樣式 + 第 n 人答案」分組;key = (mask<<1)|lastBit
        unordered_map<unsigned long long, int> cnt;
        cnt.reserve(p * 2 + 4);
        for (int j = 0; j < p; ++j) {
            unsigned int mask = 0;
            for (int i = 0; i < m; ++i)
                if (a[i][j] == 'Y') mask |= (1u << i);
            unsigned long long k = ((unsigned long long)mask << 1) | (last[j] == 'Y' ? 1u : 0u);
            cnt[k]++;
        }
        int G = (int)cnt.size();
        vector<unsigned int> gmask(G);
        vector<int> gcnt(G), glast(G);
        {
            int t = 0;
            for (auto &kv : cnt) {
                gmask[t] = (unsigned int)(kv.first >> 1);
                glast[t] = (int)(kv.first & 1);
                gcnt[t]  = kv.second;
                ++t;
            }
        }

        // 目標 Ti[i] = score[i] + Si - p (Si=第 i 人答 Y 的題數);並基本可行性檢查
        vector<int> Ti(m);
        bool bad = false;
        for (int i = 0; i < m; ++i) {
            int Si = 0;
            for (int j = 0; j < p; ++j) if (a[i][j] == 'Y') ++Si;
            Ti[i] = score[i] + Si - p;
            if (score[i] < 0 || score[i] > p) bad = true;   // 分數超範圍即矛盾
        }
        if (bad) { cout << "c\n"; continue; }

        // 結構性矛盾早捕:作答向量完全相同的兩人,對任何 key 分數必相同;若記錄分數不同 → 'c'。
        // (此類矛盾可能讓 DP 累積大量部分狀態才在末端失敗;先攔可省時省記憶體、避免 overflow 誤判。)
        {
            unordered_map<unsigned long long, int> seen;
            seen.reserve(m * 2 + 4);
            bool contra = false;
            for (int i = 0; i < m && !contra; ++i) {
                unsigned long long h = 1469598103934665603ull;
                for (int j = 0; j < p; ++j) { h ^= (unsigned char)a[i][j]; h *= 1099511628211ull; }
                auto r = seen.emplace(h, score[i]);
                if (!r.second && r.first->second != score[i]) contra = true;   // 同作答不同分
            }
            if (contra) { cout << "c\n"; continue; }
        }

        // 每組對每人的係數 w[g][i]∈{+1,-1};後綴可達下/上界(用於剪枝)
        vector<vector<int>> w(G, vector<int>(m));
        for (int g = 0; g < G; ++g)
            for (int i = 0; i < m; ++i)
                w[g][i] = ((gmask[g] >> i) & 1u) ? 1 : -1;
        vector<vector<int>> sufMin(G + 1, vector<int>(m, 0)), sufMax(G + 1, vector<int>(m, 0));
        for (int g = G - 1; g >= 0; --g)
            for (int i = 0; i < m; ++i) {
                int lo = (w[g][i] == 1) ? 0 : -gcnt[g];   // k∈[0,cnt] → w·k 範圍
                int hi = (w[g][i] == 1) ? gcnt[g] : 0;
                sufMin[g][i] = sufMin[g + 1][i] + lo;
                sufMax[g][i] = sufMax[g + 1][i] + hi;
            }

        // 代數判定:第 n 人分數 nth = base + Σ_g s_g·k_g,其中 s_g=+1(第 n 人在組 g 答 Y)否則 -1。
        // nth 對「所有可行 k」為常數 ⟺ 係數向量 s 落在約束矩陣 W 的列空間(Wᵀλ=s 有解);
        // 此時 nth ≡ base + Σ_i λ_i·Ti[i]。用 Gaussian 消去解出 λ,O(m·G)。
        // 作用:當可行解「巨量」導致 DP 爆(overflow)時,靠此判定確定值(而非誤判 'n')。
        long long base = 0;
        for (int g = 0; g < G; ++g) if (!glast[g]) base += gcnt[g];
        vector<vector<double>> M(G, vector<double>(m + 1));
        for (int g = 0; g < G; ++g) {
            for (int i = 0; i < m; ++i) M[g][i] = w[g][i];
            M[g][m] = glast[g] ? 1.0 : -1.0;               // s_g
        }
        vector<int> pivotRow(m, -1);
        for (int col = 0, row = 0; col < m && row < G; ++col) {
            int sel = -1; double best = 1e-9;
            for (int r = row; r < G; ++r) if (fabs(M[r][col]) > best) { best = fabs(M[r][col]); sel = r; }
            if (sel < 0) continue;
            swap(M[row], M[sel]);
            double pv = M[row][col];
            for (int c = col; c <= m; ++c) M[row][c] /= pv;
            for (int r = 0; r < G; ++r) if (r != row) {
                double f = M[r][col];
                if (fabs(f) > 1e-12) for (int c = col; c <= m; ++c) M[r][c] -= f * M[row][c];
            }
            pivotRow[col] = row++;
        }
        bool sInRow = true;                                // s 是否落在 W 列空間(系統一致)
        for (int r = 0; r < G && sInRow; ++r) {
            bool allZero = true;
            for (int i = 0; i < m; ++i) if (fabs(M[r][i]) > 1e-6) { allZero = false; break; }
            if (allZero && fabs(M[r][m]) > 1e-6) sInRow = false;
        }
        long long Vdet = base;
        if (sInRow) {
            double acc = 0.0;
            for (int i = 0; i < m; ++i)
                acc += (pivotRow[i] >= 0 ? M[pivotRow[i]][m] : 0.0) * (double)Ti[i];
            Vdet += llround(acc);
        }

        // 合併 DP:key = 目前各人 cur 向量(緊湊 array<signed char,m>,範圍 ±p≤60 足夠,免堆積配置省記憶體),
        // value = 第 n 人可達分數的 (min,max)。相同 cur 合併 → 狀態數遠少於 DFS 節點。後綴界剪枝。
        // 記憶體上限:CAP 使 cur+nxt 同時存活約 ~90MB(判題機容得下);真實測資狀態遠少於此。
        // 逾 CAP(可行解自由度巨大)才退回代數判定:sInRow→常數'y',否則'n'(皆正確)。
        typedef array<signed char, 20> Key;
        struct KeyHash {
            size_t operator()(const Key& v) const {
                size_t h = 1469598103934665603ull;
                for (int i = 0; i < 20; ++i) { h ^= (size_t)(unsigned char)v[i]; h *= 1099511628211ull; }
                return h;
            }
        };
        const size_t CAP = 700000;
        bool overflow = false;

        Key zero{};
        unordered_map<Key, pair<int,int>, KeyHash> cur;
        cur.reserve(1024);
        cur.emplace(zero, make_pair(0, 0));

        for (int g = 0; g < G && !overflow; ++g) {
            unordered_map<Key, pair<int,int>, KeyHash> nxt;
            nxt.reserve(cur.size() * 2 + 16);
            for (auto &st : cur) {
                const Key& v = st.first;
                int mn = st.second.first, mx = st.second.second;
                for (int k = 0; k <= gcnt[g]; ++k) {
                    Key nv = v;
                    bool ok = true;
                    for (int i = 0; i < m; ++i) {
                        int val = (int)v[i] + w[g][i] * k;
                        if (Ti[i] < val + sufMin[g + 1][i] || Ti[i] > val + sufMax[g + 1][i]) { ok = false; break; }
                        nv[i] = (signed char)val;
                    }
                    if (!ok) continue;
                    int add = glast[g] ? k : (gcnt[g] - k);   // 第 n 人此組得分
                    int nmn = mn + add, nmx = mx + add;
                    auto it = nxt.find(nv);
                    if (it == nxt.end()) nxt.emplace(nv, make_pair(nmn, nmx));
                    else {
                        if (nmn < it->second.first)  it->second.first  = nmn;
                        if (nmx > it->second.second) it->second.second = nmx;
                    }
                }
                if (nxt.size() > CAP) { overflow = true; break; }
            }
            cur.swap(nxt);
            if (cur.empty()) break;
        }

        if (overflow) {
            // 可行解巨量:sInRow ⟹ 第 n 人分數恆為 Vdet('y');否則沿零空間可變('n')。
            if (sInRow) cout << "y " << Vdet << "\n";
            else cout << "n\n";
            continue;
        }

        Key tk{};
        for (int i = 0; i < m; ++i) tk[i] = (signed char)Ti[i];
        // Ti 可能超出 signed char 表示(|Ti|≤p≤60,安全);查表
        auto it = cur.find(tk);
        if (it == cur.end())                    cout << "c\n";              // 無任何 key 吻合 → 矛盾
        else if (it->second.first == it->second.second)
                                                cout << "y " << it->second.first << "\n"; // 唯一
        else                                    cout << "n\n";             // 無法確定
    }
    return 0;
}
