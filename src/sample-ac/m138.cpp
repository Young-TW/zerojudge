#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct P{ll x,y;};

int solve_one(vector<P> a, ll K){
    int n=a.size();
    sort(a.begin(),a.end(),[](const P&u,const P&v){return u.x<v.x;});
    vector<int> best(n);
    for(int i=0;i<n;i++){
        vector<ll> ys;
        for(int j=i;j<n && a[j].x<=a[i].x+K;j++) ys.push_back(a[j].y);
        sort(ys.begin(),ys.end());
        int cur=0,l=0;
        for(int r=0;r<(int)ys.size();r++){
            while(ys[r]-ys[l]>K) ++l;
            cur=max(cur,r-l+1);
        }
        best[i]=cur;
    }
    int ans=0;
    for(int v:best) ans=max(ans,v);               // one square
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)     // two squares
        if(a[i].x+K<a[j].x) ans=max(ans,best[i]+best[j]);
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; ll K;
    while(cin>>N>>K){
        vector<P> pts(N);
        for(int i=0;i<N;i++) cin>>pts[i].x>>pts[i].y;
        int ans1=solve_one(pts,K);                // horizontal split
        // vertical: swap x and y
        for(auto &p:pts) swap(p.x,p.y);
        int ans2=solve_one(pts,K);
        cout<<max(ans1,ans2)<<"\n";
    }
    return 0;
}
