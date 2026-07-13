#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        int x;
        cin >> x;
        vector<vector<long long>> tests(x, vector<long long>(n));
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> tests[i][j];
            }
        }
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }
        
        bool reliable = true;
        for (int t = 0; t < x; ++t) {
            vector<long long> a = tests[t];
            for (int j = 0; j < m; ++j) {
                int min_row[256];
                int max_row[256];
                bool has_char[256] = {false};
                
                for (int i = 0; i < n; ++i) {
                    char c = '-';
                    if (j < grid[i].length()) {
                        c = grid[i][j];
                    }
                    if (c != '-') {
                        if (!has_char[(unsigned char)c]) {
                            has_char[(unsigned char)c] = true;
                            min_row[(unsigned char)c] = i;
                            max_row[(unsigned char)c] = i;
                        } else {
                            min_row[(unsigned char)c] = min(min_row[(unsigned char)c], i);
                            max_row[(unsigned char)c] = max(max_row[(unsigned char)c], i);
                        }
                    }
                }
                
                vector<long long> old_a = a;
                for (int c = 0; c < 256; ++c) {
                    if (has_char[c]) {
                        int u = min_row[c];
                        int v = max_row[c];
                        if (u != v) {
                            long long val_u = old_a[u];
                            long long val_v = old_a[v];
                            a[u] = min(val_u, val_v);
                            a[v] = max(val_u, val_v);
                        }
                    }
                }
            }
            
            for (int i = 0; i < n - 1; ++i) {
                if (a[i] > a[i + 1]) {
                    reliable = false;
                    break;
                }
            }
            if (!reliable) break;
        }
        
        if (reliable) {
            cout << "This is a reliable sorting ghost leg!" << endl;
        } else {
            cout << "So sad......This is just a  ghost leg." << endl;
        }
    }
    
    return 0;
}
