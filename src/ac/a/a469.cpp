#include <iostream>
#include <string>
#include <vector>
using namespace std;

void gen(const string& s, int idx, string cur) {
    if (idx == (int)s.size()) {
        cout << cur << "\n";
        return;
    }
    char c = s[idx];
    int n = (int)cur.size();
    for (int i = 0; i <= n; i++) {
        string next = cur.substr(0, i) + c + cur.substr(i);
        gen(s, idx + 1, next);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    bool first = true;
    while (cin >> s) {
        if (!first) cout << "\n";
        first = false;
        gen(s, 1, string(1, s[0]));
    }
    return 0;
}
