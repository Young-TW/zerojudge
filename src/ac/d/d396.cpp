#include <iostream>
#include <cstring>

using namespace std;

int n;
int ans[20];
bool used[20];
bool is_prime[35];

void dfs(int idx) {
    if (idx == n) {
        if (is_prime[ans[n] + ans[1]]) {
            for (int i = 1; i <= n; ++i) {
                cout << ans[i];
                if (i < n) cout << " ";
            }
            cout << "\n";
        }
        return;
    }
    for (int i = 2; i <= n; ++i) {
        if (!used[i] && is_prime[ans[idx] + i]) {
            used[i] = true;
            ans[idx + 1] = i;
            dfs(idx + 1);
            used[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(is_prime, false, sizeof(is_prime));
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    for (int p : primes) {
        is_prime[p] = true;
    }
    
    int case_num = 1;
    while (cin >> n) {
        if (case_num > 1) cout << "\n";
        cout << "Case " << case_num << ":\n";
        ans[1] = 1;
        memset(used, false, sizeof(used));
        used[1] = true;
        dfs(1);
        case_num++;
    }
    
    return 0;
}
