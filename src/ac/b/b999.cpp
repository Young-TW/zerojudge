#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    bool first = true;
    while(cin >> T){
        if(!first) cout << "\n";
        first = false;
        while(T--){
            int n, m;
            cin >> n >> m;
            vector<double> x(n), y(n);
            for(int i=0;i<n;i++) cin >> x[i] >> y[i];
            const double eps = 1e-6;
            vector<vector<int>> cv(n, vector<int>(n, 0));
            for(int i=0;i<n;i++){
                cv[i][i] = (1<<i);
                for(int j=i+1;j<n;j++){
                    double x1=x[i], y1=y[i], x2=x[j], y2=y[j];
                    double denom = x1*x1*x2 - x2*x2*x1;
                    if(fabs(denom) < eps) continue;
                    double a = (y1*x2 - y2*x1) / denom;
                    if(a >= -eps) continue;
                    double b = (y1 - a*x1*x1)/x1;
                    int mask = 0;
                    for(int k=0;k<n;k++){
                        double pred = a*x[k]*x[k] + b*x[k];
                        if(fabs(pred - y[k]) < eps) mask |= (1<<k);
                    }
                    cv[i][j] = mask;
                    cv[j][i] = mask;
                }
            }
            vector<int> dp(1<<n, INT_MAX);
            dp[0] = 0;
            for(int mask=1; mask < (1<<n); mask++){
                int i = __builtin_ctz(mask);
                for(int j=0;j<n;j++){
                    int c = cv[i][j];
                    if(c == 0) continue;
                    int sub = mask & ~c;
                    if(dp[sub] != INT_MAX) dp[mask] = min(dp[mask], dp[sub]+1);
                }
            }
            cout << dp[(1<<n)-1] << "\n";
        }
    }
    return 0;
}
