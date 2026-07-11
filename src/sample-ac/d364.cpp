#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int S, t;
vector<int> ans;

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void dfs(int idx, int rem, int last) {
    if (idx == t) {
        if (rem == 0) {
            for (int i = 0; i < t; ++i) {
                cout << ans[i] << (i == t - 1 ? "" : " ");
            }
            cout << "\n";
        }
        return;
    }
    
    int rem_cnt = t - idx;
    int start = last;
    int end = rem;
    
    if (rem_cnt == 1) {
        start = max(last, rem);
        end = rem;
    } else {
        end = rem / rem_cnt;
    }
    
    for (int cur = start; cur <= end; ++cur) {
        bool ok = true;
        for (int i = 0; i < idx; ++i) {
            if (gcd(ans[i], cur) != 1) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans.push_back(cur);
            dfs(idx + 1, rem - cur, cur);
            ans.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        for (int case_num = 1; case_num <= N; ++case_num) {
            cin >> S >> t;
            cout << "Case " << case_num << ":\n";
            ans.clear();
            dfs(0, S, 1);
        }
    }
    return 0;
}
