#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void process(const string &s) {
    if (s.length() < 10 || s.length() > 30) {
        cout << "INCORRECT\n";
        return;
    }
    for (char c : s) {
        if (c < '1' || c > '9') {
            cout << "INCORRECT\n";
            return;
        }
    }
    string rev = s;
    reverse(rev.begin(), rev.end());
    if (s != rev) {
        cout << "INCORRECT\n";
        return;
    }
    for (size_t i = 0; i < s.length() - 1; ++i) {
        int a = s[i] - '0';
        int b = s[i+1] - '0';
        if (b > 2 * a) {
            cout << "INCORRECT\n";
            return;
        }
    }
    string pwd;
    for (char c : s) {
        if ((c - '0') % 2 == 0) {
            pwd += c;
        }
    }
    if (pwd.empty()) {
        cout << "0\n";
    } else {
        cout << pwd << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) continue;
        
        bool all_digits = true;
        for (char c : line) {
            if (c < '0' || c > '9') {
                all_digits = false;
                break;
            }
        }
        
        if (all_digits) {
            process(line);
        } else {
            size_t pos = line.find("輸入");
            if (pos != string::npos) {
                string new_line = line.substr(0, pos) + "輸出" + line.substr(pos + string("輸入").length());
                cout << new_line << "\n";
            }
        }
    }
    return 0;
}
