#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while(cin>>n){
        vector<int> a(n+1), b(n+1);
        for(int i=1;i<=n;i++){
            cin>>a[i]>>b[i];
        }
        bool ok=true;
        for(int i=1;i<=n;i++){
            int x=a[i], y=b[i];
            if(x<1||x>n||y<1||y>n||x==y||x==i||y==i){ ok=false; break; }
            if(a[x]!=i && b[x]!=i){ ok=false; break; }
            if(a[y]!=i && b[y]!=i){ ok=false; break; }
        }
        if(!ok){ cout<<-1<<"\n"; continue; }
        vector<int> cyc;
        cyc.reserve(n);
        vector<char> vis(n+1,0);
        int cur=1, prevv=-1;
        bool fail=false;
        for(int i=0;i<n;i++){
            if(vis[cur]){ fail=true; break; }
            vis[cur]=1;
            cyc.push_back(cur);
            int next = (a[cur]!=prevv) ? a[cur] : b[cur];
            prevv=cur;
            cur=next;
        }
        if(fail||cur!=1){ cout<<-1<<"\n"; continue; }
        
        auto countMax=[&](vector<int>& c){
            vector<int> cnt(n,0);
            for(int j=0;j<n;j++){
                int s=c[j];
                int r=((j-(s-1))%n+n)%n;
                cnt[r]++;
            }
            int mx=0;
            for(int x:cnt) mx=max(mx,x);
            return mx;
        };
        
        int m1=countMax(cyc);
        vector<int> rev(n);
        rev[0]=cyc[0];
        for(int j=1;j<n;j++) rev[j]=cyc[n-j];
        int m2=countMax(rev);
        cout<<n-max(m1,m2)<<"\n";
    }
    return 0;
}
