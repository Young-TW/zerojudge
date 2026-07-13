#include <bits/stdc++.h>
using namespace std;

bool isPunct(char c) {
    return c == '，' || c == '。' || c == '？' || c == '！';
}

// split pattern by the literal substring "..."
vector<string> splitPattern(const string& pat) {
    vector<string> parts;
    size_t pos = 0;
    while (true) {
        size_t nxt = pat.find("...", pos);
        if (nxt == string::npos) {
            parts.push_back(pat.substr(pos));
            break;
        }
        parts.push_back(pat.substr(pos, nxt - pos));
        pos = nxt + 3;
    }
    return parts;
}

// 判斷句子是否符合模式
bool match(const string& pat, const string& s) {
    vector<string> parts = splitPattern(pat);
    size_t m = parts.size();
    size_t pos = 0;                     // 目前在 s 中已匹配到的位置
    bool first = true;

    for (size_t i = 0; i < m; ++i) {
        const string& p = parts[i];
        if (first) {                    // 處理第一段
            first = false;
            if (!p.empty()) {
                if (s.compare(pos, p.size(), p) != 0) return false;
                pos += p.size();
            }
            // 若 p 為空，代表模式以 "..." 開頭，什麼也不匹配，留給下一段處理
            continue;
        }

        // 之後每段前必須有至少一個非標點字元作為 "..."
        size_t startSearch = pos + 1;   // 必須至少留一個字元給 placeholder
        size_t found = string::npos;

        for (size_t j = startSearch; j + p.size() <= s.size(); ++j) {
            if (!p.empty() && s.compare(j, p.size(), p) != 0) continue;
            // p 為空的情況只會在最後一段（結尾 "...")，此時不需要找文字
            if (p.empty()) {
                // 直接視為找到位置
                found = j;
                break;
            }
            // 檢查 placeholder 區間是否全為非標點且至少長度 1
            bool ok = true;
            for (size_t k = pos; k < j; ++k) {
                if (isPunct(s[k])) { ok = false; break; }
            }
            if (ok) { found = j; break; }
        }

        if (found == string::npos) return false;
        pos = found + p.size();
    }

    // 判斷結尾是否有剩餘的 placeholder
    bool endsWithDots = (pat.size() >= 3 && pat.substr(pat.size() - 3) == "...");
    if (endsWithDots) {
        if (pos >= s.size()) return false;               // 必須還有至少一個字元
        for (size_t k = pos; k < s.size(); ++k) {
            if (isPunct(s[k])) return false;
        }
        return true;
    } else {
        return pos == s.size();                          // 必須完全匹配
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    if (!getline(cin, line)) return 0;
    while (line.size() == 0 && getline(cin, line));
    int T = stoi(line);

    for (int tc = 1; tc <= T; ++tc) {
        // 讀取題目前的空白行
        getline(cin, line); // 可能是空行

        // 讀取範例造句
        string pattern;
        getline(cin, pattern);
        // 讀取 n
        string nline;
        getline(cin, nline);
        while (nline.size() == 0 && getline(cin, nline));
        int n = stoi(nline);

        vector<string> sentences;
        for (int i = 0; i < n; ++i) {
            string s;
            getline(cin, s);
            sentences.push_back(s);
        }

        cout << "第" << tc << "題:" << "\n";
        for (const auto& s : sentences) {
            cout << (match(pattern, s) ? "對" : "錯") << "\n";
        }
        if (tc != T) cout << "\n";
    }
    return 0;
}
