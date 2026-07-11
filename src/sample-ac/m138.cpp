#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 2005;
const int OFFSET = 1000000000; // To handle negative coordinates if needed for array indexing, though we will use coordinate compression or direct sorting.
// Actually, coordinates are up to 1e9, so we cannot use them as array indices directly.
// We will rely on sorting and two pointers / sliding window on sorted arrays.

struct Point {
    int x, y;
    int id;
};

int N;
long long K;
Point points[MAXN];
bool covered[MAXN];

// Function to solve the 1D coverage problem for a set of points with a fixed interval length K
// Returns the maximum number of points that can be covered by one interval of length K
// Points must be sorted by the coordinate we are checking (x or y)
int max_cover_1d(vector<int>& coords) {
    if (coords.empty()) return 0;
    int n = coords.size();
    int max_pts = 0;
    int left = 0;
    for (int right = 0; right < n; ++right) {
        while ((long long)coords[right] - (long long)coords[left] > K) {
            left++;
        }
        max_pts = max(max_pts, right - left + 1);
    }
    return max_pts;
}

// Global variables to store intermediate results for splitting strategies
int best_split_x = 0;
int best_split_y = 0;

// Strategy 1: Split by X coordinate
// Sort points by x. Iterate a split index i such that square 1 covers points [0..i] and square 2 covers [i+1..N-1]
// For each group, we need to find the max points coverable by a KxK square.
// Since the group is restricted in X range by the split, we actually just need to check Y coverage for valid X windows?
// No, the standard approach for "two disjoint squares" is:
// 1. Sort by X. Try every possible vertical line x = L that separates the two squares.
//    Left square must have right edge < L, Right square must have left edge >= L.
//    Actually, simpler: The two squares are disjoint. There exists a line (vertical or horizontal) separating them.
//    We iterate over all possible separating lines derived from the point coordinates.
//    Specifically, sort points by X. For each i from 0 to N-2, consider the gap between point[i].x and point[i+1].x.
//    If point[i+1].x - point[i].x > K, then we can definitely separate them? Not necessarily optimal.
//    Correct approach:
//    Iterate i from 0 to N-1. Let the first square cover a subset of points with indices <= i (in sorted X order) 
//    and the second square cover points with indices > i.
//    Wait, a single square doesn't necessarily cover a contiguous range in sorted X if we just pick arbitrary points.
//    BUT, for a fixed square position, the points it covers form a contiguous range in X IF we only consider points within its X-span.
//    However, the optimal solution for two disjoint squares can always be separated by a vertical line or a horizontal line.
//    
//    Algorithm:
//    1. Sort points by X.
//       Precompute prefix_max[i]: max points coverable by ONE square using a subset of points[0..i].
//       Precompute suffix_max[i]: max points coverable by ONE square using a subset of points[i..N-1].
//       Then answer candidate = max(prefix_max[i] + suffix_max[i+1]) for all i.
//       How to compute prefix_max efficiently?
//       For a set of points restricted to indices 0..i, we want to find a KxK square covering max points.
//       The X-range of the square must end at some point's x or start at some point's x.
//       Actually, we can slide a window [L, R] in the sorted X array.
//       For a fixed window [l, r] (indices in sorted X), the points are candidates if x[r] - x[l] <= K.
//       Among these candidates, we need to find the max points coverable by a Y-interval of length K.
//       This looks like O(N^2) if done naively for every split. We need O(N log N) or O(N).
//
//    Optimized approach for Prefix/Suffix arrays:
//    Let's define `calc_max(points_subset)` which returns max points coverable by one KxK square.
//    If we do this for every split, it's too slow.
//    Instead, we can use a sweeping line + segment tree or just two pointers with a data structure.
//    Given N=2000, O(N^2) is acceptable! 2000^2 = 4e6, which is very fast.
//    So we can afford an O(N^2) solution.
//
//    Revised Plan (O(N^2)):
//    Case A: Separate by vertical line.
//      Sort points by X.
//      For each split index i from 0 to N-2:
//         Group1 = points[0...i], Group2 = points[i+1...N-1]
//         But wait, the square for Group1 might not include point[i] and square for Group2 might not include point[i+1].
//         The separation condition is: Square1.x_max < Square2.x_min.
//         We can iterate over all pairs (i, j) such that we force Square1 to cover points with x <= some value and Square2 with x >= some value.
//         Actually, simpler: Iterate split index i. Assume all points in Square1 have index <= i and all in Square2 have index > i in the X-sorted list.
//         Is this sufficient? Yes, because if two squares are disjoint horizontally, there is a vertical line between them. All points in Left square have x < line, all in Right have x > line. Thus, in X-sorted list, Left points appear before Right points.
//         So we just need to compute:
//         L[i] = max points coverable by one square using ONLY points from indices 0..i (in X-sorted order).
//         R[i] = max points coverable by one square using ONLY points from indices i..N-1.
//         Then ans = max(L[i] + R[i+1]).
//         How to compute L[i] for all i efficiently?
//         L[i] = max(L[i-1], max_points_in_one_square_among(points[0..i])).
//         Let M[i] = max points in one square among points[0..i].
//         Then L[i] = max(L[i-1], M[i]). Actually L[i] is just M[i] because adding more points never decreases the max coverable?
//         No, M[i] is the max coverable using subset of 0..i. M[i] >= M[i-1]. So L[i] = M[i].
//         Similarly R[i] = max points in one square among points[i..N-1].
//         
//         So the problem reduces to: For each i, compute M_prefix[i] = max coverable in points[0..i] and M_suffix[i] = max coverable in points[i..N-1].
//         Then answer = max(M_prefix[i] + M_suffix[i+1]).
//         
//         How to compute M_prefix[i] for all i in total O(N^2)?
//         For a fixed right bound i, we want to find a window [j, i] (j<=i) such that x[i]-x[j] <= K, and within this window, max points coverable by Y-interval K is maximized.
//         Wait, the square doesn't have to end at point i. It can be anywhere.
//         But M_prefix[i] = max(M_prefix[i-1], max_cover_ending_at_or_before_i).
//         Actually, M_prefix[i] is simply the maximum number of points coverable by a square considering only the first i+1 points.
//         We can compute M_prefix[i] incrementally? Or just recompute for each i?
//         If we recompute for each i:
//           For a fixed i, consider points P[0..i].
//           We need to find a square covering max points.
//           We can iterate all possible left bounds j (0 to i). If x[i] - x[j] <= K, then these points fit in X.
//           But the square doesn't have to span from x[j] to x[i]. It can be smaller.
//           However, any optimal square's X-interval can be shifted to start at some point's x or end at some point's x.
//           So we can iterate all pairs (j, k) with j<=k<=i such that x[k]-x[j] <= K. Then solve 1D Y problem for points in [j, k].
//           This is O(N^3) overall if done naively for every split. N=2000 -> 8e9, too slow.
//
//    Let's refine the O(N^2) approach.
//    We need M_prefix[i] for all i.
//    Notice that M_prefix[i] = max( M_prefix[i-1], max_cover_square_ending_with_point_i_as_rightmost_in_X? )
//    Not exactly. The optimal square for 0..i might not include point i. In that case M_prefix[i] = M_prefix[i-1].
//    If it includes point i, then point i is the rightmost point in the square (in terms of X sorted index? No, coordinate).
//    Since we sorted by X, if a square covers a set of points from 0..i, and point i is inside, then the square's X-range must cover x[i].
//    The square's X-range is [X_start, X_start+K]. So X_start <= x[i] <= X_start+K => x[i]-K <= X_start <= x[i].
//    To maximize points, we can assume the square's left edge is at x[j] for some j, or right edge at x[k].
//    Standard trick: The optimal square can be moved so its left edge aligns with some point's x, or its right edge aligns with some point's x.
//    Let's assume the square's X-interval is [x[j], x[j]+K]. Then it covers all points p with x[j] <= p.x <= x[j]+K.
//    Among these points, we need to find the max coverable by a Y-interval of length K.
//    
//    So, algorithm for M_prefix array:
//    Initialize M_prefix[0..N-1] = 0.
//    For each j from 0 to N-1 (left edge of square at x[j]):
//       Find all points k such that x[k] <= x[j] + K. Let this range be [j, r_j].
//       Consider the subset of points S = {points[j], ..., points[r_j]}.
//       Compute max_1d_y(S). Let this be val.
//       Then for all i from r_j to N-1, M_prefix[i] could be updated with val?
//       No. M_prefix[i] is max square using points 0..i.
//       If we pick a square defined by left edge x[j], it uses points in [j, r_j]. This is a valid square for any prefix ending at >= r_j.
//       So we can update M_prefix[r_j] = max(M_prefix[r_j], val).
//       Also, any square contained in 0..i is also contained in 0..i+1. So M_prefix should be non-decreasing.
//       After processing all j, we do a prefix max pass: M_prefix[i] = max(M_prefix[i], M_prefix[i-1]).
//       
//    Wait, is it sufficient to only check squares starting at x[j]?
//    What if the optimal square ends at x[k]? Then it starts at x[k]-K. This might not align with any x[j].
//    But we can shift it left until it hits a point. So yes, checking left edges at x[j] is sufficient.
//    Also need to check squares that are "pushed" against the right side?
//    Actually, shifting the square left until the left edge hits a point preserves the set of points covered (or adds more).
//    So yes, iterating j and setting left=x[j] covers all maximal sets.
//
//    Steps for X-split:
//    1. Sort points by X.
//    2. Compute M_prefix[i]: max points by one square in points[0..i].
//       Init M_prefix array to 0.
//       For j = 0 to N-1:
//          Identify range [j, r] such that x[r] <= x[j] + K.
//          Extract Y coordinates of points[j..r].
//          Compute max_1d_y for these Ys. Let it be cnt.
//          M_prefix[r] = max(M_prefix[r], cnt).
//       Then for i = 1 to N-1: M_prefix[i] = max(M_prefix[i], M_prefix[i-1]).
//       
//    3. Compute M_suffix[i]: max points by one square in points[i..N-1].
//       Similar logic. Iterate j from N-1 down to 0.
//       Consider square with right edge at x[j]? Or left edge?
//       If we use left edge x[j], it covers [j, r]. This square is valid for any suffix starting <= j.
//       So we update M_suffix[j] = max(M_suffix[j], cnt).
//       Then suffix max pass: M_suffix[i] = max(M_suffix[i], M_suffix[i+1]).
//       
//       Wait, for suffix, if we fix left edge at x[j], the square covers [j, r]. This set is available for any suffix start index <= j.
//       So we update M_suffix[j] (and implicitly all <= j).
//       Correct.
//
//    4. Ans = max(Ans, M_prefix[i] + M_suffix[i+1]) for i = 0 to N-2.
//
//    Repeat the same for Y-split (sort by Y, swap roles of X and Y).
//
//    Complexity:
//    Sorting: O(N log N).
//    Outer loop j: N iterations.
//    Inner range finding: Two pointers, amortized O(1) if done carefully, or O(log N) with binary search.
//    Extracting Ys and sorting them for 1D problem: O(N log N) per j -> Total O(N^2 log N).
//    With N=2000, N^2 log N ~ 4e6 * 11 ~ 4.4e7, which is acceptable for 1 second limit in C++.
//    Can we optimize the inner 1D part?
//    We need max points in Y-interval of length K for a dynamic set of points (as j moves, the range [j, r] changes).
//    As j increases, r increases (monotonic). The set of points slides.
//    We can maintain a data structure for Y coordinates?
//    Or since N is small, just re-sorting Y for each j is fine.
//    Actually, for a fixed j, we find r. Then we take points[j..r], extract Y, sort Y, run two pointers.
//    Sorting takes O(M log M) where M <= N.
//    Total complexity O(N^2 log N). This is safe.

