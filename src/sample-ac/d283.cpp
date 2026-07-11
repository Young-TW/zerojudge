#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

struct BigInt {
    vector<int> digits;
    
    BigInt() {}
    BigInt(int val) {
        if (val == 0) {
            digits.push_back(0);
        } else {
            while (val > 0) {
                digits.push_back(val % 1000000000);
                val /= 1000000000;
            }
        }
    }
    
    BigInt operator+(const BigInt& other) const {
        BigInt res;
        long long carry = 0;
        int n = digits.size(), m = other.digits.size();
        for (int i = 0; i < max(n, m) || carry; ++i) {
            long long sum = carry;
            if (i < n) sum += digits[i];
            if (i < m) sum += other.digits[i];
            res.digits.push_back((int)(sum % 1000000000));
            carry = sum / 1000000000;
        }
        return res;
    }
    
    void print() const {
        printf("%d", digits.back());
        for (int i = (int)digits.size() - 2; i >= 0; --i) {
            printf("%09d", digits[i]);
        }
        printf("\n");
    }
};

int main() {
    int n;
    vector<pair<int, int>> queries;
    int maxN = 0;
    int idx = 0;
    while (scanf("%d", &n) == 1) {
        queries.push_back({n, idx++});
        if (n > maxN) maxN = n;
    }
    
    sort(queries.begin(), queries.end());
    
    vector<BigInt> ans(queries.size());
    
    BigInt f0 = BigInt(0);
    BigInt f1 = BigInt(1);
    BigInt f2 = BigInt(1);
    
    int q_idx = 0;
    for (int i = 0; i <= maxN; ++i) {
        BigInt* current_ptr;
        if (i == 0) current_ptr = &f0;
        else if (i == 1) current_ptr = &f1;
        else if (i == 2) current_ptr = &f2;
        else {
            BigInt next = f1 + f2;
            std::swap(f0, f1);
            std::swap(f1, f2);
            std::swap(f2, next);
            current_ptr = &f2;
        }
        
        while (q_idx < queries.size() && queries[q_idx].first == i) {
            ans[queries[q_idx].second] = *current_ptr;
            q_idx++;
        }
    }
    
    for (int i = 0; i < ans.size(); ++i) {
        ans[i].print();
    }
    
    return 0;
}
