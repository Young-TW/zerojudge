#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    cin.ignore();
    
    while (n--) {
        string s;
        getline(cin, s);
        
        int freq[26] = {0};
        for (char c : s) {
            if (isalpha((unsigned char)c)) {
                freq[tolower((unsigned char)c) - 'a']++;
            }
        }
        
        int max_freq = 0;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] > max_freq) {
                max_freq = freq[i];
            }
        }
        
        for (int i = 0; i < 26; ++i) {
            if (freq[i] == max_freq) {
                cout << (char)('a' + i);
            }
        }
        cout << "\n";
    }
    
    return 0;
}