long long solve_one_dim_split(vector<Point>& pts, bool use_x) {
    int n = pts.size();
    if (n == 0) return 0;
    
    // Sort based on coordinate
    if (use_x) {
        sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
            return a.x < b.x;
        });
    } else {
        sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
            return a.y < b.y;
        });
    }
    
    vector<int> prefix_max(n, 0);
    vector<int> suffix_max(n, 0);
    
    // Helper lambda to get coordinate
    auto get_coord = [&](const Point& p) {
        return use_x ? p.x : p.y;
    };
    
    // Compute prefix_max
    // M_prefix[i] = max points coverable by one square using subset of pts[0..i]
    // We iterate j (left edge of square at pts[j].coord)
    for (int j = 0; j < n; ++j) {
        long long c_start = get_coord(pts[j]);
        long long c_end = c_start + K;
        
        // Find r such that pts[r].coord <= c_end
        int r = j;
        while (r + 1 < n && get_coord(pts[r+1]) <= c_end) {
            r++;
        }
        
        // Collect the other coordinate for points [j, r]
        vector<int> other_coords;
        other_coords.reserve(r - j + 1);
        for (int k = j; k <= r; ++k) {
            other_coords.push_back(use_x ? pts[k].y : pts[k].x);
        }
        sort(other_coords.begin(), other_coords.end());
        
        // Solve 1D max cover for other_coords with length K
        int max_cnt = 0;
        int left = 0;
        for (int right = 0; right < (int)other_coords.size(); ++right) {
            while ((long long)other_coords[right] - (long long)other_coords[left] > K) {
                left++;
            }
            max_cnt = max(max_cnt, right - left + 1);
        }
        
        // This square covers points in index range [j, r].
        // It is a valid candidate for any prefix ending at >= r.
        if (max_cnt > prefix_max[r]) {
            prefix_max[r] = max_cnt;
        }
    }
    
    // Propagate prefix max
    for (int i = 1; i < n; ++i) {
        prefix_max[i] = max(prefix_max[i], prefix_max[i-1]);
    }
    
    // Compute suffix_max
    // M_suffix[i] = max points coverable by one square using subset of pts[i..n-1]
    // Iterate j (left edge of square at pts[j].coord). Covers [j, r].
    // Valid for any suffix starting <= j.
    for (int j = 0; j < n; ++j) {
        long long c_start = get_coord(pts[j]);
        long long c_end = c_start + K;
        
        int r = j;
        while (r + 1 < n && get_coord(pts[r+1]) <= c_end) {
            r++;
        }
        
        vector<int> other_coords;
        other_coords.reserve(r - j + 1);
        for (int k = j; k <= r; ++k) {
            other_coords.push_back(use_x ? pts[k].y : pts[k].x);
        }
        sort(other_coords.begin(), other_coords.end());
        
        int max_cnt = 0;
        int left = 0;
        for (int right = 0; right < (int)other_coords.size(); ++right) {
            while ((long long)other_coords[right] - (long long)other_coords[left] > K) {
                left++;
            }
            max_cnt = max(max_cnt, right - left + 1);
        }
        
        // Update suffix_max[j] because this square is available for any suffix starting at <= j
        if (max_cnt > suffix_max[j]) {
            suffix_max[j] = max_cnt;
        }
    }
    
    // Propagate suffix max backwards
    for (int i = n - 2; i >= 0; --i) {
        suffix_max[i] = max(suffix_max[i], suffix_max[i+1]);
    }
    
    long long ans = 0;
    // Split between i and i+1
    for (int i = 0; i < n - 1; ++i) {
        long long current = (long long)prefix_max[i] + suffix_max[i+1];
        if (current > ans) ans = current;
    }
    
    // Edge case: what if all points are covered by one square and the other covers 0?
    // The loop handles splits. If one side is empty?
    // Our split iterates i from 0 to n-2. Left part [0..i], Right part [i+1..n-1].
    // Both parts are non-empty.
    // Is it possible that the optimal solution has one square covering everything and the other 0?
    // The problem says "two squares". They must be disjoint.
    // If all points can be covered by one square, can we place another square somewhere else covering 0? Yes.
    // But our split forces a separation. If all points are in one cluster, maybe no split yields sum = total?
    // Example: 1 point. N=1. Loop doesn't run. Ans=0. But should be 1?
    // Problem says N<=2000, but N is positive integer. If N=1, we can cover 1 point with one square, 0 with other. Total 1.
    // Our split logic requires at least 2 points to have a non-empty split?
    // If N=1, the loop `for (int i = 0; i < n - 1; ++i)` does not execute. Ans remains 0.
    // We should handle N=1 separately? Or initialize ans with max(prefix_max[n-1], 0)?
    // Actually, if N=1, prefix_max[0] = 1. suffix_max[0] = 1.
    // But we need two disjoint squares.
    // If N=1, we cover the point with square A. Square B is anywhere else. Total 1.
    // Our split approach assumes a separating line between the two sets of points covered by A and B.
    // If B covers 0 points, does a separating line exist?
    // Yes, any line far away. But our split iterates lines between points.
    // If one set is empty, the "split" is effectively before the first point or after the last.
    // We should consider:
    // Option 1: Split before first point -> Left empty, Right all. Sum = 0 + M_suffix[0].
    // Option 2: Split after last point -> Left all, Right empty. Sum = M_prefix[n-1] + 0.
    // Our loop only checks splits between points.
    // So we should initialize ans = max(ans, (long long)prefix_max[n-1]); // Case where second square covers 0
    // And also ans = max(ans, (long long)suffix_max[0]); // Same thing essentially.
    // Actually, prefix_max[n-1] is the max points coverable by ONE square.
    // Since we can always place the second square to cover 0 points, the answer is at least max_one_square.
    // So initialize ans = prefix_max[n-1].
    
    ans = max(ans, (long long)prefix_max[n-1]);
    
    return ans;
}

int main() {
    // Optimize I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N >> K) {
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) {
            cin >> pts[i].x >> pts[i].y;
            pts[i].id = i;
        }

        if (N == 0) {
            cout << 0 << "\n";
            continue;
        }
        if (N == 1) {
            cout << 1 << "\n";
            continue;
        }

        long long ans_x = solve_one_dim_split(pts, true);
        
        // For Y split, we can reuse the same function by swapping x and y logically?
        // Or just pass false. The function handles sorting and coordinate selection.
        // But note: solve_one_dim_split sorts the input vector `pts`.
        // We need to pass a copy or re-read?
        // Better to pass by value or make a copy inside?
        // The function signature takes vector<Point> by value? No, reference in my draft.
        // Let's change to pass by value to avoid manual copying, or copy manually.
        // Given N=2000, copying is cheap.
        // Let's modify function to take by value or copy inside.
        // Actually, I'll create a copy in main.
        
        vector<Point> pts_copy = pts;
        long long ans_y = solve_one_dim_split(pts_copy, false);

        cout << max(ans_x, ans_y) << "\n";
    }

    return 0;
}
