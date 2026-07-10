#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while(cin>>N>>M){
        vector<string> g(N);
        for(int i=0;i<N;i++) cin>>g[i];
        int full = 1<<M;
        // valid row states: any two set bits are >=3 apart
        vector<int> valid;
        for(int s=0;s<full;s++){
            bool ok=true;
            for(int j=0;j<M;j++){
                if((s>>j)&1){
                    if((s>>(j+1))&1 || (s>>(j+2))&1){ ok=false; break; }
                }
            }
            if(ok) valid.push_back(s);
        }
        int V = (int)valid.size();
        vector<int> pc(full);
        for(int s=0;s<full;s++) pc[s]=__builtin_popcount(s);
        // terrain allowed mask per row
        vector<int> allow(N,0);
        for(int i=0;i<N;i++){
            int m=0;
            for(int j=0;j<M;j++) if(g[i][j]=='P') m|=(1<<j);
            allow[i]=m;
        }
        // index of state 0
        int z0=0; while(valid[z0]!=0) z0++;
        // dp[a][b]: latest row state idx a, previous row state idx b
        const int NEG = -1;
        vector<vector<int>> dp(V, vector<int>(V, NEG));
        dp[z0][z0]=0; // rows -1 and -2 are empty
        for(int i=0;i<N;i++){
            vector<vector<int>> nd(V, vector<int>(V, NEG));
            int ai = allow[i];
            // gather for each b the list of c with dp[b][c]>=0
            // precompute best per (b, forbidden=a bits) on the fly
            for(int a=0;a<V;a++){
                int sa = valid[a];
                if((sa & ai)!=sa) continue; // must be on plains
                int pa = pc[sa];
                for(int b=0;b<V;b++){
                    int sb = valid[b];
                    if(sa & sb) continue; // conflicts with row i-1
                    int best = NEG;
                    // need max over c: dp[b][c]>=0 and (sa & valid[c])==0
                    for(int c=0;c<V;c++){
                        if(dp[b][c]==NEG) continue;
                        if(sa & valid[c]) continue;
                        if(dp[b][c]>best) best=dp[b][c];
                    }
                    if(best!=NEG) nd[a][b]=best+pa;
                }
            }
            dp.swap(nd);
        }
        int ans=0;
        for(int a=0;a<V;a++)
            for(int b=0;b<V;b++)
                if(dp[a][b]>ans) ans=dp[a][b];
        cout<<ans<<"\n";
    }
    return 0;
}
