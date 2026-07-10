#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstring>
using namespace std;

typedef long long ll;
static const ll MOD = 1000000000LL;

static ll pow2mod(ll e){
    if(e < 0) return 0;
    ll r = 1, base = 2 % MOD;
    while(e > 0){
        if(e & 1) r = r * base % MOD;
        base = base * base % MOD;
        e >>= 1;
    }
    return r;
}

struct DSU {
    vector<int> fa, rk, par;
    void init(int n){
        fa.resize(n); rk.assign(n, 0); par.assign(n, 0);
        iota(fa.begin(), fa.end(), 0);
    }
    pair<int,int> find(int x){
        if(fa[x] == x) return make_pair(x, 0);
        pair<int,int> p = find(fa[x]);
        fa[x] = p.first; par[x] ^= p.second;
        return make_pair(fa[x], par[x]);
    }
    bool unite(int x, int y, int w){
        pair<int,int> px = find(x), py = find(y);
        int rx = px.first, dx = px.second, ry = py.first, dy = py.second;
        if(rx == ry) return (dx ^ dy) == w;
        if(rk[rx] < rk[ry]){ fa[rx] = ry; par[rx] = dx ^ dy ^ w; }
        else if(rk[rx] > rk[ry]){ fa[ry] = rx; par[ry] = dx ^ dy ^ w; }
        else { fa[rx] = ry; par[rx] = dx ^ dy ^ w; rk[ry]++; }
        return true;
    }
};

int main(){
    ll n, m; int k;
    while(scanf("%lld %lld %d", &n, &m, &k) == 3){
        vector<int> xs(k), ys(k), cs(k);
        vector<int> vy, vx;
        vy.reserve(k); vx.reserve(k);
        for(int i = 0; i < k; i++){
            int x, y, c;
            scanf("%d %d %d", &x, &y, &c);
            xs[i] = x; ys[i] = y; cs[i] = c;
            if(x >= 2) vx.push_back(x);
            if(y >= 2) vy.push_back(y);
        }
        sort(vy.begin(), vy.end()); vy.erase(unique(vy.begin(), vy.end()), vy.end());
        sort(vx.begin(), vx.end()); vx.erase(unique(vx.begin(), vx.end()), vx.end());
        int Y = (int)vy.size(), X = (int)vx.size();
        int G = Y + X;
        int nodes = Y + X + 1;
        ll unmentioned = (m - 1 - (ll)Y) + (n - 1 - (ll)X);
        ll ans = 0;
        for(int b = 0; b < 2; b++){
            DSU dsu; dsu.init(nodes);
            bool ok = true;
            for(int i = 0; i < k && ok; i++){
                int x = xs[i], y = ys[i], c = cs[i];
                if(x == 1 && y == 1){
                    if(c != b) ok = false;
                } else if(x == 1){
                    int id = (int)(lower_bound(vy.begin(), vy.end(), y) - vy.begin());
                    if(!dsu.unite(id, G, c)) ok = false;
                } else if(y == 1){
                    int id = Y + (int)(lower_bound(vx.begin(), vx.end(), x) - vx.begin());
                    if(!dsu.unite(id, G, c)) ok = false;
                } else {
                    int p = ((x % 2 == 0) && (y % 2 == 0)) ? 1 : 0;
                    int w = c ^ p ^ b;
                    int idy = (int)(lower_bound(vy.begin(), vy.end(), y) - vy.begin());
                    int idx = Y + (int)(lower_bound(vx.begin(), vx.end(), x) - vx.begin());
                    if(!dsu.unite(idy, idx, w)) ok = false;
                }
            }
            if(!ok) continue;
            int K = 0;
            for(int v = 0; v < nodes; v++) if(dsu.find(v).first == v) K++;
            ll exp = (ll)(K - 1) + unmentioned;
            ans = (ans + pow2mod(exp)) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
