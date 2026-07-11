#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string key, cipher;
    while (cin >> key >> cipher) {
        string plain = "";
        int k_len = key.length();
        for (int i = 0; i < k_len; ++i) {
            key[i] = tolower(key[i]);
        }
        
        int c_len = cipher.length();
        for (int i = 0; i < c_len; ++i) {
            char c = cipher[i];
            char k = key[i % k_len];
            int c_val = tolower(c) - 'a';
            int k_val = k - 'a';
            int p_val = (c_val - k_val + 26) % 26;
            
            if (isupper(c)) {
                plain += 'A' + p_val;
            } else {
                plain += 'a' + p_val;
            }
        }
        cout << plain << "\n";
    }
    return 0;
}
