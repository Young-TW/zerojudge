#include <iostream>

using namespace std;

int count_leap(int n) {
    return n / 4 - n / 100 + n / 400;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b;
    while (cin >> a >> b) {
        cout << count_leap(b) - count_leap(a - 1) << "\n";
    }
    
    return 0;
}
