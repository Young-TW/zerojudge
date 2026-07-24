#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        long long ans = (a + c) - (b + d);
        cout << ans << '\n';
    }
    return 0;
}
