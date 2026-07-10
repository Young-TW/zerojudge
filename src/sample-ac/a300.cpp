#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, p;
    while (cin >> n >> k >> p) {
        vector<int> color(n+1), cost(n+1);
        for (int i = 1; i <= n; i++){
            cin >> color[i] >> cost[i];
        }
        vector<long long> cnt(k, 0);
        long long ans = 0;
        int low = 0;
        for (int j = 1; j <= n; j++){
            if (cost[j] <= p){
                for (int t = low+1; t <= j; t++){
                    cnt[color[t]]++;
                }
                low = j;
                ans += cnt[color[j]] - 1;
            } else {
                ans += cnt[color[j]];
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
