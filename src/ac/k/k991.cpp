#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/* encode a pair (x,y) into a 64‑bit integer */
static inline ll enc(int x, int y) { return ( (ll)x << 32 ) ^ (unsigned int)y; }
static inline int  decx(ll v) { return (int)(v >> 32); }
static inline int  decy(ll v) { return (int)(v & 0xffffffffULL); }

/* ---------- boss patterns ---------- */
vector<pair<int,int>> boss_cells(int level)
{
    vector<pair<int,int>> v;
    if (level == 1) {
        v = {{20,20},{20,21},{21,20},{21,21}};
    } else if (level == 2) {
        v = {{20,20},{20,21},{21,20},{21,21},
             {23,23},{23,24},{24,23},{24,24}};
    } else {                // level 3
        v = {{20,20},{20,21},{21,20},{22,22},{23,21},{23,22}};
    }
    return v;
}

/* ---------- glider placements ---------- */
vector<vector<pair<int,int>>> all_gliders;   // each entry = list of 5 cells

/* rotate (x,y) clockwise 90° : (y, -x) */
pair<int,int> rot90(const pair<int,int>& p)
{
    return {p.second, -p.first};
}

/* generate all placements that fit into [0,9] */
void generate_gliders()
{
    // base glider (moves SE)
    vector<pair<int,int>> base = {{0,2},{1,0},{1,2},{2,1},{2,2}};
    for (int r = 0; r < 4; ++r) {
        // rotate r times
        vector<pair<int,int>> cur = base;
        for (int i = 0; i < r; ++i) {
            for (auto &p : cur) p = rot90(p);
        }
        // find bounding box
        int minx = 1e9, maxx = -1e9, miny = 1e9, maxy = -1e9;
        for (auto &p : cur) {
            minx = min(minx, p.first);
            maxx = max(maxx, p.first);
            miny = min(miny, p.second);
            maxy = max(maxy, p.second);
        }
        // translate so that all cells are inside 0..9
        for (int ox = -minx; ox <= 9 - maxx; ++ox) {
            for (int oy = -miny; oy <= 9 - maxy; ++oy) {
                vector<pair<int,int>> placed;
                placed.reserve(5);
                for (auto &p : cur) {
                    placed.emplace_back(p.first + ox, p.second + oy);
                }
                all_gliders.push_back(placed);
            }
        }
    }
}

/* ---------- Life simulation (sparse) ---------- */
bool simulate(const vector<pair<int,int>>& boss,
              const vector<pair<int,int>>& ours)
{
    unordered_set<ll> cur;
    cur.reserve(256);
    for (auto &p : boss) cur.insert(enc(p.first, p.second));
    for (auto &p : ours) cur.insert(enc(p.first, p.second));

    const int dx[8] = {-1,-1,-1,0,0,1,1,1};
    const int dy[8] = {-1,0,1,-1,1,-1,0,1};

    for (int step = 0; step < 100; ++step) {
        unordered_map<ll, int> cnt;
        cnt.reserve(cur.size()*9);
        for (ll v : cur) {
            int x = decx(v), y = decy(v);
            for (int d = 0; d < 8; ++d) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                cnt[enc(nx, ny)]++;
            }
        }
        unordered_set<ll> nxt;
        nxt.reserve(cnt.size());
        for (auto &kv : cnt) {
            int c = kv.second;
            bool alive = cur.find(kv.first) != cur.end();
            if (alive) {
                if (c == 2 || c == 3) nxt.insert(kv.first);
            } else {
                if (c == 3) nxt.insert(kv.first);
            }
        }
        cur.swap(nxt);
        if (cur.empty()) return true;   // early exit possible
    }
    return cur.empty();
}

/* ---------- main ---------- */
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int level;
    if (!(cin >> level)) return 0;

    generate_gliders();

    vector<pair<int,int>> boss = boss_cells(level);
    vector<pair<int,int>> answer;          // cells we will output

    std::mt19937 rng(71268721);
    const int MAX_TRIALS = 200000;

    // try 1,2,3,4 gliders
    for (int trial = 0; trial < MAX_TRIALS; ++trial) {
        int glider_cnt = 1 + (rng() % 4);          // 1 … 4
        vector<pair<int,int>> cand;
        unordered_set<ll> used;
        bool ok = true;
        for (int i = 0; i < glider_cnt; ++i) {
            const auto &g = all_gliders[rng() % all_gliders.size()];
            for (auto &p : g) {
                ll code = enc(p.first, p.second);
                if (used.count(code)) { ok = false; break; }
                used.insert(code);
                cand.push_back(p);
            }
            if (!ok) break;
        }
        if (!ok) continue;
        if (simulate(boss, cand)) {
            answer = cand;
            break;
        }
    }

    // If random search failed (extremely unlikely) fall back to a trivial
    // safe answer: output nothing – the judge will mark WA, but this line
    // is never reached in practice.
    if (answer.empty()) {
        cout << 0 << "\n";
        return 0;
    }

    cout << answer.size() << "\n";
    for (auto &p : answer) cout << p.first << ' ' << p.second << "\n";
    return 0;
}
