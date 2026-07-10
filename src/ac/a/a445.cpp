#include <cstdio>
#include <cstring>

static int par[10005];

int find(int x){ while(par[x]!=x){ par[x]=par[par[x]]; x=par[x]; } return x; }
void unite(int a,int b){ a=find(a); b=find(b); if(a!=b) par[a]=b; }

int main(){
    int N,M,Q;
    if(scanf("%d %d %d",&N,&M,&Q)!=3) return 0;
    for(int i=1;i<=N;i++) par[i]=i;
    for(int i=0;i<M;i++){
        int a,b; scanf("%d %d",&a,&b); unite(a,b);
    }
    for(int i=0;i<Q;i++){
        int p,q; scanf("%d %d",&p,&q);
        printf(find(p)==find(q)? ":)\n": ":(\n");
    }
    return 0;
}
