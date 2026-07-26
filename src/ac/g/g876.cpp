#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long T;
    while ( (cin >> T) ) {
        // inventories of players 1..6, types 0:D 1:G 2:F
        long long inv[7][3] = {};
        // homes of teams 0:red 1:blue
        long long home[2][3] = {};

        for (long long i = 0; i < T; ++i) {
            int Y;  cin >> Y;
            if (Y == 1) {               // dig
                int A; char B; long long C;
                cin >> A >> B >> C;
                int t = (B == 'D') ? 0 : (B == 'G' ? 1 : 2);
                inv[A][t] += C;
            }
            else if (Y == 2) {          // kill
                int A1, A2;  cin >> A1 >> A2;
                for (int t = 0; t < 3; ++t) {
                    inv[A1][t] += inv[A2][t];
                    inv[A2][t] = 0;
                }
            }
            else if (Y == 3) {          // steal from opponent home
                int A; char B; long long C;
                cin >> A >> B >> C;
                int t = (B == 'D') ? 0 : (B == 'G' ? 1 : 2);
                int team = (A <= 3) ? 0 : 1;
                int opp  = 1 - team;
                home[opp][t] -= C;          // guaranteed enough
                inv[A][t]   += C;
            }
            else if (Y == 4) {          // deposit to own home
                int A; char B; long long C;
                cin >> A >> B >> C;
                int t = (B == 'D') ? 0 : (B == 'G' ? 1 : 2);
                int team = (A <= 3) ? 0 : 1;
                inv[A][t]   -= C;           // guaranteed enough
                home[team][t] += C;
            }
            else if (Y == 5) {          // trade half with villagers
                int A; char B;
                cin >> A >> B;
                int t = (B == 'D') ? 0 : (B == 'G' ? 1 : 2);
                int team = (A <= 3) ? 0 : 1;
                long long half = inv[A][t] / 2;   // even, guaranteed
                inv[A][t]   -= half;
                home[team][t] += half;
            }
        }

        const long long homeScore[3] = {20, 10, 2};
        const long long bodyScore[3] = {10, 5, 1};

        long long red = 0, blue = 0;
        for (int t = 0; t < 3; ++t) {
            red  += home[0][t] * homeScore[t];
            blue += home[1][t] * homeScore[t];
        }
        for (int p = 1; p <= 6; ++p) {
            int team = (p <= 3) ? 0 : 1;
            for (int t = 0; t < 3; ++t) {
                if (team == 0) red  += inv[p][t] * bodyScore[t];
                else           blue += inv[p][t] * bodyScore[t];
            }
        }

        cout << red << ' ' << blue << '\n';
    }
    return 0;
}
