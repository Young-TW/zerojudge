#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int n;
int pos[12];
bool col[12], d1[23], d2[23];
int cnt;
vector<string> items;

void solve(int r) {
    if (r == n) {
        string board;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board += (pos[i] == j) ? 'Q' : 'x';
            }
            if (i + 1 < n) board += '\n';
        }
        items.push_back(board);
        cnt++;
        return;
    }
    for (int c = 0; c < n; c++) {
        if (!col[c] && !d1[r + c] && !d2[r - c + n]) {
            col[c] = d1[r + c] = d2[r - c + n] = true;
            pos[r] = c;
            solve(r + 1);
            col[c] = d1[r + c] = d2[r - c + n] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n && n != 0) {
        cnt = 0;
        memset(col, 0, sizeof(col));
        memset(d1, 0, sizeof(d1));
        memset(d2, 0, sizeof(d2));
        solve(0);
        items.push_back(to_string(cnt));
    }
    string out;
    for (size_t i = 0; i < items.size(); i++) {
        if (i) out += "\n\n";
        out += items[i];
    }
    if (!out.empty()) out += '\n';
    cout << out;
    return 0;
}
