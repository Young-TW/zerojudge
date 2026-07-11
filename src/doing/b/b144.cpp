#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while(cin >> n){
        vector<pair<int,int>> nb(n+1);
        for(int i=1;i<=n;i++){
            cin >> nb[i].first >> nb[i].second;
        }
        vector<int> c(n);
        c[0] = 1;
        c[1] = nb[1].first;
        bool ok = true;
        for(int i=1;i<n-1;i++){
            int s = c[i], pr = c[i-1];
            if(nb[s].first!=pr && nb[s].second!=pr){ ok=false; break; }
            c[i+1] = (nb[s].first==pr) ? nb[s].second : nb[s].first;
        }
        if(ok){
            vector<int> seen(n+1, 0);
            for(int i=0;i<n;i++){
                if(c[i]<1 || c[i]>n || seen[c[i]]){ ok=false; break; }
                seen[c[i]] = 1;
            }
        }
        if(ok){
            for(int i=0;i<n;i++){
                int s=c[i], left=c[(i-1+n)%n], right=c[(i+1)%n];
                int a=nb[s].first, b=nb[s].second;
                if(!((a==left&&b==right)||(a==right&&b==left))){ ok=false; break; }
            }
        }
        if(!ok){ cout << -1 << "\n"; continue; }
        vector<int> pos(n+1);
        for(int i=0;i<n;i++) pos[c[i]] = i;
        vector<int> cnt(n,0), cnt2(n,0);
        for(int s=1;s<=n;s++){
            int r = ((pos[s]-s+1)%n+n)%n;
            cnt[r]++;
            int r2 = ((-pos[s]-s+1)%n+n)%n;
            cnt2[r2]++;
        }
        int maxf=0;
        for(int i=0;i<n;i++){ maxf=max(maxf,cnt[i]); maxf=max(maxf,cnt2[i]); }
        cout << (n-maxf) << "\n";
    }
    return 0;
}
