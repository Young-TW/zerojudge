#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

void print_int128(__int128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    string s;
    while (x > 0) {
        int digit = x % 10;
        s.push_back('0' + digit);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<int> v;
        int x;
        while (ss >> x) {
            v.push_back(x);
        }
        if (v.size() == 1 && v[0] == 0) break;
        
        int n = v.size();
        if (n < 3) {
            cout << 0 << '\n';
            continue;
        }
        sort(v.begin(), v.end());
        int max_val = v.back();
        vector<__int128> pref(max_val + 1, 1); // prefix sums of subset counts (including empty)
        
        __int128 total_invalid = 0;
        for (int i = 0; i < n; ++i) {
            int a = v[i];
            if (i >= 2) {
                // pref[a] includes empty subset; subtract 1 for empty, subtract i for singletons
                total_invalid += pref[a] - 1 - i;
            }
            // update prefix sums in reverse (standard knapsack style)
            for (int s = max_val; s >= a; --s) {
                pref[s] += pref[s - a];
            }
        }
        
        __int128 total_subsets_ge3 = ((__int128)1 << n) - 1 - n - (__int128)n * (n - 1) / 2;
        __int128 ans = total_subsets_ge3 - total_invalid;
        print_int128(ans);
        cout << '\n';
    }
    return 0;
}
