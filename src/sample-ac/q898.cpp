#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void solve(const vector<int>& lights) {
    int min_t = lights[0] - 5;
    for (size_t i = 1; i < lights.size(); ++i) {
        min_t = min(min_t, lights[i] - 5);
    }
    
    int current_t = min_t;
    int n = lights.size();
    
    while (current_t <= 18000) {
        bool all_green = true;
        for (int i = 0; i < n; ++i) {
            int cycle = 2 * lights[i];
            int rem = current_t % cycle;
            if (rem >= lights[i] - 5) {
                current_t = (current_t / cycle + 1) * cycle;
                all_green = false;
                break;
            }
        }
        if (all_green) {
            break;
        }
    }
    
    if (current_t > 18000) {
        cout << "Signals fail to synchronise in 5 hours" << endl;
    } else {
        int h = current_t / 3600;
        int m = (current_t % 3600) / 60;
        int s = current_t % 60;
        cout << setw(2) << setfill('0') << h << ":"
             << setw(2) << setfill('0') << m << ":"
             << setw(2) << setfill('0') << s << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x;
    vector<int> lights;
    
    while (cin >> x) {
        if (x == 0) {
            if (lights.empty()) {
                break;
            }
            solve(lights);
            lights.clear();
        } else {
            lights.push_back(x);
        }
    }
    
    if (!lights.empty()) {
        solve(lights);
    }
    
    return 0;
}
