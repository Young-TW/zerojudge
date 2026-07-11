#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<long long>> d(n, vector<long long>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> d[i][j];
            }
        }

        // Precompute vertical minimums for each column segment starting at row i with height h
        // min_v[i][h][j] = min(d[i][j], d[i+1][j], ..., d[i+h-1][j])
        // To save memory and time, we will compute row by row or use a different approach.
        // Given constraints N, M <= 1500, O(N*M*min(N,M)) is too slow (1500^3 ~ 3.3e9).
        // We need an O(N*M) or O(N*M*log(min(N,M))) solution.
        
        // Approach: Binary Search on the answer K.
        // If we can perform K cuts, then there exists a rectangle of size h x w (h, w >= 2)
        // such that every cell in it has value >= K.
        // Actually, the problem says "four trees form a rectangle". It implies we need a rectangle of ANY size >= 2x2?
        // Re-reading: "四棵樹會形成一個長方形". This usually means the four corners of a rectangle.
        // But the skill is "水平方陣斬" (Horizontal Square/Rectangle Slash), and "每施放一次劍技這四棵樹就會減少 1 單位的天命".
        // This implies one cut consumes 1 from the 4 corner trees? Or all trees in the rectangle?
        // "桐人把森林裡的樹幾乎砍光只剩下四棵樹，其中這四棵樹會形成一個長方形"
        // Context: He cuts down everything leaving 4 trees forming a rectangle.
        // Then "每施放一次劍技這四棵樹就會減少 1 單位的天命".
        // This strongly suggests that ONE practice session uses exactly 4 trees (the corners of a rectangle).
        // However, if we have a grid of trees, and we want to maximize practices, do we pick disjoint sets of 4 trees?
        // Or does the "rectangle" imply the area inside?
        // Let's look at the sample.
        // 3 3
        // 2 3 4
        // 4 5 1
        // 2 3 7
        // Output: 3.
        // If we pick rectangle (0,0), (0,2), (2,0), (2,2) -> values 2, 4, 2, 7. Min is 2. So 2 cuts?
        // If we pick (0,1), (0,2), (1,1), (1,2) -> 3, 4, 5, 1. Min 1.
        // If the operation reduces ALL trees in the rectangular area, then for a rectangle of size HxW, 
        // we need min(cell) >= K for all cells in that rectangle.
        // But the text says "這四棵樹" (these four trees). This is specific.
        // If it's just 4 corners, then for a fixed K, we need to find if there exists a rectangle where 4 corners >= K.
        // And we can reuse trees? "天命一旦耗盡，這棵樹就會消失". So if a tree is used in multiple rectangles, its value decreases.
        // This becomes a matching/packing problem which is NP-hard generally if arbitrary rectangles are allowed.
        // BUT, competitive programming problems with N=1500 usually have a greedy or flow solution, or the interpretation is simpler.
        
        // Alternative Interpretation:
        // Maybe "水平方陣斬" requires a solid square/rectangle of trees, and the "four trees" description is just flavor text describing the setup for ONE practice?
        // No, "每施放一次...這四棵樹就會減少".
        // Let's reconsider the standard interpretation of similar problems.
        // Often, "rectangle of trees" implies the subgrid. If the skill cuts a rectangular area, then all trees in that area lose 1 HP.
        // If the problem meant only corners, it would be very strange to ask for "maximum times" without specifying if rectangles can overlap arbitrarily.
        // If overlaps are allowed and only corners matter, we could potentially use the same tree as a corner for many rectangles until it dies.
        // However, the sample output 3 for the given grid:
        // Grid:
        // 2 3 4
        // 4 5 1
        // 2 3 7
        // If we assume the operation requires a full rectangular subgrid (all cells inside) to be present and they all decrease by 1:
        // Can we find a sequence of rectangles such that sum of counts is maximized?
        // Actually, if we can choose ANY rectangle (>=2x2) and decrement all cells, the maximum number of operations is determined by the bottleneck.
        // Wait, if we can pick DIFFERENT rectangles each time, this is complex.
        // BUT, notice the constraint: "四棵樹會形成一個長方形". This might mean the training setup IS just 4 trees.
        // But the input is NxM.
        // Hypothesis 1: We need to select a SINGLE rectangle (defined by 4 corners) and perform the cut K times on THAT SAME rectangle until one of the 4 corners dies. The answer is max over all possible rectangles of min(corners).
        // Let's test Sample with Hypothesis 1.
        // Rect (0,0) to (2,2): corners 2, 4, 2, 7 -> min 2.
        // Rect (0,0) to (1,2): corners 2, 4, 4, 1 -> min 1.
        // Rect (0,1) to (2,2): corners 3, 4, 3, 7 -> min 3. (Rows 0-2, Cols 1-2). Corners: (0,1)=3, (0,2)=4, (2,1)=3, (2,2)=7. Min is 3.
        // Rect (0,0) to (2,1): corners 2, 3, 2, 3 -> min 2.
        // Rect (0,1) to (1,2): corners 3, 4, 5, 1 -> min 1.
        // Max is 3. Matches sample output!
        
        // So the problem is: Find a sub-rectangle (defined by r1, c1, r2, c2 with r1<r2, c1<c2) such that min(D[r1][c1], D[r1][c2], D[r2][c1], D[r2][c2]) is maximized.
        // We need to find max_{r1<r2, c1<c2} ( min( D[r1][c1], D[r1][c2], D[r2][c1], D[r2][c2] ) ).
        
        // Algorithm:
        // Binary search on the answer X.
        // Check if there exists a rectangle with all 4 corners >= X.
        // Create a boolean matrix B where B[i][j] = (D[i][j] >= X).
        // We need to find two rows r1, r2 and two columns c1, c2 such that B[r1][c1], B[r1][c2], B[r2][c1], B[r2][c2] are all true.
        // This is equivalent to: Are there two rows that have 1s in at least two common columns?
        // For each pair of rows, we can check intersection of their 1-columns. But O(N^2 * M) is too slow (1500^3).
        // Optimization:
        // Iterate through rows. For each row, store the list of columns where B[i][j] is true.
        // We want to find if any pair of columns (c1, c2) appears together in at least two different rows.
        // We can use a 2D array or hash map to store the last row index where a pair of columns (c1, c2) was seen.
        // Since M <= 1500, M^2 is 2.25e6. We can allocate an array `last_seen[M][M]` initialized to -1.
        // Iterate r from 0 to n-1:
        //   Let cols be the list of indices j where B[r][j] is true.
        //   For each pair (c1, c2) in cols (with c1 < c2):
        //     If last_seen[c1][c2] != -1, then we found a rectangle (return true).
        //     Else, set last_seen[c1][c2] = r.
        // Complexity: O(M^2) per check in worst case (if a row is all 1s). Total O(M^2 * log(MaxVal)).
        // With N, M = 1500, M^2 = 2.25e6. Log(1e9) ~ 30. Total ops ~ 6.7e7. Feasible within 1-2 seconds.
        // Memory: M*M integers = 1500*1500*4 bytes ~ 9MB. OK.

        long long low = 0, high = 1000000000LL;
        long long ans = 0;

        // Temporary storage for column pairs
        // Using a flat vector or 2D array. 2D array is faster.
        // We need to reset it every check. memset is fast enough for 9MB? 30 * 9MB = 270MB bandwidth. Very fast.
        
        vector<int> cols;
        cols.reserve(m);
        
        // Allocate last_seen once outside to avoid reallocation
        // Use vector<vector<int>> or raw pointer? Vector of vectors has overhead.
        // Flat vector with indexing [c1 * m + c2]
        vector<int> last_seen(m * m, -1);

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (mid == 0) {
                // If mid is 0, since D_ij >= 0, and we need 4 trees, if there are any 4 trees forming a rect, it's valid.
                // But if min is 0, the tree disappears immediately? "天命一旦耗盡，這棵樹就會消失".
                // If a tree has 0天命, it's already gone? Or does it disappear after 1 cut?
                // "每施放一次...減少 1...天命一旦耗盡...消失".
                // If D=0, can we use it? If we use it, it becomes -1? No, it disappears when exhausted.
                // Usually means if D=0, it's already gone or can't be used for even 1 cut.
                // If D=1, we can cut 1 time, then it becomes 0 and disappears.
                // So we need D >= mid. If mid=0, technically any existing tree works? But the question asks "max times".
                // If max times is 0, output 0.
                // If there is a valid rectangle with min >= 1, then ans >= 1.
                // If the best we can do is min=0, then we can cut 0 times.
                // So we can start low = 1. If no solution for 1, ans=0.
                low = 1;
                continue;
            }

            // Reset last_seen
            fill(last_seen.begin(), last_seen.end(), -1);

            bool found = false;
            for (int i = 0; i < n; ++i) {
                cols.clear();
                for (int j = 0; j < m; ++j) {
                    if (d[i][j] >= mid) {
                        cols.push_back(j);
                    }
                }

                if (cols.size() < 2) continue;

                for (size_t a = 0; a < cols.size(); ++a) {
                    for (size_t b = a + 1; b < cols.size(); ++b) {
                        int c1 = cols[a];
                        int c2 = cols[b];
                        int idx = c1 * m + c2;
                        if (last_seen[idx] != -1) {
                            found = true;
                            break;
                        }
                        last_seen[idx] = i;
                    }
                    if (found) break;
                }
                if (found) break;
            }

            if (found) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
