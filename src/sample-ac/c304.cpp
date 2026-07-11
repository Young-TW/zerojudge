#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        long long temp = n;
        long long rev = 0;
        while (temp > 0) {
            rev = rev * 10 + temp % 10;
            temp /= 10;
        }
        cout << n + rev << "\n";
    }
    
    return 0;
}
