#include <bits/stdc++.h>
using namespace std;

int N;
vector<string> img;
vector<vector<int>> ps;          // prefix sum of black pixels (1)

int sumRegion(int r, int c, int sz) {
    // sum of img[r .. r+sz-1][c .. c+sz-1]
    int r2 = r + sz;
    int c2 = c + sz;
    return ps[r2][c2] - ps[r][c2] - ps[r2][c] + ps[r][c];
}

void dfs(int r, int c, int sz, vector<char> &out) {
    int black = sumRegion(r, c, sz);
    if (black == 0) {                 // all white
        out.push_back('w');
        return;
    }
    if (black == sz * sz) {           // all black
        out.push_back('b');
        return;
    }
    out.push_back('g');
    int half = sz / 2;
    // order required by the problem picture: TR, TL, BL, BR
    dfs(r, c + half, half, out);      // top‑right
    dfs(r, c, half, out);             // top‑left
    dfs(r + half, c, half, out);      // bottom‑left
    dfs(r + half, c + half, half, out); // bottom‑right
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N) {
        img.assign(N, "");
        for (int i = 0; i < N; ++i) {
            cin >> img[i];
        }

        // build prefix sum (size N+1 x N+1)
        ps.assign(N + 1, vector<int>(N + 1, 0));
        for (int i = 0; i < N; ++i) {
            int rowSum = 0;
            for (int j = 0; j < N; ++j) {
                rowSum += (img[i][j] == '1');
                ps[i + 1][j + 1] = ps[i][j + 1] + rowSum;
            }
        }

        vector<char> tokens;
        dfs(0, 0, N, tokens);

        for (size_t i = 0; i < tokens.size(); ++i) {
            if (i) cout << ' ';
            cout << tokens[i];
        }
        cout << '\n';
    }
    return 0;
}
