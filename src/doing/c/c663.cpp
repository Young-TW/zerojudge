#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

vector<long long> get_divisors(const vector<pair<long long, int>>& factors) {
    vector<long long> divisors = {1};
    for (const auto& factor : factors) {
        long long p = factor.first;
        int k = factor.second;
        int size = divisors.size();
        for (int i = 0; i < size; ++i) {
            long long current = divisors[i];
            for (int j = 1; j <= k; ++j) {
                current *= p;
                divisors.push_back(current);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    cin.ignore();

    while (T--) {
        string line;
        getline(cin, line);
        istringstream iss(line);

        vector<pair<long long, int>> factors;
        long long p;
        int k;
        while (iss >> p >> k) {
            factors.emplace_back(p, k);
        }

        vector<long long> divisors = get_divisors(factors);

        long long num = 1;
        for (const auto& factor : factors) {
            for (int i = 0; i < factor.second; ++i) {
                num *= factor.first;
            }
        }

        cout << num << " :";
        for (long long d : divisors) {
            cout << " " << d;
        }
        cout << "\n";
    }

    return 0;
}
