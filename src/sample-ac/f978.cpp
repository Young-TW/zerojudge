#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    vector<int> tokens; // 0: Ook., 1: Ook?, 2: Ook!
    bool ce = false;

    while (cin >> s) {
        if (s == "Ook.") {
            tokens.push_back(0);
        } else if (s == "Ook?") {
            tokens.push_back(1);
        } else if (s == "Ook!") {
            tokens.push_back(2);
        } else {
            ce = true;
            break;
        }
    }

    if (ce) {
        cout << "Ook. Ook. Ook! Ook! Ook. Ook.\n";
        return 0;
    }

    if (tokens.size() % 2 != 0) {
        cout << "Ook. Ook. Ook! Ook! Ook. Ook.\n";
        return 0;
    }

    stack<int> st;
    for (size_t i = 0; i < tokens.size(); i += 2) {
        int t1 = tokens[i];
        int t2 = tokens[i+1];

        if (t1 == 1 && t2 == 1) { // Ook? Ook? is invalid
            cout << "Ook. Ook. Ook! Ook! Ook. Ook.\n";
            return 0;
        }

        if (t1 == 2 && t2 == 1) { // Ook! Ook? -> [
            st.push(0);
        } else if (t1 == 1 && t2 == 2) { // Ook? Ook! -> ]
            if (st.empty()) {
                cout << "Ook. Ook. Ook! Ook! Ook. Ook.\n";
                return 0;
            }
            st.pop();
        }
    }

    if (!st.empty()) {
        cout << "Ook. Ook. Ook! Ook! Ook. Ook.\n";
        return 0;
    }

    cout << "Ook. Ook? Ook! Ook! Ook? Ook.\n";
    return 0;
}
