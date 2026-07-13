#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

pair<long long, string> get_sum_and_expr(long long x) {
    if (x == 1) {
        return {0, "=0"};
    }
    vector<long long> divs;
    divs.push_back(1);
    for (long long i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            divs.push_back(i);
            if (i * i != x) {
                divs.push_back(x / i);
            }
        }
    }
    sort(divs.begin(), divs.end());
    
    string expr;
    long long sum = 0;
    for (size_t i = 0; i < divs.size(); ++i) {
        sum += divs[i];
        if (i > 0) expr += "+";
        expr += to_string(divs[i]);
    }
    expr += "=" + to_string(sum);
    return {sum, expr};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n) {
        auto p1 = get_sum_and_expr(n);
        cout << p1.second << "\n";
        
        if (p1.first == n) {
            cout << n << " is perfect.\n";
        } else {
            long long m = p1.first;
            auto p2 = get_sum_and_expr(m);
            cout << p2.second << "\n";
            
            if (p2.first == n) {
                cout << n << " and " << m << " are friends.\n";
            } else {
                cout << n << " has no friends.\n";
            }
        }
    }
    return 0;
}
