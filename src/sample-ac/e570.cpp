#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            cout << "\n";
            continue;
        }
        vector<string> chars;
        for (size_t i = 0; i < line.length(); ) {
            unsigned char c = line[i];
            if ((c & 0x80) == 0) {
                chars.push_back(line.substr(i, 1));
                i += 1;
            } else if ((c & 0xE0) == 0xC0) {
                chars.push_back(line.substr(i, 2));
                i += 2;
            } else if ((c & 0xF0) == 0xE0) {
                chars.push_back(line.substr(i, 3));
                i += 3;
            } else if ((c & 0xF8) == 0xF0) {
                chars.push_back(line.substr(i, 4));
                i += 4;
            } else {
                chars.push_back(line.substr(i, 1));
                i += 1;
            }
        }
        
        int split_idx = -1;
        for (size_t i = 0; i < chars.size(); ++i) {
            if (chars[i] == "之" || chars[i] == "是") {
                split_idx = i;
                break;
            }
        }
        
        if (split_idx != -1) {
            for (size_t i = split_idx + 1; i < chars.size(); ++i) {
                cout << chars[i];
            }
            for (int i = 0; i < split_idx; ++i) {
                cout << chars[i];
            }
            cout << "\n";
        } else {
            cout << line << "\n";
        }
    }
    return 0;
}
