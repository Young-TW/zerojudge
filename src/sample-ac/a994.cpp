#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b) {
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll N;
    int M;
    while (cin >> N >> M) {
        vector<ll> v(M);
        for (int i = 0; i < M; ++i) {
            cin >> v[i];
        }
        
        sort(v.begin(), v.end());
        vector<ll> nums;
        for (int i = 0; i < M; ++i) {
            bool ok = true;
            for (ll y : nums) {
                if (v[i] % y == 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                nums.push_back(v[i]);
            }
        }
        
        int m = nums.size();
        ll ans = 0;
        for (int mask = 1; mask < (1 << m); ++mask) {
            ll lcm = 1;
            int bits = 0;
            for (int i = 0; i < m; ++i) {
                if (mask & (1 << i)) {
                    bits++;
                    ll g = gcd(lcm, nums[i]);
                    if (lcm / g > N / nums[i]) {
                        lcm = N + 1;
                        break;
                    } else {
                        lcm = lcm / g * nums[i];
                    }
                }
            }
            if (lcm <= N) {
                if (bits % 2 == 1) {
                    ans += N / lcm;
                } else {
                    ans -= N / lcm;
                }
            }
        }
        cout << N - ans << "\n";
    }
    
    return 0;
}
