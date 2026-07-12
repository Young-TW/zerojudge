#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int MAX_N = 10000;
    vector<unsigned long long> ugly(MAX_N + 1);
    ugly[1] = 1;
    
    int i2 = 1, i3 = 1, i5 = 1;
    unsigned long long next2 = 2, next3 = 3, next5 = 5;
    
    for (int i = 2; i <= MAX_N; ++i) {
        unsigned long long next_ugly = min(next2, min(next3, next5));
        ugly[i] = next_ugly;
        
        if (next_ugly == next2) {
            i2++;
            next2 = ugly[i2] * 2;
        }
        if (next_ugly == next3) {
            i3++;
            next3 = ugly[i3] * 3;
        }
        if (next_ugly == next5) {
            i5++;
            next5 = ugly[i5] * 5;
        }
    }
    
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            if (cin >> n) {
                cout << ugly[n] << "\n";
            }
        }
    }
    
    return 0;
}
