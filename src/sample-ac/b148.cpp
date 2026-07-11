#include <iostream>
#include <string>

using namespace std;

char solve(int l, int r, const string& s) {
    if (r - l == 1) {
        char c = (s[l] == '0' ? 'B' : 'I');
        cout << c;
        return c;
    }
    int mid = l + (r - l) / 2;
    char left = solve(l, mid, s);
    char right = solve(mid, r, s);
    
    char c;
    if (left == right) {
        c = left;
    } else {
        c = 'F';
    }
    cout << c;
    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    string s;
    while (cin >> N >> s) {
        solve(0, s.length(), s);
        cout << "\n";
    }
    return 0;
}
