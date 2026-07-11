#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            char type;
            cin >> type;
            int a, b;
            char op;
            cin >> a >> op >> b;
            if (op == '+') {
                cout << a + b << "\n";
            } else {
                cout << a - b << "\n";
            }
        }
    }
    
    return 0;
}
