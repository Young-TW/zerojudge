#include <iostream>
#include <string>

using namespace std;

void dfs(int start, int depth, int n, int m, string& current) {
    if (depth == m) {
        cout << current << "\n";
        return;
    }
    for (int i = start; i < n; ++i) {
        current.push_back('a' + i);
        dfs(i + 1, depth + 1, n, m, current);
        current.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        string current;
        current.reserve(m);
        dfs(0, 0, n, m, current);
    }
    return 0;
}
