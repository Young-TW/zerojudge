#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, m, a;
    while (cin >> n >> m >> a) {
        long long cn = n / a + (n % a != 0);
        long long cm = m / a + (m % a != 0);
        cout << cn * cm << "\n";
    }
    
    return 0;
}
