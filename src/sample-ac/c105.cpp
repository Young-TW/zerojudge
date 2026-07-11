#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct Point {
    long long x, y;
};

long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    if (!getline(cin, line)) return 0;
    istringstream iss_T(line);
    int T;
    if (!(iss_T >> T)) return 0;
    
    bool first_case = true;
    int cases_done = 0;
    
    while (cases_done < T) {
        while (getline(cin, line)) {
            if (!line.empty()) break;
        }
        if (line.empty() && cin.eof()) break;
        
        vector<Point> points;
        do {
            if (line.empty()) break;
            istringstream iss(line);
            long long x, y;
            if (iss >> x >> y) {
                points.push_back({x, y});
            } else {
                break;
            }
        } while (getline(cin, line));
        
        if (!points.empty()) {
            if (!first_case) cout << "\n";
            first_case = false;
            
            int n = points.size();
            int max_pts = 0;
            if (n > 0) max_pts = 1;
            
            for (int i = 0; i < n; ++i) {
                vector<pair<long long, long long>> slopes;
                for (int j = 0; j < n; ++j) {
                    if (i == j) continue;
                    long long dx = points[j].x - points[i].x;
                    long long dy = points[j].y - points[i].y;
                    long long g = gcd(dx, dy);
                    if (g == 0) g = 1;
                    dx /= g;
                    dy /= g;
                    if (dx < 0 || (dx == 0 && dy < 0)) {
                        dx = -dx;
                        dy = -dy;
                    }
                    slopes.push_back({dx, dy});
                }
                sort(slopes.begin(), slopes.end());
                int cur = 1;
                for (size_t k = 1; k < slopes.size(); ++k) {
                    if (slopes[k] == slopes[k-1]) {
                        cur++;
                    } else {
                        if (cur + 1 > max_pts) max_pts = cur + 1;
                        cur = 1;
                    }
                }
                if (cur + 1 > max_pts) max_pts = cur + 1;
            }
            
            cout << max_pts << "\n";
            cases_done++;
        }
    }
    
    return 0;
}
