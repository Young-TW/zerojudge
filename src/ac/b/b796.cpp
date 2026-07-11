#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int L;
vector<string> grid;
vector<pair<int, int>> grass_positions;
int max_power = -1;
long long min_cost = -1;
int best_count = 0;
vector<bool> best_selection;

// Directions: 8 directions (horizontal, vertical, diagonal)
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Check if a position is valid
bool isValid(int r, int c) {
    return r >= 0 && r < L && c >= 0 && c < L;
}

// Calculate the power (number of enemies hit) for a cannon at (r, c)
int calculatePower(int r, int c) {
    int power = 0;
    for (int d = 0; d < 8; ++d) {
        int nr = r + dx[d];
        int nc = c + dy[d];
        while (isValid(nr, nc)) {
            if (grid[nr][nc] == 'x') {
                power++;
            } else if (grid[nr][nc] == 'C') {
                // Stop at another cannon? The problem says "貫穿性" (penetrating), 
                // but usually in these problems, cannons block line of sight or 
                // the condition is just about not hitting each other.
                // Re-reading: "射程遠、火力強且具有貫穿性". This implies it goes through everything.
                // However, the constraint is "倆倆互相不在友軍的攻擊範圍內".
                // If cannon A hits cannon B, that's invalid.
                // Does a cannon block the shot? "貫穿性" suggests no.
                // But let's look at the example logic.
                // Example 1:
                // xx.C
                // Cxxx
                // ..Cx
                // ...x
                // Cannon at (0,3). Down: (1,3)='x', (2,3)='x', (3,3)='x'. Hits 3.
                // Left: (0,2)='.', (0,1)='x', (0,0)='x'. Hits 2.
                // Diagonal SW: (1,2)='x', (2,1)='.', (3,0)='.'. Hits 1.
                // Total for (0,3) = 6?
                // Let's re-calculate manually based on the example explanation.
                // Explanation says:
                // First cannon (0,3): "攻擊次數 +6".
                // My trace:
                // Dir (-1,-1): out
                // Dir (-1,0): out
                // Dir (-1,1): out
                // Dir (0,-1): (0,2)., (0,1)x, (0,0)x -> 2 hits
                // Dir (0,1): out
                // Dir (1,-1): (1,2)x, (2,1)., (3,0). -> 1 hit
                // Dir (1,0): (1,3)x, (2,3)x, (3,3)x -> 3 hits
                // Dir (1,1): out
                // Sum = 2+1+3 = 6. Correct.
                // It seems cannons do NOT block shots, only count as targets if they are in the line.
                // But the constraint is we cannot place them such that they hit each other.
                // So when calculating power for a valid configuration, we count 'x'.
                // Do we count 'C' as a hit? No, the goal is to hit enemies ('x').
                // The constraint is just that no 'C' is in the line of fire of another 'C'.
                // Since we ensure no 'C' hits 'C' during validation, we just sum up 'x' hits.
                // And since shots penetrate, one cannon can hit multiple 'x's in one direction.
            }
            nr += dx[d];
            nc += dy[d];
        }
    }
    return power;
}

// Check if placing a cannon at (r, c) is safe given existing cannons in 'selection'
// 'selection' represents the set of currently chosen cannons (indices in grass_positions)
// We are checking if adding index 'idx' (which corresponds to r,c) causes conflict
bool isSafe(int idx, const vector<bool>& selection) {
    int r = grass_positions[idx].first;
    int c = grass_positions[idx].second;

    // Check against all already selected cannons
    for (size_t i = 0; i < grass_positions.size(); ++i) {
        if (!selection[i]) continue;
        if (i == (size_t)idx) continue; // Should not happen in this flow but safety check

        int r2 = grass_positions[i].first;
        int c2 = grass_positions[i].second;

        // Check if (r,c) and (r2,c2) are in the same 8-directional line
        int dr = r - r2;
        int dc = c - c2;

        // They are in line if dr==0 or dc==0 or abs(dr)==abs(dc)
        if (dr == 0 || dc == 0 || abs(dr) == abs(dc)) {
            // They are in line. Now check if there is any obstacle between them?
            // Problem says "貫穿性" (penetrating). This usually means no obstacles block.
            // So if they are in line, they hit each other.
            return false;
        }
    }
    return true;
}

