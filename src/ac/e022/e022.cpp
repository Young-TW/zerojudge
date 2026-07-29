#include <bits/stdc++.h>
using namespace std;

// e022 - 橋
// concrete bridge (1) forms a matching (each city touches at most one concrete edge);
// movable bridge (0) are free edges.
// augmenting path: alternates movable,concrete,movable,...,concrete,movable
//   first & last edge movable; endpoints are free (no concrete edge).
// Find the longest such path length (#bridges). -1 if none.
// Branching happens only at movable steps (concrete partner is unique), and the
// problem guarantees the number of such paths is bounded (<= 5,000,000).

static int M, N;
static vector<int> movA, movB;              // CSR adjacency for movable edges
static vector<int> movAstart, movBstart;
static vector<int> matchA, matchB;          // concrete partner (1-indexed), 0 = none
static vector<char> visA, visB;
static int ans;

// arrived at city `cur` (side A if isA) via a movable bridge, current length = len (odd)
static void dfs(int cur, bool isA, int len) {
    if (isA) {
        int w = matchA[cur];                // concrete partner on side B
        if (w == 0) { if (len > ans) ans = len; return; }  // free endpoint
        if (visB[w]) return;                // cannot extend; cur not free -> not an endpoint
        visB[w] = 1;
        for (int i = movBstart[w]; i < movBstart[w + 1]; i++) {
            int x = movB[i];
            if (!visA[x]) { visA[x] = 1; dfs(x, true, len + 2); visA[x] = 0; }
        }
        visB[w] = 0;
    } else {
        int w = matchB[cur];                // concrete partner on side A
        if (w == 0) { if (len > ans) ans = len; return; }
        if (visA[w]) return;
        visA[w] = 1;
        for (int i = movAstart[w]; i < movAstart[w + 1]; i++) {
            int x = movA[i];
            if (!visB[x]) { visB[x] = 1; dfs(x, false, len + 2); visB[x] = 0; }
        }
        visA[w] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int K, L;
    string out;
    while (cin >> M >> N >> K >> L) {
        matchA.assign(M + 1, 0);
        matchB.assign(N + 1, 0);
        vector<int> ea, eb;                 // movable edges (a,b)
        ea.reserve(K); eb.reserve(K);
        vector<int> degA(M + 1, 0), degB(N + 1, 0);
        for (int i = 0; i < K; i++) {
            int a, b, t;
            cin >> a >> b >> t;
            if (t == 1) {                   // concrete: matching, keep first
                if (matchA[a] == 0) matchA[a] = b;
                if (matchB[b] == 0) matchB[b] = a;
            } else {
                ea.push_back(a); eb.push_back(b);
                degA[a]++; degB[b]++;
            }
        }
        movAstart.assign(M + 2, 0);
        movBstart.assign(N + 2, 0);
        for (int a = 1; a <= M; a++) movAstart[a + 1] = movAstart[a] + degA[a];
        for (int b = 1; b <= N; b++) movBstart[b + 1] = movBstart[b] + degB[b];
        movA.assign(ea.size(), 0);
        movB.assign(eb.size(), 0);
        {
            vector<int> pa(M + 1), pb(N + 1);
            for (int a = 1; a <= M; a++) pa[a] = movAstart[a];
            for (int b = 1; b <= N; b++) pb[b] = movBstart[b];
            for (size_t i = 0; i < ea.size(); i++) {
                movA[pa[ea[i]]++] = eb[i];
                movB[pb[eb[i]]++] = ea[i];
            }
        }
        visA.assign(M + 1, 0);
        visB.assign(N + 1, 0);
        ans = -1;

        for (int a = 1; a <= M; a++) {      // start from every free A-city
            if (matchA[a] != 0) continue;
            visA[a] = 1;
            for (int i = movAstart[a]; i < movAstart[a + 1]; i++) {
                int b = movA[i];
                if (!visB[b]) { visB[b] = 1; dfs(b, false, 1); visB[b] = 0; }
            }
            visA[a] = 0;
        }
        for (int b = 1; b <= N; b++) {      // start from every free B-city
            if (matchB[b] != 0) continue;
            visB[b] = 1;
            for (int i = movBstart[b]; i < movBstart[b + 1]; i++) {
                int a = movB[i];
                if (!visA[a]) { visA[a] = 1; dfs(a, true, 1); visA[a] = 0; }
            }
            visB[b] = 0;
        }

        out += to_string(ans);
        out += '\n';
    }
    cout << out;
    return 0;
}
