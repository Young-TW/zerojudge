#include <iostream>
#include <string>

using namespace std;

long long to_num(const string& s) {
    long long res = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        res = res * 26 + (s[i] - 'A' + 1);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s1, s2;
    while (cin >> s1 >> s2) {
        cout << to_num(s2) - to_num(s1) + 1 << "\n";
    }
    return 0;
}
