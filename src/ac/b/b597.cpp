#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int n;
int sticks[55];
bool used[55];
int L;

bool dfs(int rest_sticks, int rest_len, int start_idx) {
    if (rest_sticks == 0) return true;
    if (rest_len == 0) {
        return dfs(rest_sticks - 1, L, 0);
    }
    for (int i = start_idx; i < n; ++i) {
        if (used[i] || sticks[i] > rest_len) continue;
        used[i] = true;
        if (dfs(rest_sticks, rest_len - sticks[i], i + 1)) return true;
        used[i] = false;
        
        if (rest_len == L || sticks[i] == rest_len) return false;
        while (i + 1 < n && sticks[i + 1] == sticks[i]) ++i;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n && n) {
        for (int i = 0; i < n; ++i) {
            cin >> sticks[i];
        }
        sort(sticks, sticks + n, [](int a, int b) { return a > b; });
        int sum = accumulate(sticks, sticks + n, 0);
        int max_len = sticks[0];
        
        for (L = max_len; L <= sum; ++L) {
            if (sum % L != 0) continue;
            fill(used, used + n, false);
            if (dfs(sum / L, L, 0)) {
                cout << L << "\n";
                break;
            }
        }
    }
    return 0;
}
