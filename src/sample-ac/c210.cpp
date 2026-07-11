#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    bool first_case = true;
    while (cin >> n >> m) {
        if (!first_case) {
            cout << '\n';
        }
        first_case = false;
        
        long long t = 0;
        while (t < n && m >= n - t - 1) {
            m -= n - t - 1;
            ++t;
        }
        long long k = n - t;
        
        bool first_num = true;
        auto print_num = [&](long long x) {
            if (first_num) {
                cout << x;
                first_num = false;
            } else {
                cout << ' ' << x;
            }
        };
        
        for (long long i = n; i > n - t; --i) {
            print_num(i);
        }
        
        if (k > 0) {
            print_num(m + 1);
            for (long long i = 1; i <= k; ++i) {
                if (i != m + 1) {
                    print_num(i);
                }
            }
        }
        cout << '\n';
    }
    return 0;
}
