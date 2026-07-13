#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    while (cin >> n >> m) {
        if (n % m == 0) {
            cout << "整數 " << n / m << "\n";
        } else if (n < m) {
            cout << "真分數 " << n << "/" << m << "\n";
        } else {
            cout << "帶分數 " << n / m << " " << n % m << "/" << m << "\n";
        }
    }
    
    return 0;
}
