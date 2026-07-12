#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        stack<string> dreams;
        for (int i = 0; i < n; ++i) {
            string cmd;
            cin >> cmd;
            if (cmd == "Sleep") {
                string name;
                cin >> name;
                dreams.push(name);
            } else if (cmd == "Kick") {
                if (!dreams.empty()) {
                    dreams.pop();
                }
            } else if (cmd == "Test") {
                if (!dreams.empty()) {
                    cout << dreams.top() << "\n";
                } else {
                    cout << "Not in a dream\n";
                }
            }
        }
    }
    
    return 0;
}
