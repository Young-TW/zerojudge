#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<unsigned int> s1, s2;
    string op;
    while (cin >> op) {
        if (op == "push") {
            unsigned int x;
            cin >> x;
            s1.push(x);
            cout << '1';
        } else if (op == "pop") {
            if (s2.empty()) {
                while (!s1.empty()) {
                    s2.push(s1.top());
                    s1.pop();
                    cout << '5';
                }
            }
            s2.pop();
            cout << '4';
        }
    }
    cout << endl;
    return 0;
}
