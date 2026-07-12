#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool check(int r, int c, int s, const vector<string>& grid) {
    int W = 3 * s - 2;
    int H = 2 * s - 2;
    int N = grid.size();
    int M = grid[0].size();
    
    if (r + H > N || c + W > M) return false;
    
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            char expected;
            if (i == 0 || i == s / 2 || i == s - 1 || j == 0 || j == s - 1) {
                expected = 'x';
            } else {
                expected = '.';
            }
            if (grid[r + i][c + j] != expected) return false;
            if (grid[r + i][c + 2 * s - 2 + j] != expected) return false;
        }
        for (int j = s; j < 2 * s - 2; ++j) {
            if (grid[r + i][c + j] != '.') return false;
        }
    }
    
    for (int i = s; i < H; ++i) {
        if (grid[r + i][c] != 'x') return false;
        if (grid[r + i][c + W - 1] != 'x') return false;
        for (int j = 1; j < W - 1; ++j) {
            if (grid[r + i][c + j] != '.') return false;
        }
    }
    
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    vector<string> grid;
    size_t max_len = 0;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        grid.push_back(line);
        if (line.length() > max_len) {
            max_len = line.length();
        }
    }
    
    if (grid.empty() || max_len == 0) {
        cout << 0 << endl;
        return 0;
    }
    
    for (string& s : grid) {
        if (s.length() < max_len) {
            s.append(max_len - s.length(), '.');
        }
    }
    
    int N = grid.size();
    int M = max_len;
    
    int count = 0;
    int max_s = 0;
    
    int max_possible_s = min((M + 2) / 3, (N + 2) / 2);
    if (max_possible_s % 2 == 0) max_possible_s--;
    
    for (int s = max_possible_s; s >= 5; s -= 2) {
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (grid[r][c] != 'x') continue;
                if (check(r, c, s, grid)) {
                    count++;
                    max_s = max(max_s, s);
                    int W = 3 * s - 2;
                    int H = 2 * s - 2;
                    for (int i = 0; i < H; ++i) {
                        for (int j = 0; j < W; ++j) {
                            if (grid[r + i][c + j] == 'x') {
                                grid[r + i][c + j] = '.';
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (count == 0) {
        cout << 0 << endl;
    } else {
        cout << count << " " << max_s << endl;
    }
    
    return 0;
}
