#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> seq;
    int val;
    while (cin >> val) {
        seq.push_back(val);
    }

    if (seq.empty()) {
        cout << 0 << endl;
        return 0;
    }

    long long total_diff = 0;
    vector<int> path;
    vector<int> children_count; 
    vector<int> children_visited; 

    int idx = 0;
    int n = seq.size();

    while (idx < n) {
        int current_val = seq[idx];
        
        if (current_val == 0) {
            if (path.empty()) {
                idx++;
                continue;
            }
            children_visited.back()++;
            
            while (!path.empty() && children_visited.back() >= children_count.back()) {
                path.pop_back();
                children_count.pop_back();
                children_visited.pop_back();
                
                if (!path.empty()) {
                    children_visited.back()++;
                }
            }
            idx++;
        } else {
            if (!path.empty()) {
                long long diff = abs((long long)path.back() - (long long)current_val);
                total_diff += diff;
            }

            path.push_back(current_val);
            
            int branches = (current_val % 2 == 0) ? 2 : 3;
            children_count.push_back(branches);
            children_visited.push_back(0);
            
            idx++;
        }
    }

    cout << total_diff << endl;

    return 0;
}
