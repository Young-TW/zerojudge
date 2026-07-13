#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    if (!getline(cin, line)) return 0;
    
    int N;
    {
        stringstream ss(line);
        ss >> N;
    }

    for (int t = 0; t < N; ++t) {
        vector<int> heights;
        
        while (getline(cin, line)) {
            if (line.empty()) {
                if (!heights.empty()) {
                    break;
                } else {
                    continue;
                }
            }
            stringstream ss(line);
            int h;
            if (ss >> h) {
                heights.push_back(h);
            }
        }

        vector<int> tails;
        vector<int> pos(heights.size());
        
        for (size_t i = 0; i < heights.size(); ++i) {
            auto it = lower_bound(tails.begin(), tails.end(), heights[i]);
            int idx = it - tails.begin();
            if (it == tails.end()) {
                tails.push_back(heights[i]);
            } else {
                *it = heights[i];
            }
            pos[i] = idx + 1;
        }

        int len = tails.size();
        vector<int> ans(len);
        int curr_len = len;
        
        for (int i = heights.size() - 1; i >= 0 && curr_len > 0; --i) {
            if (pos[i] == curr_len) {
                ans[curr_len - 1] = heights[i];
                curr_len--;
            }
        }

        if (t > 0) {
            cout << "\n";
        }
        cout << "Max hits: " << len << "\n";
        for (int i = 0; i < len; ++i) {
            cout << ans[i] << "\n";
        }
    }

    return 0;
}
