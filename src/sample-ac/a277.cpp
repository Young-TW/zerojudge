#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    int n;
    static int a[100005];
    while(scanf("%d",&n)==1){
        for(int i=0;i<n;i++) scanf("%d",&a[i]);
        sort(a,a+n);
        long long k=(long long)n*(n-1)/2;
        long long target=(k+1)/2;
        long long lo=0, hi=(long long)a[n-1]-a[0], ans=hi;
        auto countLE=[&](long long D)->long long{
            long long cnt=0;
            int j=0;
            for(int i=0;i<n;i++){
                if(j<i) j=i;
                while(j+1<n && (long long)a[j+1]-a[i]<=D) j++;
                cnt += j-i;
            }
            return cnt;
        };
        while(lo<=hi){
            long long mid=(lo+hi)/2;
            if(countLE(mid)>=target){ ans=mid; hi=mid-1; }
            else lo=mid+1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
