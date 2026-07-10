#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isBoundary(char ch) {
    return ch == ' ' || ch == ',' || ch == '.' || ch == '!' || ch == '?';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        bool start = true;
        for (int idx = 0; idx < (int)line.size(); idx++) {
            char c = line[idx];
            if (c == '.' || c == '!' || c == '?') {
                cout << c;
                start = true;
            } else if (c == ' ') {
                cout << c;
            } else if (c == ',') {
                cout << c;
                start = false;
            } else {
                if (start) {
                    cout << (char)toupper((unsigned char)c);
                    start = false;
                } else if (c == 'i') {
                    bool prevOk = (idx == 0) || isBoundary(line[idx - 1]);
                    bool nextOk = (idx == (int)line.size() - 1) || isBoundary(line[idx + 1]);
                    if (prevOk && nextOk) {
                        cout << 'I';
                    } else {
                        cout << c;
                    }
                } else {
                    cout << c;
                }
            }
        }
        cout << '\n';
    }
    return 0;
}
