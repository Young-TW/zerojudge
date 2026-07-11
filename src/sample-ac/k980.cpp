#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <cstring>
using namespace std;

vector<long long> getFactors(long long n) {
    vector<long long> factors;
    if (n == 1) {
        factors.push_back(1);
        return factors;
    }
    factors.push_back(1);
    factors.push_back(n);
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            factors.push_back(i);
            if (i != n / i) {
                factors.push_back(n / i);
            }
        }
    }
    sort(factors.begin(), factors.end());
    return factors;
}

int countFactors(long long n) {
    if (n == 1) return 1;
    int count = 2;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            count++;
            if (i != n / i) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    string s;
    while (cin >> s) {
        int max_factors = 0;
        vector<long long> candidates;

        for (int i = 0; i < s.size(); ++i) {
            long long num = 0;
            for (int j = i; j < s.size(); ++j) {
                num = num * 10 + (s[j] - '0');
                int cnt = countFactors(num);
                if (cnt > max_factors) {
                    max_factors = cnt;
                    candidates.clear();
                    candidates.push_back(num);
                } else if (cnt == max_factors) {
                    candidates.push_back(num);
                }
            }
        }

        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

        if (candidates.size() == 1) {
            cout << candidates[0] << endl;
        } else {
            for (long long num : candidates) {
                cout << num << endl;
            }
            long long gcd_val = candidates[0];
            for (size_t i = 1; i < candidates.size(); ++i) {
                long long a = gcd_val;
                long long b = candidates[i];
                while (b != 0) {
                    long long temp = b;
                    b = a % b;
                    a = temp;
                }
                gcd_val = a;
            }
            long long lcm_val = candidates[0];
            for (size_t i = 1; i < candidates.size(); ++i) {
                long long a = lcm_val;
                long long b = candidates[i];
                long long g = gcd_val;
                lcm_val = (a / g) * b;
            }
            cout << gcd_val << endl;
            cout << lcm_val << endl;
        }
    }
    return 0;
}
