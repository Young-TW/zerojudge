#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int X, Y;
int A[16];
int sumv[1<<16];
vector<vector<char>> dp;

bool can(int mask, int w) {
    if (dp[mask][w] != 0) return dp[mask][w] == 1;
    int area = sumv[mask];
    int h = area / w;
    if (h > Y) { dp[mask][w] = 2; return false; }

    if ((mask & (mask-1)) == 0) { dp[mask][w] = 1; return true; }

    int low = mask & (-mask);
    int rest = mask ^ low;

    bool res = false;
    for (int sub = rest; ; sub = (sub-1) & rest) {
        int t = sub | low;
        if (t != mask) {
            int ta = sumv[t];
            if (ta % w == 0) {
                if (can(t, w) && can(mask^t, w)) { res = true; break; }
            }
            if (!res && ta % h == 0) {
                int tw = ta / h;
                if (can(t, tw) && can(mask^t, w - tw)) { res = true; break; }
            }
        }
        if (sub == 0) break;
    }

    dp[mask][w] = res ? 1 : 2;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, caseNo = 0;
    while (cin >> n && n) {
        caseNo++;
        cin >> X >> Y;
        for (int i = 0; i < n; i++) cin >> A[i];

        int total = 0;
        for (int i = 0; i < n; i++) total += A[i];

        if (X > Y) swap(X, Y);

        if (total != (long long)X * Y) {
            cout << "Case " << caseNo << ": No\n";
            continue;
        }

        int FULL = (1<<n) - 1;

        sumv[0] = 0;
        for (int s = 1; s <= FULL; s++)
            sumv[s] = sumv[s ^ (s & (-s))] + A[__builtin_ctz(s)];

        dp.assign(1<<n, vector<char>(X+1, 0));

        cout << "Case " << caseNo << ": " << (can(FULL, X) ? "Yes" : "No") << "\n";
    }
    return 0;
}
