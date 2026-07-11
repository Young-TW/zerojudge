#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    while (cin >> n >> m) {
        if (m == 0) {
            cout << "Go Kevin!!\n";
            continue;
        }
        
        long long L = 1;
        long long R = (long long)sqrt(2.0 * n / m) + 5;
        if (R < 1) R = 1;
        
        bool found = false;
        while (L <= R) {
            long long mid = L + (R - L) / 2;
            long long sum = mid + m * mid * (mid - 1) / 2;
            
            if (sum == n) {
                found = true;
                break;
            } else if (sum < n) {
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        
        if (found) {
            cout << "Go Kevin!!\n";
        } else {
            cout << "No Stop!!\n";
        }
    }
    
    return 0;
}
