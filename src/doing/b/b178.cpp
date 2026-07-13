#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        vector<pair<int, int>> boats(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &boats[i].first, &boats[i].second);
        }
        
        sort(boats.begin(), boats.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) {
                return a.first < b.first;
            }
            return a.second > b.second;
        });
        
        vector<int> tails;
        for (int i = 0; i < n; ++i) {
            int y = -boats[i].second;
            auto it = upper_bound(tails.begin(), tails.end(), y);
            if (it == tails.end()) {
                tails.push_back(y);
            } else {
                *it = y;
            }
        }
        
        printf("%d\n", (int)tails.size());
    }
    return 0;
}
