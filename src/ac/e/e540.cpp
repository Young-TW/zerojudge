#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        while (T--) {
            string s;
            cin >> s;
            int total_score = 0;
            int current_streak = 0;
            for (char c : s) {
                if (c == 'O') {
                    current_streak++;
                    total_score += current_streak;
                } else {
                    current_streak = 0;
                }
            }
            cout << total_score << '\n';
        }
    }
    
    return 0;
}
