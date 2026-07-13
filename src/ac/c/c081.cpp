#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int b1, g1, c1, b2, g2, c2, b3, g3, c3;
    while (cin >> b1 >> g1 >> c1 >> b2 >> g2 >> c2 >> b3 >> g3 >> c3) {
        int bins[3][3];
        bins[0][0] = b1; bins[0][1] = g1; bins[0][2] = c1;
        bins[1][0] = b2; bins[1][1] = g2; bins[1][2] = c2;
        bins[2][0] = b3; bins[2][1] = g3; bins[2][2] = c3;
        
        int total = b1 + g1 + c1 + b2 + g2 + c2 + b3 + g3 + c3;
        
        string perms[] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};
        int max_stay = -1;
        string best_perm;
        
        for (const string& p : perms) {
            int stay = 0;
            for (int i = 0; i < 3; ++i) {
                char c = p[i];
                int idx = (c == 'B') ? 0 : (c == 'G') ? 1 : 2;
                stay += bins[i][idx];
            }
            if (stay > max_stay) {
                max_stay = stay;
                best_perm = p;
            }
        }
        
        cout << best_perm << " " << total - max_stay << "\n";
    }
    return 0;
}
