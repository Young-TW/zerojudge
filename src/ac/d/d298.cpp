#include <iostream>
#include <cstring>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Which children (0-indexed) each command 1..9 affects
    static const int cmd_children[9][5] = {
        {0, 1, 3, 4, -1},   // 1
        {0, 1, 2, -1, -1},  // 2
        {1, 2, 4, 5, -1},   // 3
        {0, 3, 6, -1, -1},  // 4
        {1, 3, 4, 5, 7},    // 5
        {2, 5, 8, -1, -1},  // 6
        {3, 4, 6, 7, -1},   // 7
        {6, 7, 8, -1, -1},  // 8
        {4, 5, 7, 8, -1}    // 9
    };
    static const int cmd_size[9] = {4, 3, 4, 3, 5, 3, 4, 3, 4};
    
    const int N = 262144; // 4^9
    static int best_c[N];
    static int best_sum[N];
    static bool has_sol[N];
    memset(has_sol, 0, sizeof(has_sol));
    memset(best_c, 0, sizeof(best_c));
    memset(best_sum, 0, sizeof(best_sum));
    
    // Precompute: for every count vector c (each command used 0..3 times),
    // compute the resulting b vector (how much each child rotates mod 4).
    // For each b, keep the best c: minimize total sum, then maximize c[0],
    // c[1], ... (which gives lexicographically smallest sorted sequence).
    for (int c_enc = 0; c_enc < N; ++c_enc) {
        int c[9];
        int x = c_enc;
        int sum = 0;
        for (int i = 0; i < 9; ++i) {
            c[i] = x & 3;
            x >>= 2;
            sum += c[i];
        }
        int b[9] = {0,0,0,0,0,0,0,0,0};
        for (int j = 0; j < 9; ++j) {
            int cj = c[j];
            if (cj == 0) continue;
            for (int k = 0; k < cmd_size[j]; ++k) {
                b[cmd_children[j][k]] += cj;
            }
        }
        int b_enc = 0;
        for (int i = 0; i < 9; ++i) {
            b_enc += (b[i] & 3) << (2 * i);
        }
        
        if (!has_sol[b_enc]) {
            has_sol[b_enc] = true;
            best_c[b_enc] = c_enc;
            best_sum[b_enc] = sum;
        } else {
            if (sum < best_sum[b_enc]) {
                best_c[b_enc] = c_enc;
                best_sum[b_enc] = sum;
            } else if (sum == best_sum[b_enc]) {
                int cur = best_c[b_enc];
                bool better = false;
                for (int i = 0; i < 9; ++i) {
                    int ci = (c_enc >> (2 * i)) & 3;
                    int curi = (cur >> (2 * i)) & 3;
                    if (ci > curi) { better = true; break; }
                    if (ci < curi) { break; }
                }
                if (better) {
                    best_c[b_enc] = c_enc;
                }
            }
        }
    }
    
    int T;
    while (cin >> T) {
        while (T--) {
            int b_enc = 0;
            for (int i = 0; i < 9; ++i) {
                int init;
                cin >> init;
                int bi = (4 - init) & 3;
                b_enc += bi << (2 * i);
            }
            int c_enc = best_c[b_enc];
            bool first = true;
            for (int i = 0; i < 9; ++i) {
                int ci = (c_enc >> (2 * i)) & 3;
                for (int k = 0; k < ci; ++k) {
                    if (!first) cout << " ";
                    cout << (i + 1);
                    first = false;
                }
            }
            cout << "\n";
        }
    }
    return 0;
}
