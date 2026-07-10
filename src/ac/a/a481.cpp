#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int fa[MAXN], ch[MAXN][2];
ll val[MAXN], sum[MAXN];
bool rev[MAXN];
int par[MAXN]; // explicit tree-parent (for op3 cut)

inline bool isroot(int x){ return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x; }
inline void upd(int x){
    sum[x] = val[x];
    if(ch[x][0]) sum[x]+=sum[ch[x][0]];
    if(ch[x][1]) sum[x]+=sum[ch[x][1]];
}
inline void pushrev(int x){ if(!x) return; rev[x]^=1; swap(ch[x][0],ch[x][1]); }
inline void pushdown(int x){
    if(rev[x]){
        if(ch[x][0]) pushrev(ch[x][0]);
        if(ch[x][1]) pushrev(ch[x][1]);
        rev[x]=0;
    }
}
inline void rotate(int x){
    int y=fa[x], z=fa[y];
    int k=(ch[y][1]==x);
    if(!isroot(y)) ch[z][ch[z][1]==y]=x;
    fa[x]=z;
    ch[y][k]=ch[x][k^1]; if(ch[x][k^1]) fa[ch[x][k^1]]=y;
    ch[x][k^1]=y; fa[y]=x;
    upd(y); upd(x);
}
int stk[MAXN];
inline void splay(int x){
    int top=0; stk[top++]=x;
    for(int y=x;!isroot(y);y=fa[y]) stk[top++]=fa[y];
    while(top) pushdown(stk[--top]);
    while(!isroot(x)){
        int y=fa[x], z=fa[y];
        if(!isroot(y)) ((ch[y][1]==x)^(ch[z][1]==y))?rotate(x):rotate(y);
        rotate(x);
    }
}
inline void access(int x){
    for(int y=0;x;y=x,x=fa[x]){
        splay(x); ch[x][1]=y; upd(x);
    }
}
inline void makeroot(int x){ access(x); splay(x); pushrev(x); }
inline int findroot(int x){
    access(x); splay(x);
    while(ch[x][0]){ pushdown(x); x=ch[x][0]; }
    splay(x);
    return x;
}
inline void split(int x,int y){ makeroot(x); access(y); splay(y); }
inline void link(int x,int y){ makeroot(x); if(findroot(y)!=x) fa[x]=y; }
inline void cut(int x,int y){ makeroot(x); if(findroot(y)==x && fa[y]==x && ch[y][0]==0){ fa[y]=0; ch[x][1]=0; upd(x); } }

int main(){
    int n;
    if(scanf("%d",&n)!=1) return 0;
    for(int i=1;i<=n;i++){
        int p; ll w; scanf("%d %lld",&p,&w);
        fa[i]=0; ch[i][0]=ch[i][1]=0; val[i]=w; sum[i]=w; rev[i]=0;
        par[i]=p;
        if(i!=1 && p!=0){
            link(i,p);
        }
    }
    int q; scanf("%d",&q);
    while(q--){
        int t,x,y; scanf("%d %d %d",&t,&x,&y);
        if(t==1){
            split(x,y);
            printf("%lld\n",sum[y]);
        } else if(t==2){
            splay(x);
            val[x]=y; upd(x);
        } else {
            // change parent of x (x!=1) to y
            int oldp = par[x];
            if(oldp!=0) cut(x,oldp);
            par[x]=y;
            link(x,y);
        }
    }
    return 0;
}
