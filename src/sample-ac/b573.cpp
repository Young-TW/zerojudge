#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (cin >> n) {
        while (n--) {
            long long i, j, k;
            cin >> i >> j >> k;
            string s = to_string(i);
            long long val1 = -1, val2 = -1;
            long long cnt = 1;
            while (true) {
                if (cnt == j) val1 = stoll(s);
                if (cnt == k) val2 = stoll(s);
                if (val1 != -1 && val2 != -1) break;
                next_permutation(s.begin(), s.end());
                cnt++;
            }
            cout << gcd(val1, val2) << "\n";
        }
    }
    return 0;
}
