#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        long long prev2 = 0, prev1 = 0, curr = 0;
        for (int i = 0; i < n; ++i) {
            long long x;
            cin >> x;
            curr = max(prev1, prev2 + x);
            prev2 = prev1;
            prev1 = curr;
        }
        cout << curr << "\n";
    }
    
    return 0;
}
