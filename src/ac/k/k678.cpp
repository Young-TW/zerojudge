#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        while (n--) {
            long long a, b, c;
            char op;
            cin >> a >> op >> b >> c;
            if (a + b == c) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        }
    }
    
    return 0;
}
