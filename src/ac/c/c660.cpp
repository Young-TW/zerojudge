#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        // keep empty lines (they produce no output)
        vector<int> pos;
        for (int i = 0; i < (int)line.size(); ++i) {
            if (isalpha(static_cast<unsigned char>(line[i])))
                pos.push_back(i);
        }
        for (size_t k = 0; k < pos.size(); ++k) {
            string t = line;
            // lower case all alphabetic characters
            for (int idx : pos) {
                t[idx] = static_cast<char>(tolower(static_cast<unsigned char>(t[idx])));
            }
            // raise the k‑th head
            int idx = pos[k];
            t[idx] = static_cast<char>(toupper(static_cast<unsigned char>(t[idx])));
            cout << t << '\n';
        }
    }
    return 0;
}
