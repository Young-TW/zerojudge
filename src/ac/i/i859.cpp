#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            long long x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            
            long long idx1 = (x1 + y1) * (x1 + y1 + 1) / 2 + x1;
            long long idx2 = (x2 + y2) * (x2 + y2 + 1) / 2 + x2;
            
            cout << "Case " << i << ": " << idx2 - idx1 << "\n";
        }
    }
    
    return 0;
}
