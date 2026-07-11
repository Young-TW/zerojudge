#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int n, k;
    bool first = true;
    while (cin >> n >> k) {
        if (n == 0) break;
        if (!first) cout << "\n";
        first = false;
        
        int games = k * n * (n - 1) / 2;
        int wins[105] = {0}, losses[105] = {0};
        
        for (int i = 0; i < games; i++) {
            int p1, p2;
            string m1, m2;
            cin >> p1 >> m1 >> p2 >> m2;
            
            if (m1 == m2) continue;
            bool p1wins = false;
            if ((m1 == "rock" && m2 == "scissors") ||
                (m1 == "scissors" && m2 == "paper") ||
                (m1 == "paper" && m2 == "rock")) {
                p1wins = true;
            }
            if (p1wins) { wins[p1]++; losses[p2]++; }
            else { wins[p2]++; losses[p1]++; }
        }
        
        for (int i = 1; i <= n; i++) {
            int total = wins[i] + losses[i];
            if (total == 0) cout << "-\n";
            else printf("%.3f\n", (double)wins[i] / total);
        }
    }
    return 0;
}
