#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>
#include <utility>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
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
    if (!(cin >> n)) return 0;
    
    map<tuple<ll, ll, ll>, int> cnt;
    int m = 0;
    
    for (int i = 0; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        ll arr[3] = {a, b, c};
        sort(arr, arr + 3);
        // Triangle condition: arr[0] + arr[1] > arr[2]
        // Equivalent to arr[0] > arr[2] - arr[1] (avoids overflow)
        // Also need positive side lengths
        if (arr[0] > 0 && arr[0] > arr[2] - arr[1]) {
            ll g = gcd(arr[0], gcd(arr[1], arr[2]));
            cnt[make_tuple(arr[0] / g, arr[1] / g, arr[2] / g)]++;
            m++;
        }
    }
    
    int maxXi = 0;
    for (auto& p : cnt) {
        if (p.second - 1 > maxXi) {
            maxXi = p.second - 1;
        }
    }
    
    cout << m << " " << maxXi << "\n";
    return 0;
}
