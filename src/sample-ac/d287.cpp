#include <iostream>
#include <algorithm>

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    while (cin >> a >> b) {
        long long g = gcd(a, b);
        cout << a + b - g << "\n";
    }
    
    return 0;
}
