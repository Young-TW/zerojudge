#include <iostream>
using namespace std;

int main() {
    int n, m;
    while (cin >> n) {
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            m = n - i - 1;
            for (int a = 0; a < m; a++) {
                cout << "_";
            }
            for (int b = 0; b < i + 1; b++) {
                cout << "+";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}