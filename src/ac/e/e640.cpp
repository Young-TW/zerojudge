#include <bits/stdc++.h>
using namespace std;

/* length of a UTF‑8 character, given its first byte */
int charLen(unsigned char c) {
    if (c < 0x80) return 1;
    if ((c >> 5) == 0x6) return 2;
    if ((c >> 4) == 0xE) return 3;
    if ((c >> 3) == 0x1E) return 4;
    return 1;                     // should never happen for valid input
}

/* build prefix array: pref[i] = number of non‑punctuation characters
   in s[0..i) (byte index) */
vector<int> buildPrefix(const string &s) {
    int N = (int)s.size();
    vector<int> pref(N + 1, 0);
    int cnt = 0;
    for (int i = 0; i < N; ) {
        int len = charLen(static_cast<unsigned char>(s[i]));
        for (int k = 1; k < len; ++k) pref[i + k] = cnt;   // inner bytes
        string ch = s.substr(i, len);
        bool isP = (ch == "，" || ch == "。" || ch == "？" || ch == "！");
        if (!isP) ++cnt;
        pref[i + len] = cnt;
        i += len;
    }
    return pref;
}

/* split pattern into tokens: type 0 = literal, type 1 = dots */
struct Token {
    int type;          // 0 literal, 1 dots
    string txt;        // only for literal
};

vector<Token> tokenize(const string &pat) {
    vector<Token> res;
    size_t i = 0, n = pat.size();
    while (i < n) {
        if (i + 3 <= n && pat.substr(i, 3) == "...") {
            res.push_back({1, ""});
            i += 3;
        } else {
            size_t j = i;
            while (j < n) {
                if (j + 3 <= n && pat.substr(j, 3) == "...") break;
                j += charLen(static_cast<unsigned char>(pat[j]));
            }
            res.push_back({0, pat.substr(i, j - i)});
            i = j;
        }
    }
    return res;
}

/* check one sentence against the token list */
bool matches(const vector<Token> &tokens, const string &sent) {
    int N = (int)sent.size();
    vector<int> pref = buildPrefix(sent);
    auto hasNonPunct = [&](int l, int r) -> bool {
        return pref[r] - pref[l] > 0;
    };

    vector<char> dp(N + 1, 0), ndp(N + 1, 0);
    dp[0] = 1;

    for (const Token &tk : tokens) {
        fill(ndp.begin(), ndp.end(), 0);
        if (tk.type == 0) {                     // literal
            int L = (int)tk.txt.size();
            for (int pos = 0; pos <= N; ++pos) if (dp[pos]) {
                if (pos + L <= N && sent.compare(pos, L, tk.txt) == 0)
                    ndp[pos + L] = 1;
            }
        } else {                                // dots
            for (int pos = 0; pos <= N; ++pos) if (dp[pos]) {
                for (int k = pos + 1; k <= N; ++k) {
                    if (hasNonPunct(pos, k)) ndp[k] = 1;
                }
            }
        }
        dp.swap(ndp);
    }
    /* Accept if the tokens are satisfied and only trailing punctuation is left
       (sentences always terminate with a punctuation mark, and punctuation "不算",
       so a literal-ending pattern such as 「是...的」 must still match 「...的。」). */
    for (int P = N; P >= 0; --P)
        if (dp[P] && pref[N] - pref[P] == 0) return true;
    return false;
}

/* strip trailing CR / spaces so CRLF test data is handled portably */
static inline void rstrip(string &s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' '))
        s.pop_back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    int T = 0;
    while (getline(cin, line)) {
        rstrip(line);
        if (!line.empty()) { T = stoi(line); break; }
    }

    for (int tc = 1; tc <= T; ++tc) {
        /* read pattern (skip blank lines) */
        while (getline(cin, line)) { rstrip(line); if (!line.empty()) break; }
        string pattern = line;

        /* read n */
        while (getline(cin, line)) { rstrip(line); if (!line.empty()) break; }
        int n = stoi(line);

        vector<string> sentences(n);
        for (int i = 0; i < n; ++i) { getline(cin, sentences[i]); rstrip(sentences[i]); }

        vector<Token> tokens = tokenize(pattern);

        cout << "第" << tc << "題:\n";
        for (const string &s : sentences) {
            cout << (matches(tokens, s) ? "對" : "錯") << "\n";
        }
        if (tc != T) cout << "\n";
    }
    return 0;
}
