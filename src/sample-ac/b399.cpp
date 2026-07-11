#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    int caseNum = 0;
    while (cin >> T) {
        while (T--) {
            caseNum++;
            int N, D, K;
            cin >> N >> D >> K;
            vector<vector<int>> p(N, vector<int>(D));
            for (int i = 0; i < N; i++)
                for (int j = 0; j < D; j++)
                    cin >> p[i][j];
            
            // Generate all subsets of size K as bitmasks
            vector<int> subsets;
            for (int mask = 0; mask < (1 << D); mask++) {
                if (__builtin_popcount(mask) == K)
                    subsets.push_back(mask);
            }
            
            vector<bool> dominated(N, false);
            
            for (int j = 0; j < N; j++) {
                for (int i = 0; i < N; i++) {
                    if (i == j) continue;
                    // Compute ge_mask (>=) and gt_mask (>) as bitmasks
                    int ge_mask = 0, gt_mask = 0;
                    for (int d = 0; d < D; d++) {
                        if (p[i][d] >= p[j][d]) ge_mask |= (1 << d);
                        if (p[i][d] > p[j][d]) gt_mask |= (1 << d);
                    }
                    // Check if any subset S' of size K satisfies:
                    //   S' subset of ge_mask  (all dims in S' have p_i >= p_j)
                    //   S' intersects gt_mask (at least one dim in S' has p_i > p_j)
                    bool found = false;
                    for (int s : subsets) {
                        if ((s & ~ge_mask) == 0 && (s & gt_mask) != 0) {
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        dominated[j] = true;
                        break;
                    }
                }
            }
            
            cout << "Case #" << caseNum << ":";
            bool any = false;
            for (int i = 0; i < N; i++) {
                if (!dominated[i]) {
                    cout << " " << (i + 1);
                    any = true;
                }
            }
            if (!any) cout << " NONE";
            cout << "\n";
        }
    }
    return 0;
}
