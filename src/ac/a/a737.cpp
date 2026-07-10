#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main(){
    int t;
    if(scanf("%d", &t) != 1) return 0;
    while(t--){
        int r;
        scanf("%d", &r);
        static int s[505];
        for(int i=0;i<r;i++) scanf("%d", &s[i]);
        sort(s, s+r);
        int med = s[r/2];
        long long sum = 0;
        for(int i=0;i<r;i++) sum += (long long)abs(s[i]-med);
        printf("%lld\n", sum);
    }
    return 0;
}
