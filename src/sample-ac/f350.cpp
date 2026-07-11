#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Condition {
    int idx[10];
    int cnt;
    int target;
};

void solve(const vector<Condition>& conditions) {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    do {
        bool ok = true;
        for (const auto& cond : conditions) {
            int sum = 0;
            for (int i = 0; i < cond.cnt; ++i) {
                sum += a[cond.idx[i]];
            }
            if (sum != cond.target) {
                ok = false;
                break;
            }
        }
        if (ok) {
            for (int i = 0; i < 10; ++i) {
                cout << a[i] << (i == 9 ? '\n' : ' ');
            }
        }
    } while (next_permutation(a, a + 10));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    vector<Condition> conditions;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        bool all_space = true;
        for (char c : line) {
            if (c != ' ' && c != '\t') {
                all_space = false;
                break;
            }
        }
        if (all_space) {
            if (!conditions.empty()) {
                solve(conditions);
                conditions.clear();
            }
            continue;
        }
        Condition cond;
        cond.cnt = 0;
        cond.target = 0;
        bool after_equals = false;
        for (char c : line) {
            if (c == '=') {
                after_equals = true;
            } else if (c >= 'A' && c <= 'J') {
                if (!after_equals) {
                    cond.idx[cond.cnt++] = c - 'A';
                }
            } else if (c >= '0' && c <= '9') {
                if (after_equals) {
                    cond.target = cond.target * 10 + (c - '0');
                }
            }
        }
        if (cond.cnt > 0) {
            conditions.push_back(cond);
        }
    }
    if (!conditions.empty()) {
        solve(conditions);
    }
    return 0;
}
