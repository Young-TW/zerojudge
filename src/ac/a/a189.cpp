#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, M; long long Q;
    if(scanf("%d %d %lld", &N, &M, &Q)!=3) return 0;
    vector<vector<int>> adj(N+1);
    for(int i=0;i<M;i++){
        int a,b; if(scanf("%d %d",&a,&b)!=2) break;
        if(a>=1&&a<=N&&b>=1&&b<=N){ adj[a].push_back(b); adj[b].push_back(a); }
    }
    if(M != N-1){ printf("-1\n-1\n"); return 0; }
    vector<int> parent(N+1,0), order; order.reserve(N);
    vector<char> vis(N+1,0);
    {
        queue<int> qq; qq.push(1); vis[1]=1; parent[1]=0;
        while(!qq.empty()){
            int v=qq.front(); qq.pop(); order.push_back(v);
            for(int u:adj[v]) if(!vis[u]){ vis[u]=1; parent[u]=v; qq.push(u); }
        }
    }
    if((int)order.size()!=N){ printf("-1\n-1\n"); return 0; }

    // min inconvenience DP
    vector<array<int,3>> m(N+1);
    for(int i=N-1;i>=0;i--){
        int v=order[i];
        int c0=0,c1=0,c2=0;
        for(int u:adj[v]) if(u!=parent[v]){
            int f2=m[u][2], f1=m[u][1];
            int n2 = min( max(c2, f2+1), max(c1, f1) );
            int n1 = min( max(c1, f2+1), max(c0, f1) );
            int n0 = max(c0, f2+1);
            c2=n2;c1=n1;c0=n0;
        }
        m[v][0]=c0;m[v][1]=c1;m[v][2]=c2;
    }
    int L = m[1][2];

    // counting DP over budget b = 0..L
    vector<long long> prev0(N+1,0),prev1(N+1,0),prev2(N+1,0);
    vector<long long> cur0(N+1,0),cur1(N+1,0),cur2(N+1,0);
    for(int b=0;b<=L;b++){
        for(int i=N-1;i>=0;i--){
            int v=order[i];
            long long c0=1%Q,c1=0,c2=0;
            for(int u:adj[v]) if(u!=parent[v]){
                long long T1=(cur0[u]+cur1[u])%Q;
                long long T2=(prev0[u]+prev1[u]+prev2[u])%Q;
                long long n2=(c2*T2 + c1*T1)%Q;
                long long n1=(c1*T2 + c0*T1)%Q;
                long long n0=(c0*T2)%Q;
                c0=n0;c1=n1;c2=n2;
            }
            cur0[v]=c0;cur1[v]=c1;cur2[v]=c2;
        }
        swap(prev0,cur0); swap(prev1,cur1); swap(prev2,cur2);
    }
    long long ans = (prev0[1]+prev1[1]+prev2[1])%Q;
    printf("%d\n%lld\n", L, ans);
    return 0;
}
