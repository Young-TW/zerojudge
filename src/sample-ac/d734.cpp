#include <iostream>

using namespace std;

int n;
int current[25];
int target[25];
int steps;

char get_char(int x) {
    if (x == 1) return 'a';
    if (x == 2) return 'b';
    return 'c';
}

void solve(int k) {
    if (k == 0) return;
    if (current[k] == target[k]) {
        solve(k - 1);
    } else {
        int other = 6 - current[k] - target[k];
        int old_target[25];
        for (int i = 1; i < k; i++) {
            old_target[i] = target[i];
            target[i] = other;
        }
        solve(k - 1);
        
        cout << "ring " << k << " : " << get_char(current[k]) << " -> " << get_char(target[k]) << "\n";
        current[k] = target[k];
        steps++;
        
        for (int i = 1; i < k; i++) {
            target[i] = old_target[i];
        }
        solve(k - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        for (int i = 1; i <= n; i++) cin >> current[i];
        for (int i = 1; i <= n; i++) cin >> target[i];
        steps = 0;
        solve(n);
        cout << steps << "\n";
    }
    return 0;
}
