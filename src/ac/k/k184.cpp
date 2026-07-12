#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct House {
    long long x, y, r;
    int id;
    long long dist_sq;
};

struct Station {
    long long x, y;
};

bool cmp(const House& a, const House& b) {
    if (a.dist_sq != b.dist_sq) return a.dist_sq < b.dist_sq;
    if (a.r != b.r) return a.r < b.r;
    return a.id < b.id;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<House> houses(n);
        for (int i = 0; i < n; ++i) {
            cin >> houses[i].x >> houses[i].y >> houses[i].r;
            houses[i].id = i + 1;
            houses[i].dist_sq = LLONG_MAX;
        }
        
        vector<Station> stations(m);
        for (int i = 0; i < m; ++i) {
            cin >> stations[i].x >> stations[i].y;
        }
        
        for (int i = 0; i < n; ++i) {
            long long hx = houses[i].x;
            long long hy = houses[i].y;
            long long min_dist_sq = LLONG_MAX;
            for (int j = 0; j < m; ++j) {
                long long dx = hx - stations[j].x;
                long long dy = hy - stations[j].y;
                long long dist_sq = dx * dx + dy * dy;
                if (dist_sq < min_dist_sq) {
                    min_dist_sq = dist_sq;
                }
            }
            houses[i].dist_sq = min_dist_sq;
        }
        
        sort(houses.begin(), houses.end(), cmp);
        
        for (int i = 0; i < n; ++i) {
            cout << houses[i].id << "\n";
        }
    }
    
    return 0;
}
