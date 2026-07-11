#include <iostream>
#include <vector>
#include <algorithm>

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
        vector<int> last_col(vals.size(), -1);
        vector<int> version(vals.size(), 0);
        vector<int> L(m);

        for (int u = 0; u < n; ++u) {
            int current_version = u + 1;
            fill(L.begin(), L.end(), 0);

            for (int d = u; d < n; ++d) {
                const vector<int>& row = a[d];
                int height = d - u + 1;
                for (int j = 0; j < m; ++j) {
                    int v = row[j];
                    int lc = (version[v] == current_version) ? last_col[v] : -1;
                    if (lc + 1 > L[j]) L[j] = lc + 1;
                    last_col[v] = j;
                    version[v] = current_version;
                    if (j > 0) {
                        if (L[j - 1] > L[j]) L[j] = L[j - 1];
                    }
                    int width = j - L[j] + 1;
                    if (width > 0) {
                        int area = height * width;
                        if (area > max_area) {
                            max_area = area;
                        }
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
