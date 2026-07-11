#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

void solve() {
    int n;
    while (cin >> n) {
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }

        // dist[i][j] will store the minimum Manhattan distance to any hole ('.')
        // Initialize with 0 if hole, else a large number.
        vector<vector<int> > dist(n, vector<int>(n, INT_MAX));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '.') {
                    dist[i][j] = 0;
                }
            }
        }

        // Pass 1: Top-Left to Bottom-Right
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i > 0 && dist[i-1][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i-1][j] + 1);
                }
                if (j > 0 && dist[i][j-1] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][j-1] + 1);
                }
            }
        }

        // Pass 2: Top-Right to Bottom-Left
        for (int i = 0; i < n; ++i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i > 0 && dist[i-1][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i-1][j] + 1);
                }
                if (j < n - 1 && dist[i][j+1] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][j+1] + 1);
                }
            }
        }

        // Pass 3: Bottom-Left to Top-Right
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                if (i < n - 1 && dist[i+1][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i+1][j] + 1);
                }
                if (j > 0 && dist[i][j-1] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][j-1] + 1);
                }
            }
        }

        // Pass 4: Bottom-Right to Top-Left
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i < n - 1 && dist[i+1][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i+1][j] + 1);
                }
                if (j < n - 1 && dist[i][j+1] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][j+1] + 1);
                }
            }
        }

        long long count = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '.') continue;

                // Calculate distance to borders (outside of grid)
                // Distance to row -1 is i+1
                // Distance to row n is n-i
                // Distance to col -1 is j+1
                // Distance to col n is n-j
                int border_dist = min(min(i + 1, n - i), min(j + 1, n - j));
                
                int d = min(dist[i][j], border_dist);
                
                // If d is the min distance to a hole or border, then the max radius R is d-1.
                // Because if radius is R, it includes points at distance R.
                // So we need R < d => R <= d-1.
                // Valid radii are 1, 2, ..., d-1.
                // Number of such kites is d-1 (if d-1 >= 1).
                if (d > 1) {
                    count += (d - 1);
                }
            }
        }
        
        // Now count squares (axis-aligned)
        // dp_sq[i][j] = size of largest square ending at (i,j) (bottom-right)
        vector<vector<int> > dp_sq(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '.') {
                    dp_sq[i][j] = 0;
                    continue;
                }
                if (i == 0 || j == 0) {
                    dp_sq[i][j] = 1;
                } else {
                    int m = dp_sq[i-1][j];
                    if (dp_sq[i][j-1] < m) m = dp_sq[i][j-1];
                    if (dp_sq[i-1][j-1] < m) m = dp_sq[i-1][j-1];
                    dp_sq[i][j] = m + 1;
                }
                
                // Count squares of size >= 2
                // If max size is k, then squares of size 2, 3, ..., k exist.
                // Count = k-1 if k>=2.
                if (dp_sq[i][j] > 1) {
                    count += (dp_sq[i][j] - 1);
                }
            }
        }

        cout << count << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
