#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        int V = n * m * k;
        vector<int> init(V);
        for (int i = 0; i < V; ++i) cin >> init[i];

        // build matrix
        vector<uint64_t> mat(V, 0);
        vector<int> rhs(V, 0);
        auto id = [&](int x, int y, int z) {
            return (x * m + y) * k + z;
        };
        const int dx[7] = {0, 1, -1, 0, 0, 0, 0};
        const int dy[7] = {0, 0, 0, 1, -1, 0, 0};
        const int dz[7] = {0, 0, 0, 0, 0, 1, -1};

        for (int x = 0; x < n; ++x)
            for (int y = 0; y < m; ++y)
                for (int z = 0; z < k; ++z) {
                    int row = id(x, y, z);
                    uint64_t mask = 0;
                    for (int dir = 0; dir < 7; ++dir) {
                        int nx = x + dx[dir];
                        int ny = y + dy[dir];
                        int nz = z + dz[dir];
                        if (0 <= nx && nx < n && 0 <= ny && ny < m && 0 <= nz && nz < k) {
                            int col = id(nx, ny, nz);
                            mask |= (1ULL << col);
                        }
                    }
                    mat[row] = mask;
                    rhs[row] = init[row] ^ 1;          // want final 1
                }

        // Gaussian elimination (reduced row echelon)
        vector<int> where(V, -1);
        int row = 0;
        for (int col = 0; col < V && row < V; ++col) {
            int sel = -1;
            for (int i = row; i < V; ++i) {
                if ((mat[i] >> col) & 1ULL) {
                    sel = i; break;
                }
            }
            if (sel == -1) continue;
            swap(mat[sel], mat[row]);
            swap(rhs[sel], rhs[row]);
            where[col] = row;

            for (int i = 0; i < V; ++i) if (i != row && ((mat[i] >> col) & 1ULL)) {
                mat[i] ^= mat[row];
                rhs[i] ^= rhs[row];
            }
            ++row;
        }

        bool impossible = false;
        for (int i = 0; i < V; ++i) {
            if (mat[i] == 0 && rhs[i]) {
                impossible = true;
                break;
            }
        }
        if (impossible) {
            cout << "BBQQ~\n";
            continue;
        }

        // particular solution
        uint64_t particular = 0;
        for (int col = 0; col < V; ++col) {
            if (where[col] != -1) {
                if (rhs[where[col]]) particular |= (1ULL << col);
            }
        }

        // basis of nullspace
        vector<uint64_t> basis;
        for (int freeCol = 0; freeCol < V; ++freeCol) {
            if (where[freeCol] != -1) continue;          // not free
            uint64_t vec = 0;
            vec |= (1ULL << freeCol);                    // the free variable itself
            for (int col = 0; col < V; ++col) {
                if (where[col] == -1) continue;
                if ((mat[where[col]] >> freeCol) & 1ULL)
                    vec |= (1ULL << col);
            }
            basis.push_back(vec);
        }

        int f = (int)basis.size();
        int answer = V + 1;   // larger than any possible answer

        if (f <= 20) {
            int total = 1 << f;
            for (int mask = 0; mask < total; ++mask) {
                uint64_t cur = particular;
                for (int i = 0; i < f; ++i)
                    if (mask & (1 << i)) cur ^= basis[i];
                int w = __builtin_popcountll(cur);
                if (w < answer) answer = w;
            }
        } else {
            // fallback (should never be needed with given limits)
            // simple BFS over subsets using Gray code to keep it fast enough
            uint64_t cur = particular;
            answer = __builtin_popcountll(cur);
            uint64_t prev = 0;
            int total = 1 << f;
            for (int i = 1; i < total; ++i) {
                uint64_t g = i ^ (i >> 1);          // Gray code
                uint64_t diff = g ^ prev;          // bits that changed
                // apply changes
                while (diff) {
                    int b = __builtin_ctzll(diff);
                    cur ^= basis[b];
                    diff &= diff - 1;
                }
                int w = __builtin_popcountll(cur);
                if (w < answer) answer = w;
                prev = g;
            }
        }

        cout << answer << '\n';
    }
    return 0;
}
