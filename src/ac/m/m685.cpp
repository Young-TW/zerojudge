#include <iostream>
#include <algorithm>
#include <set>
#include <tuple>

using namespace std;

long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        a %= b;
        long long temp = a;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        set<tuple<long long, long long, long long>> s;
        for (long long i = 0; i < n; ++i) {
            long long a, b, c;
            cin >> a >> b >> c;
            long long g = gcd(a, gcd(b, c));
            if (g != 0) {
                a /= g;
                b /= g;
                c /= g;
            }
            long long arr[3] = {a, b, c};
            sort(arr, arr + 3);
            s.insert(make_tuple(arr[0], arr[1], arr[2]));
        }
        cout << s.size() << "\n";
    }
    return 0;
}
