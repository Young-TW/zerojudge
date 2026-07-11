#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int J, R;
    while (cin >> J >> R && (J || R)) {
        vector<int> scores(J + 1, 0);
        int total_turns = J * R;
        
        for (int i = 0; i < total_turns; ++i) {
            int p;
            cin >> p;
            int player = (i % J) + 1;
            scores[player] += p;
        }
        
        int max_score = -1;
        int winner = 0;
        for (int i = 1; i <= J; ++i) {
            if (scores[i] >= max_score) {
                max_score = scores[i];
                winner = i;
            }
        }
        
        cout << winner << "\n";
    }
    
    return 0;
}
