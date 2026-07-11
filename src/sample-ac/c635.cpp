#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        vector<long long> nums;
        string temp;
        for (char c : line) {
            if (c == ',') {
                nums.push_back(stoll(temp));
                temp.clear();
            } else {
                temp += c;
            }
        }
        if (!temp.empty()) {
            nums.push_back(stoll(temp));
        }
        
        vector<long long> odd_pos, even_pos;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (i % 2 == 0) {
                odd_pos.push_back(nums[i]);
            } else {
                even_pos.push_back(nums[i]);
            }
        }
        
        sort(odd_pos.begin(), odd_pos.end());
        sort(even_pos.begin(), even_pos.end());
        
        for (size_t i = 0; i < nums.size(); ++i) {
            if (i % 2 == 0) {
                nums[i] = odd_pos[i / 2];
            } else {
                nums[i] = even_pos[i / 2];
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
