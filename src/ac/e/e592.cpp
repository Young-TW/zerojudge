#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    string line;
    getline(cin, line); // 讀取 T 後面的換行符

    for (int t = 0; t < T; ++t) {
        // 讀取空行（如果有），直到讀到 n
        int n = 0;
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (!line.empty()) {
                istringstream iss(line);
                if (iss >> n) {
                    break;
                }
            }
        }
        
        if (n == 0) {
            break;
        }

        vector<string> candidates(n + 1);
        for (int i = 1; i <= n; ++i) {
            if (!getline(cin, candidates[i])) {
                candidates[i] = "";
            }
            if (!candidates[i].empty() && candidates[i].back() == '\r') {
                candidates[i].pop_back();
            }
        }

        vector<vector<int>> ballots;
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) break; // 遇到空行，該組測資選票結束

            istringstream iss(line);
            vector<int> b;
            int num;
            while (iss >> num) {
                b.push_back(num);
            }
            if (!b.empty()) {
                ballots.push_back(b);
            }
        }

        vector<bool> eliminated(n + 1, false);
        
        while (true) {
            vector<int> votes(n + 1, 0);
            int total_votes = 0;

            for (const auto& b : ballots) {
                for (int candidate : b) {
                    if (candidate >= 1 && candidate <= n && !eliminated[candidate]) {
                        votes[candidate]++;
                        total_votes++;
                        break;
                    }
                }
            }

            int max_votes = -1;
            int min_votes = 1000000;
            for (int i = 1; i <= n; ++i) {
                if (!eliminated[i]) {
                    if (votes[i] > max_votes) max_votes = votes[i];
                    if (votes[i] < min_votes) min_votes = votes[i];
                }
            }

            if (max_votes > total_votes / 2) {
                for (int i = 1; i <= n; ++i) {
                    if (!eliminated[i] && votes[i] == max_votes) {
                        cout << candidates[i] << "\n";
                    }
                }
                break;
            }

            bool all_tied = true;
            for (int i = 1; i <= n; ++i) {
                if (!eliminated[i] && votes[i] != max_votes) {
                    all_tied = false;
                    break;
                }
            }

            if (all_tied) {
                for (int i = 1; i <= n; ++i) {
                    if (!eliminated[i]) {
                        cout << candidates[i] << "\n";
                    }
                }
                break;
            }

            for (int i = 1; i <= n; ++i) {
                if (!eliminated[i] && votes[i] == min_votes) {
                    eliminated[i] = true;
                }
            }
        }

        if (t < T - 1) {
            cout << "\n";
        }
    }

    return 0;
}
