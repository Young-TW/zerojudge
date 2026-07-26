#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using u128  = unsigned __int128;

/* ---------- global variables for one test case ---------- */
int64 targetLen;                     // length we are looking for
unordered_map<int64, u128> memo;    // memoisation for F(len)

/* ---------- number of target intervals inside a length ---------- */
u128 countLeaves(int64 len) {
    if (len < targetLen) return 0;
    if (len == targetLen) return 1;
    auto it = memo.find(len);
    if (it != memo.end()) return it->second;
    int64 left  = (len - 1) / 2;
    int64 right = len / 2;
    u128 res = countLeaves(left) + countLeaves(right);
    memo[len] = res;
    return res;
}

/* ---------- find left border of the idx‑th target interval ---------- */
int64 findLeft(int64 L, int64 len, u128 idx) {
    if (len == targetLen) return L;               // leaf
    int64 leftLen  = (len - 1) / 2;
    int64 rightLen = len / 2;
    u128 leftCnt = countLeaves(leftLen);
    if (idx <= leftCnt) {
        return findLeft(L, leftLen, idx);
    } else {
        int64 newL = L + (len + 1) / 2;           // left border of right child
        return findLeft(newL, rightLen, idx - leftCnt);
    }
}

/* ---------- solve one test case ---------- */
int64 solve_one(int64 n, int64 k) {
    if (k == 1) return 1;
    if (k == 2) return n;

    int64 steps = k - 2;                 // people after the first two
    map<int64, u128> cnt;                // length -> how many intervals
    if (n > 2) cnt[n - 2] = 1;           // initial empty interval

    int64 target = -1;
    u128 idx = 0;                        // 1‑based inside the target length

    u128 remaining = steps;
    while (true) {
        auto it = prev(cnt.end());       // largest length
        int64 len = it->first;
        u128 c = it->second;
        cnt.erase(it);
        if (remaining <= c) {
            target = len;
            idx = remaining;             // 1‑based
            break;
        }
        remaining -= c;
        int64 left = (len - 1) / 2;
        int64 right = len / 2;
        if (left > 0) cnt[left] += c;
        if (right > 0) cnt[right] += c;
    }

    targetLen = target;
    memo.clear();

    // left border of the idx‑th interval of length targetLen
    int64 leftBorder = findLeft(1, n - 2, idx);
    // final stall
    int64 answer = leftBorder + (targetLen + 1) / 2;
    return answer;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int64 n, k;
        cin >> n >> k;
        cout << solve_one(n, k) << '\n';
    }
    return 0;
}
