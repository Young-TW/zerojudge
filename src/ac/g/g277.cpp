#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 300005;
const int K = 20;
int st[K][MAXN];

inline int get_log(int x) {
    return 31 - __builtin_clz(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> a(n + 1);
        vector<long long> pref(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            pref[i] = pref[i - 1] + a[i];
        }
        
        if (n == 1) {
            cout << a[1] << "\n";
            continue;
        }
        
        for (int i = 1; i <= n; ++i) {
            st[0][i] = i;
        }
        
        for (int k = 1; k < K; ++k) {
            for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
                int left = st[k - 1][i];
                int right = st[k - 1][i + (1 << (k - 1))];
                st[k][i] = (a[left] < a[right]) ? left : right;
            }
        }
        
        auto query_min = [&](int L, int R) {
            int k = get_log(R - L + 1);
            int left = st[k][L];
            int right = st[k][R - (1 << k) + 1];
            return (a[left] < a[right]) ? left : right;
        };
        
        int L = 1, R = n;
        while (L < R) {
            int m = query_min(L, R);
            long long sumL = (m > L) ? (pref[m - 1] - pref[L - 1]) : 0;
            long long sumR = (m < R) ? (pref[R] - pref[m]) : 0;
            if (sumL > sumR) {
                R = m - 1;
            } else {
                L = m + 1;
            }
        }
        
        cout << a[L] << "\n";
    }
    
    return 0;
}
