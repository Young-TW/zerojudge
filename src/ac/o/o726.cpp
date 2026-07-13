#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        int min_cost = 2000000000;
        for (int x = 0; x <= 21; ++x) {
            for (int y = 0; y <= 101; ++y) {
                int packs = 50 * x + 10 * y;
                int cost = 850 * x + 180 * y;
                if (packs < n) {
                    cost += (n - packs) * 20;
                }
                if (cost < min_cost) {
                    min_cost = cost;
                }
            }
        }
        cout << min_cost << "\n";
    }
    return 0;
}
