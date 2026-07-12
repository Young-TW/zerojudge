#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long n, m;
    while (cin >> n >> m) {
        unsigned long long a = (n + 1) * n / 2;
        unsigned long long b = (m + 1) * m / 2;
        cout << a * b << "\n";
    }
    
    return 0;
}
