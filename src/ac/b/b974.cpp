#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        string dummy;
        getline(cin, dummy); // Consume the rest of the line after n and m

        vector<int> score(21, 0);

        for (int i = 0; i < n; ++i) {
            string line;
            while (getline(cin, line)) {
                if (!line.empty()) {
                    break;
                }
            }
            
            stringstream ss(line);
            string correct_ans;
            ss >> correct_ans;
            
            int team_id;
            string team_ans;
            while (ss >> team_id >> team_ans) {
                if (team_ans == correct_ans) {
                    score[team_id]++;
                    break; // Only the first correct answer gets a point
                }
            }
        }

        int max_score = -1;
        for (int i = 1; i <= m; ++i) {
            if (score[i] > max_score) {
                max_score = score[i];
            }
        }

        bool first = true;
        for (int i = 1; i <= m; ++i) {
            if (score[i] == max_score) {
                if (!first) {
                    cout << " ";
                }
                cout << i;
                first = false;
            }
        }
        cout << "\n";

        for (int i = 1; i <= m; ++i) {
            cout << i << " " << score[i] << "\n";
        }
    }

    return 0;
}
