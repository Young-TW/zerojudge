#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d;
    if (cin >> n >> d) {
        int count = 0;
        long long total_cost = 0;

        for (int i = 0; i < n; ++i) {
            int p1, p2, p3;
            cin >> p1 >> p2 >> p3;
            
            int min_p = min({p1, p2, p3});
            int max_p = max({p1, p2, p3});
            
            if (max_p - min_p >= d) {
                count++;
                total_cost += (p1 + p2 + p3) / 3;
            }
        }
        
        cout << count << " " << total_cost << "\n";
    }

    return 0;
}
