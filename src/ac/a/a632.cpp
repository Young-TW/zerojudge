#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dominoes[29][2] = {
        {0, 0}, {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6},
        {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6},
        {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
        {3, 3}, {3, 4}, {3, 5}, {3, 6},
        {4, 4}, {4, 5}, {4, 6},
        {5, 5}, {5, 6},
        {6, 6}
    };

    int id;
    char dir;
    vector<pair<int, int>> stk; // {id, right_end}

    while (cin >> id >> dir) {
        if (id == 0) {
            if (stk.empty()) {
                cout << "DATASET CLEARED\n";
            } else {
                bool first = true;
                for (const auto& p : stk) {
                    if (!first) cout << " ";
                    cout << p.first;
                    first = false;
                }
                cout << "\n";
            }
            stk.clear();
        } else {
            int left_end, right_end;
            if (dir == 'F') {
                left_end = dominoes[id][0];
                right_end = dominoes[id][1];
            } else {
                left_end = dominoes[id][1];
                right_end = dominoes[id][0];
            }

            if (!stk.empty() && stk.back().second == left_end) {
                stk.pop_back();
            } else {
                stk.push_back({id, right_end});
            }
        }
    }

    return 0;
}
