#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Course {
    int D, S, T;
};

bool cmp(const Course& a, const Course& b) {
    if (a.T != b.T) return a.T < b.T;
    return a.S < b.S;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<Course> courses[6];
        for (int i = 0; i < N; ++i) {
            int d, s, t;
            cin >> d >> s >> t;
            courses[d].push_back({d, s, t});
        }
        
        int total = 0;
        for (int i = 1; i <= 5; ++i) {
            sort(courses[i].begin(), courses[i].end(), cmp);
            int last_end = 0;
            for (size_t j = 0; j < courses[i].size(); ++j) {
                if (courses[i][j].S >= last_end) {
                    total++;
                    last_end = courses[i][j].T;
                }
            }
        }
        cout << total << "\n";
    }
    
    return 0;
}
