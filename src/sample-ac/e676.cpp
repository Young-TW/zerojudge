#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
int visited[100][100];
int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int dfs(int r, int c) {
    if (r < 0 || r >= n || c < 0 || c >= m) return 0;
    if (visited[r][c] || grid[r][c] != 'W') return 0;
    visited[r][c] = 1;
    int count = 1;
    for (int i = 0; i < 8; i++) {
        count += dfs(r + dr[i], c + dc[i]);
    }
    return count;
}

bool isQueryLine(const string& line) {
    for (char c : line) {
        if (isdigit((unsigned char)c)) return true;
    }
    return false;
}

void stripCR(string& line) {
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    string line;
    getline(cin, line);
    stripCR(line);
    
    for (int tc = 0; tc < T; tc++) {
        while (getline(cin, line)) {
            stripCR(line);
            if (!line.empty()) break;
        }
        if (cin.eof()) break;
        
        grid.clear();
        while (!line.empty() && !isQueryLine(line)) {
            grid.push_back(line);
            if (!getline(cin, line)) break;
            stripCR(line);
        }
        
        n = grid.size();
        m = n > 0 ? grid[0].size() : 0;
        
        while (!line.empty()) {
            stringstream ss(line);
            int i, j;
            ss >> i >> j;
            memset(visited, 0, sizeof(visited));
            int result = dfs(i-1, j-1);
            cout << result << "\n";
            
            if (!getline(cin, line)) {
                line = "";
                break;
            }
            stripCR(line);
        }
        
        if (tc < T - 1) cout << "\n";
    }
    
    return 0;
}
