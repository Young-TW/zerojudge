#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n) {
        long long m = n / 2;
        cout << (m + 1) * (m + 2) / 2 << "\n";
    }
    
    return 0;
}
