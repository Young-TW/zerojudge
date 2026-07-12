#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point {
    int x, y;
};

Point candidates[10];
int cand_cap[5] = {0, 270, 180, 110, 70};
int cand_cost[5] = {0, 5000, 4200, 2900, 2200};

Point demands[20];
int demand_val[20];

int main() {
    candidates[0] = {1184, 463};
    candidates[1] = {1262, 593};
    candidates[2] = {1158, 418};
    candidates[3] = {957, 562};
    candidates[4] = {872, 343};
    candidates[5] = {725, 302};
    candidates[6] = {674, 448};
    candidates[7] = {864, 377};
    candidates[8] = {605, 315};
    candidates[9] = {920, 427};

    int dx[20] = {1268, 1222, 1345, 1151, 1265, 1207, 1167, 1166, 1142, 1045, 1087, 948, 831, 816, 927, 823, 816, 689, 760, 678};
    int dy[20] = {453, 427, 492, 429, 527, 589, 630, 582, 528, 503, 597, 605, 426, 350, 382, 493, 584, 444, 241, 271};
    int dv[20] = {33, 35, 22, 29, 28, 34, 37, 45, 37, 45, 50, 33, 29, 35, 43, 42, 23, 34, 31, 37};
    for (int i = 0; i < 20; ++i) {
        demands[i] = {dx[i], dy[i]};
        demand_val[i] = dv[i];
    }

    double n;
    while (cin >> n) {
        double best_total_cost = 1e18;
        int best_mask = -1;
        vector<int> best_levels(10, 0);
        int best_build_cost = 0;
        double best_move_cost = 0;

        for (int mask = 1; mask < (1 << 10); ++mask) {
            vector<int> req(10, 0);
            double move_cost = 0;
            bool valid = true;
            for (int i = 0; i < 20; ++i) {
                double min_dist_sq = 1e18;
                int best_j = -1;
                for (int j = 0; j < 10; ++j) {
                    if (mask & (1 << j)) {
                        double ddx = demands[i].x - candidates[j].x;
                        double ddy = demands[i].y - candidates[j].y;
                        double dsq = ddx * ddx + ddy * ddy;
                        if (dsq < min_dist_sq) {
                            min_dist_sq = dsq;
                            best_j = j;
                        }
                    }
                }
                if (best_j == -1) {
                    valid = false;
                    break;
                }
                req[best_j] += demand_val[i];
                move_cost += demand_val[i] * sqrt(min_dist_sq);
            }
            if (!valid) continue;

            int build_cost = 0;
            vector<int> levels(10, 0);
            for (int j = 0; j < 10; ++j) {
                if (mask & (1 << j)) {
                    if (req[j] == 0) {
                        continue;
                    }
                    if (req[j] > 270) {
                        valid = false;
                        break;
                    }
                    int min_l_cost = 1e9;
                    int best_l = -1;
                    for (int l = 1; l <= 4; ++l) {
                        if (cand_cap[l] >= req[j]) {
                            if (cand_cost[l] < min_l_cost) {
                                min_l_cost = cand_cost[l];
                                best_l = l;
                            }
                        }
                    }
                    if (best_l == -1) {
                        valid = false;
                        break;
                    }
                    levels[j] = best_l;
                    build_cost += cand_cost[best_l];
                }
            }
            if (!valid) continue;

            double total_move_cost = move_cost * 2.0 * n * 3650.0 / 10000.0;
            double total_cost = build_cost + total_move_cost;

            if (total_cost < best_total_cost - 1e-9) {
                best_total_cost = total_cost;
                best_mask = mask;
                best_levels = levels;
                best_build_cost = build_cost;
                best_move_cost = total_move_cost;
            }
        }

        bool first = true;
        for (int j = 0; j < 10; ++j) {
            if (best_mask & (1 << j)) {
                if (best_levels[j] > 0) {
                    if (!first) cout << ",";
                    cout << (char)('A' + j) << " " << best_levels[j];
                    first = false;
                }
            }
        }
        cout << "\n";

        cout << best_build_cost << ",";
        cout << fixed << setprecision(2) << best_move_cost << "," << best_total_cost << "\n";
    }
    return 0;
}
