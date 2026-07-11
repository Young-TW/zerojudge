#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(2);
    
    string s;
    while (cin >> s) {
        int cnt[26] = {0};
        int total = 0;
        for (char c : s) {
            if (c >= 'a' && c <= 'z') {
                cnt[c - 'a']++;
                total++;
            } else if (c >= 'A' && c <= 'Z') {
                cnt[c - 'A']++;
                total++;
            }
        }
        for (int i = 0; i < 26; i++) {
            if (i) cout << ' ';
            cout << cnt[i];
        }
        cout << '\n';
        for (int i = 0; i < 26; i++) {
            if (i) cout << ' ';
            double pct = total == 0 ? 0.0 : (double)cnt[i] * 100.0 / total;
            cout << pct;
        }
        cout << '\n';
    }
    return 0;
}
