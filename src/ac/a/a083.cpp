// a083 食物链 - weighted union-find (relation mod 3)
#include <cstdio>
#include <vector>
using namespace std;

int par[50005];
int d[50005]; // d[x] = (type(x) - type(parent)) mod 3

int find(int x){
    if(par[x]==x) return x;
    int r = find(par[x]);
    d[x] = (d[x] + d[par[x]]) % 3;
    par[x] = r;
    return r;
}

int main(){
    int N,K;
    if(scanf("%d %d",&N,&K)!=2) return 0;
    for(int i=1;i<=N;i++){ par[i]=i; d[i]=0; }
    long long lies=0;
    int D,X,Y;
    int cnt=0;
    while(cnt<K && scanf("%d %d %d",&D,&X,&Y)==3){
        cnt++;
        if(X>N || Y>N){ lies++; continue; }
        if(D==2 && X==Y){ lies++; continue; }
        int fx=find(X), fy=find(Y);
        // required relation r = (type(X)-type(Y)) mod 3
        // D==1 same -> 0 ; D==2 X eats Y -> type(X)-type(Y)=2 (since type(Y)-type(X)=1)
        int r = (D==1)?0:2;
        if(fx==fy){
            int rel = ((d[X]-d[Y])%3+3)%3;
            if(rel != r) lies++;
        } else {
            par[fx]=fy;
            d[fx] = ((d[Y] + r - d[X])%3+3)%3;
        }
    }
    printf("%lld\n", lies);
    return 0;
}
