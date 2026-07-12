#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    while (cin >> n >> q) {
        unordered_map<string, long long> min_code;
        
        for (int i = 0; i < n; ++i) {
            string b;
            cin >> b;
            long long val = stoll(b);
            for (size_t l = 1; l <= b.length(); ++l) {
                string suffix = b.substr(b.length() - l);
                auto it = min_code.find(suffix);
                if (it == min_code.end() || it->second > val) {
                    min_code[suffix] = val;
                }
            }
        }
        
        for (int i = 0; i < q; ++i) {
            int l;
            string c;
            cin >> l >> c;
            while (c.length() < (size_t)l) {
                c = "0" + c;
            }
            auto it = min_code.find(c);
            if (it != min_code.end()) {
                cout << it->second << "\n";
            } else {
                cout << -1 << "\n";
            }
        }
    }
    
    return 0;
}
