#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n;
    while(scanf("%d", &n) == 1){
        vector<long long> w(n);
        for(int i = 0; i < n; i++) scanf("%lld", &w[i]);
        vector<long long> dp0(n, 0), dp1(n);
        for(int i = 0; i < n; i++) dp1[i] = w[i];
        vector<int> par(n, -1);
        for(int i = 1; i < n; i++){
            int p;
            scanf("%d", &p);
            par[i] = p;
        }
        for(int v = n - 1; v >= 1; v--){
            int p = par[v];
            long long m = (dp0[v] > dp1[v]) ? dp0[v] : dp1[v];
            dp0[p] += m;
            dp1[p] += dp0[v];
        }
        long long ans = (dp0[0] > dp1[0]) ? dp0[0] : dp1[0];
        printf("%lld\n", ans);
    }
    return 0;
}
