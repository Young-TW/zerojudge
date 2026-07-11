#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

using namespace std;

void solve() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> a(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> a[i][j];
            }
        }

        if (n > m) {
            vector<vector<int>> b(m, vector<int>(n));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    b[j][i] = a[i][j];
                }
            }
            a = b;
            swap(n, m);
        }

        vector<int> vals;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                vals.push_back(a[i][j]);
            }
        }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = lower_bound(vals.begin(), vals.end(), a[i][j]) - vals.begin();
            }
        }

        int max_area = 0;
        // occ[v] = 目前 strip (rows u..d) 中值 v 出現過的欄位集合
        vector<set<int>> occ(vals.size());
        vector<int> touched;      // 本輪 u 動過的值，方便重置
        vector<int> raiseArr(m);  // raiseArr[j] = 以第 j 欄為右界時，左界至少要 >= raiseArr[j]

        for (int u = 0; u < n; ++u) {
            fill(raiseArr.begin(), raiseArr.end(), 0);
            for (int v : touched) occ[v].clear();
            touched.clear();

            for (int d = u; d < n; ++d) {
                const vector<int>& row = a[d];
                for (int j = 0; j < m; ++j) {
                    int v = row[j];
                    set<int>& s = occ[v];
                    if (s.empty()) touched.push_back(v);

                    auto it = s.lower_bound(j);       // 第一個 >= j 的欄位
                    if (it != s.end() && *it == j) {
                        // 同一欄已出現過 v（不同列）→ 含此欄的矩形必重複
                        if (j + 1 > raiseArr[j]) raiseArr[j] = j + 1;
                        auto itr = next(it);
                        if (itr != s.end()) { int cR = *itr; if (j + 1 > raiseArr[cR]) raiseArr[cR] = j + 1; }
                        if (it != s.begin()) { int cL = *prev(it); if (cL + 1 > raiseArr[j]) raiseArr[j] = cL + 1; }
                    } else {
                        // it 為最近的右鄰 (>j)
                        if (it != s.end()) { int cR = *it; if (j + 1 > raiseArr[cR]) raiseArr[cR] = j + 1; }
                        // 最近的左鄰 (<j)
                        if (it != s.begin()) { int cL = *prev(it); if (cL + 1 > raiseArr[j]) raiseArr[j] = cL + 1; }
                    }
                    s.insert(j);
                }

                int lim = 0, height = d - u + 1;
                for (int j = 0; j < m; ++j) {
                    if (raiseArr[j] > lim) lim = raiseArr[j];   // 左界對 j 取前綴最大 → 單調
                    int width = j - lim + 1;
                    if (width > 0) {
                        int area = height * width;
                        if (area > max_area) max_area = area;
                    }
                }
            }
        }
        cout << max_area << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
