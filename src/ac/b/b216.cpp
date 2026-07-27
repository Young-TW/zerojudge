#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int lines[6][3] = {
        {1,2,3}, {4,5,6}, {7,8,9},
        {1,4,7}, {2,5,8}, {3,6,9}
    };
    const int mids[4]   = {2,4,6,8};
    const int corners[4]= {1,3,7,9};

    vector<pair<int,int>> pts;
    int x, y;
    while (cin >> x >> y) {
        pts.emplace_back(x, y);
        if (pts.size() == 9) {
            bool hit[10] = {false};          // indices 1..9

            for (auto &p : pts) {
                int xx = p.first, yy = p.second;
                if (xx > 0 && xx < 30 && yy > 0 && yy < 30 &&
                    xx % 10 != 0 && yy % 10 != 0) {
                    int col = xx / 10;                // 0..2
                    int rowB = yy / 10;               // 0..2 from bottom
                    int cell = (2 - rowB) * 3 + col + 1; // 1..9
                    hit[cell] = true;
                }
            }

            int lineCnt = 0;
            for (int i = 0; i < 6; ++i) {
                if (hit[lines[i][0]] && hit[lines[i][1]] && hit[lines[i][2]])
                    ++lineCnt;
            }

            int score = 0;
            if (hit[5]) score += 2;
            for (int c : mids)   if (hit[c]) score += 5;
            for (int c : corners)if (hit[c]) score += 8;

            cout << lineCnt << ' ' << score << '\n';
            pts.clear();                     // start next test case
        }
    }
    return 0;
}
