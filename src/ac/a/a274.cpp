#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int N;
long long A[12];
bool used[12];
long long seq[12];
bool found;

void dfs(int pos) {
    if (found) return;
    if (pos == N) { found = true; return; }
    for (int i = 0; i < N; i++) {
        if (used[i]) continue;
        if (i > 0 && A[i] == A[i-1] && !used[i-1]) continue; // dedup
        if (pos >= 2) {
            long long sum = seq[pos-2] + seq[pos-1];
            long long prod = seq[pos-2] * seq[pos-1];
            if (sum % A[i] != 0 && prod % A[i] != 0) continue;
        }
        used[i] = true;
        seq[pos] = A[i];
        dfs(pos+1);
        if (found) return;
        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N) {
        for (int i = 0; i < N; i++) cin >> A[i];
        sort(A, A+N);
        memset(used, 0, sizeof(used));
        found = false;
        dfs(0);
        if (!found) {
            cout << "No\n";
        } else {
            for (int i = 0; i < N; i++) cout << seq[i] << ' ';
            cout << '\n';
        }
    }
    return 0;
}
