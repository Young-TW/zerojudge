#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

/* transition of the DFA, -1 = illegal */
int trans(int state, char type) {
    // type: 'n', 'v', 'a'
    switch (state) {
        case 0:                     // before noun of NP
            if (type == 'a') return 0;
            if (type == 'n') return 1;
            return -1;
        case 1:                     // just finished NP
            if (type == 'a') return 2;
            if (type == 'v') return 3;
            return -1;
        case 2:                     // inside a* of VP
            if (type == 'a') return 2;
            if (type == 'v') return 3;
            return -1;
        case 3:                     // just finished VP
            if (type == 'a') return 0;
            if (type == 'n') return 1;
            return -1;
        default: return -1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    unordered_map<string, vector<char>> dict;
    dict.reserve(n * 2);
    string line;
    for (int i = 0; i < n; ++i) {
        cin >> line;
        char tp = line[0];               // 'n','v','a'
        string w = line.substr(2);       // after the dot
        dict[w].push_back(tp);
    }
    string article;
    cin >> article;                       // the whole line ending with '.'
    if (!article.empty() && article.back() == '.') article.pop_back();
    int L = (int)article.size();
    int maxLen = 0;
    for (auto &kv : dict)
        if ((int)kv.first.size() > maxLen) maxLen = kv.first.size();
    if (maxLen == 0) maxLen = 20;         // safety
    
    vector<int> dpSent(L + 1, INF), dpWord(L + 1, INF);
    dpSent[L] = dpWord[L] = 0;
    
    // auxiliary array reused for every start position
    vector<array<int,4>> best(L + 1);
    
    for (int start = L - 1; start >= 0; --start) {
        // initialise best
        for (int i = start; i <= L; ++i)
            best[i] = {INF, INF, INF, INF};
        best[start][0] = 0;
        
        for (int pos = start; pos < L; ++pos) {
            for (int st = 0; st < 4; ++st) {
                int cur = best[pos][st];
                if (cur == INF) continue;
                // try all possible words beginning at pos
                int maxTake = min(maxLen, L - pos);
                for (int len = 1; len <= maxTake; ++len) {
                    string sub = article.substr(pos, len);
                    auto it = dict.find(sub);
                    if (it == dict.end()) continue;
                    for (char tp : it->second) {
                        int ns = trans(st, tp);
                        if (ns == -1) continue;
                        int &ref = best[pos + len][ns];
                        if (cur + 1 < ref) ref = cur + 1;
                    }
                }
            }
        }
        
        int bestSent = INF, bestWords = INF;
        for (int end = start + 1; end <= L; ++end) {
            int w = INF;
            if (best[end][1] < w) w = best[end][1];
            if (best[end][3] < w) w = best[end][3];
            if (w == INF) continue;               // not a statement end
            int candSent = 1 + dpSent[end];
            int candWords = w + dpWord[end];
            if (candSent < bestSent ||
                (candSent == bestSent && candWords < bestWords)) {
                bestSent = candSent;
                bestWords = candWords;
            }
        }
        dpSent[start] = bestSent;
        dpWord[start] = bestWords;
    }
    
    cout << dpSent[0] << "\n" << dpWord[0] << "\n";
    return 0;
}
