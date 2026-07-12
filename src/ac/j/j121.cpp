#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s1, s2;
    while (cin >> s1 >> s2) {
        vector<int> cnt1(26, 0), cnt2(26, 0);
        for (char c : s1) cnt1[c - 'A']++;
        for (char c : s2) cnt2[c - 'A']++;
        sort(cnt1.begin(), cnt1.end());
        sort(cnt2.begin(), cnt2.end());
        if (cnt1 == cnt2) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
