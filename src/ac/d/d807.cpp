#include <iostream>

using namespace std;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    while (cin >> n >> m) {
        cout << gcd(n, m) << "\n";
    }
    
    return 0;
}
