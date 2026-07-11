#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <array>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool firstCase = true;
    int N;
    while (cin >> N) {
        if (!firstCase) cout << "\n";
        firstCase = false;

        vector<int> H(N + 1);
        for (int i = 1; i <= N; ++i) cin >> H[i];

        long long X0;
        cin >> X0;
        int M;
        cin >> M;
        vector<pair<int, long long>> queries(M);
        for (int i = 0; i < M; ++i) {
            int s; long long x;
            cin >> s >> x;
            queries[i] = {s, x};
        }

        // Compute nextA and nextB
        vector<int> nextA(N + 1, 0), nextB(N + 1, 0);
        set<pair<int, int>> st; // (altitude, index)
        for (int i = N; i >= 1; --i) {
            vector<array<long long, 3>> cand; // {distance, altitude, index}
            auto it = st.lower_bound({H[i], 0});

            // Successor and its next
            if (it != st.end()) {
                int j = it->second;
                long long d = (H[i] > H[j]) ? (long long)H[i] - H[j] : (long long)H[j] - H[i];
                cand.push_back({d, H[j], j});
                auto it2 = next(it);
                if (it2 != st.end()) {
                    int j2 = it2->second;
                    long long d2 = (H[i] > H[j2]) ? (long long)H[i] - H[j2] : (long long)H[j2] - H[i];
                    cand.push_back({d2, H[j2], j2});
                }
            }
            // Predecessor and its previous
            if (it != st.begin()) {
                auto it_pred = prev(it);
                int j = it_pred->second;
                long long d = (H[i] > H[j]) ? (long long)H[i] - H[j] : (long long)H[j] - H[i];
                cand.push_back({d, H[j], j});
                if (it_pred != st.begin()) {
                    auto it_pred2 = prev(it_pred);
                    int j2 = it_pred2->second;
                    long long d2 = (H[i] > H[j2]) ? (long long)H[i] - H[j2] : (long long)H[j2] - H[i];
                    cand.push_back({d2, H[j2], j2});
                }
            }

            sort(cand.begin(), cand.end(), [](const array<long long, 3>& a, const array<long long, 3>& b) {
                if (a[0] != b[0]) return a[0] < b[0];
                return a[1] < b[1];
            });

            if (cand.size() >= 1) nextB[i] = cand[0][2];
            if (cand.size() >= 2) nextA[i] = cand[1][2];

            st.insert({H[i], i});
        }

        // Distances for A and B moves
        vector<long long> distA(N + 1, 0), distB(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            if (nextA[i] != 0) distA[i] = (H[i] > H[nextA[i]]) ? (long long)H[i] - H[nextA[i]] : (long long)H[nextA[i]] - H[i];
            if (nextB[i] != 0) distB[i] = (H[i] > H[nextB[i]]) ? (long long)H[i] - H[nextB[i]] : (long long)H[nextB[i]] - H[i];
        }

        // Binary lifting for full (A then B) pairs
        int LOG = 0;
        while ((1 << LOG) <= N) ++LOG;

        vector<vector<int>> nxt(LOG, vector<int>(N + 1, 0));
        vector<vector<long long>> sumA(LOG, vector<long long>(N + 1, 0));
        vector<vector<long long>> sumB(LOG, vector<long long>(N + 1, 0));
        vector<vector<long long>> sumTot(LOG, vector<long long>(N + 1, 0));

        for (int i = 1; i <= N; ++i) {
            if (nextA[i] != 0 && nextB[nextA[i]] != 0) {
                nxt[0][i] = nextB[nextA[i]];
                sumA[0][i] = distA[i];
                sumB[0][i] = distB[nextA[i]];
                sumTot[0][i] = sumA[0][i] + sumB[0][i];
            }
        }

        for (int k = 1; k < LOG; ++k) {
            for (int i = 1; i <= N; ++i) {
                int mid = nxt[k - 1][i];
                if (mid != 0 && nxt[k - 1][mid] != 0) {
                    nxt[k][i] = nxt[k - 1][mid];
                    sumA[k][i] = sumA[k - 1][i] + sumA[k - 1][mid];
                    sumB[k][i] = sumB[k - 1][i] + sumB[k - 1][mid];
                    sumTot[k][i] = sumTot[k - 1][i] + sumTot[k - 1][mid];
                }
            }
        }

        // Lambda to answer a single query
        auto solve_query = [&](int S, long long X) -> pair<long long, long long> {
            long long totalA = 0, totalB = 0;
            long long rem = X;
            int cur = S;

            for (int k = LOG - 1; k >= 0; --k) {
                if (nxt[k][cur] != 0 && sumTot[k][cur] <= rem) {
                    totalA += sumA[k][cur];
                    totalB += sumB[k][cur];
                    rem -= sumTot[k][cur];
                    cur = nxt[k][cur];
                }
            }

            // Possible extra A move
            if (nextA[cur] != 0 && distA[cur] <= rem) {
                totalA += distA[cur];
                rem -= distA[cur];
                cur = nextA[cur];
            }

            return {totalA, totalB};
        };

        // Part 1: Find best starting city for X0
        int bestS = -1;
        long long bestA = 0, bestB = 0;
        for (int S = 1; S <= N; ++S) {
            pair<long long, long long> res = solve_query(S, X0);
            long long a = res.first;
            long long b = res.second;

            if (bestS == -1) {
                bestS = S; bestA = a; bestB = b;
            } else {
                bool better = false;
                if (b == 0 && bestB == 0) {
                    if (H[S] > H[bestS]) better = true;
                } else if (b == 0) {
                    better = false;
                } else if (bestB == 0) {
                    better = true;
                } else {
                    __int128 lhs = (__int128)a * bestB;
                    __int128 rhs = (__int128)bestA * b;
                    if (lhs < rhs) better = true;
                    else if (lhs == rhs) {
                        if (H[S] > H[bestS]) better = true;
                    }
                }
                if (better) {
                    bestS = S;
                    bestA = a;
                    bestB = b;
                }
            }
        }
        cout << bestS << "\n";

        // Part 2: Answer the M queries
        for (const auto& q : queries) {
            int s = q.first;
            long long x = q.second;
            pair<long long, long long> res = solve_query(s, x);
            cout << res.first << " " << res.second << "\n";
        }
    }
    return 0;
}
