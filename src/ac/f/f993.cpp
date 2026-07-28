#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef __int128 i128;

const int SCALE = 100000;

struct Obstacle {
    int t;
    ll x;
    ll A, B;
};

int n;
ll R;
int q;
vector<Obstacle> obs;

ll simulate(ll x0, ll K0, ll p, ll M) {
    int start = lower_bound(obs.begin(), obs.end(), x0, [](const Obstacle& o, ll val) { return o.x < val; }) - obs.begin();
    ll K = K0;
    ll bombs = 0;
    for (int i = start; i < n; ++i) {
        ll dis = obs[i].x - x0;
        if (obs[i].t == 1) {
            ll C_scaled = obs[i].A + obs[i].B * dis;
            ll ceil_C = (C_scaled + SCALE - 1) / SCALE;
            ll K_min = ceil_C + 1;
            if (K < K_min) {
                ll need = K_min - K;
                ll m_add = (need + p - 1) / p;
                bombs += m_add;
                if (bombs > M) return M + 1;
                K += m_add * p;
            }
            K = K - ceil_C;
            if (K <= 0) return M + 1;
        } else if (obs[i].t == 2) {
            ll D_scaled = obs[i].A + obs[i].B * dis;
            ll ceil_D = (D_scaled + SCALE - 1) / SCALE;
            ll K_min = ceil_D;
            if (K < K_min) {
                ll need = K_min - K;
                ll m_add = (need + p - 1) / p;
                bombs += m_add;
                if (bombs > M) return M + 1;
                K += m_add * p;
            }
            i128 K_big = (i128)K * SCALE;
            K = (ll)(K_big / D_scaled);
            if (K <= 0) return M + 1;
        } else if (obs[i].t == 3) {
            if (K <= 0) return M + 1;
            if (K == 1) {
                continue;
            }
            ll D_scaled = obs[i].A + obs[i].B * dis;
            if (D_scaled >= 60LL * SCALE) {
                K = 1;
            } else {
                long double D_ld = (long double)D_scaled / SCALE;
                long double K_ld = (long double)K;
                long double y_ld = powl(K_ld, 1.0L / D_ld);
                ll y = (ll)floorl(y_ld);
                if (y < 1) y = 1;
                while (powl((long double)(y+1), D_ld) <= K_ld + 1e-9L) {
                    y++;
                }
                while (y > 1 && powl((long double)y, D_ld) > K_ld + 1e-9L) {
                    y--;
                }
                K = y;
            }
            if (K <= 0) return M + 1;
        } else if (obs[i].t == 4) {
            ll D_scaled = obs[i].A + obs[i].B * dis;
            ll ceil_D = (D_scaled + SCALE - 1) / SCALE;
            ll K_min = ceil_D;
            if (K < K_min) {
                ll need = K_min - K;
                ll m_add = (need + p - 1) / p;
                bombs += m_add;
                if (bombs > M) return M + 1;
                K += m_add * p;
            }
            long double D_ld = (long double)D_scaled / SCALE;
            long double K_ld = (long double)K;
            ll y;
            if (K_ld < D_ld) {
                y = 0;
            } else {
                y = (ll)floorl(logl(K_ld) / logl(D_ld));
                while (powl(D_ld, y+1) <= K_ld + 1e-12L) y++;
                while (y > 0 && powl(D_ld, y) > K_ld + 1e-12L) y--;
            }
            K = y;
            if (K <= 0) return M + 1;
        }
    }
    return bombs;
}

int main() {
    while (scanf("%d %lld %d", &n, &R, &q) == 3) {
        obs.resize(n);
        for (int i = 0; i < n; ++i) {
            int t;
            ll x;
            int a_int, a_frac, b_int, b_frac;
            scanf("%d %lld %d.%d %d.%d", &t, &x, &a_int, &a_frac, &b_int, &b_frac);
            obs[i].t = t;
            obs[i].x = x;
            obs[i].A = (ll)a_int * SCALE + a_frac;
            obs[i].B = (ll)b_int * SCALE + b_frac;
        }
        for (int i = 0; i < q; ++i) {
            ll K0, p, M;
            scanf("%lld %lld %lld", &K0, &p, &M);
            ll low = 0, high = R, ans_x0 = R;
            while (low <= high) {
                ll mid = (low + high) / 2;
                ll bombs = simulate(mid, K0, p, M);
                if (bombs <= M) {
                    ans_x0 = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            ll dis_max = R - ans_x0;
            ll m_min = simulate(ans_x0, K0, p, M);
            printf("%lld %lld\n", dis_max, m_min);
        }
    }
    return 0;
}
