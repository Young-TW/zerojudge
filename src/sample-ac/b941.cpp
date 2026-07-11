#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int N, M, K;
int S;
long long total_solutions;

// Check if (r, c) is attacked by any Queen (given masks)
inline bool is_attacked_by_queen(int r, int c, int rq, int cq, int d1q, int d2q) {
    if ((rq >> r) & 1) return true;
    if ((cq >> c) & 1) return true;
    int d1 = r - c + S - 1;
    int d2 = r + c;
    if ((d1q >> d1) & 1) return true;
    if ((d2q >> d2) & 1) return true;
    return false;
}

void place_bishops(int idx, int db1, int db2, int rq, int cq, int d1q, int d2q, const vector<pair<int, int> >& rook_list, int last_pos) {
    if (idx == K) {
        total_solutions++;
        return;
    }
    
    // Pruning: if remaining cells are not enough
    // Not strictly necessary for N+M+K <= 10 but good practice
    // Total cells = S*S. Used/Invalid? Hard to count exactly without scanning. Skip for simplicity.
    
    for (int pos = last_pos + 1; pos < S * S; ++pos) {
        int r = pos / S;
        int c = pos % S;
        
        // Check vs Queens
        if (is_attacked_by_queen(r, c, rq, cq, d1q, d2q)) continue;
        
        // Check vs Rooks
        bool conflict_rook = false;
        for (size_t i = 0; i < rook_list.size(); ++i) {
            int rr = rook_list[i].first;
            int rc = rook_list[i].second;
            if (r == rr || c == rc) {
                conflict_rook = true;
                break;
            }
            if (std::abs(r - rr) == std::abs(c - rc)) {
                conflict_rook = true;
                break;
            }
        }
        if (conflict_rook) continue;
        
        // Check vs Bishops (diagonals only)
        int d1 = r - c + S - 1;
        int d2 = r + c;
        if (((db1 >> d1) & 1) || ((db2 >> d2) & 1)) continue;
        
        // Place Bishop
        place_bishops(idx + 1, db1 | (1 << d1), db2 | (1 << d2), rq, cq, d1q, d2q, rook_list, pos);
    }
}

void place_rooks(int idx, int rr, int cr, vector<pair<int, int> >& rook_list, int rq, int cq, int d1q, int d2q, int last_pos) {
    if (idx == M) {
        place_bishops(0, 0, 0, rq, cq, d1q, d2q, rook_list, -1);
        return;
    }
    
    for (int pos = last_pos + 1; pos < S * S; ++pos) {
        int r = pos / S;
        int c = pos % S;
        
        // Check vs Queens
        if (is_attacked_by_queen(r, c, rq, cq, d1q, d2q)) continue;
        
        // Check vs other Rooks (row/col only)
        if (((rr >> r) & 1) || ((cr >> c) & 1)) continue;
        
        // Place Rook
        rook_list.push_back(make_pair(r, c));
        place_rooks(idx + 1, rr | (1 << r), cr | (1 << c), rook_list, rq, cq, d1q, d2q, pos);
        rook_list.pop_back();
    }
}

void place_queens(int idx, int rq, int cq, int d1q, int d2q, int last_pos) {
    if (idx == N) {
        vector<pair<int, int> > rook_list;
        rook_list.reserve(M);
        place_rooks(0, 0, 0, rook_list, rq, cq, d1q, d2q, -1);
        return;
    }
    
    for (int pos = last_pos + 1; pos < S * S; ++pos) {
        int r = pos / S;
        int c = pos % S;
        
        // Check vs existing Queens
        if (is_attacked_by_queen(r, c, rq, cq, d1q, d2q)) continue;
        
        int d1 = r - c + S - 1;
        int d2 = r + c;
        
        place_queens(idx + 1, rq | (1 << r), cq | (1 << c), d1q | (1 << d1), d2q | (1 << d2), pos);
    }
}

int main() {
    // Optimize I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> N >> M >> K) {
        S = N + M + K;
        total_solutions = 0;
        
        // Edge case: if S==0, though problem says not all zero.
        if (S == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        place_queens(0, 0, 0, 0, 0, -1);
        
        cout << total_solutions << "\n";
    }
    
    return 0;
}
