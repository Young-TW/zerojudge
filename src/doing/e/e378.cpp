#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x;
    bool first = true;
    while (cin >> x) {
        if (!first) cout << '\n';
        first = false;
        long long k = x / 2;
        long long multiplier = 1;
        for (int i = 0; i < k; i++) multiplier *= 10;
        long double pi = acosl((long double)-1);
        long long ans = floor(pi * (long double)multiplier);
        cout << ans;
    }
    return 0;
}
