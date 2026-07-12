#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    char op;
    while (cin >> a >> op >> b) {
        if (op == '+') {
            cout << a + b << "\n";
        } else if (op == '-') {
            cout << a - b << "\n";
        } else if (op == '*') {
            cout << a * b << "\n";
        } else if (op == '/') {
            cout << a / b << "\n";
        }
    }
    
    return 0;
}
