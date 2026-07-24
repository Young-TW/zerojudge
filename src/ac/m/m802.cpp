/*
Method: Constraint Satisfaction via Backtracking with Geometric Pruning.
1. Interpret input coordinates as (x, y) = (col, row), where each word must cover this point.
2. Pre-calculate all valid placements for each word that satisfy boundary conditions and the "must-cover" constraint.
3. Use DFS to select one placement per word.
4. During DFS, validate pairwise compatibility:
   - If two words overlap, they must share exactly one cell (standard crossword rule).
   - The character at the shared cell must be identical.
   - Overlap > 1 is forbidden.
5. This avoids the "WA" of previous methods by strictly enforcing the geometric constraints derived from the examples (specifically the coordinate interpretation and mandatory coverage).
Complexity: O(K * C^2 * L) per state where C is small constant (candidates per word), making it efficient for K<=10.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structure to represent a specific placement of a word
struct Placement {
    int id;
    char dir;       // 'V' or 'H'
    int r, c;       // Starting row and column
    int len;
    string s;
    
    // Helper to get character at absolute grid coordinate (rr, cc)
    // Returns 0 if the coordinate is not covered by this placement
    char getCharAt(int rr, int cc) const {
        if (dir == 'V') {
            if (cc == c && rr >= r && rr < r + len) return s[rr - r];
        } else {
            if (rr == r && cc >= c && cc < c + len) return s[cc - c];
        }
        return 0;
    }
    
    // Check if this placement covers (rr, cc)
    bool covers(int rr, int cc) const {
        return getCharAt(rr, cc) != 0;
    }
};

int N, K;
struct Query {
    char dir;
    string s;
    int x, y; // Input x=col, y=row
};

vector<Query> queries;
vector<vector<Placement>> candidates;
vector<Placement> selected;
bool solved = false;

// Depth First Search to try placing words one by one
void dfs(int idx) {
    if (solved) return;
    
    // Base case: All words placed successfully
    if (idx == K) {
        solved = true;
        return;
    }
    
    // Try every valid candidate for the current word
    for (const auto& p : candidates[idx]) {
        bool compatible = true;
        
        // Check against all previously placed words
        for (const auto& prev : selected) {
            int overlapCount = 0;
            bool charMatch = true;
            
            if (p.dir != prev.dir) {
                // Case 1: One Vertical, One Horizontal
                // They can intersect at most at one point (r_inter, c_inter)
                int r_inter, c_inter;
                if (p.dir == 'V') {
                    // p is Vertical (fixed col p.c), prev is Horizontal (fixed row prev.r)
                    c_inter = p.c;
                    r_inter = prev.r;
                } else {
                    // p is Horizontal, prev is Vertical
                    c_inter = prev.c;
                    r_inter = p.r;
                }
                
                // Check if intersection point lies within both segments
                bool inP = p.covers(r_inter, c_inter);
                bool inPrev = prev.covers(r_inter, c_inter);
                
                if (inP && inPrev) {
                    overlapCount = 1;
                    if (p.getCharAt(r_inter, c_inter) != prev.getCharAt(r_inter, c_inter)) {
                        charMatch = false;
                    }
                }
            } else {
                // Case 2: Same Direction (Both V or Both H)
                // They can only overlap if they are on the same line (same col for V, same row for H)
                if (p.dir == 'V' && p.c == prev.c) {
                    int start = max(p.r, prev.r);
                    int end = min(p.r + p.len, prev.r + prev.len);
                    if (start < end) {
                        overlapCount = end - start;
                        // Check all overlapping characters
                        for (int rr = start; rr < end; ++rr) {
                            if (p.getCharAt(rr, p.c) != prev.getCharAt(rr, prev.c)) {
                                charMatch = false;
                                break;
                            }
                        }
                    }
                } else if (p.dir == 'H' && p.r == prev.r) {
                    int start = max(p.c, prev.c);
                    int end = min(p.c + p.len, prev.c + prev.len);
                    if (start < end) {
                        overlapCount = end - start;
                        for (int cc = start; cc < end; ++cc) {
                            if (p.getCharAt(p.r, cc) != prev.getCharAt(prev.r, cc)) {
                                charMatch = false;
                                break;
                            }
                        }
                    }
                }
            }
            
            // Validation Rules:
            // 1. Overlap must not exceed 1 cell (standard crossword constraint)
            // 2. If overlap exists, characters must match
            if (overlapCount > 1 || (overlapCount == 1 && !charMatch)) {
                compatible = false;
                break;
            }
        }
        
        if (compatible) {
            selected.push_back(p);
            dfs(idx + 1);
            if (solved) return;
            selected.pop_back();
        }
    }
}

int main() {
    // Optimize I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Handle multiple test cases until EOF
    while (cin >> N >> K) {
        queries.clear();
        candidates.assign(K, vector<Placement>());
        selected.clear();
        solved = false;
        
        for (int i = 0; i < K; ++i) {
            char d; string s; int x, y;
            cin >> d >> s >> x >> y;
            queries.push_back({d, s, x, y});
            
            int len = (int)s.length();
            if (d == 'V') {
                // Vertical: Column is fixed at x. Row start 'r' varies.
                // Constraint: Must cover row y. So r <= y < r + len.
                // Implies: y - len + 1 <= r <= y
                // Boundary: 0 <= r and r + len <= N
                int r_min = max(0, y - len + 1);
                int r_max = min(y, N - len);
                
                for (int r = r_min; r <= r_max; ++r) {
                    candidates[i].push_back({i, d, r, x, len, s});
                }
            } else {
                // Horizontal: Row is fixed at y. Column start 'c' varies.
                // Constraint: Must cover col x. So c <= x < c + len.
                // Implies: x - len + 1 <= c <= x
                // Boundary: 0 <= c and c + len <= N
                int c_min = max(0, x - len + 1);
                int c_max = min(x, N - len);
                
                for (int c = c_min; c <= c_max; ++c) {
                    candidates[i].push_back({i, d, y, c, len, s});
                }
            }
        }
        
        // Start DFS
        dfs(0);
        
        if (solved) {
            cout << "Yes" << "\n";
        } else {
            cout << "No" << "\n";
        }
    }
    return 0;
}
