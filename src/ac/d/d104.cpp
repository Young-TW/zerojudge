#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M, N, K, L, D;
    while (cin >> M >> N >> K >> L >> D) {
        vector<int> row_cnt(M + 1, 0);
        vector<int> col_cnt(N + 1, 0);
        
        for (int i = 0; i < D; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 == x2) {
                int col = min(y1, y2);
                col_cnt[col]++;
            } else {
                int row = min(x1, x2);
                row_cnt[row]++;
            }
        }
        
        vector<pair<int, int>> rows;
        for (int i = 1; i < M; ++i) {
            rows.push_back({row_cnt[i], i});
        }
        sort(rows.begin(), rows.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first > b.first;
            return a.second < b.second;
        });
        
        vector<int> ans_rows;
        for (int i = 0; i < K && i < (int)rows.size(); ++i) {
            ans_rows.push_back(rows[i].second);
        }
        sort(ans_rows.begin(), ans_rows.end());
        
        vector<pair<int, int>> cols;
        for (int i = 1; i < N; ++i) {
            cols.push_back({col_cnt[i], i});
        }
        sort(cols.begin(), cols.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first > b.first;
            return a.second < b.second;
        });
        
        vector<int> ans_cols;
        for (int i = 0; i < L && i < (int)cols.size(); ++i) {
            ans_cols.push_back(cols[i].second);
        }
        sort(ans_cols.begin(), ans_cols.end());
        
        for (size_t i = 0; i < ans_rows.size(); ++i) {
            cout << ans_rows[i] << (i + 1 == ans_rows.size() ? "" : " ");
        }
        cout << "\n";
        for (size_t i = 0; i < ans_cols.size(); ++i) {
            cout << ans_cols[i] << (i + 1 == ans_cols.size() ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}
