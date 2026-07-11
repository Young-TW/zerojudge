#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const double EPS = 1e-9;

struct Interval {
    double left, right;
    bool operator<(const Interval& other) const {
        if (right < other.right) return true;
        if (right > other.right) return false;
        return left < other.left;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, d;
    int case_id = 1;
    while (cin >> n >> d) {
        if (n == 0 && d == 0) break;
        
        vector<Interval> intervals;
        bool possible = true;
        
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            if (y > d || y < 0 || d < 0) {
                possible = false;
            }
            if (possible) {
                double dx = sqrt((double)d * d - (double)y * y);
                intervals.push_back({(double)x - dx, (double)x + dx});
            }
        }
        
        if (!possible) {
            cout << "Case " << case_id << ": -1\n";
        } else {
            sort(intervals.begin(), intervals.end());
            int count = 0;
            double last_radar = -1e18;
            for (int i = 0; i < n; ++i) {
                if (intervals[i].left > last_radar + EPS) {
                    count++;
                    last_radar = intervals[i].right;
                }
            }
            cout << "Case " << case_id << ": " << count << "\n";
        }
        case_id++;
    }
    
    return 0;
}
