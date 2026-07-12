#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<string> first_period(n);
        for (int i = 0; i < n; ++i) {
            cin >> first_period[i];
        }
        
        set<string> second_period;
        for (int i = 0; i < m; ++i) {
            string name;
            cin >> name;
            second_period.insert(name);
        }
        
        int count = 0;
        for (const string& name : first_period) {
            if (second_period.find(name) == second_period.end()) {
                ++count;
            }
        }
        
        cout << count << "\n";
    }
    
    return 0;
}
