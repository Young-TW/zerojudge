#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n,k,m;
    while(cin>>n>>k>>m){
        vector<long long> w(n);
        for(auto &x:w) cin>>x;
        // dp[c] = pair(buses, load) lexicographically minimized, for boarding exactly c turtles
        const long long INFB = LLONG_MAX/4;
        vector<pair<long long,long long>> dp(n+1, {INFB,0});
        dp[0]={1,0}; // on bus 1, load 0
        int maxc=0;
        for(int idx=0;idx<n;idx++){
            long long wt=w[idx];
            if(wt>m) continue; // can never board
            for(int c=maxc+1;c>=1;c--){
                if(dp[c-1].first>=INFB) continue;
                long long b=dp[c-1].first, L=dp[c-1].second;
                long long nb,nl;
                if(L+wt<=m){ nb=b; nl=L+wt; }
                else { nb=b+1; nl=wt; }
                // lexicographic min into dp[c]
                if(nb<dp[c].first || (nb==dp[c].first && nl<dp[c].second)){
                    dp[c]={nb,nl};
                    if(c>maxc) maxc=c;
                }
            }
        }
        int ans=0;
        for(int c=0;c<=n;c++){
            if(dp[c].first<=k) ans=max(ans,c);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
