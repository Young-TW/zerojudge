#include <cstdio>
#include <iostream>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE];
int buf_pos = 0, buf_len = 0;

inline int get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUFFER_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return (unsigned char)buf[buf_pos++];
}

inline int readInt() {
    int c = get_char();
    while (c < '0' || c > '9') {
        if (c == EOF) return EOF;
        c = get_char();
    }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return x;
}

inline int readChar() {
    int c = get_char();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
        c = get_char();
    }
    return c;
}

int main() {
    int T;
    while ((T = readInt()) != EOF) {
        long long player_inv[7][3] = {0};
        long long team_home[2][3] = {0};
        
        for (int t = 0; t < T; ++t) {
            int Y = readInt();
            if (Y == 1 || Y == 3 || Y == 4) {
                int A = readInt();
                int B = readChar();
                int C = readInt();
                int b_idx = (B == 'D') ? 0 : ((B == 'G') ? 1 : 2);
                
                if (Y == 1) {
                    player_inv[A][b_idx] += C;
                } else if (Y == 3) {
                    int team_id = (A <= 3) ? 0 : 1;
                    int opp_id = 1 - team_id;
                    team_home[opp_id][b_idx] -= C;
                    player_inv[A][b_idx] += C;
                } else if (Y == 4) {
                    int team_id = (A <= 3) ? 0 : 1;
                    player_inv[A][b_idx] -= C;
                    team_home[team_id][b_idx] += C;
                }
            } else if (Y == 2) {
                int A1 = readInt();
                int A2 = readInt();
                for (int i = 0; i < 3; ++i) {
                    player_inv[A1][i] += player_inv[A2][i];
                    player_inv[A2][i] = 0;
                }
            } else if (Y == 5) {
                int A = readInt();
                int B = readChar();
                int b_idx = (B == 'D') ? 0 : ((B == 'G') ? 1 : 2);
                
                int team_id = (A <= 3) ? 0 : 1;
                long long half = player_inv[A][b_idx] / 2;
                player_inv[A][b_idx] -= half;
                team_home[team_id][b_idx] += half;
            }
        }
        
        long long score_home[3] = {20, 10, 2};
        long long score_inv[3] = {10, 5, 1};
        
        long long red_score = 0, blue_score = 0;
        for (int i = 0; i < 3; ++i) {
            red_score += team_home[0][i] * score_home[i];
            blue_score += team_home[1][i] * score_home[i];
        }
        
        for (int p = 1; p <= 6; ++p) {
            int team_id = (p <= 3) ? 0 : 1;
            for (int i = 0; i < 3; ++i) {
                if (team_id == 0) {
                    red_score += player_inv[p][i] * score_inv[i];
                } else {
                    blue_score += player_inv[p][i] * score_inv[i];
                }
            }
        }
        
        printf("%lld %lld\n", red_score, blue_score);
    }
    return 0;
}
