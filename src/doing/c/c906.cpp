#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

struct BigInt {
    vector<int> d; // base 10000
    
    BigInt() {}
    BigInt(long long x) {
        if (x == 0) d.push_back(0);
        while (x > 0) {
            d.push_back(x % 10000);
            x /= 10000;
        }
    }
    
    void trim() {
        while (d.size() > 1 && d.back() == 0) d.pop_back();
    }
};

BigInt mul4(const BigInt& a) {
    BigInt res;
    res.d.reserve(a.d.size() + 1);
    int carry = 0;
    for (size_t i = 0; i < a.d.size() || carry; ++i) {
        int sum = carry;
        if (i < a.d.size()) sum += a.d[i] * 4;
        res.d.push_back(sum % 10000);
        carry = sum / 10000;
    }
    res.trim();
    return res;
}

BigInt sub_abs(const BigInt& a, const BigInt& b) { // assumes a >= b
    BigInt res;
    res.d.reserve(a.d.size());
    int borrow = 0;
    for (size_t i = 0; i < a.d.size(); ++i) {
        int diff = a.d[i] - borrow;
        if (i < b.d.size()) diff -= b.d[i];
        if (diff < 0) {
            diff += 10000;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.d.push_back(diff);
    }
    res.trim();
    return res;
}

ostream& operator<<(ostream& os, const BigInt& b) {
    os << b.d.back();
    char old_fill = os.fill('0');
    for (int i = b.d.size() - 2; i >= 0; --i) {
        os.width(4);
        os << b.d[i];
    }
    os.fill(old_fill);
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<long long> nums;
    long long x;
    while (cin >> x) {
        nums.push_back(x);
    }
    
    if (nums.empty()) return 0;
    
    vector<pair<long long, int>> queries;
    if (nums.size() == (size_t)nums[0] + 1 && nums[0] >= 0) {
        for (size_t i = 1; i < nums.size(); ++i) {
            queries.push_back({nums[i], (int)(i - 1)});
        }
    } else {
        for (size_t i = 0; i < nums.size(); ++i) {
            queries.push_back({nums[i], (int)i});
        }
    }
    
    if (queries.empty()) return 0;
    
    sort(queries.begin(), queries.end());
    
    vector<BigInt> ans(queries.size());
    
    BigInt prev2(0); // a(0)
    BigInt prev1(1); // a(1)
    
    long long curr = 0;
    for (size_t i = 0; i < queries.size(); ++i) {
        long long target = queries[i].first;
        if (target <= 0) {
            ans[queries[i].second] = BigInt(0);
            continue;
        }
        while (curr < target) {
            curr++;
            if (curr == 1) {
                // prev1 is already 1
            } else {
                BigInt next = sub_abs(mul4(prev1), prev2);
                prev2 = move(prev1);
                prev1 = move(next);
            }
        }
        ans[queries[i].second] = prev1;
    }
    
    for (size_t i = 0; i < ans.size(); ++i) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}
