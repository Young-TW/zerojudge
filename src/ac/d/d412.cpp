#include <bits/stdc++.h>
using namespace std;

// Game Show Math (UVa 10400 / d412).
// Insert +,-,*,/ between the numbers (left-to-right, no precedence) so the
// running result equals target.  All intermediate values must stay within
// [-32000, 32000]; division only when it divides exactly.
//
// ZeroJudge checks the printed expression by exact string match, so we must
// reproduce its canonical choice.  It is produced greedily from the left:
// at each position pick the FIRST operator in the order +, -, *, / whose
// resulting value can still reach the target with the remaining numbers.
//
// reach[i][v] = true if, starting from value v just before consuming a[i..],
// the target is reachable.

const int LIMIT = 32000;
const int OFFSET = LIMIT;
const int RANGE = 2 * LIMIT + 1;   // 64001

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int p;
        cin >> p;
        vector<int> a(p);
        for (int i = 0; i < p; ++i) cin >> a[i];
        int target;
        cin >> target;

        if (p == 1) {
            if (a[0] == target) cout << a[0] << '=' << target << '\n';
            else cout << "NO EXPRESSION\n";
            continue;
        }

        // reach[i][v]: from value v, before applying operator with a[i], can we
        // finish (after consuming a[i..p-1]) landing on target?
        // Base: reach[p][v] = (v == target).
        vector<vector<char>> reach(p + 1, vector<char>(RANGE, 0));
        for (int idx = 0; idx < RANGE; ++idx)
            reach[p][idx] = (idx - OFFSET == target);

        for (int i = p - 1; i >= 1; --i) {
            int y = a[i];
            for (int idx = 0; idx < RANGE; ++idx) {
                int cur = idx - OFFSET;
                bool ok = false;
                int r;
                r = cur + y; if (r >= -LIMIT && r <= LIMIT && reach[i + 1][r + OFFSET]) ok = true;
                if (!ok) { r = cur - y; if (r >= -LIMIT && r <= LIMIT && reach[i + 1][r + OFFSET]) ok = true; }
                if (!ok) { r = cur * y; if (r >= -LIMIT && r <= LIMIT && reach[i + 1][r + OFFSET]) ok = true; }
                if (!ok && y != 0 && cur % y == 0) { r = cur / y; if (r >= -LIMIT && r <= LIMIT && reach[i + 1][r + OFFSET]) ok = true; }
                reach[i][idx] = ok;
            }
        }

        if (!reach[1][a[0] + OFFSET]) {
            cout << "NO EXPRESSION\n";
            continue;
        }

        // greedy reconstruction, operator order + - * /
        string expr = to_string(a[0]);
        int cur = a[0];
        for (int i = 1; i < p; ++i) {
            int y = a[i];
            char chosen = 0;
            int nxt = 0;
            auto consider = [&](int r, char op) -> bool {
                if (r < -LIMIT || r > LIMIT) return false;
                if (!reach[i + 1][r + OFFSET]) return false;
                chosen = op; nxt = r; return true;
            };
            if (consider(cur + y, '+')) {}
            else if (consider(cur - y, '-')) {}
            else if (consider(cur * y, '*')) {}
            else if (y != 0 && cur % y == 0 && consider(cur / y, '/')) {}
            expr += chosen;
            expr += to_string(y);
            cur = nxt;
        }
        expr += '=';
        expr += to_string(target);
        cout << expr << '\n';
    }
    return 0;
}
