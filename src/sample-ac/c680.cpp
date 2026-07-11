#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        string ans;
        cin >> ans;
        int N;
        cin >> N;
        int score_per_q = 100 / T;
        for (int i = 0; i < N; ++i) {
            string stu;
            cin >> stu;
            int score = 0;
            int len = stu.length();
            for (int j = 0; j < T; ++j) {
                if (j < len && stu[j] != '=' && stu[j] == ans[j]) {
                    score += score_per_q;
                }
            }
            cout << score << "\n";
        }
    }
    return 0;
}
