#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    int caseNum = 1;
    string out;
    out.reserve(1 << 20);
    char buf[64];

    while (scanf("%d", &N) == 1) {
        vector<pair<int,int>> pts(N);
        for (int i = 0; i < N; ++i) scanf("%d %d", &pts[i].first, &pts[i].second);

        // maximal points: sort by x desc, y desc; keep if y strictly > running max_y
        sort(pts.begin(), pts.end(), [](const pair<int,int>& a, const pair<int,int>& b){
            if (a.first != b.first) return a.first > b.first;
            return a.second > b.second;
        });

        vector<pair<int,int>> ans;
        int maxY = -1;
        for (auto& p : pts) {
            if (p.second > maxY) { ans.push_back(p); maxY = p.second; }
        }
        reverse(ans.begin(), ans.end()); // now ascending by x

        int len = snprintf(buf, sizeof(buf), "Case %d:\n", caseNum);
        out.append(buf, len);
        len = snprintf(buf, sizeof(buf), "Dominate Point: %d\n", (int)ans.size());
        out.append(buf, len);
        for (auto& p : ans) {
            len = snprintf(buf, sizeof(buf), "(%d,%d)\n", p.first, p.second);
            out.append(buf, len);
        }
        ++caseNum;
    }
    fputs(out.c_str(), stdout);
    return 0;
}
