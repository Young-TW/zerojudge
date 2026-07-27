#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<int> succ_[2005], pred_[2005];
int outdeg[2005], k[2005], cnt[2005];
int solveX(int x){
    // count max flights placed after x; answer = n - that = pos where x forced
    for(int v=1;v<=n;v++) cnt[v]=outdeg[v];
    priority_queue<pair<int,int>> pq; // (k, node)
    for(int v=1;v<=n;v++) if(v!=x && cnt[v]==0) pq.push({k[v],v});
    int pos=n;
    while(pos>=1){
        if(pq.empty() || pq.top().first < pos){ // x forced here
            return pos;
        }
        auto t=pq.top(); pq.pop();
        int v=t.second;
        for(int u: pred_[v]){
            if(--cnt[u]==0 && u!=x) pq.push({k[u],u});
        }
        pos--;
    }
    return 0; // shouldn't happen
}
int main(){
    bool first=true;
    while(scanf("%d %d",&n,&m)==2){
        for(int v=1;v<=n;v++){succ_[v].clear();pred_[v].clear();outdeg[v]=0;}
        for(int v=1;v<=n;v++) scanf("%d",&k[v]);
        for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);succ_[a].push_back(b);pred_[b].push_back(a);outdeg[a]++;}
        if(!first) printf("\n");
        first=false;
        for(int x=1;x<=n;x++){
            printf("%d%c", solveX(x), x==n?'\n':' ');
        }
    }
    return 0;
}
