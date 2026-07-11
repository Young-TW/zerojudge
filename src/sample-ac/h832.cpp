#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll euler_phi(ll n) {
    ll result = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (__int128)result * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

// 計算塔狀次方，並回傳實際值是否大於等於 phi
// 如果實際值 >= phi，回傳 (value % phi + phi)，否則回傳實際值
pair<ll, bool> tower_power(const vector<ll>& a, int l, int r, ll mod) {
    if (mod == 1) return {0, true};
    if (l == r) {
        if (a[l] >= mod) return {a[l] % mod, true};
        return {a[l], a[l] >= mod};
    }
    
    ll phi = euler_phi(mod);
    pair<ll, bool> next_val = tower_power(a, l + 1, r, phi);
    
    ll exp = next_val.first;
    bool large = next_val.second;
    
    // 如果指數部分已經很大，或者底數的冪次會超過 mod
    ll result = mod_pow(a[l], exp + (large ? phi : 0), mod);
    
    // 判斷結果是否實際上大於等於 mod
    // 這裡需要小心處理，因為我們只保留了 mod 後的值
    // 簡單判斷：如果底數 >= 2 且指數足夠大，結果通常會很大
    bool is_large = false;
    if (a[l] == 1) {
        is_large = (1 >= mod);
    } else if (a[l] >= 2) {
        // 粗略估計：如果指數部分很大，結果就會很大
        if (large) is_large = true;
        else {
            // 指數不大時，直接計算看看
            double check = pow((double)a[l], (double)next_val.first);
            if (check >= mod || check > 1e18) is_large = true;
        }
    }
    
    return {result, is_large};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll m;
    while (cin >> n >> m) {
        vector<ll> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        
        int q;
        cin >> q;
        while (q--) {
            int l, r;
            cin >> l >> r;
            
            pair<ll, bool> result = tower_power(a, l, r, m);
            cout << result.first << "\n";
        }
    }
    
    return 0;
}
