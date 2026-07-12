#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Point {
    int x, y;
};

bool cmp(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y > b.y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    int case_num = 1;
    
    while (cin >> N) {
        vector<Point> points(N);
        for (int i = 0; i < N; ++i) {
            cin >> points[i].x >> points[i].y;
        }
        
        sort(points.begin(), points.end(), cmp);
        
        vector<Point> ans;
        int max_y = -1;
        for (int i = N - 1; i >= 0; --i) {
            if (points[i].y > max_y) {
                ans.push_back(points[i]);
                max_y = points[i].y;
            }
        }
        reverse(ans.begin(), ans.end());
        
        auto print_aligned = [](const string& s, const string& comment) {
            cout << s;
            size_t len = s.length();
            if (len < 38) {
                cout << string(38 - len, ' ');
            } else {
                cout << " ";
            }
            cout << comment << "\n";
        };
        
        print_aligned("Case " + to_string(case_num) + ":", "//第幾筆測資");
        print_aligned("Dominate Point: " + to_string(ans.size()), "//點的個數");
        
        for (size_t i = 0; i < ans.size(); ++i) {
            cout << "(" << ans[i].x << "," << ans[i].y << ")\n";
        }
        
        case_num++;
    }
    
    return 0;
}
