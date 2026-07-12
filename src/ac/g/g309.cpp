#include <iostream>

using namespace std;

int L[15], R[15];
long long ans[15];
int N;
long long K;

void dfs(int u, long long val) {
    if (u == -1) return;
    int cnt = 0;
    if (L[u] != -1) cnt++;
    if (R[u] != -1) cnt++;
    long long parts = 1 + cnt;
    long long share = val / parts;
    long long rem = val % parts;
    ans[u] = share + rem;
    if (L[u] != -1) dfs(L[u], share);
    if (R[u] != -1) dfs(R[u], share);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N >> K) {
        for (int i = 0; i < N; i++) {
            int a;
            cin >> a >> L[a] >> R[a];
        }
        dfs(0, K);
        for (int i = 0; i < N; i++) {
            cout << ans[i];
            if (i < N - 1) cout << " ";
        }
        cout << "\n";
    }
    return 0;
}
