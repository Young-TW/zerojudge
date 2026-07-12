#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    if (!getline(cin, line)) return 0;
    
    int T = 0;
    try {
        T = stoi(line);
    } catch (...) {
        return 0;
    }

    while (T--) {
        string S;
        if (!getline(cin, S)) break;
        
        string c_line;
        if (!getline(cin, c_line)) break;
        
        char c1 = 0, c2 = 0;
        bool first = true;
        for (char ch : c_line) {
            if (!isspace(static_cast<unsigned char>(ch))) {
                if (first) {
                    c1 = ch;
                    first = false;
                } else {
                    c2 = ch;
                }
            }
        }
        
        if (c1 == 0 || c2 == 0) {
            continue;
        }

        size_t i = S.find(c1);
        size_t j = S.find(c2);

        if (i == string::npos || j == string::npos) {
            continue;
        }

        if (i > j) {
            swap(i, j);
        }

        string removed = S.substr(i + 1, j - i - 1);
        string merged = S.substr(0, i + 1) + S.substr(j);

        cout << merged << "\n";
        cout << removed << "\n";
    }

    return 0;
}
