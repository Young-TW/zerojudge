#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

vector<int> next_arr(3000005);

int kmp_find(const string& text, int start, int end, const string& pattern, int p_start, int p_len) {
    int m = p_len;
    if (m == 0) return start;
    if (end - start < m) return -1;
    
    next_arr[0] = -1;
    int j = -1;
    for (int i = 1; i < m; ++i) {
        while (j != -1 && pattern[p_start + i] != pattern[p_start + j + 1]) j = next_arr[j];
        if (pattern[p_start + i] == pattern[p_start + j + 1]) ++j;
        next_arr[i] = j;
    }
    
    j = -1;
    for (int i = start; i < end; ++i) {
        while (j != -1 && text[i] != pattern[p_start + j + 1]) j = next_arr[j];
        if (text[i] == pattern[p_start + j + 1]) ++j;
        if (j == m - 1) return i - m + 1;
    }
    return -1;
}

bool solve(const string& S, const string& T) {
    bool has_star = false;
    for (char c : S) {
        if (c == '*') {
            has_star = true;
            break;
        }
    }
    if (!has_star) {
        return S == T;
    }
    
    vector<pair<int, int>> patterns;
    int n = S.length();
    int i = 0;
    while (i < n) {
        if (S[i] == '*') {
            i++;
        } else {
            int j = i;
            while (j < n && S[j] != '*') j++;
            patterns.push_back({i, j - i});
            i = j;
        }
    }
    
    if (patterns.empty()) {
        return true;
    }
    
    int t_len = T.length();
    int start = 0;
    int end = t_len;
    
    if (S[0] != '*') {
        if (t_len < patterns[0].second) return false;
        if (T.compare(0, patterns[0].second, S, patterns[0].first, patterns[0].second) != 0) return false;
        start = patterns[0].second;
    }
    
    if (S[n - 1] != '*') {
        if (t_len - start < patterns.back().second) return false;
        if (T.compare(t_len - patterns.back().second, patterns.back().second, S, patterns.back().first, patterns.back().second) != 0) return false;
        end = t_len - patterns.back().second;
    }
    
    int p_start = (S[0] != '*') ? 1 : 0;
    int p_end = (S[n - 1] != '*') ? patterns.size() - 1 : patterns.size();
    
    for (int k = p_start; k < p_end; ++k) {
        int pos = kmp_find(T, start, end, S, patterns[k].first, patterns[k].second);
        if (pos == -1) return false;
        start = pos + patterns[k].second;
    }
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        while (N--) {
            string S, T;
            cin >> S >> T;
            if (solve(S, T)) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    return 0;
}
