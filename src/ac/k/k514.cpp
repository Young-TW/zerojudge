#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long A[4];
    while (cin >> A[0] >> A[1] >> A[2] >> A[3]) {
        int N;
        if (!(cin >> N)) break;
        vector<vector<long long>> mat(4, vector<long long>(N));
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < N; ++j)
                cin >> mat[i][j];

        // Build candidate sets
        vector<unordered_set<long long>> candSet(4);
        vector<vector<long long>> candVec(4);
        for (int i = 0; i < 4; ++i) {
            candSet[i].reserve(N * 2);
            for (int j = 0; j < N; ++j) {
                long long v = mat[i][j];
                if (v % A[i] == 0) {
                    long long k = v / A[i];
                    if (k > 0 && candSet[i].insert(k).second) {
                        candVec[i].push_back(k);
                    }
                }
            }
        }

        // Choose the row with the smallest candidate size
        int base = 0;
        for (int i = 1; i < 4; ++i)
            if (candVec[i].size() < candVec[base].size())
                base = i;

        // Sort candidates of the base row
        sort(candVec[base].begin(), candVec[base].end());

        long long answerK = -1;
        for (long long k : candVec[base]) {
            bool ok = true;
            for (int i = 0; i < 4; ++i) {
                if (i == base) continue;
                if (candSet[i].find(k) == candSet[i].end()) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                answerK = k;
                break;
            }
        }

        if (answerK == -1) {
            cout << -1 << "\n";
        } else {
            cout << answerK * A[0] << ' '
                 << answerK * A[1] << ' '
                 << answerK * A[2] << ' '
                 << answerK * A[3] << "\n";
        }
    }
    return 0;
}
