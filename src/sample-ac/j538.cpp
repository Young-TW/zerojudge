#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s, d;
    while (cin >> s >> d) {
        int n = (int)s.length();
        
        vector<int> positions[26];
        for (int i = 0; i < n; i++) {
            char c = tolower(s[i]);
            positions[c - 'a'].push_back(i);
        }
        
        vector<int> output(n);
        
        for (int c = 0; c < 26; c++) {
            if (positions[c].empty()) continue;
            int cnt = (int)positions[c].size();
            int sum = 0;
            for (int p : positions[c]) {
                sum += d[p] - '0';
            }
            int floorVal = sum / cnt;
            int remainder = sum % cnt;
            
            for (int i = 0; i < cnt; i++) {
                if (i < cnt - remainder) {
                    output[positions[c][i]] = floorVal;
                } else {
                    output[positions[c][i]] = floorVal + 1;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            cout << output[i];
        }
        cout << "\n";
    }
    
    return 0;
}
