#include <iostream>
#include <string>
using namespace std;

string shapes[5][2] = {
    {"*000", "***0"},
    {"0000", "****"},
    {"00*0", "***0"},
    {"**00", "**00"},
    {"***0", "0*00"}
};

int n, m;
int seq[6];
int cnt[5];
long long total;
bool first;

void printSeq() {
    if (!first) cout << "\n\n";
    first = false;
    for (int row = 0; row < 2; row++) {
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < 4; c++) {
                char ch = shapes[seq[i]][row][c];
                cout << (ch == '0' ? ' ' : ch);
            }
            cout << "|";
        }
        cout << "\n";
    }
}

void dfs(int pos) {
    if (pos == n) {
        printSeq();
        total++;
        return;
    }
    for (int t = 0; t < 5; t++) {
        if (pos > 0 && seq[pos-1] == t) continue;
        if (cnt[t] >= m) continue;
        seq[pos] = t;
        cnt[t]++;
        dfs(pos + 1);
        cnt[t]--;
    }
}

int main() {
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        total = 0;
        first = true;
        for (int i = 0; i < 5; i++) cnt[i] = 0;
        dfs(0);
        cout << "\n\nSum : " << total << "\n";
    }
    return 0;
}
