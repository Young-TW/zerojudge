#include <bits/stdc++.h>
using namespace std;

/* ---------- SA‑IS (linear suffix array) ---------- */
static void getBuckets(const vector<int> &s, vector<int> &bkt,
                       int sigma, bool end) {
    fill(bkt.begin(), bkt.end(), 0);
    for (int v : s) ++bkt[v];
    int sum = 0;
    for (int i = 0; i < sigma; ++i) {
        sum += bkt[i];
        bkt[i] = end ? sum : sum - bkt[i];
    }
}

/* induced sorting of L-type suffixes */
static void induceL(const vector<int> &s, vector<int> &SA,
                    const vector<char> &t, vector<int> &bkt, int sigma) {
    getBuckets(s, bkt, sigma, false);               // bucket heads
    for (int i = 0; i < (int)SA.size(); ++i) {
        int j = SA[i] - 1;
        if (j >= 0 && !t[j]) {                      // L-type
            int c = s[j];
            SA[bkt[c]++] = j;
        }
    }
}

/* induced sorting of S-type suffixes */
static void induceS(const vector<int> &s, vector<int> &SA,
                    const vector<char> &t, vector<int> &bkt, int sigma) {
    getBuckets(s, bkt, sigma, true);                // bucket tails
    for (int i = (int)SA.size() - 1; i >= 0; --i) {
        int j = SA[i] - 1;
        if (j >= 0 && t[j]) {                       // S-type
            int c = s[j];
            SA[--bkt[c]] = j;
        }
    }
}

/* main SA‑IS routine */
static void SA_IS(const vector<int> &s, vector<int> &SA, int sigma) {
    int n = (int)s.size();
    SA.assign(n, -1);
    if (n == 0) return;
    if (n == 1) { SA[0] = 0; return; }

    /* 1. type classification */
    vector<char> t(n);               // 1 = S-type, 0 = L-type
    t[n - 1] = 1;                     // sentinel is S-type
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] < s[i + 1]) t[i] = 1;
        else if (s[i] > s[i + 1]) t[i] = 0;
        else t[i] = t[i + 1];
    }

    auto isLMS = [&](int i) -> bool {
        return i > 0 && t[i] && !t[i - 1];
    };

    /* 2. place LMS suffixes */
    vector<int> bkt(sigma);
    getBuckets(s, bkt, sigma, true);               // bucket tails
    for (int i = 0; i < n; ++i) SA[i] = -1;
    for (int i = 0; i < n; ++i) {
        if (isLMS(i)) {
            int c = s[i];
            SA[--bkt[c]] = i;
        }
    }

    /* 3. induce L and S */
    induceL(s, SA, t, bkt, sigma);
    induceS(s, SA, t, bkt, sigma);

    /* 4. compact LMS substrings */
    vector<int> lmsNames(n, -1);
    int nLMS = 0;
    for (int i = 0; i < n; ++i)
        if (isLMS(SA[i])) ++nLMS;

    vector<int> lmsPos; lmsPos.reserve(nLMS);
    for (int i = 0; i < n; ++i)
        if (isLMS(i)) lmsPos.push_back(i);

    int name = 0;
    int prev = -1;
    for (int idx = 0; idx < n; ++idx) {
        int pos = SA[idx];
        if (!isLMS(pos)) continue;
        bool diff = false;
        if (prev == -1) diff = true;
        else {
            for (int d = 0; ; ++d) {
                if (s[pos + d] != s[prev + d] ||
                    t[pos + d] != t[prev + d]) {
                    diff = true; break;
                }
                if (d > 0 && isLMS(pos + d)) break;
                if (d > 0 && isLMS(prev + d)) break;
            }
        }
        if (diff) ++name;
        lmsNames[pos] = name - 1;
        prev = pos;
    }

    vector<int> s1; s1.reserve(nLMS);
    for (int p : lmsPos) s1.push_back(lmsNames[p]);

    /* 5. recurse if needed */
    vector<int> SA1;
    if (name < nLMS) {
        SA_IS(s1, SA1, name);
    } else {
        SA1.resize(nLMS);
        for (int i = 0; i < nLMS; ++i) SA1[s1[i]] = i;
    }

    /* 6. final induced sorting using order of LMS */
    // clear SA
    fill(SA.begin(), SA.end(), -1);
    // place LMS in order given by SA1
    getBuckets(s, bkt, sigma, true);
    for (int i = nLMS - 1; i >= 0; --i) {
        int pos = lmsPos[SA1[i]];
        int c = s[pos];
        SA[--bkt[c]] = pos;
    }
    induceL(s, SA, t, bkt, sigma);
    induceS(s, SA, t, bkt, sigma);
}

/* ---------- wrapper ---------- */
static vector<int> buildSA(const vector<int> &s, int sigma) {
    vector<int> SA;
    SA_IS(s, SA, sigma);
    return SA;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        string s;
        int K;
        cin >> s >> K;
        int n = (int)s.size();
        string t = s + s;                     // length 2n
        int N = 2 * n + 1;                     // + sentinel
        vector<int> a(N);
        for (int i = 0; i < 2 * n; ++i)
            a[i] = (t[i] - 'a') + 1;           // shift, 1..26
        a[2 * n] = 0;                          // sentinel

        vector<int> SA = buildSA(a, 27);       // sigma = 27 (0..26)

        int cnt = 0, pos = -1;
        for (size_t i = 1; i < SA.size(); ++i) {   // SA[0] is sentinel
            if (SA[i] < n) {
                ++cnt;
                if (cnt == K) {
                    pos = SA[i];
                    break;
                }
            }
        }
        // pos is guaranteed to be found (1 ≤ K ≤ n)
        cout << t.substr(pos, n) << '\n';
    }
    return 0;
}
