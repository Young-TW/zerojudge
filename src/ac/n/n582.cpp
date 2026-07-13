#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n) {
        long long m = n - 1;
        cout << 2LL * m * m + 2 << "\n";
    }
    return 0;
}
