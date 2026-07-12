#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int third, second, first, hit;
    while (cin >> third >> second >> first >> hit) {
        int bases[4] = {0};
        bases[1] = first;
        bases[2] = second;
        bases[3] = third;
        
        int score = 0;
        if (hit > 0) {
            int new_bases[4] = {0};
            for (int i = 1; i <= 3; ++i) {
                if (bases[i]) {
                    int new_pos = i + hit;
                    if (new_pos >= 4) {
                        score++;
                    } else {
                        new_bases[new_pos] = 1;
                    }
                }
            }
            if (hit >= 4) {
                score++;
            } else {
                new_bases[hit] = 1;
            }
            bases[1] = new_bases[1];
            bases[2] = new_bases[2];
            bases[3] = new_bases[3];
        }
        
        cout << score << "\n";
        cout << bases[3] << " " << bases[2] << " " << bases[1] << "\n";
    }
    
    return 0;
}
