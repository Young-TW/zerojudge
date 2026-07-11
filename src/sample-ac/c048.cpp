#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n && n != 0) {
        long long k = sqrt((double)n);
        while (k * k > n) {
            k--;
        }
        while ((k + 1) * (k + 1) <= n) {
            k++;
        }
        
        long long r = n - k * k;
        long long x, y;
        
        if (k % 2 == 1) {
            if (r == 0) {
                x = 1;
                y = k;
            } else if (r <= k + 1) {
                x = r;
                y = k + 1;
            } else {
                x = k + 1;
                y = 2 * (k + 1) - r;
            }
        } else {
            if (r == 0) {
                x = k;
                y = 1;
            } else if (r <= k + 1) {
                x = k + 1;
                y = r;
            } else {
                x = 2 * (k + 1) - r;
                y = k + 1;
            }
        }
        
        cout << x << " " << y << "\n";
    }
    
    return 0;
}
