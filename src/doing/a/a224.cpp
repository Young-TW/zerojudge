#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string s;
    while (cin >> s) {
        int cnt[26] = {0};
        for (char c : s) {
            if (isalpha((unsigned char)c)) {
                cnt[tolower((unsigned char)c) - 'a']++;
            }
        }
        int odd = 0;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] & 1) odd++;
        }
        cout << (odd <= 1 ? "yes !" : "no...") << "\n";
    }
    return 0;
}
