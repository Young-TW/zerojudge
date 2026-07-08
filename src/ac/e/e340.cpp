#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    vector<long long> a(n);
    a[0] = b[0];
    for (int i = 1; i < n; i++) a[i] = b[i] - b[i - 1];
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
