#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string L;
    while (getline(cin, L)) {
        string letters;
        if (!getline(cin, letters)) break;

        int cnt[26] = {0};
        for (char c : letters) {
            if (c >= 'A' && c <= 'Z') {
                cnt[c - 'A']++;
            }
        }

        stringstream ss(L);
        string word;
        string ans;
        bool stop = false;

        while (ss >> word) {
            if (stop) break;
            
            string temp;
            for (char c : word) {
                if (c >= 'A' && c <= 'Z') {
                    if (cnt[c - 'A'] > 0) {
                        cnt[c - 'A']--;
                        temp += c;
                    } else {
                        break;
                    }
                }
            }

            if (!temp.empty()) {
                if (!ans.empty()) {
                    ans += " ";
                }
                ans += temp;
            }

            if (temp.length() < word.length()) {
                stop = true;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
