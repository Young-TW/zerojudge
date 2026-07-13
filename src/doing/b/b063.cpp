#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<pair<int, int>> cities(n);
        for (int i = 0; i < n; ++i) {
            cin >> cities[i].first >> cities[i].second;
        }
        
        long long min_dist = -1;
        pair<int, int> best_city;
        
        for (int i = 0; i < n; ++i) {
            long long current_dist = 0;
            for (int j = 0; j < n; ++j) {
                current_dist += abs(cities[i].first - cities[j].first) + abs(cities[i].second - cities[j].second);
            }
            if (min_dist == -1 || current_dist < min_dist) {
                min_dist = current_dist;
                best_city = cities[i];
            }
        }
        
        cout << best_city.first << " " << best_city.second << "\n";
        cout << min_dist << "\n";
    }
    
    return 0;
}
