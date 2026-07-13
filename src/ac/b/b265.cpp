#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        map<vector<int>, int> course_count;
        int max_freq = 0;
        
        for (int i = 0; i < n; ++i) {
            vector<int> courses(5);
            for (int j = 0; j < 5; ++j) {
                cin >> courses[j];
            }
            sort(courses.begin(), courses.end());
            int current_count = ++course_count[courses];
            if (current_count > max_freq) {
                max_freq = current_count;
            }
        }
        
        int ans = 0;
        for (map<vector<int>, int>::iterator it = course_count.begin(); it != course_count.end(); ++it) {
            if (it->second == max_freq) {
                ans += it->second;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
