#include <cstdio>
#include <climits>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int MAXN = 500005;
int n, k, L, R;
long long S[MAXN];
int LOG[MAXN];
int st[20][MAXN];

pair<long long,int> query(int l, int r){
    if(l > r) return {LLONG_MIN, -1};
    int g = LOG[r - l + 1];
    int a = st[g][l], b = st[g][r - (1 << g) + 1];
    return (S[a] >= S[b]) ? make_pair(S[a], a) : make_pair(S[b], b);
}

struct Item{ long long val; int j, l, r, mp; };
struct Cmp{ bool operator()(const Item&a, const Item&b) const { return a.val < b.val; } };

int main(){
    scanf("%d %d %d %d", &n, &k, &L, &R);
    S[0] = 0;
    for(int i = 1; i <= n; i++){ int x; scanf("%d", &x); S[i] = S[i-1] + x; }
    LOG[1] = 0;
    for(int i = 2; i <= n + 1; i++) LOG[i] = LOG[i/2] + 1;
    for(int i = 0; i <= n; i++) st[0][i] = i;
    for(int g = 1; (1 << g) <= n + 1; g++){
        for(int i = 0; i + (1 << g) - 1 <= n; i++){
            int a = st[g-1][i], b = st[g-1][i + (1 << (g-1))];
            st[g][i] = (S[a] >= S[b]) ? a : b;
        }
    }
    priority_queue<Item, vector<Item>, Cmp> pq;
    for(int j = 0; j + L <= n; j++){
        int l = j + L, r = min(j + R, n);
        auto p = query(l, r);
        if(p.second >= 0) pq.push({p.first - S[j], j, l, r, p.second});
    }
    long long ans = 0;
    for(int t = 0; t < k && !pq.empty(); t++){
        Item it = pq.top(); pq.pop();
        ans += it.val;
        int j = it.j, l = it.l, r = it.r, mp = it.mp;
        if(l <= mp - 1){
            auto p = query(l, mp - 1);
            if(p.second >= 0) pq.push({p.first - S[j], j, l, mp - 1, p.second});
        }
        if(mp + 1 <= r){
            auto p = query(mp + 1, r);
            if(p.second >= 0) pq.push({p.first - S[j], j, mp + 1, r, p.second});
        }
    }
    printf("%lld\n", ans);
    return 0;
}
