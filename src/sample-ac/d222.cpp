#include <iostream>
#include <string>

using namespace std;

int n;
string pattern;
string s;
int ans;

inline bool is_triple_free(int L) {
    for (int k = 1; 3 * k <= L; ++k) {
        bool match = true;
        for (int i = 0; i < k; ++i) {
            if (s[L - 3*k + i] != s[L - 2*k + i] || s[L - 2*k + i] != s[L - k + i]) {
                match = false;
                break;
            }
        }
        if (match) return false;
    }
    return true;
}

void dfs(int idx) {
    if (idx == n) {
        ans++;
        return;
    }
    if (pattern[idx] == '0' || pattern[idx] == '1') {
        s[idx] = pattern[idx];
        if (is_triple_free(idx + 1)) {
            dfs(idx + 1);
        }
    } else {
        s[idx] = '0';
        if (is_triple_free(idx + 1)) {
            dfs(idx + 1);
        }
        s[idx] = '1';
        if (is_triple_free(idx + 1)) {
            dfs(idx + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int case_num = 1;
    while (cin >> n && n) {
        cin >> pattern;
        s.resize(n);
        ans = 0;
        dfs(0);
        cout << "Case " << case_num << ": " << ans << "\n";
        case_num++;
    }
    return 0;
}
