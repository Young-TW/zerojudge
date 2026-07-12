#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    string dummy;
    getline(cin, dummy);
    
    string s;
    for (int i = 0; i < n; ++i) {
        if (!getline(cin, s)) break;
        
        while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) {
            s.pop_back();
        }
        
        bool valid = !s.empty();
        for (char c : s) {
            if (c != '0' && c != '1') {
                valid = false;
                break;
            }
        }
        
        if (!valid) {
            cout << -1 << "\n";
            continue;
        }
        
        vector<string> codes;
        int len = s.length();
        int j = 0;
        
        while (j < len) {
            char current = s[j];
            int count = 0;
            while (j < len && s[j] == current && count < 7) {
                count++;
                j++;
            }
            string code = "";
            code += current;
            code += (count & 4 ? '1' : '0');
            code += (count & 2 ? '1' : '0');
            code += (count & 1 ? '1' : '0');
            codes.push_back(code);
        }
        
        int compressed_bits = codes.size() * 4;
        int original_bits = s.length();
        int ratio = (compressed_bits * 100 + original_bits / 2) / original_bits;
        
        for (size_t k = 0; k < codes.size(); ++k) {
            if (k > 0) cout << " ";
            cout << codes[k];
        }
        cout << " " << ratio << "%\n";
    }
    
    return 0;
}
