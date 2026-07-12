#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    string dummy;
    getline(cin, dummy);
    
    for (int i = 0; i < n; ++i) {
        string s1, s2;
        getline(cin, s1);
        getline(cin, s2);
        
        int cnt1[26] = {0};
        int cnt2[26] = {0};
        
        for (char c : s1) {
            if (c >= 'A' && c <= 'Z') {
                cnt1[c - 'A']++;
            } else if (c >= 'a' && c <= 'z') {
                cnt1[c - 'a']++;
            }
        }
        
        for (char c : s2) {
            if (c >= 'A' && c <= 'Z') {
                cnt2[c - 'A']++;
            } else if (c >= 'a' && c <= 'z') {
                cnt2[c - 'a']++;
            }
        }
        
        bool is_anagram = true;
        for (int j = 0; j < 26; ++j) {
            if (cnt1[j] != cnt2[j]) {
                is_anagram = false;
                break;
            }
        }
        
        cout << (is_anagram ? 1 : 0) << "\n";
    }
    
    return 0;
}
