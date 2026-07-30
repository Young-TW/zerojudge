#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long R;
    if (!(cin >> R)) return 0;
    while (R--) {
        long long a, b, c;
        cin >> a >> b >> c;
        int odd = (a & 1) + (b & 1) + (c & 1);
        if (odd == 1) {               // the odd one wins
            if (a & 1) cout << "A\n";
            else if (b & 1) cout << "B\n";
            else cout << "C\n";
        } else if (odd == 2) {        // the even one wins
            if ((a & 1) == 0) cout << "A\n";
            else if ((b & 1) == 0) cout << "B\n";
            else cout << "C\n";
        } else {                      // all three equal probability
            cout << "A B C\n";
        }
    }
    return 0;
}
