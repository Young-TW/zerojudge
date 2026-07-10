#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MOD = 1000007;

int main(){
    int n, m;
    while(scanf("%d %d", &n, &m) == 2){
        static int a[105];
        for(int i=0;i<n;i++){
            if(scanf("%d", &a[i]) != 1) a[i] = 0;
        }
        static int dp[105];
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for(int i=0;i<n;i++){
            static int ndp[105];
            memset(ndp, 0, sizeof(ndp));
            for(int j=0;j<=m;j++){
                if(dp[j]==0) continue;
                int lim = a[i];
                if(lim > m - j) lim = m - j;
                for(int k=0;k<=lim;k++){
                    ndp[j+k] += dp[j];
                    if(ndp[j+k] >= MOD) ndp[j+k] -= MOD;
                }
            }
            memcpy(dp, ndp, sizeof(dp));
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}
