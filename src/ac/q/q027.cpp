#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    // The problem states a single test case, but reading until EOF also works.
    while (cin >> s) {
        int rem = 0;
        for (char c : s) {
            rem = (rem * 10 + (c - '0')) % 17;
        }
        if (rem == 0) {
            cout << "Yes";
        } else {
            int diff = rem < 17 - rem ? rem : 17 - rem;
            cout << diff;
        }
        // If there could be more test cases, separate outputs by newline.
        if (!cin.eof()) cout << '\n';
    }
    return 0;
}
