#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    long long x, y;
    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        if (N <= 0) continue;
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) {
            cin >> pts[i].x >> pts[i].y;
        }
        Point S = pts[0], T = pts[0];
        for (const auto& p : pts) {
            if (p.x < S.x || (p.x == S.x && p.y < S.y)) S = p;
            if (p.x > T.x || (p.x == T.x && p.y > T.y)) T = p;
        }
        if (S == T) {
            cout << S.x << ' ' << S.y << '\n';
            continue;
        }
        vector<Point> cand;
        cand.reserve(N);
        cand.push_back(S);
        cand.push_back(T);
        for (const auto& p : pts) {
            if (p == S || p == T) continue;
            if (p.x < S.x || p.x > T.x) continue;
            if (p.y < S.y || p.y > T.y) continue;
            cand.push_back(p);
        }
        sort(cand.begin(), cand.end(), [](const Point& a, const Point& b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        });
        cand.erase(unique(cand.begin(), cand.end(), [](const Point& a, const Point& b) {
            return a.x == b.x && a.y == b.y;
        }), cand.end());

        vector<Point> st;
        st.reserve(cand.size());
        for (const auto& p : cand) {
            while (st.size() >= 2) {
                const Point& a = st[st.size()-2];
                const Point& b = st.back();
                __int128 cross = (__int128)(b.x - a.x) * (p.y - b.y) - (__int128)(b.y - a.y) * (p.x - b.x);
                if (cross < 0) {
                    st.pop_back();
                } else {
                    break;
                }
            }
            st.push_back(p);
        }
        for (const auto& p : st) {
            cout << p.x << ' ' << p.y << '\n';
        }
    }
    return 0;
}
