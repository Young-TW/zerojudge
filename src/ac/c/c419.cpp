#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            cout << "_";
        }
        for (int j = n - i; j <= n; j++) {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}