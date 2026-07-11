#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int bit[1005];

void add(int idx, int val) {
    for (; idx <= 1000; idx += idx & -idx)
        bit[idx] += val;
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum += bit[idx];
    return sum;
}

struct Point {
    int x, y, id;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        memset(bit, 0, sizeof(bit));
        vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
            points[i].id = i;
        }
        
        sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
            if (p1.x != p2.x) return p1.x < p2.x;
            return p1.y > p2.y;
        });
        
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[points[i].id] = query(points[i].y - 1);
            add(points[i].y, 1);
        }
        
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << "\n";
        }
    }
    
    return 0;
}
