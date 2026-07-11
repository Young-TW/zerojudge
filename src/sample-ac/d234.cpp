#include <iostream>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long a, b, c;
    while (cin >> a >> b >> c) {
        if (gcd(a, b) == 1 && c > a * b - a - b) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
