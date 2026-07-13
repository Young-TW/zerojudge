#include <iostream>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k, m;
    while (cin >> k >> m && k) {
        set<int> selected;
        for (int i = 0; i < k; ++i) {
            int course;
            cin >> course;
            selected.insert(course);
        }
        
        bool can_graduate = true;
        for (int i = 0; i < m; ++i) {
            int c, r;
            cin >> c >> r;
            int taken = 0;
            for (int j = 0; j < c; ++j) {
                int course;
                cin >> course;
                if (selected.find(course) != selected.end()) {
                    taken++;
                }
            }
            if (taken < r) {
                can_graduate = false;
            }
        }
        
        if (can_graduate) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
    
    return 0;
}
