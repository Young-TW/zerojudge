#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>
using namespace std;

typedef long long ll;

ll countInversions(vector<ll>& arr) {
    int n = (int)arr.size();
    if (n <= 1) return 0;
    
    vector<ll> sorted_arr = arr;
    sort(sorted_arr.begin(), sorted_arr.end());
    sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());
    
    int m = (int)sorted_arr.size();
    vector<ll> bit(m + 2, 0);
    
    auto update = [&](int i) -> void {
        for (; i <= m; i += i & (-i)) bit[i]++;
    };
    auto query = [&](int i) -> ll {
        ll s = 0;
        for (; i > 0; i -= i & (-i)) s += bit[i];
        return s;
    };
    
    ll inv = 0;
    for (int i = n - 1; i >= 0; i--) {
        int rank = (int)(lower_bound(sorted_arr.begin(), sorted_arr.end(), arr[i]) - sorted_arr.begin()) + 1;
        inv += query(rank - 1);
        update(rank);
    }
    return inv;
}

int main() {
    string line;
    int state = 0;
    int k = 0;
    int needed = 0;
    vector<ll> s, r;
    
    while (getline(cin, line)) {
        while (!line.empty() && line.back() == '\r') line.pop_back();
        
        istringstream iss(line);
        vector<ll> nums;
        string tok;
        bool all_numeric = true;
        bool has_token = false;
        while (iss >> tok) {
            has_token = true;
            bool numeric = true;
            size_t start = 0;
            if (!tok.empty() && tok[0] == '-') start = 1;
            if (start >= tok.size()) numeric = false;
            for (size_t i = start; i < tok.size(); i++) {
                if (!isdigit((unsigned char)tok[i])) { numeric = false; break; }
            }
            if (numeric) {
                nums.push_back(stoll(tok));
            } else {
                all_numeric = false;
            }
        }
        if (!has_token) {
            cout << "\n";
        } else if (all_numeric) {
            size_t idx = 0;
            while (idx < nums.size()) {
                if (state == 0) {
                    k = (int)nums[idx++];
                    if (idx < nums.size()) idx++;
                    s.clear();
                    r.clear();
                    needed = k;
                    state = 1;
                } else if (state == 1) {
                    while (needed > 0 && idx < nums.size()) {
                        s.push_back(nums[idx++]);
                        needed--;
                    }
                    if (needed == 0) {
                        needed = k;
                        state = 2;
                    }
                } else {
                    while (needed > 0 && idx < nums.size()) {
                        r.push_back(nums[idx++]);
                        needed--;
                    }
                    if (needed == 0) {
                        vector<pair<ll, ll> > pairs(k);
                        for (int i = 0; i < k; i++) {
                            pairs[i] = make_pair(s[i], r[i]);
                        }
                        sort(pairs.begin(), pairs.end());
                        vector<ll> r_sorted(k);
                        for (int i = 0; i < k; i++) {
                            r_sorted[i] = pairs[i].second;
                        }
                        ll ans = countInversions(r_sorted);
                        cout << ans << "\n";
                        state = 0;
                    }
                }
            }
        } else {
            cout << line << "\n";
        }
    }
    return 0;
}
