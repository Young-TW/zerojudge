#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        string line;
        getline(cin, line);
        
        bool has_num = false;
        for (char c : line) {
            if (isdigit(static_cast<unsigned char>(c))) {
                has_num = true;
                break;
            }
        }
        
        while (!has_num) {
            if (!getline(cin, line)) {
                break;
            }
            for (char c : line) {
                if (isdigit(static_cast<unsigned char>(c))) {
                    has_num = true;
                    break;
                }
            }
        }
        
        if (!has_num) {
            cout << "\n";
            continue;
        }
        
        stringstream ss(line);
        vector<int> nums;
        int x;
        while (ss >> x) {
            nums.push_back(x);
        }
        
        int power = 2;
        for (int round = 0; round < n; ++round) {
            set<int> T;
            for (int num : nums) {
                int sum = 0;
                int temp = num;
                if (temp == 0) {
                    sum = 0;
                } else {
                    while (temp > 0) {
                        int digit = temp % 10;
                        int p = 1;
                        for (int i = 0; i < power; ++i) {
                            p *= digit;
                        }
                        sum += p;
                        temp /= 10;
                    }
                }
                T.insert(sum);
            }
            
            vector<int> next_nums;
            for (int num : nums) {
                if (T.find(num) == T.end()) {
                    next_nums.push_back(num);
                }
            }
            nums = next_nums;
            power++;
        }
        
        sort(nums.begin(), nums.end());
        for (size_t i = 0; i < nums.size(); ++i) {
            if (i > 0) cout << " ";
            cout << nums[i];
        }
        cout << "\n";
    }
    
    return 0;
}
