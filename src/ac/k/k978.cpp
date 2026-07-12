#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        vector<string> nums(T);
        for (int i = 0; i < T; i++) {
            cin >> nums[i];
        }
        int n;
        cin >> n;
        
        vector<string> reached, notReached;
        for (int i = 0; i < T; i++) {
            if ((int)nums[i].length() >= n) {
                reached.push_back(nums[i]);
            } else {
                notReached.push_back(nums[i]);
            }
        }
        
        sort(reached.begin(), reached.end(), [n](const string& a, const string& b) {
            char da = a[n-1], db = b[n-1];
            if (da != db) return da < db;
            if (a.length() != b.length()) return a.length() < b.length();
            return a < b;
        });
        
        vector<string> result;
        
        if (notReached.size() == 1) {
            result.push_back(notReached[0]);
        }
        
        for (int i = 0; i < (int)reached.size(); i++) {
            result.push_back(reached[i]);
        }
        
        if (notReached.size() > 1) {
            sort(notReached.begin(), notReached.end(), [](const string& a, const string& b) {
                char la = a.back(), lb = b.back();
                if (la != lb) return la > lb;
                if (a.length() != b.length()) return a.length() > b.length();
                return a > b;
            });
            for (int i = 0; i < (int)notReached.size(); i++) {
                result.push_back(notReached[i]);
            }
        }
        
        for (int i = 0; i < (int)result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }
    
    return 0;
}
