#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    int k;
    while (cin >> s >> k) {
        char c = k + '0';
        string t;
        for (char ch : s) {
            if (ch != c) {
                t += ch;
            }
        }
        string rev_t = t;
        reverse(rev_t.begin(), rev_t.end());
        if (t == rev_t) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
