#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<string> board(8);
    int game_num = 1;
    while (cin >> board[0]) {
        for (int i = 1; i < 8; ++i) {
            cin >> board[i];
        }
        
        bool all_empty = true;
        for (int i = 0; i < 8; ++i) {
            if (board[i] != "........") {
                all_empty = false;
                break;
            }
        }
        if (all_empty) break;
        
        int wr = -1, wc = -1, br = -1, bc = -1;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == 'K') {
                    wr = i; wc = j;
                } else if (board[i][j] == 'k') {
                    br = i; bc = j;
                }
            }
        }
        
        auto is_valid = [](int r, int c) {
            return r >= 0 && r < 8 && c >= 0 && c < 8;
        };
        
        bool white_check = false;
        bool black_check = false;
        
        // Check white king
        {
            int kr = wr, kc = wc;
            // Knight
            int kn_dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
            int kn_dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};
            for (int i = 0; i < 8; ++i) {
                int nr = kr + kn_dr[i];
                int nc = kc + kn_dc[i];
                if (is_valid(nr, nc) && board[nr][nc] == 'n') {
                    white_check = true;
                    break;
                }
            }
            // Pawn
            if (!white_check) {
                if (is_valid(kr + 1, kc - 1) && board[kr + 1][kc - 1] == 'p') white_check = true;
                if (is_valid(kr + 1, kc + 1) && board[kr + 1][kc + 1] == 'p') white_check = true;
            }
            // Rook / Queen
            if (!white_check) {
                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};
                for (int i = 0; i < 4; ++i) {
                    for (int step = 1; step < 8; ++step) {
                        int nr = kr + dr[i] * step;
                        int nc = kc + dc[i] * step;
                        if (!is_valid(nr, nc)) break;
                        if (board[nr][nc] != '.') {
                            if (board[nr][nc] == 'r' || board[nr][nc] == 'q') {
                                white_check = true;
                            }
                            break;
                        }
                    }
                    if (white_check) break;
                }
            }
            // Bishop / Queen
            if (!white_check) {
                int dr[] = {-1, -1, 1, 1};
                int dc[] = {-1, 1, -1, 1};
                for (int i = 0; i < 4; ++i) {
                    for (int step = 1; step < 8; ++step) {
                        int nr = kr + dr[i] * step;
                        int nc = kc + dc[i] * step;
                        if (!is_valid(nr, nc)) break;
                        if (board[nr][nc] != '.') {
                            if (board[nr][nc] == 'b' || board[nr][nc] == 'q') {
                                white_check = true;
                            }
                            break;
                        }
                    }
                    if (white_check) break;
                }
            }
        }
        
        // Check black king
        {
            int kr = br, kc = bc;
            // Knight
            int kn_dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
            int kn_dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};
            for (int i = 0; i < 8; ++i) {
                int nr = kr + kn_dr[i];
                int nc = kc + kn_dc[i];
                if (is_valid(nr, nc) && board[nr][nc] == 'N') {
                    black_check = true;
                    break;
                }
            }
            // Pawn
            if (!black_check) {
                if (is_valid(kr - 1, kc - 1) && board[kr - 1][kc - 1] == 'P') black_check = true;
                if (is_valid(kr - 1, kc + 1) && board[kr - 1][kc + 1] == 'P') black_check = true;
            }
            // Rook / Queen
            if (!black_check) {
                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};
                for (int i = 0; i < 4; ++i) {
                    for (int step = 1; step < 8; ++step) {
                        int nr = kr + dr[i] * step;
                        int nc = kc + dc[i] * step;
                        if (!is_valid(nr, nc)) break;
                        if (board[nr][nc] != '.') {
                            if (board[nr][nc] == 'R' || board[nr][nc] == 'Q') {
                                black_check = true;
                            }
                            break;
                        }
                    }
                    if (black_check) break;
                }
            }
            // Bishop / Queen
            if (!black_check) {
                int dr[] = {-1, -1, 1, 1};
                int dc[] = {-1, 1, -1, 1};
                for (int i = 0; i < 4; ++i) {
                    for (int step = 1; step < 8; ++step) {
                        int nr = kr + dr[i] * step;
                        int nc = kc + dc[i] * step;
                        if (!is_valid(nr, nc)) break;
                        if (board[nr][nc] != '.') {
                            if (board[nr][nc] == 'B' || board[nr][nc] == 'Q') {
                                black_check = true;
                            }
                            break;
                        }
                    }
                    if (black_check) break;
                }
            }
        }
        
        cout << "Game #" << game_num++ << ": ";
        if (white_check) {
            cout << "white king is in check.\n";
        } else if (black_check) {
            cout << "black king is in check.\n";
        } else {
            cout << "no king is in check.\n";
        }
    }
    
    return 0;
}
