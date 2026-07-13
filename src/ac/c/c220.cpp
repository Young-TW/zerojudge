#include <iostream>
#include <cstring>

using namespace std;

int n, L;
int cnt;
char ans[85];
int ans_len;
bool found;

bool is_hard(char* s, int len) {
    for (int i = 1; i <= len / 2; ++i) {
        if (memcmp(s + len - 2 * i, s + len - i, i) == 0) {
            return false;
        }
    }
    return true;
}

void dfs(char* s, int len) {
    if (found) return;
    if (len > 0) {
        cnt++;
        if (cnt == n) {
            memcpy(ans, s, len);
            ans_len = len;
            found = true;
            return;
        }
    }
    for (int i = 0; i < L; ++i) {
        s[len] = 'A' + i;
        if (is_hard(s, len + 1)) {
            dfs(s, len + 1);
            if (found) return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n >> L && (n || L)) {
        cnt = 0;
        found = false;
        char s[85];
        dfs(s, 0);
        
        for (int i = 0; i < ans_len; ++i) {
            cout << ans[i];
            if ((i + 1) % 4 == 0) {
                if (i + 1 != ans_len) {
                    if (((i + 1) / 4) % 16 == 0) {
                        cout << "\n";
                    } else {
                        cout << " ";
                    }
                }
            }
        }
        cout << "\n" << ans_len << "\n";
    }
    return 0;
}
