#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, i, j;
    while (cin >> n >> i >> j) {
        long long k = min(min(i, j), min(n - i + 1, n - j + 1));
        long long base = 1 + 4LL * (k - 1) * (n - k + 1);
        long long L = n - 2 * (k - 1);
        long long offset = 0;
        
        if (i == k) {
            offset = j - k;
        } else if (j == n - k + 1) {
            offset = L - 1 + (i - k);
        } else if (i == n - k + 1) {
            offset = 2 * (L - 1) + (n - k + 1 - j);
        } else if (j == k) {
            offset = 3 * (L - 1) + (n - k + 1 - i);
        }
        
        cout << base + offset << "\n";
    }
    
    return 0;
}
