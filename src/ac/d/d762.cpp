#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> nums(5);
    while (cin >> nums[0] >> nums[1] >> nums[2] >> nums[3] >> nums[4]) {
        if (nums[0] == 0 && nums[1] == 0 && nums[2] == 0 && nums[3] == 0 && nums[4] == 0) {
            break;
        }
        
        sort(nums.begin(), nums.end());
        bool possible = false;
        
        do {
            int a = nums[0], b = nums[1], c = nums[2], d = nums[3], e = nums[4];
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        for (int l = 0; l < 3; ++l) {
                            int res = a;
                            if (i == 0) res += b; else if (i == 1) res -= b; else res *= b;
                            if (j == 0) res += c; else if (j == 1) res -= c; else res *= c;
                            if (k == 0) res += d; else if (k == 1) res -= d; else res *= d;
                            if (l == 0) res += e; else if (l == 1) res -= e; else res *= e;
                            
                            if (res == 23) {
                                possible = true;
                                break;
                            }
                        }
                        if (possible) break;
                    }
                    if (possible) break;
                }
                if (possible) break;
            }
            if (possible) break;
        } while (next_permutation(nums.begin(), nums.end()));
        
        if (possible) {
            cout << "Possible\n";
        } else {
            cout << "Impossible\n";
        }
    }
    
    return 0;
}
