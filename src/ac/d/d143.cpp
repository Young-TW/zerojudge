#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        while (n--) {
            long long a, b;
            cin >> a >> b;
            if (a < b) {
                cout << "<\n";
            } else if (a > b) {
                cout << ">\n";
            } else {
                cout << "=\n";
            }
        }
    }
    
    return 0;
}
