#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string X, Y;
    while (cin >> X >> Y) {
        int rem = 0;
        for (char c : X) {
            rem = (rem * 10 + (c - '0')) % 11;
        }
        for (char c : Y) {
            rem = (rem * 10 + (c - '0')) % 11;
        }
        if (rem == 0) cout << "Yes\n";
        else          cout << "No\n";
    }
    return 0;
}
