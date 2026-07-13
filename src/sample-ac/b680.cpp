#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Runner {
    int id;
    int score;
};

bool cmp(const Runner& a, const Runner& b) {
    return a.score < b.score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<Runner> runners(N);
        for (int i = 0; i < N; ++i) {
            string s;
            cin >> runners[i].id >> s;
            string num = "";
            for (char c : s) {
                if (c != '.') {
                    num += c;
                }
            }
            runners[i].score = stoi(num);
        }

        sort(runners.begin(), runners.end(), cmp);

        int groups = N / 8;
        vector<vector<int>> group_assignments(groups);

        for (int i = 0; i < N; ++i) {
            int pos = i % (2 * groups);
            int group_id;
            if (pos < groups) {
                group_id = pos;
            } else {
                group_id = 2 * groups - pos - 1;
            }
            group_assignments[group_id].push_back(runners[i].id);
        }

        int lane_order[8] = {3, 4, 2, 5, 1, 6, 0, 7};

        for (int g = 0; g < groups; ++g) {
            int lanes[8];
            for (int j = 0; j < 8; ++j) {
                lanes[lane_order[j]] = group_assignments[g][j];
            }
            cout << g + 1;
            for (int j = 0; j < 8; ++j) {
                cout << " " << lanes[j];
            }
            cout << "\n";
        }
    }

    return 0;
}
