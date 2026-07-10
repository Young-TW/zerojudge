#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main(){
    int n,m,k;
    if(!(cin>>n>>m>>k)) return 0;
    vector<long long> D(n+1,0);
    for(int i=1;i<=n-1;i++) cin>>D[i];
    vector<long long> T(m), A(m), B(m);
    for(int i=0;i<m;i++){ cin>>T[i]>>A[i]>>B[i]; }
    vector<long long> L(n+1,0);
    for(int i=0;i<m;i++) L[A[i]]=max(L[A[i]],T[i]);
    vector<long long> arr(n+1,0);
    arr[1]=0;
    for(int i=2;i<=n;i++) arr[i]=max(arr[i-1],L[i-1])+D[i-1];
    // suffix passengers: cnt[i]=number of passengers with dest >= i
    vector<long long> cnt(n+2,0);
    for(int i=0;i<m;i++) cnt[B[i]]++;
    for(int i=n;i>=1;i--) cnt[i]+=cnt[i+1];
    long long total=0;
    for(int i=0;i<m;i++) total+=arr[B[i]]-T[i];
    // batched greedy
    while(k>0){
        // nextWait[j] = first j'>=j with arr[j']<=L[j'], else n
        vector<int> nextWait(n+2,n);
        nextWait[n+1]=n;
        for(int j=n;j>=1;j--){
            if(arr[j]<=L[j]) nextWait[j]=j;
            else nextWait[j]=nextWait[j+1];
        }
        long long best=0; int bi=-1; int br=n;
        for(int i=1;i<=n-1;i++){
            if(D[i]==0) continue;
            int r=nextWait[i+1];
            long long ben=cnt[i+1]-cnt[r+1];
            if(ben>best){ best=ben; bi=i; br=r; }
        }
        if(bi==-1 || best<=0) break;
        // gap: how many units keep benefit==best before some intermediate spot
        // becomes a waiting spot (arr[j] drops to L[j]) or D[bi] hits 0.
        // Spots in [bi+1, br-1] (if br<n) or [bi+1, n] (if br==n) are non-waiting;
        // the first to hit L caps the benefit.
        long long gap = D[bi];
        int hi = (br==n) ? n : br-1;
        for(int j=bi+1; j<=hi; j++) gap = min(gap, arr[j]-L[j]);
        if(gap<=0) gap=1;
        long long use = min((long long)k, gap);
        D[bi]-=use; k-=(int)use;
        arr[1]=0;
        for(int i=2;i<=n;i++) arr[i]=max(arr[i-1],L[i-1])+D[i-1];
        total -= use*best;
    }
    cout<<total<<"\n";
    return 0;
}
