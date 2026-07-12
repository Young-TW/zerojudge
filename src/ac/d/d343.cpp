#include <iostream>
#include <string>

using namespace std;

char dp[32][150005]; // 0: unvisited, 1: win, 2: lose

char solve(int sum, int mask) {
    if (dp[sum][mask] != 0) return dp[sum][mask];
    
    bool can_win = false;
    for (int i = 1; i <= 6; ++i) {
        int shift = 3 * (i - 1);
        int count = (mask >> shift) & 7;
        if (count > 0 && sum + i <= 31) {
            int next_mask = mask - (1 << shift);
            if (solve(sum + i, next_mask) == 2) {
                can_win = true;
                break;
            }
        }
    }
    
    dp[sum][mask] = can_win ? 1 : 2;
    return dp[sum][mask];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        int mask = 0;
        for (int i = 1; i <= 6; ++i) {
            mask |= (4 << (3 * (i - 1)));
        }
        
        int sum = 0;
        for (char c : s) {
            int card = c - '0';
            sum += card;
            mask -= (1 << (3 * (card - 1)));
        }
        
        bool a_turn = (s.length() % 2 == 0);
        char win = solve(sum, mask);
        
        if (a_turn) {
            cout << s << " " << (win == 1 ? 'A' : 'B') << "\n";
        } else {
            cout << s << " " << (win == 1 ? 'B' : 'A') << "\n";
        }
    }
    
    return 0;
}
