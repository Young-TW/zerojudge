#include <iostream>

using namespace std;

int ans[16] = {0};
int count_val;
int mask;

void dfs(int row, int ld, int rd) {
    if (row == mask) {
        count_val++;
        return;
    }
    int available = ~(row | ld | rd) & mask;
    while (available) {
        int p = available & -available;
        available ^= p;
        dfs(row | p, (ld | p) << 1, (rd | p) >> 1);
    }
}

void precompute() {
    for (int n = 1; n <= 15; ++n) {
        count_val = 0;
        mask = (1 << n) - 1;
        dfs(0, 0, 0);
        ans[n] = count_val;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int n;
    while (cin >> n) {
        if (n >= 1 && n <= 15) {
            cout << ans[n] << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
    return 0;
}
