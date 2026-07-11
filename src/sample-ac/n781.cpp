#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Contestant {
    int id;
    int solved;
    int penalty;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    cin.ignore();

    for (int t = 1; t <= T; t++) {
        bool participated[105] = {false};
        int solved_count[105] = {0};
        int penalty[105] = {0};
        int incorrect_attempts[105][15] = {0};
        bool is_solved[105][15] = {false};

        string line;
        bool firstLine = true;
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) {
                if (!firstLine) break;
                else continue;
            }
            firstLine = false;
            
            stringstream ss(line);
            int c, p, time;
            char L;
            if (ss >> c >> p >> time >> L) {
                if (c >= 1 && c <= 100 && p >= 1 && p <= 9) {
                    participated[c] = true;
                    if (L == 'C') {
                        if (!is_solved[c][p]) {
                            is_solved[c][p] = true;
                            solved_count[c]++;
                            penalty[c] += time + incorrect_attempts[c][p] * 20;
                        }
                    } else if (L == 'I') {
                        if (!is_solved[c][p]) {
                            incorrect_attempts[c][p]++;
                        }
                    }
                }
            }
        }

        vector<Contestant> contestants;
        for (int i = 1; i <= 100; i++) {
            if (participated[i]) {
                contestants.push_back({i, solved_count[i], penalty[i]});
            }
        }

        sort(contestants.begin(), contestants.end(), [](const Contestant& a, const Contestant& b) {
            if (a.solved != b.solved) return a.solved > b.solved;
            if (a.penalty != b.penalty) return a.penalty < b.penalty;
            return a.id < b.id;
        });

        if (t > 1) cout << "\n";
        for (const auto& cont : contestants) {
            cout << cont.id << " " << cont.solved << " " << cont.penalty << "\n";
        }
    }

    return 0;
}
