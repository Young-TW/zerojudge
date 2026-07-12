#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Hourly rates for each hour 0..23
    // Based on the problem's rate intervals:
    // 0:00-4:00   -> 1500
    // 4:00-6:00   -> 1400
    // 6:00-9:00   -> 1500
    // 9:00-18:00  -> 900
    // 18:00-24:00 -> 1200
    int rate[24] = {
        1500, 1500, 1500, 1500, // 0-3
        1400, 1400,             // 4-5
        1500, 1500, 1500,       // 6-8
        900, 900, 900, 900, 900, 900, 900, 900, 900, // 9-17
        1200, 1200, 1200, 1200, 1200, 1200            // 18-23
    };
    
    int h1, m1, h2, m2;
    while (cin >> h1 >> m1 >> h2 >> m2) {
        int sum = 0;
        // Hours from h1 to h2-1 are fully covered
        for (int h = h1; h < h2; ++h) {
            sum += rate[h];
        }
        // If end minute > 0, the hour h2 is also partially covered
        if (m2 > 0) {
            sum += rate[h2];
        }
        cout << sum << '\n';
    }
    return 0;
}
