#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        set<long long> seen;
        long long x = n;
        seen.insert(x);
        long long max_val = x;
        
        while (true) {
            long long next_x;
            if (x % 2 == 0) {
                next_x = x / 2;
            } else {
                next_x = 3 * x + 1;
            }
            
            if (seen.count(next_x)) {
                break;
            }
            
            seen.insert(next_x);
            if (next_x > max_val) {
                max_val = next_x;
            }
            x = next_x;
        }
        
        cout << seen.size() << " " << max_val << "\n";
    }
    
    return 0;
}
