#include <iostream>
#include <string>
using namespace std;

static int cnt[10];

static bool canMelds(int c[]) {
    int t[10];
    for (int i = 1; i <= 9; i++) t[i] = c[i];
    for (int i = 1; i <= 9; i++) {
        if (t[i] < 0) return false;
        if (t[i] >= 3) t[i] -= 3;
        if (t[i] > 0) {
            if (i + 2 > 9) return false;
            t[i + 1] -= t[i];
            t[i + 2] -= t[i];
            t[i] = 0;
        }
    }
    for (int i = 1; i <= 9; i++) if (t[i] != 0) return false;
    return true;
}

static bool canWin(int c[]) {
    for (int i = 1; i <= 9; i++) {
        if (c[i] >= 2) {
            c[i] -= 2;
            bool ok = canMelds(c);
            c[i] += 2;
            if (ok) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        int cur[10] = {0};
        for (char ch : s) cur[ch - '0']++;
        string out;
        for (int w = 1; w <= 9; w++) {
            if (cur[w] >= 4) continue;
            cur[w]++;
            if (canWin(cur)) out += char('0' + w);
            cur[w]--;
        }
        cout << out << "\n";
    }
    return 0;
}
