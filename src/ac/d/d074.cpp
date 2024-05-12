#include <iostream>
using namespace std;

int main() {
    int n, reg, max = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> reg;
        if (reg > max) {
            max = reg;
        }
    }
    cout << max;
    return 0;
}