#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    
    for (int t = 0; t < T; ++t) {
        vector<string> phrases;
        string line;
        
        // 讀取第一個非空行
        while (getline(cin, line)) {
            if (!line.empty()) {
                phrases.push_back(line);
                break;
            }
        }
        
        // 讀取剩餘的行，直到遇到空行或 EOF
        while (getline(cin, line)) {
            if (line.empty()) break;
            phrases.push_back(line);
        }
        
        sort(phrases.begin(), phrases.end());
        
        vector<string> signatures(phrases.size());
        for (size_t i = 0; i < phrases.size(); ++i) {
            string sig = phrases[i];
            sig.erase(remove(sig.begin(), sig.end(), ' '), sig.end());
            for (char &c : sig) c = tolower(c);
            sort(sig.begin(), sig.end());
            signatures[i] = sig;
        }
        
        if (t > 0) cout << "\n";
        
        for (size_t i = 0; i < phrases.size(); ++i) {
            for (size_t j = i + 1; j < phrases.size(); ++j) {
                if (signatures[i] == signatures[j]) {
                    cout << phrases[i] << " = " << phrases[j] << "\n";
                }
            }
        }
    }
    
    return 0;
}
