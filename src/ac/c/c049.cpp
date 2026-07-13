#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    bool first = true;
    
    while (cin >> n) {
        if (!first) {
            cout << "\n";
        }
        first = false;
        
        long long R2_4 = 4LL * n * n - 4LL * n + 1;
        int partial = 0;
        int complete = 0;
        
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                long long d_near_4 = 4LL * (x * x + y * y);
                long long d_far_4 = 4LL * ((x + 1) * (x + 1) + (y + 1) * (y + 1));
                
                if (d_far_4 <= R2_4) {
                    complete++;
                } else if (d_near_4 < R2_4) {
                    partial++;
                }
            }
        }
        
        cout << "In the case n = " << n << ", " << partial * 4 << " cells contain segments of the circle.\n";
        cout << "There are " << complete * 4 << " cells completely contained in the circle.\n";
    }
    
    return 0;
}
