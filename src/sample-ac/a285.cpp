#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(){
    int n;
    while(cin >> n){
        int m = 2*n;
        vector<vector<int>> a(m, vector<int>(m));
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
                cin >> a[i][j];
        int full = 1<<m;
        const long long NEG = LLONG_MIN/4;
        vector<long long> dp(full, NEG);
        dp[0]=0;
        for(int mask=1; mask<full; mask++){
            if(__builtin_popcount(mask) & 1) continue; // odd, skip
            int i = __builtin_ctz(mask); // lowest set bit
            long long best = NEG;
            for(int j=i+1; j<m; j++){
                if(mask & (1<<j)){
                    int prev = mask ^ (1<<i) ^ (1<<j);
                    if(dp[prev] > NEG){
                        long long val = dp[prev] + (long long)a[i][j]*10;
                        if(val>best) best=val;
                    }
                }
            }
            dp[mask]=best;
        }
        cout << dp[full-1] << "\n";
    }
    return 0;
}
