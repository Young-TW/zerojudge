#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    while(cin >> n >> k){
        vector<int> p(k+1);
        for(int i=1;i<=k;i++) cin >> p[i];
        vector<vector<int>> cost(n+1, vector<int>(n+1));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                cin >> cost[i][j];
        
        const long long INF = (long long)4e18;
        // dp[j]: after completing current task, the person who did it is at p[i],
        // the other person is at location (j==0 ? 1 : p[j])
        vector<long long> prev(k+1, INF);
        prev[0] = cost[1][p[1]];
        
        for(int i=1;i<k;i++){
            vector<long long> cur(k+1, INF);
            int pi = p[i], pip1 = p[i+1];
            for(int j=0;j<i;j++){
                if(prev[j] >= INF) continue;
                int locOther = (j==0)?1:p[j];
                // same person does task i+1
                long long v1 = prev[j] + cost[pi][pip1];
                if(v1 < cur[j]) cur[j] = v1;
                // other person does task i+1
                long long v2 = prev[j] + cost[locOther][pip1];
                if(v2 < cur[i]) cur[i] = v2;
            }
            prev.swap(cur);
        }
        
        long long ans = INF;
        for(int j=0;j<k;j++){
            if(prev[j] >= INF) continue;
            int locOther = (j==0)?1:p[j];
            long long total = prev[j] + cost[p[k]][n] + cost[locOther][n];
            if(total < ans) ans = total;
        }
        cout << ans << "\n";
    }
    return 0;
}
