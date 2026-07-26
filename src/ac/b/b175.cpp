#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int PERIOD = 63;                 // lcm(3,7,9)

    long long N, M, X, P, T;
    while (cin >> N >> M >> X >> P >> T) {
        if (P == 1) {                      // everything is 0
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (j) cout << ' ';
                    cout << 0;
                }
                cout << '\n';
            }
            continue;
        }

        const int S = (int)(N * M);
        vector<int> L(S);
        vector<string> cmd(S);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                int idx = i * (int)M + j;
                int len; string s;
                cin >> len >> s;
                L[idx] = len;
                cmd[idx] = s;
            }
        }

        /* neighbour indices, -1 if outside */
        vector<int> up(S, -1), down(S, -1), left(S, -1), right(S, -1);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                int id = i * (int)M + j;
                if (i > 0) up[id] = (i - 1) * (int)M + j;
                if (i + 1 < N) down[id] = (i + 1) * (int)M + j;
                if (j > 0) left[id] = i * (int)M + (j - 1);
                if (j + 1 < M) right[id] = i * (int)M + (j + 1);
            }
        }

        /* ---------- 1. mapping after one whole period (63 steps) ---------- */
        vector<int> nextPos(S);
        for (int i = 0; i < S; ++i) nextPos[i] = i;          // current position of a bead that started at i
        for (int t = 0; t < PERIOD; ++t) {
            for (int i = 0; i < S; ++i) {
                int pos = nextPos[i];
                if (pos == -1) continue;
                char c = cmd[pos][ t % L[pos] ];
                if (c == 'C') continue;
                else if (c == 'U') pos = up[pos];
                else if (c == 'D') pos = down[pos];
                else if (c == 'L') pos = left[pos];
                else               pos = right[pos];
                nextPos[i] = pos;          // -1 stays -1
            }
        }

        /* ---------- 2. vector B : result of one period starting from zero ---------- */
        vector<int> cur(S, 0), nxt(S, 0);
        for (int t = 0; t < PERIOD; ++t) {
            fill(nxt.begin(), nxt.end(), 0);
            for (int i = 0; i < S; ++i) {
                char c = cmd[i][ t % L[i] ];
                int beads = cur[i];
                if (c == 'C') {
                    ll val = ( (ll)beads + X ) % P;
                    nxt[i] = (nxt[i] + (int)val) % P;
                } else {
                    int nb = -1;
                    if (c == 'U') nb = up[i];
                    else if (c == 'D') nb = down[i];
                    else if (c == 'L') nb = left[i];
                    else nb = right[i];
                    if (nb != -1 && beads) {
                        nxt[nb] = (nxt[nb] + beads) % P;
                    }
                }
            }
            cur.swap(nxt);
        }
        vector<int> baseAdd = cur;          // B

        /* ---------- 3. binary exponentiation of the period map ---------- */
        long long q = T / PERIOD;
        int r = (int)(T % PERIOD);
        vector<int> state(S, 0);            // start with zero board

        vector<int> curMap = nextPos;       // move part of current power
        vector<int> curAdd = baseAdd;       // add part of current power

        while (q > 0) {
            if (q & 1LL) {
                // apply curMap and curAdd to state
                vector<int> newState(S, 0);
                for (int i = 0; i < S; ++i) {
                    int val = state[i];
                    if (!val) continue;
                    int to = curMap[i];
                    if (to != -1) {
                        int sum = newState[to] + val;
                        if (sum >= P) sum -= P;
                        newState[to] = sum;
                    }
                }
                for (int i = 0; i < S; ++i) {
                    int sum = newState[i] + curAdd[i];
                    if (sum >= P) sum -= P;
                    newState[i] = sum;
                }
                state.swap(newState);
            }

            // square the current affine map
            vector<int> nextMap(S);
            for (int i = 0; i < S; ++i) {
                int mid = curMap[i];
                nextMap[i] = (mid == -1) ? -1 : curMap[mid];
            }

            vector<int> movedAdd(S, 0);
            for (int i = 0; i < S; ++i) {
                int val = curAdd[i];
                if (!val) continue;
                int to = curMap[i];
                if (to != -1) {
                    int sum = movedAdd[to] + val;
                    if (sum >= P) sum -= P;
                    movedAdd[to] = sum;
                }
            }

            vector<int> nextAdd(S);
            for (int i = 0; i < S; ++i) {
                int sum = movedAdd[i] + curAdd[i];
                if (sum >= P) sum -= P;
                nextAdd[i] = sum;
            }

            curMap.swap(nextMap);
            curAdd.swap(nextAdd);
            q >>= 1LL;
        }

        /* ---------- 4. remaining r single steps ---------- */
        if (r > 0) {
            // offset[i] = (q0 * 63) % Li
            long long q0 = T / PERIOD;          // original number of periods
            vector<int> offset(S);
            for (int i = 0; i < S; ++i) {
                int Li = L[i];
                int mod63 = 63 % Li;
                int qmod = (int)(q0 % Li);
                offset[i] = (int)((1LL * qmod * mod63) % Li);
            }

            vector<int> tmp(S, 0);
            for (int step = 0; step < r; ++step) {
                fill(tmp.begin(), tmp.end(), 0);
                for (int i = 0; i < S; ++i) {
                    char c = cmd[i][ (offset[i] + step) % L[i] ];
                    int beads = state[i];
                    if (c == 'C') {
                        ll val = ( (ll)beads + X ) % P;
                        tmp[i] = (tmp[i] + (int)val) % P;
                    } else {
                        int nb = -1;
                        if (c == 'U') nb = up[i];
                        else if (c == 'D') nb = down[i];
                        else if (c == 'L') nb = left[i];
                        else nb = right[i];
                        if (nb != -1 && beads) {
                            int sum = tmp[nb] + beads;
                            if (sum >= P) sum -= P;
                            tmp[nb] = sum;
                        }
                    }
                }
                state.swap(tmp);
            }
        }

        /* ---------- 5. output ---------- */
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (j) cout << ' ';
                cout << state[i * (int)M + j];
            }
            cout << '\n';
        }
    }
    return 0;
}
