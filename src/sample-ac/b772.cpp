#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    while (cin >> s) {
        bool hasInvalid = false;
        string cmd;
        while (cin >> cmd) {
            if (cmd == "end") {
                if (!hasInvalid) {
                    cout << s << "\n";
                }
                break;
            } else if (cmd == "replace") {
                char x, y;
                cin >> x >> y;
                for (size_t i = 0; i < s.length(); ++i) {
                    if (s[i] == x) {
                        s[i] = y;
                    }
                }
            } else if (cmd == "remove") {
                char x;
                cin >> x;
                string temp;
                temp.reserve(s.length());
                for (size_t i = 0; i < s.length(); ++i) {
                    if (s[i] != x) {
                        temp += s[i];
                    }
                }
                s = temp;
            } else if (cmd == "addhead") {
                char x;
                cin >> x;
                s.insert(s.begin(), x);
            } else if (cmd == "addtail") {
                char x;
                cin >> x;
                s.push_back(x);
            } else {
                hasInvalid = true;
                string dummy;
                // Attempt to consume the argument if it exists on the same line/logical token stream
                // The problem format suggests commands like "addpangfeng b" have one argument.
                // We must consume it to align the next read.
                if (cin >> dummy) {
                    // consumed
                }
                cout << "invalid command " << cmd << "\n";
            }
        }
    }
    return 0;
}
