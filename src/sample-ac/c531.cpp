#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        vector<int> nums;
        stringstream ss(line);
        string token;
        
        while (getline(ss, token, ',')) {
            nums.push_back(stoi(token));
        }
        
        vector<int> evens;
        for (int x : nums) {
            if (x % 2 == 0) {
                evens.push_back(x);
            }
        }
        
        sort(evens.begin(), evens.end());
        
        size_t even_idx = 0;
        for (int& x : nums) {
            if (x % 2 == 0) {
                x = evens[even_idx++];
            }
        }
        
        for (size_t i = 0; i < nums.size(); ++i) {
            if (i > 0) cout << ',';
            cout << nums[i];
        }
        cout << '\n';
    }
    
    return 0;
}
