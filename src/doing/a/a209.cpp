#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <climits>

using namespace std;

const int MAX_K = 400;
using BS = bitset<MAX_K>;

struct Solver {
    int K;                              // number of 1-cells
    vector<BS> squares;                 // maximal squares (each as a bitset)
    vector<vector<int>> elem_squares;   // for each element, list of square indices covering it
    BS universe;                        // bitset with first K bits set
    int best;                           // current best answer

    // Lower bound: greedy maximal independent set in the conflict graph
    int packing_lower_bound(const BS& covered) {
        BS uncovered = universe & ~covered;
        int count = 0;
        while (uncovered.any()) {
            int e = -1;
            for (int i = 0; i < K; ++i) {
                if (uncovered[i]) { e = i; break; }
            }
            if (e == -1) break;
            ++count;
            for (int sq_idx : elem_squares[e]) {
                uncovered &= ~squares[sq_idx];
            }
        }
        return count;
    }

    void dfs(BS covered, int count) {
        if (covered == universe) {
            best = min(best, count);
            return;
        }
        if (count >= best) return;

        int lb = packing_lower_bound(covered);
        if (count + lb >= best) return;

        // Choose uncovered element with fewest covering squares (that add new coverage)
        int chosen = -1;
        int min_options = INT_MAX;
        vector<int> chosen_candidates;

        for (int e = 0; e < K; ++e) {
            if (covered[e]) continue;
            vector<int> cands;
            for (int sq_idx : elem_squares[e]) {
                BS new_cov = squares[sq_idx] & ~covered;
                if (new_cov.any()) cands.push_back(sq_idx);
            }
            if (cands.empty()) return; // should not happen for valid instances
            if ((int)cands.size() < min_options) {
                min_options = cands.size();
                chosen = e;
                chosen_candidates = cands;
                if (min_options == 1) break; // forced move
            }
        }
        if (chosen == -1) return;

        // Filter dominated squares (by new coverage)
        vector<BS> cand_new;
        for (int sq_idx : chosen_candidates) {
            cand_new.push_back(squares[sq_idx] & ~covered);
        }
        vector<int> filtered;
        for (int i = 0; i < (int)chosen_candidates.size(); ++i) {
            bool dominated = false;
            for (int j = 0; j < (int)chosen_candidates.size(); ++j) {
                if (i == j) continue;
                if ((cand_new[j] & cand_new[i]) == cand_new[i]) {
                    dominated = true;
                    break;
                }
            }
            if (!dominated) filtered.push_back(chosen_candidates[i]);
        }

        // Sort by number of newly covered elements (descending)
        sort(filtered.begin(), filtered.end(),
             [&](int a, int b) {
                 return (squares[a] & ~covered).count() > (squares[b] & ~covered).count();
             });

        for (int sq_idx : filtered) {
            BS new_covered = covered | squares[sq_idx];
            dfs(new_covered, count + 1);
            if (count + 1 >= best) break; // further branches cannot improve
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;

        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> grid[i][j];

        // Map each 1-cell to an index
        vector<vector<int>> idx(n, vector<int>(m, -1));
        int K = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (grid[i][j] == 1) idx[i][j] = K++;

        if (K == 0) {
            cout << 0 << '\n';
            continue;
        }

        // DP for largest all-1 square with top-left at (i,j)
        vector<vector<int>> maxSize(n, vector<int>(m, 0));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                if (grid[i][j] == 1) {
                    int down  = (i + 1 < n) ? maxSize[i + 1][j] : 0;
                    int right = (j + 1 < m) ? maxSize[i][j + 1] : 0;
                    int diag  = (i + 1 < n && j + 1 < m) ? maxSize[i + 1][j + 1] : 0;
                    maxSize[i][j] = 1 + min({down, right, diag});
                }
            }
        }

        // Generate candidate squares (largest for each top-left)
        struct Cand { int r, c, k; BS bits; };
        vector<Cand> candidates;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (maxSize[i][j] > 0) {
                    Cand sq;
                    sq.r = i; sq.c = j; sq.k = maxSize[i][j];
                    sq.bits.reset();
                    for (int di = 0; di < sq.k; ++di)
                        for (int dj = 0; dj < sq.k; ++dj) {
                            int ni = i + di, nj = j + dj;
                            if (idx[ni][nj] != -1) sq.bits.set(idx[ni][nj]);
                        }
                    candidates.push_back(sq);
                }
            }
        }

        // Keep only maximal squares (not contained in any other candidate)
        vector<BS> maximal_bits;
        for (size_t i = 0; i < candidates.size(); ++i) {
            bool contained = false;
            for (size_t j = 0; j < candidates.size(); ++j) {
                if (i == j) continue;
                if (candidates[j].r <= candidates[i].r &&
                    candidates[j].c <= candidates[i].c &&
                    candidates[j].r + candidates[j].k >= candidates[i].r + candidates[i].k &&
                    candidates[j].c + candidates[j].k >= candidates[i].c + candidates[i].k) {
                    contained = true;
                    break;
                }
            }
            if (!contained) maximal_bits.push_back(candidates[i].bits);
        }

        // Remove duplicate squares
        vector<BS> squares;
        for (const BS& b : maximal_bits) {
            bool dup = false;
            for (const BS& ex : squares) if (ex == b) { dup = true; break; }
            if (!dup) squares.push_back(b);
        }

        // Build element -> squares mapping
        vector<vector<int>> elem_squares(K);
        for (int i = 0; i < (int)squares.size(); ++i) {
            for (int e = 0; e < K; ++e)
                if (squares[i][e]) elem_squares[e].push_back(i);
        }

        // Universe bitset
        BS universe;
        for (int i = 0; i < K; ++i) universe.set(i);

        // Greedy upper bound
        BS covered;
        int greedy_count = 0;
        while (covered != universe) {
            int best_sq = -1, best_new = 0;
            for (int i = 0; i < (int)squares.size(); ++i) {
                int cnt = (squares[i] & ~covered).count();
                if (cnt > best_new) { best_new = cnt; best_sq = i; }
            }
            if (best_sq == -1) break;
            covered |= squares[best_sq];
            ++greedy_count;
        }

        Solver solver;
        solver.K = K;
        solver.squares = squares;
        solver.elem_squares = elem_squares;
        solver.universe = universe;
        solver.best = greedy_count;

        solver.dfs(BS(), 0);
        cout << solver.best << '\n';
    }
    return 0;
}
