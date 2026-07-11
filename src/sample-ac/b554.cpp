#include <iostream>

using namespace std;

int n;
int grid[6][6];
int max_len;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int x, int y, long long visited, int current_len, int unvisited_ones) {
    if (current_len > max_len) {
        max_len = current_len;
    }
    if (current_len + unvisited_ones <= max_len) {
        return;
    }
    
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
            int bit = nx * n + ny;
            if (grid[nx][ny] == 1 && !((visited >> bit) & 1)) {
                dfs(nx, ny, visited | (1LL << bit), current_len + 1, unvisited_ones - 1);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> n) {
        int total_ones = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                char c;
                cin >> c;
                grid[i][j] = c - '0';
                if (grid[i][j] == 1) {
                    total_ones++;
                }
            }
        }
        
        max_len = 0;
        if (grid[0][0] == 1) {
            dfs(0, 0, 1LL << 0, 1, total_ones - 1);
        }
        
        cout << max_len << "\n";
    }
    
    return 0;
}
