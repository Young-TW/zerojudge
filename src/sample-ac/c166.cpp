#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  const int MOD = 10007;
  int n, m;
  bool first = true;
  while (cin >> n >> m) {
    vector<long long> num(n+1), col(n+1);
    for (int i = 1; i <= n; i++) cin >> num[i];
    for (int i = 1; i <= n; i++) cin >> col[i];
    vector<vector<vector<pair<long long,long long>>>> g(m+1, vector<vector<pair<long long,long long>>>(2));
    for (int i = 1; i <= n; i++) {
      int c = (int)col[i];
      int par = i % 2;
      g[c][par].push_back({i % MOD, num[i] % MOD});
    }
    long long ans = 0;
    for (int c = 1; c <= m; c++) {
      for (int par = 0; par < 2; par++) {
        auto &vec = g[c][par];
        long long sum_pv = 0, sum_p = 0, sum_v = 0, cnt = 0;
        for (auto &pr : vec) {
          long long p = pr.first, val = pr.second;
          ans = (ans + sum_pv + val*sum_p + p*sum_v + cnt*p%MOD*val) % MOD;
          sum_pv = (sum_pv + p*val) % MOD;
          sum_p = (sum_p + p) % MOD;
          sum_v = (sum_v + val) % MOD;
          cnt = (cnt + 1) % MOD;
        }
      }
    }
    if (!first) cout << "\n";
    first = false;
    cout << ans << "\n";
  }
  return 0;
}
