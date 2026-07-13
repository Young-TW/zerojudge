#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, K;
    while (cin >> N >> K) {
        ll g = gcd(N, K);
        ll L = N / g;
        ll ans = g * (L / 2);
        cout << ans << "\n";
    }
    return 0;
}
