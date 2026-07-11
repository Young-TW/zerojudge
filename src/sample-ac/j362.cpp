#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a;
    string s;
    while (cin >> a >> s) {
        vector<long long> factors;
        for (long long i = 1; i * i <= a; ++i) {
            if (a % i == 0) {
                factors.push_back(i);
                if (i * i != a) {
                    factors.push_back(a / i);
                }
            }
        }
        sort(factors.begin(), factors.end());
        
        long long count = 0;
        long long sum = 0;
        for (long long factor : factors) {
            if (s == "no") {
                if (factor == 1 || factor == a) {
                    continue;
                }
            }
            cout << factor << "\n";
            count++;
            sum += factor;
        }
        cout << a << "的因數的個數是" << count << "，" << a << "的因數的總和是" << sum << "\n";
    }
    return 0;
}
