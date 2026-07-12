#include <iostream>
#include <iomanip>

using namespace std;

bool isPrime(long long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0) return false;
        if (n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int prefix[10005];
    prefix[0] = 0;
    for (int i = 0; i <= 10000; ++i) {
        long long val = (long long)i * i + i + 41;
        prefix[i + 1] = prefix[i] + (isPrime(val) ? 1 : 0);
    }
    
    int a, b;
    while (cin >> a >> b) {
        int count = prefix[b + 1] - prefix[a];
        double percentage = (double)count / (b - a + 1) * 100.0;
        cout << fixed << setprecision(2) << percentage << "\n";
    }
    
    return 0;
}