// Global variables for backtracking state
vector<bool> current_selection;
int current_power_sum;
long long current_cost_sum;
int current_count;

void backtrack(int idx) {
    if (idx == (int)grass_positions.size()) {
        // End of recursion, check if this solution is better
        if (current_power_sum > max_power) {
            max_power = current_power_sum;
            min_cost = current_cost_sum;
            best_count = current_count;
            best_selection = current_selection;
        } else if (current_power_sum == max_power) {
            if (min_cost == -1 || current_cost_sum < min_cost) {
                min_cost = current_cost_sum;
                best_count = current_count;
                best_selection = current_selection;
            }
        }
        return;
    }

    // Option 1: Try to place a cannon at grass_positions[idx]
    int r = grass_positions[idx].first;
    int c = grass_positions[idx].second;

    if (isSafe(idx, current_selection)) {
        // Place cannon
        current_selection[idx] = true;
        current_count++;
        
        // Calculate cost: (y+1)^3 * (x+1)^2. Note: problem says (row, col) -> (y, x)?
        // "假設地圖最左上角是 (0,0)，最右下角是 (L-1,L-1)"
        // Usually matrix is (row, col). Problem says "(y+1)^3 * (x+1)^2".
        // In standard Cartesian, y is row (down?), x is col (right?).
        // Or is y the vertical coordinate (row) and x the horizontal (col)?
        // Let's check the example calculation:
        // Example 1:
        // Cannon at (1, 0) (Row 1, Col 0). "成本 16 + (2^3 * 1^2)".
        // If row=y=1, col=x=0: (1+1)^3 * (0+1)^2 = 8 * 1 = 8. Matches the added cost 8.
        // Cannon at (0, 3): (0+1)^3 * (3+1)^2 = 1 * 16 = 16. Matches first cost 16.
        // Cannon at (2, 2): (2+1)^3 * (2+1)^2 = 27 * 9 = 243. Matches third cost 243.
        // So y = row index, x = column index.
        
        long long cost = (long long)(r + 1) * (r + 1) * (r + 1) * (c + 1) * (c + 1);
        int power = calculatePower(r, c);
        
        current_cost_sum += cost;
        current_power_sum += power;

        backtrack(idx + 1);

        // Backtrack
        current_selection[idx] = false;
        current_count--;
        current_cost_sum -= cost;
        current_power_sum -= power;
    }

    // Option 2: Skip this grass position
    backtrack(idx + 1);
}

void solve() {
    cin >> L;
    grid.resize(L);
    grass_positions.clear();
    
    for (int i = 0; i < L; ++i) {
        cin >> grid[i];
        for (int j = 0; j < L; ++j) {
            if (grid[i][j] == '.') {
                grass_positions.push_back({i, j});
            }
        }
    }

    int n = grass_positions.size();
    current_selection.assign(n, false);
    current_power_sum = 0;
    current_cost_sum = 0;
    current_count = 0;
    
    max_power = -1;
    min_cost = -1;
    best_count = 0;
    best_selection.assign(n, false);

    backtrack(0);

    cout << "Quantity: " << best_count << endl;
    cout << "Cost: " << min_cost << endl;
    cout << "Power: " << max_power << endl;
    cout << "Strategy Map:" << endl;

    // Construct the result map
    vector<string> result = grid;
    for (int i = 0; i < n; ++i) {
        if (best_selection[i]) {
            int r = grass_positions[i].first;
            int c = grass_positions[i].second;
            result[r][c] = 'C';
        }
    }

    for (int i = 0; i < L; ++i) {
        cout << result[i] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
