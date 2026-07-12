#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        vector<char> nums;
        for (char c : s) {
            if (c != '+') {
                nums.push_back(c);
            }
        }
        sort(nums.begin(), nums.end());
        
        for (size_t i = 0; i < nums.size(); ++i) {
            cout << nums[i];
            if (i < nums.size() - 1) {
                cout << '+';
            }
        }
        cout << '\n';
    }
    return 0;
}
