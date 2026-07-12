#include <iostream>
#include <string>

using namespace std;

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            string s1, s2;
            cin >> s1 >> s2;
            
            if (s1.length() != s2.length()) {
                cout << "No\n";
                continue;
            }
            
            bool same = true;
            for (size_t j = 0; j < s1.length(); ++j) {
                if (isVowel(s1[j])) {
                    if (!isVowel(s2[j])) {
                        same = false;
                        break;
                    }
                } else {
                    if (s1[j] != s2[j]) {
                        same = false;
                        break;
                    }
                }
            }
            
            if (same) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    
    return 0;
}
