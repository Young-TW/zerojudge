#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int N, M, K;
vector<vector<pair<int,long long>>> adj;
vector<vector<array<long long,2>>> dp; // dp[u][i][s]: i big nodes in subtree, s=state of u
vector<int> sz;
const long long INF = LLONG_MAX/4;

void dfs(int u, int p){
    dp[u].assign(2, {INF, INF});
    dp[u][0][0] = 0;       // u small, 0 big nodes
    dp[u][1][1] = 0;       // u big, 1 big node (itself)
    sz[u] = 1;
    for(auto &e : adj[u]){
        int v = e.first; long long w = e.second;
        if(v == p) continue;
        dfs(v, u);
        int newSz = min(sz[u]+sz[v], K);
        vector<array<long long,2>> ndp(newSz+1, {INF,INF});
        int szU = (int)dp[u].size();
        int szV = (int)dp[v].size();
        for(int iu=0; iu<szU; iu++){
            for(int su=0; su<2; su++){
                long long cu = dp[u][iu][su];
                if(cu >= INF) continue;
                for(int iv=0; iv<szV; iv++){
                    for(int sv=0; sv<2; sv++){
                        long long cv = dp[v][iv][sv];
                        if(cv >= INF) continue;
                        int i = iu+iv;
                        if(i > K) continue;
                        long long add = 0;
                        if(su==1 && sv==1) add += w;           // both big: within-B
                        else if(su==0 && sv==0) add += (M==2 ? w : 0); // both small
                        long long val = cu + cv + add;
                        if(val < ndp[i][su]) ndp[i][su] = val;
                    }
                }
            }
        }
        dp[u] = std::move(ndp);
        sz[u] = newSz;
    }
}

int main(){
    while(cin >> N >> M >> K){
        adj.assign(N+1, {});
        for(int i=0;i<N-1;i++){
            int a,b; long long c;
            cin >> a >> b >> c;
            adj[a].push_back({b,c});
            adj[b].push_back({a,c});
        }
        // feasibility: small region (N-K nodes) must fill M-1 non-empty small heads
        if(N - K < M - 1){
            cout << -1 << "\n";
            continue;
        }
        dp.assign(N+1, {});
        sz.assign(N+1, 0);
        dfs(1, 0);
        cout << dp[1][K][1] << "\n";
    }
    return 0;
}
