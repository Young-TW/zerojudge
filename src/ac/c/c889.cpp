#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    while(scanf("%d %d",&n,&m)==2){
        vector<vector<int>> adj(n+1);
        for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);adj[a].push_back(b);adj[b].push_back(a);}
        vector<int> col(n+1,-1);
        long long total=0; bool ok=true;
        for(int s=1;s<=n&&ok;s++){
            if(col[s]!=-1) continue;
            queue<int> q; q.push(s); col[s]=0;
            long long c0=0,c1=0;
            while(!q.empty()&&ok){
                int u=q.front();q.pop();
                if(col[u]==0)c0++;else c1++;
                for(int v:adj[u]){
                    if(col[v]==-1){col[v]=col[u]^1;q.push(v);}
                    else if(col[v]==col[u]){ok=false;break;}
                }
            }
            total+=min(c0,c1);
        }
        printf("%lld\n", ok?total:0);
    }
}
