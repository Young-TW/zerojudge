#include <iostream>

using namespace std;

bool is_new_line = true;

int dfs(int n, int depth) {
    if (n <= 1) {
        if (is_new_line) {
            for (int i = 0; i < depth * 5; ++i) {
                cout << ' ';
            }
        }
        cout << "f(" << n << ")\n";
        is_new_line = true;
        return n;
    } else {
        if (is_new_line) {
            for (int i = 0; i < depth * 5; ++i) {
                cout << ' ';
            }
        }
        cout << "f(" << n << ") ";
        is_new_line = false;
        int val1 = dfs(n - 1, depth + 1);
        int val2 = dfs(n - 2, depth + 1);
        return val1 + val2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        is_new_line = true;
        int ans = dfs(n, 0);
        cout << "f(" << n << ") = " << ans << "\n";
    }
    return 0;
}
