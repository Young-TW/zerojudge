#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, n;
    while (cin >> m >> n) {
        string id;
        for (int i = 0; i < m; ++i) cin >> id; // all members
        for (int i = 0; i < n; ++i) cin >> id; // present members
        cout << (m - n) << '\n';
    }
    return 0;
}
