#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    bool firstCase = true;
    while (cin >> n >> m) {
        if (!firstCase) cout << '\n';
        firstCase = false;
        
        vector<int> x(m + 1);
        vector<int> cnt(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            cin >> x[i];
            ++cnt[x[i]];
        }
        
        vector<long long> count_A(n + 1, 0), count_B(n + 1, 0),
                          count_C(n + 1, 0), count_D(n + 1, 0);
        
        int v_max = (n - 2) / 9;
        if (v_max >= 1) {
            vector<long long> P(n + 1), preP(n + 1), Q(n + 1), preQ(n + 1);
            for (int v = 1; v <= v_max; ++v) {
                int max_c = n - v;
                preP[0] = 0;
                for (int c = 1; c <= max_c; ++c) {
                    P[c] = (long long)cnt[c] * cnt[c + v];
                    preP[c] = preP[c - 1] + P[c];
                }
                
                int max_a = n - 2 * v;
                preQ[0] = 0;
                for (int a = 1; a <= max_a; ++a) {
                    Q[a] = (long long)cnt[a] * cnt[a + 2 * v];
                    preQ[a] = preQ[a - 1] + Q[a];
                }
                
                // Roles A and B
                int a_max = n - 9 * v - 1;
                for (int a = 1; a <= a_max; ++a) {
                    int b = a + 2 * v;
                    int L = a + 8 * v + 1;
                    int R = n - v;
                    long long sum_c = preP[R] - preP[L - 1];
                    if (sum_c != 0) {
                        count_A[a] += (long long)cnt[b] * sum_c;
                        count_B[b] += (long long)cnt[a] * sum_c;
                    }
                }
                
                // Roles C and D
                int c_min = 8 * v + 2;
                int c_max = n - v;
                for (int c = c_min; c <= c_max; ++c) {
                    int d = c + v;
                    int R = c - 8 * v - 1;
                    long long sum_a = preQ[R];
                    if (sum_a != 0) {
                        count_C[c] += (long long)cnt[d] * sum_a;
                        count_D[d] += (long long)cnt[c] * sum_a;
                    }
                }
            }
        }
        
        for (int i = 1; i <= m; ++i) {
            int val = x[i];
            cout << count_A[val] << ' ' << count_B[val] << ' '
                 << count_C[val] << ' ' << count_D[val] << '\n';
        }
    }
    return 0;
}
