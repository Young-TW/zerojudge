#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n && n >= 0) {
        cout << n * (n + 1) / 2 + 1 << '\n';
    }
    
    return 0;
}
