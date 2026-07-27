#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    bool first = true;
    while(cin >> n >> m >> k){
        vector<int> X(n+1), Y(n+1); // position 1..n use params of column index (1-based transition)
        for(int i=1;i<=n;i++) cin >> X[i] >> Y[i];
        vector<int> gapL(n+1,-1), gapH(n+1,-1);
        vector<char> hasPipe(n+1,0);
        for(int i=0;i<k;i++){
            int P,L,H; cin >> P >> L >> H;
            hasPipe[P]=1; gapL[P]=L; gapH[P]=H;
        }
        // dp
        vector<int> prev(m+1, INF), cur(m+1, INF);
        for(int j=1;j<=m;j++) prev[j]=0; // start column 0, any height 1..m, 0 clicks

        bool success = true;
        int passed = 0;      // pipes passed (for failure output)
        int ansClicks = INF;

        for(int i=1;i<=n;i++){
            int x = X[i], y = Y[i];
            for(int j=0;j<=m;j++) cur[j]=INF;
            // UP: click at least once (complete knapsack). exact landings j in [x+1, m]
            for(int j=x+1;j<=m;j++){
                int s1 = prev[j-x];
                int s2 = cur[j-x];
                int best = min(s1, s2);
                if(best < INF) cur[j] = min(cur[j], best + 1);
            }
            // overshoot / exact to top m: sources in [m-x, m] -> clamp to m
            for(int s=m-x; s<=m; s++){
                if(s < 1) continue;
                int best = min(prev[s], cur[s]);
                if(best < INF) cur[m] = min(cur[m], best + 1);
            }
            // DOWN: no click, source j+y <= m
            for(int j=1;j<=m-y;j++){
                if(prev[j+y] < INF) cur[j] = min(cur[j], prev[j+y]);
            }
            // pipe constraint at column i
            if(hasPipe[i]){
                int L=gapL[i], H=gapH[i];
                for(int j=1;j<=m;j++){
                    if(j<=L || j>=H) cur[j]=INF;
                }
            }
            // reachability
            bool ok=false;
            for(int j=1;j<=m;j++) if(cur[j]<INF){ ok=true; break; }

            if(hasPipe[i]){
                if(ok) passed++;
                else { success=false; break; }
            } else {
                if(!ok){ success=false; break; }
            }
            swap(prev, cur);
        }

        if(success){
            for(int j=1;j<=m;j++) ansClicks=min(ansClicks, prev[j]);
        }

        if(!first) cout << "\n";
        first=false;
        if(success) cout << 1 << "\n" << ansClicks << "\n";
        else cout << 0 << "\n" << passed << "\n";
    }
    return 0;
}
